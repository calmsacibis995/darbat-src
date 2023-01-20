/*
 * the floppyd daemon running on the local X-Server
 *
 * written by:
 *
 * Peter Schlaile
 *
 * udbz@rz.uni-karlsruhe.de
 *
 * Large parts of the network code shamelessly stolen from 
 * transproxy by John Saunders <john@nlc.net.au>
 *
 * Rewritten in C by Alain Knaff.  Apparently C++ is still not as
 * portable as C.  */

#define DEBUG 0

#include "config.h"

#ifdef USE_FLOPPYD

#define USE_FLOPPYD_BUFFERED_IO  1
#define FLOPPYD_DEFAULT_PORT     5703

#include "sysincludes.h"
#include "grp.h"
#include <X11/Xlib.h>
#include <X11/Xauth.h>

#include "floppyd_io.h"

#ifndef SIGCLD
#define SIGCLD SIGCHLD
#endif

/* For Linux 1.2.13 */
#ifndef SOMAXCONN
#define SOMAXCONN 5
#endif

extern int errno;

/*
   To compile:

   gcc -Wall floppyd.cpp -o floppyd -lX11

   floppyd

   Communication to the clients works the following way:

   Client sends his protocol-version. If the version between server and client
   differ: bail out.

   After that,we send our .Xauthority-file (a maximum of MAX_XAUTHORITY_LENGTH 
   Bytes long) to the server.

   The server then checks, if it already has a .Xauthority file. If so
   it is interpreted as LOCK-File for the floppy-device and the communication
   gets terminated.

   (What if we have 2 floppy devices? Well. Two floppy users with different
   home-directories should work nicely...)

   Now, the data is written to the .Xauthority file. Then we try to open
   a connection to the local X-Server. If this fails -> bail out.

   ***

   The data packets are built as follows:

   Base-packets: 1 Dword length, then data.
                 length is in Network-Byte order. (4 Bytes)

   Commands are: 1. Packet Opcode (length 1), 1. Data packet as parameter.

   Return: 1.Packet: 1. Dword: Bytes processed, 2. Dword: Error-Code

   ***

   TODO:
	  * Implement some IOCTL calls to format floppy disks or so...
	  * Read is somewhat dirty implemented. Tries multiple times to
	    read the expected bytes from the socket stream. Don't know
	    why this is necessary. Maybe the socket stream is nonblocking
	    or something IT SHOULD NOT BE!
	    
*/

typedef unsigned char Byte;
typedef unsigned long Dword;


#define MAX_XAUTHORITY_LENGTH    3000
#define MAX_DATA_REQUEST         3000000
#define BUFFERED_IO_SIZE         16348


void serve_client(int sock, char* device_name);



#define New(type) ((type*)(malloc(sizeof(type))))

#ifdef USE_FLOPPYD_BUFFERED_IO
typedef struct io_buffer {
	Byte out_buffer[BUFFERED_IO_SIZE];
	Byte in_buffer[BUFFERED_IO_SIZE];
	
	long in_valid;
	long in_start;
	long out_valid;
	
	int handle;
} *io_buffer;

io_buffer new_io_buffer (int _handle) {
	io_buffer buffer;

	buffer = New(struct io_buffer);

	buffer->handle = _handle;
	buffer->in_valid = buffer->in_start = 0;
	buffer->out_valid = 0;
	return buffer;
}


static void flush(io_buffer buffer) {
	if (buffer->out_valid) {
		write(buffer->handle, buffer->out_buffer, buffer->out_valid);
		buffer->out_valid = 0;
	}
}

void free_io_buffer(io_buffer buffer) {
	flush(buffer);
	free(buffer);
}


size_t buf_read (io_buffer buf, Byte* buffer, size_t nbytes) {
	size_t rval;
	
	if (nbytes <= buf->in_valid) {
		memcpy(buffer, buf->in_buffer+buf->in_start, nbytes);
		buf->in_valid -= nbytes;
		buf->in_start += nbytes;
		rval = nbytes;
	} else {
		if (buf->in_valid) 
			memcpy(buffer, buf->in_buffer+buf->in_start, 
				   buf->in_valid);
		nbytes -= buf->in_valid;
		buffer += buf->in_valid;
		if (nbytes > BUFFERED_IO_SIZE) {
			rval = read(buf->handle, buffer, nbytes);
			if (rval >= 0) {
				rval += buf->in_valid;
			}
			buf->in_valid = buf->in_start = 0;
		} else {
			rval = read(buf->handle, buf->in_buffer, 
						BUFFERED_IO_SIZE);
			if (rval >= 0) {
				if (rval < nbytes) {
					memcpy(buffer, buf->in_buffer, rval);
					rval += buf->in_valid;
					buf->in_valid = buf->in_start = 0;
				} else {
					size_t a;
					memcpy(buffer, buf->in_buffer, nbytes);
					buf->in_start = nbytes;
					a = buf->in_valid;
					buf->in_valid = rval-nbytes;
					rval = a + nbytes;
				}
			}
		}
	}
	return rval;
}

size_t buf_write(io_buffer buf, void* buffer, size_t nbytes) {
	if (buf->out_valid + nbytes > BUFFERED_IO_SIZE) {
		flush(buf);
		return write(buf->handle, buffer, nbytes);
	}
	memcpy(buf->out_buffer+buf->out_valid, buffer, nbytes);
	buf->out_valid += nbytes;
	return nbytes;
}



#else

typedef int io_buffer;

io_buffer new_io_buffer (int handle) {
	return handle;
}


size_t buf_read (io_buffer handle, Byte* buffer, size_t nbytes) {
	return (read(handle, buffer, nbytes));
}

size_t buf_write(io_buffer handle, void* buffer, size_t nbytes) {
	return (write(handle, buffer, nbytes));
}


void free_io_buffer(io_buffer buffer) { }


void flush(io_buffer buffer) { }

#endif

typedef struct Packet {
	Byte* data;
	Dword len;
	Dword alloc_size;
} *Packet;

Dword byte2dword(Byte* val) {
	Dword l;
	l = (val[0] << 24) + (val[1] << 16) + (val[2] << 8) + val[3];
	
#if DEBUG
	fprintf(stderr, "byte2dword(): %ld, 0x%x\n", l, (unsigned int) l);
#endif		
	
	return l;
}	

void dword2byte(Dword parm, Byte* rval) {
	rval[0] = (parm >> 24) & 0xff;
	rval[1] = (parm >> 16) & 0xff;
	rval[2] = (parm >> 8)  & 0xff;
	rval[3] = parm         & 0xff;
}

Dword read_dword(io_buffer fp) {
	Byte val[4];
	if (buf_read(fp, val, 4) < 4) {
		return 0xffffffff;
	}
	
	return byte2dword(val);
}

void write_dword(io_buffer fp, Dword parm) {
	Byte val[4];
	
	dword2byte(parm, val);
	
	buf_write(fp, val,4);
}


Packet newPacket() {
	Packet packet;

	packet = New(struct Packet);
	packet->data = NULL;
	packet->len = packet->alloc_size = 0;
	return packet;
}


void destroyPacket(Packet packet) {
	if(packet->data)
		free(packet->data);
	free(packet);
}

void kill_packet(Packet packet) {
	if(packet->data)
		free(packet->data);
	packet->data = NULL;
	packet->len = 0;
	packet->alloc_size = 0;
}

void make_new(Packet packet, unsigned long l) {
	if (l < packet->alloc_size) {
		packet->len = l;
		return;
	}
	kill_packet(packet);
	packet->len = packet->alloc_size = l;
	packet->data = malloc(l);
	memset(packet->data, 0, l);
}

char send_packet(Packet packet, io_buffer fp) {
	if (packet->data) {
		write_dword(fp, packet->len);
		buf_write(fp, packet->data, packet->len);
		flush(fp);
#if DEBUG
		fprintf(stderr, "send_packet(): Size: %li\n", packet->len);
#endif

#if DEBUG
		fprintf(stderr, "send_packet(): ");
		for (int i = 0; i < packet->len; i++) {
			fprintf(stderr, "%d ", packet->data[i]);
		}
		fprintf(stderr, "\n");
#endif		

	}
	return (packet->data != NULL);
}

char recv_packet(Packet packet, io_buffer fp, Dword maxlength) {
	int start;
	int l;
	Dword length = read_dword(fp);
#if DEBUG
	fprintf(stderr, "recv_packet(): Size: %li\n", length);
#endif
	if (length > maxlength || length == 0xffffffff ) {
		return 0;
	}
	make_new(packet, length);
	l = 0;
	for (start = 0; start < length; start += l) {
		l = buf_read(fp, packet->data+start, length-start);
		if (l == 0) {
			return 0;
		}
	}
	if (packet->len == 0) {
		return 0;
	}
#if DEBUG
	fprintf(stderr, "*** read: %li\n", packet->len);
#endif
	
#if DEBUG
	fprintf(stderr, "recv_packet(): ");
	for (i = 0; i < packet->len; i++) {
		fprintf(stderr, "%d ", packet->data[i]);
	}
	fprintf(stderr, "\n");
#endif		
	return 1;
}

void read_packet(Packet packet, int fd, int length) {
	make_new(packet, length);
	packet->len = read(fd, packet->data, packet->len);
}

int write_packet(Packet packet, int fd) {
	return (write(fd, packet->data, packet->len));
}

void put_dword(Packet packet, int index, Dword val) {
	dword2byte(val, packet->data+index);
}

Dword get_dword(Packet packet, int index) {
	return byte2dword(packet->data+index);
}	

char is_valid(Packet packet) {
	return (packet->data != NULL);
}

Dword get_length(Packet packet) {
	return packet->len;
}

int eat(char **ptr, int *len, unsigned char c) {
    /* remove length + size code + terminating 0 */
    if (*len < c + 3)
	return -1;
    (*ptr) += c + 2;
    (*len) -= c + 2;
    return 0;
}


char do_auth(io_buffer sock, int *version) 
{
	int fd;
	Display* displ;
	Packet proto_version = newPacket();
	Packet mit_cookie;
	char *ptr;
	int len;

	char template[4096];

	Packet reply = newPacket();

	make_new(reply, 4);

	if (!recv_packet(proto_version, sock, 4)) {
		put_dword(reply, 0, AUTH_PACKETOVERSIZE);
		send_packet(reply, sock);
		destroyPacket(reply);
		destroyPacket(proto_version);
		return 0;
	}

	*version = get_dword(proto_version, 0);
	if (*version > FLOPPYD_PROTOCOL_VERSION || 
	    *version < FLOPPYD_PROTOCOL_VERSION_OLD) {
		/* fail if client requests a newer version than us */
		put_dword(reply, 0, AUTH_WRONGVERSION);
		send_packet(reply, sock);
		destroyPacket(reply);
		destroyPacket(proto_version);
		return 0;
	}

	if(*version == FLOPPYD_PROTOCOL_VERSION_OLD) {
		put_dword(reply, 0, AUTH_SUCCESS);
	} else {
		make_new(reply, 12);
		put_dword(reply, 0, AUTH_SUCCESS);
		put_dword(reply, 4, FLOPPYD_PROTOCOL_VERSION);
		put_dword(reply, 8, FLOPPYD_CAP_EXPLICIT_OPEN);
	}
	send_packet(reply, sock);
	destroyPacket(proto_version);

	make_new(reply, 4);
	mit_cookie = newPacket();
	if (!recv_packet(mit_cookie, sock, MAX_XAUTHORITY_LENGTH)) {
		put_dword(reply, 0, AUTH_PACKETOVERSIZE);
		send_packet(reply, sock);
		destroyPacket(reply);
		destroyPacket(mit_cookie);
		return 0;
	}

	/* CPhipps 2000/02/11 - Do the open and test in one call, to avoid
	 * race condition. Open with safe permissions. */
	fd = open(XauFileName(), O_WRONLY | O_CREAT | O_EXCL, 0600);
	
	/* Locked! */
	if (fd == -1) {
		put_dword(reply, 0, AUTH_DEVLOCKED);
		send_packet(reply, sock);
		close(fd);
		destroyPacket(reply);
		destroyPacket(mit_cookie);
		return 0;
	}

	ptr = template;
	ptr[4095] = 0;
	*ptr++ = 1;
	*ptr++ = 0;
	*ptr++ = 0;
	gethostname(ptr+1, 4088);
	len = strlen(ptr+1);
	*ptr++ = len;
	ptr += len;
	*ptr++ = 0;
	*ptr++ = 1;
	*ptr++ = '0'; /* Display number */
	*ptr++ = '\0';

	write(fd, template, len+8);
	ptr = (char *)mit_cookie->data;
	len = mit_cookie->len;

	if (eat(&ptr,&len,1) ||    /* the "type"    */
	    eat(&ptr,&len,*ptr) || /* the hostname  */
	    eat(&ptr,&len,*ptr)) { /* the display number */
	    destroyPacket(mit_cookie);
	    unlink(XauFileName());
	    put_dword(reply, 0, AUTH_BADPACKET);
	    send_packet(reply, sock);
	    destroyPacket(reply);
	    return 0;
	}

	write(fd, ptr, len);
	close(fd);

	destroyPacket(mit_cookie);

	displ = XOpenDisplay(":0");
	if (!displ) {
		unlink(XauFileName());
		put_dword(reply, 0, AUTH_AUTHFAILED);
		send_packet(reply, sock);
		destroyPacket(reply);
		return 0;
	}
	XCloseDisplay(displ);

	put_dword(reply, 0, AUTH_SUCCESS);
	send_packet(reply, sock);
	destroyPacket(reply);
	return 1;
}

/*
 * Return the port number, in network order, of the specified service.
 */
static short getportnum(char *portnum)
{
	char			*digits = portnum;
	struct servent	*serv;
	short			port;

	for (port = 0; isdigit(*digits); ++digits)
		{
			port = (port * 10) + (*digits - '0');
		}

	if ((*digits != '\0') || (port <= 0))
		{
			if ((serv = getservbyname(portnum, "tcp")) != NULL)
				{
					port = ntohs(serv->s_port);
				}
			else
				{
					port = -1;
				}
			endservent();
		}

#if DEBUG
	fprintf(stderr, "Port lookup %s -> %hd\n", portnum, port);
#endif

	return (port);
}

/*
 * Return the IP address of the specified host.
 */
static IPaddr_t getipaddress(char *ipaddr)
{
	struct hostent	*host;
	IPaddr_t ip;

	if (((ip = inet_addr(ipaddr)) == INADDR_NONE)
	    &&
		(strcmp(ipaddr, "255.255.255.255") != 0))
		{
			if ((host = gethostbyname(ipaddr)) != NULL)
				{
					memcpy(&ip, host->h_addr, sizeof(ip));
				}
			endhostent();
		}

#if DEBUG
	fprintf(stderr, "IP lookup %s -> 0x%08lx\n", ipaddr, ip);
#endif

	return (ip);
}

/*
 * Find the userid of the specified user.
 */
static uid_t getuserid(char *user)
{
	struct passwd	*pw;
	uid_t			uid;

	if ((pw = getpwnam(user)) != NULL)
		{
			uid = pw->pw_uid;
		}
	else if (*user == '#')
		{
			uid = (uid_t)atoi(&user[1]);
		}
	else
		{
			uid = 65535;
		}

#if DEBUG
	fprintf(stderr, "User lookup %s -> %d\n", user, uid);
#endif

	endpwent();

	return (uid);
}

/*
 * Find the groupid of the specified user.
 */
static uid_t getgroupid(uid_t uid)
{
	struct passwd	*pw;
	gid_t			gid;

	if ((pw = getpwuid(uid)) != NULL)
		{
			gid = pw->pw_gid;
		}
	else
		{
			gid = 65535;
		}

#if DEBUG
	fprintf(stderr, "Group lookup %d -> %d\n", uid, gid);
#endif

	endpwent();

	return (gid);
}

/*
 * Bind to the specified ip and port.
 */
static int bind_to_port(IPaddr_t bind_ip, short bind_port)
{
	struct sockaddr_in	addr;
	int					sock;

	/*
	 * Allocate a socket.
	 */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			perror("socket()");
			exit(1);
		}

	/*
	 * Set the SO_REUSEADDR option for debugging.
	 */
	{
	 	int	on = 1;
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, 
				   (char *)&on, sizeof(on));
	}

	/*
	 * Set the address to listen to.
	 */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(bind_port);
	addr.sin_addr.s_addr = bind_ip;

	/*
	 * Bind our socket to the above address.
	 */
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			perror("bind()");
			exit(1);
		}

	/*
	 * Establish a large listen backlog.
	 */
	if (listen(sock, SOMAXCONN) < 0)
		{
			perror("listen()");
			exit(1);
		}

	return (sock);
}

static int sockethandle_now = -1;
  
/*
 * Catch alarm signals and exit.
 */
static void alarm_signal(int a)
{
	if (sockethandle_now != -1) {
		close(sockethandle_now);
		sockethandle_now = -1;
		unlink(XauFileName());
	}
	exit(1);
}


/*
 * This is the main loop when running as a server.
 */
static void server_main_loop(int sock, char* device_name)
{
	struct sockaddr_in	addr;
	unsigned int		len;

	/*
	 * Ignore dead servers so no zombies should be left hanging.
	 */
	signal(SIGCLD, SIG_IGN);

	for (;;) {
		int					new_sock;
		/*
		 * Accept an incoming connection.
		 */
		len = sizeof(addr);
		while ((new_sock = accept(sock, (struct sockaddr *)&addr, &len)) < 0){}
		
		/*
		 * Create a new process to handle the connection.
		 */
#if DEBUG == 0
		switch (fork()) {
			case -1:
				/*
				 * Under load conditions just ignore new connections.
				 */
				break;
				
			case 0:
				/*
				 * Start the proxy work in the new socket.
				 */
#endif
				serve_client(new_sock,device_name);
				exit(0);
#if DEBUG == 0
		}
#endif
		/*
		 * Close the socket as the child does the handling.
		 */
		close(new_sock);
		new_sock = -1;
	}
}

/*
 * Print some basic help information.
 */
static void usage(char *prog, char *opt)
{
	if (opt)
		{
			fprintf(stderr, "%s: %s\n", prog, opt);
		}
	fprintf(stderr, "usage: %s [-s port [-r user] [-b ipaddr]] devicename [Names of local host]\n", 
			prog);
	fprintf(stderr, "    -d          Run as a server (default port 5703 + DISPLAY)\n");
	fprintf(stderr, "    -s port     Run as a server bound to the specified port.\n");
	fprintf(stderr, "    -r user     Run as the specified user in server mode.\n");
	fprintf(stderr, "    -b ipaddr   Bind to the specified ipaddr in server mode.\n");
	fprintf(stderr, "    -l          Do not attempt to connect to localhost:0 to validate connection\n");
	exit(1);
}


char *makeDisplayName(char *base, int port)
{
	char *result;
	int displaynr = (port - FLOPPYD_DEFAULT_PORT) % 10;
	int len=strlen(base);

	result = malloc(len+5);
	strcpy(result, base);
	result[len++] = ':';
	result[len++] = '0' + displaynr;
	result[len++] = '.';
	result[len++] = '0';
	result[len]='\0';
	return result;
}

int main (int argc, char** argv) 
{
	int sockfd = 0;
	int			arg;
	int			run_as_server = 0;
	IPaddr_t		bind_ip = INADDR_ANY;
	short			bind_port = FLOPPYD_DEFAULT_PORT;
	uid_t			run_uid = 65535;
	gid_t			run_gid = 65535;
	char*			username = strdup("nobody");
	int			sock;
	int			port_is_supplied = 0;
	int			no_local = 0;

	char *server_hostname=NULL;
	char* device_name = NULL; 
	char *authFile=0;
	char *p, *q;
	const char *authKey = "XAUTHORITY";


	/*
	 * Parse the command line arguments.
	 */
	while ((arg = getopt(argc, argv, "lds:r:b:")) != EOF)
		{
			switch (arg)
				{
					case 'd':
						run_as_server = 1;
						break;
					case 's':
						run_as_server = 1;
						port_is_supplied = 1;
						bind_port = getportnum(optarg);
						break;

					case 'r':
						free(username); username = strdup(optarg);
						run_uid = getuserid(optarg);
						run_gid = getgroupid(run_uid);
						break;

					case 'b':
						run_as_server = 1;
						bind_ip = getipaddress(optarg);
						server_hostname=optarg;
						break;

					case 'l':
						no_local = 1;
						break;

					case '?':
						usage(argv[0], NULL);
						break;
				}
		}

	if(optind < argc) {
		device_name = argv[optind++];
	}

	if(optind < argc) {
		fprintf(stderr, "Ignoring extra argument %s\n", argv[optind]);
	}

	if(!run_as_server) {
		struct sockaddr_in	addr;
		unsigned int len = sizeof(addr);
		
		/* try to find out port that we are connected to */
		if(getsockname(0, (struct sockaddr*) &addr, &len) >= 0 && 
		   len == sizeof(addr)) {
			port_is_supplied = 1;
			bind_port = ntohs(addr.sin_port);
			server_hostname = strdup(inet_ntoa(addr.sin_addr));
		}
	}

	umask(0077);

	/*
	 * Test to make sure required args were provided and are valid.
	 */
	if (run_as_server && (bind_ip == INADDR_NONE)) {
		usage(argv[0], "The server ipaddr is invalid.");
	}
	if (run_as_server && (bind_port == -1))	{
		usage(argv[0], "No server port was specified (or it was invalid).");
	}
	
	if(!device_name) {
		device_name = "/dev/fd0";
	}

	if (!device_name || !*device_name) {
		usage(argv[0], "No device name specified.");
	}

	authFile = malloc(strlen(authKey) + 1+ strlen(device_name)*2+7);
	strcpy(authFile, authKey);
	strcat(authFile, "=/tmp/");
	for(p=device_name, q = strlen(authKey) + authFile+6; *p; p++) {
		switch(*p) {
			case '/':
				*q++ = '-';
				*q++ = '+';
				break;
			case '-':
				*q++ = '-';
				*q++ = '-';
				break;
			default:
				*q++ = *p;
		}
	}
	*q = *p;
	putenv(authFile);

	/*
	 * See if we should run as a server.
	 */
	if (run_as_server)
		{
			/*
			 * Start by binding to the port, the child inherits this socket.
			 */
			sock = bind_to_port(bind_ip, bind_port);

			/*
			 * Start a server process. When DEBUG is defined, just run
			 * in the foreground.
			 */
#if DEBUG
			switch (0)
#else
				switch (fork())
#endif
					{
						case -1:
							perror("fork()");
							exit(1);

						case 0:
							/*
							 * Ignore some signals.
							 */
							signal(SIGHUP, SIG_IGN);
#if DEBUG
							signal(SIGINT, SIG_IGN);
#endif
							signal(SIGQUIT, SIG_IGN);
							signal(SIGTSTP, SIG_IGN);
							signal(SIGCONT, SIG_IGN);
							signal(SIGPIPE, alarm_signal);
							/*signal(SIGALRM, alarm_signal);*/

							/*
							 * Drop back to an untrusted user.
							 */
							setgid(run_gid);
							initgroups(username, -1);
							setuid(run_uid);

							/*
							 * Start a new session and group.
							 */
							setsid();
#ifdef SETPGRP_VOID
							setpgrp();
#else
							setpgrp(0,0);
#endif
#if DEBUG
							close(2);
							open("/dev/null", O_WRONLY);
#endif
							/*
							 * Handle the server main loop.
							 */
							server_main_loop(sock, device_name);

							/*
							 * Should never exit.
							 */
							exit(1);
					}

			/*
			 * Parent exits at this stage.
			 */
			exit(0);
		}

	signal(SIGHUP, alarm_signal);
#if DEBUG == 0
	signal(SIGINT, alarm_signal);
#endif
	signal(SIGQUIT, alarm_signal);
	signal(SIGTERM, alarm_signal);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	signal(SIGPIPE, alarm_signal);
	/*signal(SIGALRM, alarm_signal);*/

#if DEBUG == 0
	close(2);
	open("/dev/null", O_WRONLY);
#endif
	/* Starting from inetd */

	serve_client(sockfd, device_name);
	return 0;
}

void send_reply(int rval, io_buffer sock, int len) {
	Packet reply = newPacket();

	make_new(reply, 8);
	put_dword(reply, 0, len);
	if (rval == -1) {
		put_dword(reply, 4, 0);
	} else {
		put_dword(reply, 4, errno);
	}
	send_packet(reply, sock);
	destroyPacket(reply);
}

void cleanup(int x) {
	unlink(XauFileName());
	exit(-1);
}

void serve_client(int sockhandle, char* device_name) {
	Packet opcode;
	Packet parm;

	int readOnly;
	int devFd;
	io_buffer sock;
	int stopLoop;
	int version;
	int needSendReply=0;
	int rval=0;
	
	/*
	 * Set the keepalive socket option to on.
	 */
	{
		int		on = 1;
		setsockopt(sockhandle, SOL_SOCKET, 
				   SO_KEEPALIVE, (char *)&on, sizeof(on));
	}

	sock = new_io_buffer(sockhandle);
	
	/*
	 * Allow 60 seconds for any activity.
	 */
	alarm(60);
	
	version = 0;
	if (!do_auth(sock, &version)) {
		free_io_buffer(sock);
		return;
	}
	alarm(0);


	signal(SIGTERM, cleanup);
	signal(SIGALRM, cleanup);



	sockethandle_now = sockhandle;


	opcode = newPacket();
	parm = newPacket();

	devFd = -1;
	readOnly = 1;

	stopLoop = 0;
	if(version == FLOPPYD_PROTOCOL_VERSION_OLD) {
				/* old protocol */
		readOnly = 0;
		devFd = open(device_name, O_RDWR);
		
		if (devFd < 0) {
			readOnly = 1;
			devFd = open(device_name, 
				     O_RDONLY);
		}
		if(devFd < 0) {
			send_reply(0, sock, devFd);
			stopLoop = 1;
		}
	}


	while(!stopLoop) {
		int rval = 0;
		/*
		 * Allow 60 seconds for any activity.
		 */
		/*alarm(60);*/

		if (!recv_packet(opcode, sock, 1)) {
		    fprintf(stderr, "No Recv packet\n");
			break;
		}
/*		if(opcode->data[0] != OP_CLOSE)*/
		    recv_packet(parm, sock, MAX_DATA_REQUEST);

		switch(opcode->data[0]) {
			case OP_OPRO:
				devFd = open(device_name, O_RDONLY);
#if DEBUG
				fprintf(stderr, "Device opened\n");
#endif
				send_reply(0, sock, devFd);
				readOnly = 1;
				break;
			case OP_OPRW:
				devFd = open(device_name, O_RDWR);
				send_reply(0, sock, devFd);
				readOnly = 0;
				break;
			case OP_READ:
#if DEBUG
				fprintf(stderr, "READ:\n");
#endif
				read_packet(parm, devFd, get_dword(parm, 0));
				send_reply(devFd, sock, get_length(parm));
				send_packet(parm, sock);
				
				break;
			case OP_WRITE:
#if DEBUG
				fprintf(stderr, "WRITE:\n");
#endif
				if(readOnly) {
					errno = -EROFS;
					rval = -1;
				} else {
					rval = write_packet(parm, devFd);
				}
				send_reply(devFd, sock, rval);
				break;
			case OP_SEEK:
#if DEBUG
				fprintf(stderr, "SEEK:\n");
#endif

				lseek(devFd, 
				      get_dword(parm, 0), get_dword(parm, 4));
				send_reply(devFd, 
					   sock, 
					   lseek(devFd, 0, SEEK_CUR));
				break;
			case OP_FLUSH:
#if DEBUG
				fprintf(stderr, "FLUSH:\n");
#endif
				fsync(devFd);
				send_reply(devFd, sock, 0);
				break;
			case OP_CLOSE:
#if DEBUG
				fprintf(stderr, "CLOSE:\n");
#endif

				close(devFd);
				needSendReply = 1;
				rval = devFd;
				devFd = -1;
				stopLoop = 1;
				break;
			case OP_IOCTL:
				/* Unimplemented for now... */
				break;
			default:
#if DEBUG
				fprintf(stderr, "Invalid Opcode!\n");
#endif
				errno = EINVAL;
				send_reply(devFd, sock, -1);
				break;
		}
		kill_packet(parm);
		alarm(0);
	}

	

#if DEBUG
	fprintf(stderr, "Closing down...\n");
#endif

	if (devFd >= 0) {
		close(devFd);
		devFd = -1;
	}

	free_io_buffer(sock);

	/* remove "Lock"-File  */
	unlink(XauFileName());

	if(needSendReply)
	    send_reply(rval, sock, 0);
	destroyPacket(opcode);
	destroyPacket(parm);
}

#else
#include <stdio.h>

int main(int argc, char **argv) 
{
	puts("Floppyd support not included!");
	return -1;
}
	
#endif

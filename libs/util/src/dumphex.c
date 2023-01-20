#include <stdio.h>
#include <ctype.h>
#include <util/dumphex.h>

/* Dump a buffer in hex format. Very useful for debugging */
void
dumphex(char *buffer, size_t len)
{
	int i;
	char ascii_buf[17];

	ascii_buf[16] = '\0';

	printf("BUFFER: %p (%zd)\n", buffer, len);
	for (i=0; i < len; i++) {
		if ((i % 16) == 0) {
			printf("%04x: ", i);
		}
		printf("%02x ", (unsigned char) buffer[i]);

		if (isprint(buffer[i])) {
			ascii_buf[i%16] = buffer[i];
		} else {
			ascii_buf[i%16] = '.';
		}

		if ((i+1) % 16 == 0) {
			printf("<%s>", ascii_buf);
			printf("\n");
		} else if ((i+1) % 4 == 0) {
			printf(" ");
		}
	}
	printf("\n");

}

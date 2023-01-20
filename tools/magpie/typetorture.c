/* C type torture! */

/* It's not really torture, more of a gentle poking */

typedef unsigned int unsignedint;
typedef struct {
	int a;
	int b;
} boringstruct;

typedef struct {
	int a;
} boring2;

typedef union {
	int a;
	int b;
} boringtypedef;

typedef union {
	int a;
	struct {
		char a1;
		char a2;
	} ax;
} boring3;

typedef union {
	unsigned long a;
	struct {
		int a1: 8;
		int a2: 8;
		int a3: 10;
	} ax;
} bitfields1;

struct somestruct
{
	int h;
} somestruct_inst;

struct _IO_FILE
{
	unsigned int a;
	int b;
	unsigned long long c;
};

typedef struct _IO_FILE NEW_FILE_TYPE;

/* Incomplete type allowed in typedefs */
typedef struct UNDEFINED_TYPE UNDEFINED_TYPE_ALIAS;


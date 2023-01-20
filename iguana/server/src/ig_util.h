#ifndef _IG_UTIL_H_
#define _IG_UTIL_H_

#include <util/ansi.h>

#define BASE_LOG2_PAGESIZE 12
#define BASE_PAGESIZE (1 << BASE_LOG2_PAGESIZE)
#define PAGEMASK  (BASE_PAGESIZE - 1)
#define PAGEOFFSETMASK (~PAGEMASK)
 
#define page_round_up(address) ((address + PAGEMASK) & PAGEOFFSETMASK)
#define round_up(address, size) ((((address) + (size-1)) & (~(size-1))))
#define page_round_down(address) ((address) & PAGEOFFSETMASK)
#define round_down(address, size) (((address)) & (~(size-1)))

#define ASSERT_PTR(ptr) assert(((void*) (ptr)) > ((void*) BASE_PAGESIZE))

#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)

#define MARK printf(ANSI_RED "%s:%d %s: " ANSI_NORMAL, __FILE__, __LINE__, __func__)

#define DEBUG
#ifdef DEBUG
 #define ERROR_PRINT MARK; printf 
 #define DEBUG_PRINT printf
#else
 #define ERROR_PRINT(...) 
 #define DEBUG_PRINT(...)
#endif

#define ERROR_PRINT_L4 ERROR_PRINT("Error: %lx\n", L4_ErrorCode())

/*#define VERBOSE*/
#ifdef VERBOSE
#define INIT_PRINT MARK; printf
#define FPAGE_PRINT MARK; printf
#define MEMSECTION_PRINT MARK; printf
#define QUOTA_PRINT MARK; printf
#define SECURITY_PRINT MARK; printf
#else
#define INIT_PRINT(...)
#define FPAGE_PRINT(...)
#define MEMSECTION_PRINT(...)
#define QUOTA_PRINT(...)
#define SECURITY_PRINT(...)
#endif

#endif /* _IG_UTIL_H_ */

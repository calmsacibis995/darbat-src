/*********************************************************************
 *                
 * Copyright (C) 2002-2004,  Karlsruhe University
 *                
 * File path:     debug.h
 * Description:   Debug functions
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: debug.h,v 1.30 2004/03/18 13:18:22 ud3 Exp $
 *                
 ********************************************************************/
#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __ELF__
#define SEC_KDEBUG ".kdebug"
#elif defined(__APPLE_CC__)
#define SEG_KDEBUG "__KDEBUG"
#define SEC_KDEBUG "__kdebug"
#else
#error "unknown compiler"
#endif


/*
 * Escape codes for controlling text color, brightness, etc.
 */

#define TXT_CLRSCREEN		"\e[2J"
#define TXT_NORMAL		"\e[0m"
#define TXT_BRIGHT		"\e[1m"
#define TXT_REVERSED		"\e[7m"
#define TXT_FG_BLACK		"\e[30m"
#define TXT_FG_RED		"\e[31m"
#define TXT_FG_GREEN		"\e[32m"
#define TXT_FG_YELLOW		"\e[33m"
#define TXT_FG_BLUE		"\e[34m"
#define TXT_FG_MAGENTA		"\e[35m"
#define TXT_FG_CYAN		"\e[36m"
#define TXT_FG_WHITE		"\e[37m"
#define TXT_BG_BLACK		"\e[40m"
#define TXT_BG_RED		"\e[41m"
#define TXT_BG_GREEN		"\e[42m"
#define TXT_BG_YELLOW		"\e[43m"
#define TXT_BG_BLUE		"\e[44m"
#define TXT_BG_MAGENTA		"\e[45m"
#define TXT_BG_CYAN		"\e[46m"
#define TXT_BG_WHITE		"\e[47m"

/*
 * Assert Levels
 */
#define	REGRESSION	4
#define	DEBUG		3
#define	NORMAL		2
#define	PRODUCTION	1
#define	ALWAYS		0


#if defined(CONFIG_DEBUG)

#include INC_ARCH(debug.h)

#ifdef __ELF__
void init_console (void) SECTION (".init");
#elif defined(__APPLE_CC__)
void init_console (void) SECTION ("__INIT", "__init");
#else
#error "unknown compiler"
#endif
extern "C" int printf (const char * format, ...);

# define UNIMPLEMENTED()				\
do {							\
    printf ("\nNot implemented: %s\n%s, line %d\n",	\
	    __PRETTY_FUNCTION__, __FILE__, __LINE__);	\
    for (;;)						\
	enter_kdebug ("unimplemented");			\
} while (false)

#if !defined(CONFIG_KDB_NO_ASSERTS)
# define ASSERT(level, x)						\
do {									\
    if (EXPECT_FALSE(! (x)) && (level <= CONFIG_ASSERT_LEVEL)) {	\
	printf ("Assertion "#x" failed in file %s, line %d (fn=%p)\n",	\
		__FILE__, __LINE__, __builtin_return_address(0));	\
	enter_kdebug ("assert");					\
    }									\
} while(false)

# define WARNING(fmt, args...)						\
do {									\
    printf ("WARNING: %s, line %d (fn=%p)\n===> " fmt,			\
	    __FILE__, __LINE__, __builtin_return_address(0) , ## args);	\
    enter_kdebug ("warning");						\
} while (false)

# define TRACEF(f, x...)					\
do {								\
    printf ("%s:%d: " f, __FUNCTION__, __LINE__ ,##x);		\
} while(false)
# define TRACE(x...)	printf(x)

# else /* defined(CONFIG_KDB_NO_ASSERTS) */

#define ASSERT(level, x)
#define TRACE(x...)
#define TRACEF(x...)
#define WARNING(fmt...)

# endif

# define TID(x)		((x).get_raw())

/* From kdb/generic/entry.cc */
void kdebug_entry (void *);


#else /* !CONFIG_DEBUG */

/*
 * Define all functions as empty.
 */

# define init_console()
# define printf(fmt, args...)	do { } while (false)
# define enter_kdebug(x)	do { } while (true)
# define UNIMPLEMENTED()	do { } while (true)
# define ASSERT(level, x)	do { } while (false)
# define WARNING(fmt, args...)	do { } while (false)
# define TRACE(x...)		do { } while (false)
# define TRACEF(x...)		do { } while (false)
# define spin_forever(x...)	do { } while (true)
# define spin(x...)		do { } while (false)

#endif /* CONFIG_DEBUG */



#define panic(x...)					\
do {							\
    printf ("PANIC in %s, %s, line %d:\n===> ",		\
	    __PRETTY_FUNCTION__, __FILE__, __LINE__);	\
    printf (x);						\
    for (;;)						\
	enter_kdebug ("panic");				\
} while (false)

/*
 * Verbose initialization.
 */

#if defined(CONFIG_VERBOSE_INIT)
# define TRACE_INIT(x...)	printf (x)
#else
# define TRACE_INIT(x...)
#endif

/*
 * kdebug break-in
 */
# if defined(CONFIG_KDB_BREAKIN)
void kdebug_check_breakin();
# else
#  define kdebug_check_breakin()
# endif /* CONFIG_DEBUG_BREAKIN */

/*
 * Trace buffer
 */
#if defined(CONFIG_TRACEBUFFER)
void init_tracebuffer();
# include <tracebuffer.h>
# if defined(CONFIG_KDB_NO_ASSERTS)
#  undef TBUF_RECORD
#  define TBUF_RECORD(_a...)
#  undef TBUF_RECORD_EVENT
#  define TBUF_RECORD_EVENT(_a)
#  undef TBUF_CLEAR_BUFFER
#  define TBUF_CLEAR_BUFFER()
# endif /* defined(CONFIG_KDB_NO_ASSERTS) */
#else /* !CONFIG_TRACEBUFFER */
# define init_tracebuffer()
# define TBUF_RECORD(_a...)
# define TBUF_RECORD_EVENT(_a)
# define TBUF_CLEAR_BUFFER()
#endif /* !CONFIG_TRACEBUFFER */


#endif /* !__DEBUG_H__ */

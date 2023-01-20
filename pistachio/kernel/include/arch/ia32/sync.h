/*********************************************************************
 *                
 * Copyright (C) 2002-2003,  Karlsruhe University
 *                
 * File path:     arch/ia32/sync.h
 * Description:   synchronization primitives for IA32
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
 * $Id: sync.h,v 1.7 2003/09/25 17:18:48 ud3 Exp $
 *                
 ********************************************************************/
#ifndef __ARCH__IA32__SYNC_H__
#define __ARCH__IA32__SYNC_H__

#ifndef CONFIG_SMP
# error should not be included!
#endif

class spinlock_t 
{
public:
    void init(word_t val = 0)
	{ this->_lock= val; }
    void lock();
    void unlock();
    bool is_locked() { return _lock; }
    
public: // to allow initializers
    volatile word_t _lock;
};

#define DECLARE_SPINLOCK(name) extern spinlock_t name;
#define DEFINE_SPINLOCK(name) spinlock_t name = {_lock: 0}

#if 0
/* VU: 
 * @todo: use asm function to implement contention case
 */
INLINE void spinlock_t::lock()
{
    word_t dummy;
    __asm__ __volatile__ (
        "1:                     \n"
	"xchg	(%1), %2	\n"
	"orl	$0, %2		\n"
	"jnz	2f		\n"
        ".section .spinlock     \n"
        "2:testb $1, (%1)       \n"
        "jne    2b              \n"
        "jmp    1b              \n"
        ".previous              \n"
        : "=r"(dummy)
        : "r"(&this->_lock), "r"(1));
}
#else
INLINE void spinlock_t::lock()
{
    word_t dummy;
    __asm__ __volatile__ (
        "1:                     \n"
	"xchg	%1, %2		\n"
	"orl	$0, %2		\n"
	"jnz	2f		\n"
#ifdef __ELF__
        ".section .spinlock     \n"
#endif
        "2:testb $1, %1		\n"
        "jne    2b              \n"
        "jmp    1b              \n"
#ifdef __ELF__
        ".previous              \n"
#endif
        : "=r"(dummy)
        : "m"(this->_lock), "r"(1));
}
#endif

INLINE void spinlock_t::unlock()
{
    this->_lock = 0;
}

#endif /* !__ARCH__IA32__SYNC_H__ */

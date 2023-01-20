/*********************************************************************
 *                
 * Copyright (C) 2001, 2002, 2003,  Karlsruhe University
 *                
 * File path:     l4/ipc.h
 * Description:   L4 IPC operations
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
 * $Id: ipc.h,v 1.12 2003/09/24 19:06:21 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __L4__IPC_H__
#define __L4__IPC_H__

#include <l4/types.h>
#include __L4_INC_ARCH(syscalls.h)
#include <l4/message.h>
#include <l4/thread.h>

/*
 * in Xnu_glue
 *
 * XXX FIXME!!
 */
void L4_Sleep(L4_Time_t	t);

/*
 * Support functions
 */

L4_INLINE L4_Bool_t L4_IpcSucceeded (L4_MsgTag_t t)
{
    return (t.X.flags & 0x8) == 0;
}

L4_INLINE L4_Bool_t L4_IpcFailed (L4_MsgTag_t t)
{
    return (t.X.flags & 0x8) != 0;
}

L4_INLINE L4_Bool_t L4_IpcPropagated (L4_MsgTag_t t)
{
    return (t.X.flags & 0x1) != 0;
}

L4_INLINE L4_Bool_t L4_IpcRedirected (L4_MsgTag_t t)
{
    return (t.X.flags & 0x2) != 0;
}

L4_INLINE L4_Bool_t L4_IpcXcpu (L4_MsgTag_t t)
{
    return (t.X.flags & 0x4) != 0;
}

L4_INLINE void L4_Set_Propagation (L4_MsgTag_t * t)
{
    t->X.flags |= 1;
}

L4_INLINE void L4_Set_Notify(L4_MsgTag_t * t)
{
    t->X.flags |= 2;
}

L4_INLINE void L4_Set_ReceiveBlock(L4_MsgTag_t * t)
{
    t->X.flags |= 4;
}

L4_INLINE void L4_Set_SendBlock(L4_MsgTag_t * t)
{
    t->X.flags |= 8;
}

L4_INLINE void L4_Clear_ReceiveBlock(L4_MsgTag_t * t)
{
    t->X.flags &= (~4u);
}

L4_INLINE void L4_Clear_SendBlock(L4_MsgTag_t * t)
{
    t->X.flags &= (~8u);
}


/*
 * Derived functions
 */

/*
 * These are the functions derived from the two IPC syscalls.  For
 * normal C, function overloading is not supported.  Functions with
 * unique names (i.e., with the suffix inside <> appended) have
 * therefore been provided.
 *
 *   L4_Call			(to)
 *   L4_Send			(to)
 *   L4_Send_Nonblocking	(to)
 *   L4_Reply			(to)
 *   L4_Receive			(from)
 *   L4_Receive_Nonblocking	(from)
 *   L4_Wait			(&from)
 *   L4_ReplyWait		(to, &from)
 *   L4_ReplyWait_Nonblocking	(to, &from)
 *   L4_Lcall			(to)
 *   L4_Lreply_Wait		(to, &from)
 *   L4_WaitForever		()
 *
 */

L4_INLINE L4_MsgTag_t L4_Call (L4_ThreadId_t to)
{
    L4_ThreadId_t dummy;
    L4_MsgTag_t tag = L4_MsgTag ();

    L4_Set_SendBlock(&tag);
    L4_Set_ReceiveBlock(&tag);

    return L4_Ipc (to, to, tag, &dummy);
}

L4_INLINE L4_MsgTag_t L4_Send_Nonblocking(L4_ThreadId_t to)
{
    L4_MsgTag_t tag = L4_MsgTag ();
    L4_Clear_SendBlock(&tag);

    return L4_Ipc (to, L4_nilthread, tag, (L4_ThreadId_t *) 0);
}

#if defined(__l4_cplusplus)
L4_INLINE L4_MsgTag_t L4_Send (L4_ThreadId_t to, L4_MsgTag_t tag)
{
    return L4_Ipc (to, L4_nilthread, tag, (L4_ThreadId_t *) 0);
}
#endif

L4_INLINE L4_MsgTag_t L4_Send (L4_ThreadId_t to)
{
    L4_MsgTag_t tag = L4_MsgTag ();
    L4_Set_SendBlock(&tag);

    return L4_Ipc (to, L4_nilthread, tag, (L4_ThreadId_t *) 0);
}

L4_INLINE L4_MsgTag_t L4_Reply (L4_ThreadId_t to)
{
    return L4_Send_Nonblocking(to);
}

L4_INLINE L4_MsgTag_t L4_Receive_Nonblocking (L4_ThreadId_t from)
{
    L4_ThreadId_t dummy;
    L4_MsgTag_t tag = L4_Niltag;

    L4_Clear_ReceiveBlock(&tag);

    return L4_Ipc (L4_nilthread, from, tag, &dummy);
}

#if defined(__l4_cplusplus)
L4_INLINE L4_MsgTag_t L4_Receive (L4_ThreadId_t from, L4_MsgTag_t tag)
{
    L4_ThreadId_t dummy;
    return L4_Ipc (L4_nilthread, from, tag, &dummy);
}
#endif

L4_INLINE L4_MsgTag_t L4_Receive (L4_ThreadId_t from)
{
    L4_ThreadId_t dummy;
    L4_MsgTag_t tag = L4_Niltag;

    L4_Set_ReceiveBlock(&tag);

    return L4_Ipc (L4_nilthread, from, tag, &dummy);
}

#if defined(__l4_cplusplus)
L4_INLINE L4_MsgTag_t L4_Wait (L4_Time_t RcvTimeout, L4_MsgTag_t tag, L4_ThreadId_t * from)
{
    return L4_Ipc (L4_nilthread, L4_anythread, tag, from);
}
#endif

L4_INLINE L4_MsgTag_t L4_Wait (L4_ThreadId_t * from)
{
    L4_MsgTag_t tag = L4_Niltag;
    L4_Set_ReceiveBlock(&tag);

    return L4_Ipc (L4_nilthread, L4_anythread, tag, from);
}

L4_INLINE L4_MsgTag_t L4_ReplyWait_Nonblocking (L4_ThreadId_t to,
					    L4_ThreadId_t * from)
{
    L4_MsgTag_t tag = L4_MsgTag ();
    L4_Clear_SendBlock(&tag);
    L4_Clear_ReceiveBlock(&tag);

    return L4_Ipc (to, L4_anythread, tag, from);
}

#if defined(__l4_cplusplus)
L4_INLINE L4_MsgTag_t L4_ReplyWait (L4_ThreadId_t to,
				    L4_MsgTag_t tag,
				    L4_ThreadId_t * from)
{
    return L4_Ipc (to, L4_anythread, tag, from);
}
#endif


L4_INLINE L4_MsgTag_t L4_ReplyWait (L4_ThreadId_t to, L4_ThreadId_t * from)
{
    L4_MsgTag_t tag = L4_MsgTag ();
    L4_Clear_SendBlock(&tag);
    L4_Set_ReceiveBlock(&tag);

    return L4_Ipc (to, L4_anythread, tag, from);
}

L4_INLINE L4_MsgTag_t L4_Lcall (L4_ThreadId_t to)
{
    L4_ThreadId_t dummy;
    L4_MsgTag_t tag = L4_MsgTag ();

    L4_Set_SendBlock(&tag);
    L4_Set_ReceiveBlock(&tag);

    return L4_Lipc (to, to, tag, &dummy);
}

L4_INLINE L4_MsgTag_t L4_LreplyWait (L4_ThreadId_t to, L4_ThreadId_t * from)
{
    L4_MsgTag_t tag = L4_MsgTag ();
    L4_Clear_SendBlock(&tag);
    L4_Set_ReceiveBlock(&tag);

    return L4_Lipc (to, L4_anythread, tag, from);
}

L4_INLINE L4_MsgTag_t L4_WaitForever(void)
{
    L4_ThreadId_t dummy;
    L4_MsgTag_t tag = L4_Niltag;

    L4_Set_ReceiveBlock(&tag);

    return L4_Ipc (L4_nilthread, L4_MyGlobalId (), tag, &dummy);
}

#endif /* !__L4__IPC_H__ */

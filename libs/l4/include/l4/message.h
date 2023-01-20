/*********************************************************************
 *                
 * Copyright (C) 2001, 2002, 2003-2004,  Karlsruhe University
 *                
 * File path:     l4/message.h
 * Description:   Message construction functions
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
 * $Id: message.h,v 1.30 2004/03/12 13:41:21 skoglund Exp $
 *                
 ********************************************************************/
#ifndef __L4__MESSAGE_H__
#define __L4__MESSAGE_H__

#include <l4/types.h>
#include __L4_INC_ARCH(vregs.h)

#if defined(L4_64BIT)
# define __PLUS32	+ 32
#else
# define __PLUS32
#endif




/*
 * Message tag
 */

typedef union {
    L4_Word_t	raw;
    struct {
	L4_BITFIELD4( L4_Word_t,
	    u:6,
	    t:6,
	    flags:4,
	    label:16 __PLUS32
	);
    } X;
} L4_MsgTag_t;

#define L4_Niltag		((L4_MsgTag_t) { raw : 0UL })
#define L4_Notifytag		((L4_MsgTag_t) { raw : (1UL << 13) })
#define L4_Waittag		((L4_MsgTag_t) { raw : (1UL << 14) })

L4_INLINE L4_Bool_t L4_IsMsgTagEqual (const L4_MsgTag_t l,
				      const L4_MsgTag_t r)
{
    return l.raw == r.raw;
}

L4_INLINE L4_Bool_t L4_IsMsgTagNotEqual (const L4_MsgTag_t l,
					 const L4_MsgTag_t r)
{
    return l.raw != r.raw;
}

#if defined(__l4_cplusplus)
static inline L4_Bool_t operator == (const L4_MsgTag_t & l,
				     const L4_MsgTag_t & r)
{
    return l.raw == r.raw;
}

static inline L4_Bool_t operator != (const L4_MsgTag_t & l,
				     const L4_MsgTag_t & r)
{
    return l.raw != r.raw;
}
#endif /* __l4_cplusplus */

L4_INLINE L4_MsgTag_t L4_MsgTagAddLabel (const L4_MsgTag_t t, int label)
{
    L4_MsgTag_t tag = t;
    tag.X.label = label;
    return tag;
}

L4_INLINE L4_MsgTag_t L4_MsgTagAddLabelTo (L4_MsgTag_t * t, int label)
{
    t->X.label = label;
    return *t;
}

#if defined(__l4_cplusplus)
static inline L4_MsgTag_t operator + (const L4_MsgTag_t & t, int label)
{
    return L4_MsgTagAddLabel (t, label);
}

static inline L4_MsgTag_t operator += (L4_MsgTag_t & t, int label)
{
    return L4_MsgTagAddLabelTo (&t, label);
}
#endif /* __l4_cplusplus */

L4_INLINE L4_Word_t L4_Label (L4_MsgTag_t t)
{
    return t.X.label;
}

L4_INLINE L4_Word_t L4_UntypedWords (L4_MsgTag_t t)
{
    return t.X.u;
}

L4_INLINE L4_Word_t L4_TypedWords (L4_MsgTag_t t)
{
    return t.X.t;
}

L4_INLINE void L4_Set_Label (L4_MsgTag_t * t, L4_Word_t label)
{
    t->X.label = label;
}

L4_INLINE L4_MsgTag_t L4_MsgTag (void)
{
    L4_MsgTag_t msgtag;
    L4_StoreMR (0, &msgtag.raw);
    return msgtag;
}

L4_INLINE void L4_Set_MsgTag (L4_MsgTag_t t)
{
    L4_LoadMR (0, t.raw);
}



/*
 * Map item
 */

typedef union {
    L4_Word_t	raw[2];
    struct {
	struct {
	    L4_BITFIELD3( L4_Word_t,
		__type:4,
		__zeros:6,
		snd_base:22 __PLUS32
	    );
	};
	L4_Fpage_t	snd_fpage;
    } X;
} L4_MapItem_t;	


L4_INLINE L4_MapItem_t L4_MapItem (L4_Fpage_t f, L4_Word_t SndBase)
{
    L4_MapItem_t item;
    item.raw[0] = 0;
    item.X.__type = 0x08;
    item.X.snd_base = SndBase >> 10;
    item.X.snd_fpage.raw = f.raw;
    return item;
}

L4_INLINE L4_Bool_t L4_IsMapItem (L4_MapItem_t m)
{
    return m.X.__type == 0x08;
}

L4_INLINE L4_Fpage_t L4_MapItemSndFpage (L4_MapItem_t m)
{
    return m.X.snd_fpage;
}

L4_INLINE L4_Word_t L4_MapItemSndBase (L4_MapItem_t m)
{
    return m.X.snd_base << 10;
}

#if defined(__l4_cplusplus)
L4_INLINE L4_Bool_t L4_MapItem (L4_MapItem_t m)
{
    return L4_IsMapItem (m);
}

L4_INLINE L4_Fpage_t L4_SndFpage (L4_MapItem_t m)
{
    return L4_MapItemSndFpage (m);
}

L4_INLINE L4_Word_t L4_SndBase (L4_MapItem_t m)
{
    return L4_MapItemSndBase (m);
}
#endif /* __l4_cplusplus */





/*
 * Grant item
 */

typedef union {
    L4_Word_t	raw[2];
    struct {
	struct {
	    L4_BITFIELD3( L4_Word_t,
		__type:4,
		__zeros:6,
		snd_base:22 __PLUS32
	    );
	};
	L4_Fpage_t	snd_fpage;
    } X;
} L4_GrantItem_t;	

L4_INLINE L4_Bool_t L4_IsGrantItem (L4_GrantItem_t g)
{
    return g.X.__type == 0x0A;
}

L4_INLINE L4_GrantItem_t L4_GrantItem (L4_Fpage_t f, L4_Word_t SndBase)
{
    L4_GrantItem_t item;
    item.raw[0] = 0;
    item.X.__type = 0x0A;
    item.X.snd_base = SndBase >> 10;
    item.X.snd_fpage.raw = f.raw;
    return item;
}

L4_INLINE L4_Fpage_t L4_GrantItemSndFpage (L4_GrantItem_t m)
{
    return m.X.snd_fpage;
}

L4_INLINE L4_Word_t L4_GrantItemSndBase (L4_GrantItem_t m)
{
    return m.X.snd_base << 10;
}

#if defined(__l4_cplusplus)
L4_INLINE L4_Bool_t L4_GrantItem (L4_GrantItem_t g)
{
    return L4_IsGrantItem (g);
}

L4_INLINE L4_Fpage_t L4_SndFpage (L4_GrantItem_t m)
{
    return L4_GrantItemSndFpage (m);
}

L4_INLINE L4_Word_t L4_SndBase (L4_GrantItem_t m)
{
    return L4_GrantItemSndBase (m);
}
#endif /* __l4_cplusplus */





/*
 * Message objects
 */

typedef union {
    L4_Word_t raw[__L4_NUM_MRS];
    L4_Word_t msg[__L4_NUM_MRS];
    L4_MsgTag_t tag;
} L4_Msg_t;

L4_INLINE void L4_MsgPut (L4_Msg_t * msg, L4_Word_t label,
			  int u, L4_Word_t * Untyped,
			  int t, void * Items)
{
    int i;

    for (i = 0; i < u; i++)
	msg->msg[i+1] = Untyped[i];
    for (i = 0; i < t; i++)
	msg->msg[i+u+1] = ((L4_Word_t *) Items)[i];

    msg->tag.X.label = label;
    msg->tag.X.flags = 0;
    msg->tag.X.u = u;
    msg->tag.X.t = t;
}

L4_INLINE void L4_MsgGet (const L4_Msg_t * msg, L4_Word_t * Untyped,
			  void * Items)
{
    int i, u, t;
    u = msg->tag.X.u;
    t = msg->tag.X.t;

    for (i = 0; i < u; i++)
	Untyped[i] = msg->msg[i + 1];
    for (i = 0; i < t; i++)
	((L4_Word_t *) Items)[i] = msg->msg[i + 1 + u];
}

L4_INLINE L4_MsgTag_t L4_MsgMsgTag (const L4_Msg_t * msg)
{
    return msg->tag;
}

L4_INLINE void L4_Set_MsgMsgTag (L4_Msg_t * msg, L4_MsgTag_t t)
{
    msg->tag = t;
}

L4_INLINE L4_Word_t L4_MsgLabel (const L4_Msg_t * msg)
{
    return msg->tag.X.label;
}

L4_INLINE void L4_Set_MsgLabel (L4_Msg_t * msg, L4_Word_t label)
{
    msg->tag.X.label = label;
}

L4_INLINE void L4_MsgLoad (L4_Msg_t * msg)
{
    L4_LoadMRs (0, msg->tag.X.u + msg->tag.X.t + 1, &msg->msg[0]);
}

L4_INLINE void L4_MsgStore (L4_MsgTag_t t, L4_Msg_t * msg)
{
    L4_StoreMRs (1, t.X.u + t.X.t, &msg->msg[1]);
    msg->tag = t;
}

L4_INLINE void L4_MsgClear (L4_Msg_t * msg)
{
    msg->msg[0] = 0;
}

L4_INLINE void L4_MsgAppendWord (L4_Msg_t * msg, L4_Word_t w)
{
    if (msg->tag.X.t)
    {
	L4_Word_t i = 1 + msg->tag.X.u + msg->tag.X.t;
	for (; i > (L4_Word_t)(msg->tag.X.u + 1); i--)
	    msg->msg[i] = msg->msg[i-1];
    }
    msg->msg[++msg->tag.X.u] = w;
}

L4_INLINE void L4_MsgAppendMapItem (L4_Msg_t * msg, L4_MapItem_t m)
{
    msg->msg[msg->tag.X.u + msg->tag.X.t + 1] = m.raw[0];
    msg->msg[msg->tag.X.u + msg->tag.X.t + 2] = m.raw[1];
    msg->tag.X.t += 2;
}

L4_INLINE void L4_MsgAppendGrantItem (L4_Msg_t * msg, L4_GrantItem_t g)
{
    msg->msg[msg->tag.X.u + msg->tag.X.t + 1] = g.raw[0];
    msg->msg[msg->tag.X.u + msg->tag.X.t + 2] = g.raw[1];
    msg->tag.X.t += 2;
}

L4_INLINE void L4_MsgPutWord (L4_Msg_t * msg, L4_Word_t u, L4_Word_t w)
{
    msg->msg[u+1] = w;
}

L4_INLINE void L4_MsgPutMapItem (L4_Msg_t * msg, L4_Word_t t, L4_MapItem_t m)
{
    msg->msg[msg->tag.X.u + t + 1] = m.raw[0];
    msg->msg[msg->tag.X.u + t + 2] = m.raw[1];
}

L4_INLINE void L4_MsgPutGrantItem (L4_Msg_t * msg, L4_Word_t t,
				   L4_GrantItem_t g)
{
    msg->msg[msg->tag.X.u + t + 1] = g.raw[0];
    msg->msg[msg->tag.X.u + t + 2] = g.raw[1];
}

L4_INLINE L4_Word_t L4_MsgWord (L4_Msg_t * msg, L4_Word_t u)
{
    return msg->msg[u + 1];
}

L4_INLINE void L4_MsgGetWord (L4_Msg_t * msg, L4_Word_t u, L4_Word_t * w)
{
    *w = msg->msg[u + 1];
}

L4_INLINE L4_Word_t L4_MsgGetMapItem (L4_Msg_t * msg, L4_Word_t t,
				      L4_MapItem_t * m)
{
    m->raw[0] = msg->msg[msg->tag.X.u + t + 1];
    m->raw[1] = msg->msg[msg->tag.X.u + t + 2];
    return 2;
}

L4_INLINE L4_Word_t L4_MsgGetGrantItem (L4_Msg_t * msg, L4_Word_t t,
					L4_GrantItem_t * g)
{
    g->raw[0] = msg->msg[msg->tag.X.u + t + 1];
    g->raw[1] = msg->msg[msg->tag.X.u + t + 2];
    return 2;
}

#if defined(__l4_cplusplus)
L4_INLINE void L4_Put (L4_Msg_t * msg, L4_Word_t label,
		       int u, L4_Word_t * Untyped,
		       int t, void * Items)
{
    L4_MsgPut (msg, label, u, Untyped, t, Items);
}

L4_INLINE void L4_Get (const L4_Msg_t * msg, L4_Word_t * Untyped, void * Items)
{
    L4_MsgGet (msg, Untyped, Items);
}

L4_INLINE L4_MsgTag_t L4_MsgTag (const L4_Msg_t * msg)
{
    return L4_MsgMsgTag (msg);
}

L4_INLINE void L4_Set_MsgTag (L4_Msg_t * msg, L4_MsgTag_t t)
{
    L4_Set_MsgMsgTag (msg, t);
}

L4_INLINE L4_Word_t L4_Label (const L4_Msg_t * msg)
{
    return L4_MsgLabel (msg);
}

L4_INLINE void L4_Set_Label (L4_Msg_t * msg, L4_Word_t label)
{
    L4_Set_MsgLabel (msg, label);
}

L4_INLINE void L4_Load (L4_Msg_t * msg)
{
    L4_MsgLoad (msg);
}

L4_INLINE void L4_Store (L4_MsgTag_t t, L4_Msg_t * msg)
{
    L4_MsgStore (t, msg);
}

L4_INLINE void L4_Clear (L4_Msg_t * msg)
{
    L4_MsgClear (msg);
}

L4_INLINE void L4_Append (L4_Msg_t * msg, L4_Word_t w)
{
    L4_MsgAppendWord (msg, w);
}

L4_INLINE void L4_Append (L4_Msg_t * msg, int w)
{
    L4_MsgAppendWord (msg, (L4_Word_t) w);
}

L4_INLINE void L4_Append (L4_Msg_t * msg, L4_MapItem_t m)
{
    L4_MsgAppendMapItem (msg, m);
}

L4_INLINE void L4_Append (L4_Msg_t * msg, L4_GrantItem_t g)
{
    L4_MsgAppendGrantItem (msg, g);
}

L4_INLINE void L4_Put (L4_Msg_t * msg, L4_Word_t u, L4_Word_t w)
{
    L4_MsgPutWord (msg, u, w);
}

L4_INLINE void L4_Put (L4_Msg_t * msg, L4_Word_t t, L4_MapItem_t m)
{
    L4_MsgPutMapItem (msg, t, m);
}

L4_INLINE void L4_Put (L4_Msg_t * msg, L4_Word_t t, L4_GrantItem_t g)
{
    L4_MsgPutGrantItem (msg, t, g);
}

L4_INLINE L4_Word_t L4_Get (L4_Msg_t * msg, L4_Word_t u)
{
    return L4_MsgWord (msg, u);
}

L4_INLINE void L4_Get (L4_Msg_t * msg, L4_Word_t u, L4_Word_t * w)
{
    L4_MsgGetWord (msg, u, w);
}

L4_INLINE L4_Word_t L4_Get (L4_Msg_t * msg, L4_Word_t t, L4_MapItem_t * m)
{
    return L4_MsgGetMapItem (msg, t, m);
}

L4_INLINE L4_Word_t L4_Get (L4_Msg_t * msg, L4_Word_t t, L4_GrantItem_t * g)
{
    return L4_MsgGetGrantItem (msg, t, g);
}
#endif /* __l4_cplusplus */




/*
 * Acceptors and mesage buffers.
 */

typedef union {
    L4_Word_t	raw;
    struct {
	L4_BITFIELD4( L4_Word_t,
	    __zero1:1,
	    a:1,
	    __zero2:2,
	    RcvWindow:28 __PLUS32
	);
    } X;
} L4_Acceptor_t;

#define L4_UntypedWordsAcceptor		((L4_Acceptor_t) { raw: 0 })
#define L4_AsynchItemsAcceptor		((L4_Acceptor_t) { raw: 2 })

L4_INLINE L4_Acceptor_t L4_MapGrantItems (L4_Fpage_t RcvWindow)
{
    L4_Acceptor_t a;
    a.raw = RcvWindow.raw;
    return a;
}

L4_INLINE L4_Acceptor_t L4_AddAcceptor (const L4_Acceptor_t l,
					const L4_Acceptor_t r)
{
    L4_Acceptor_t a;
    a.raw = 0;
    a.X.a = (l.X.a | r.X.a);
    a.X.RcvWindow = (r.X.RcvWindow != 0) ? r.X.RcvWindow : l.X.RcvWindow;
    return a;
}

L4_INLINE L4_Acceptor_t L4_AddAcceptorTo (L4_Acceptor_t l,
					  const L4_Acceptor_t r)
{
    l.X.a = (l.X.a | r.X.a);
    if (r.X.RcvWindow != 0)
	l.X.RcvWindow = r.X.RcvWindow;
    return l;
}

L4_INLINE L4_Acceptor_t L4_RemoveAcceptor (const L4_Acceptor_t l,
					   const L4_Acceptor_t r)
{
    L4_Acceptor_t a = l;
    if (r.X.a)
	a.X.a = 0;
    if (r.X.RcvWindow != 0)
	a.X.RcvWindow = 0;
    return a;
}

L4_INLINE L4_Acceptor_t L4_RemoveAcceptorFrom (L4_Acceptor_t l,
					       const L4_Acceptor_t r)
{
    if (r.X.a)
	l.X.a = 0;
    if (r.X.RcvWindow != 0)
	l.X.RcvWindow = 0;
    return l;
}

#if defined(__l4_cplusplus)
static inline L4_Acceptor_t operator + (const L4_Acceptor_t & l,
					const L4_Acceptor_t & r)
{
    return L4_AddAcceptor (l, r);
}

static inline L4_Acceptor_t operator += (L4_Acceptor_t & l,
					 const L4_Acceptor_t & r)
{
    return L4_AddAcceptorTo (l, r);
}

static inline L4_Acceptor_t operator - (const L4_Acceptor_t & l,
					const L4_Acceptor_t & r)
{
    return L4_RemoveAcceptor (l, r);
}

static inline L4_Acceptor_t operator -= (L4_Acceptor_t & l,
					 const L4_Acceptor_t & r)
{
    return L4_RemoveAcceptorFrom (l, r);
}
#endif /* __l4_cplusplus */

L4_INLINE L4_Bool_t L4_HasMapGrantItems (const L4_Acceptor_t a)
{
    return (a.raw & ~0x0fUL) != 0;
}

#if defined(__l4_cplusplus)
L4_INLINE L4_Bool_t L4_MapGrantItems (const L4_Acceptor_t a)
{
    return L4_HasMapGrantItems (a);
}
#endif /* __l4_cplusplus */

L4_INLINE L4_Fpage_t L4_RcvWindow (const L4_Acceptor_t a)
{
    L4_Fpage_t fp;
    fp.raw = a.raw;
    fp.X.rwx = 0;
    return fp;
}

L4_INLINE void L4_Accept (const L4_Acceptor_t a)
{
    __L4_TCR_Set_Acceptor( a.raw );
}

L4_INLINE L4_Acceptor_t L4_Accepted (void)
{
    L4_Acceptor_t a;
    a.raw = __L4_TCR_Acceptor();
    return a;
}

L4_INLINE void L4_Set_NotifyMask (const L4_Word_t mask)
{
    __L4_TCR_Set_NotifyMask( mask );
}

L4_INLINE L4_Word_t L4_Get_NotifyMask (void)
{
    L4_Word_t mask;
    mask = __L4_TCR_NotifyMask();
    return mask;
}

L4_INLINE void L4_Set_NotifyBits (const L4_Word_t mask)
{
    __L4_TCR_Set_NotifyBits( mask );
}

L4_INLINE L4_Word_t L4_Get_NotifyBits (void)
{
    L4_Word_t mask;
    mask = __L4_TCR_NotifyBits();
    return mask;
}

#undef __PLUS32

#endif /* !__L4__MESSAGE_H__ */

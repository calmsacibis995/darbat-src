/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Portions copyright Apple Computer, Inc.
 * Portions copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-06-20.
 *
 * @NICTA_MODIFICATIONS_END@
 */
/*
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
#include <igcompat/compat.h>
/*	$FreeBSD: src/sys/netinet6/esp_rijndael.c,v 1.1.2.1 2001/07/03 11:01:50 ume Exp $	*/
/*	$KAME: esp_rijndael.c,v 1.4 2001/03/02 05:53:05 itojun Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/socket.h>
#include <sys/queue.h>
#include <sys/syslog.h>
#include <sys/mbuf.h>

#include <kern/locks.h>

#include <net/if.h>
#include <net/route.h>

#include <netinet6/ipsec.h>
#include <netinet6/esp.h>
#include <netinet6/esp_rijndael.h>

#include <crypto/aes/aes.h>

#include <net/net_osdep.h>
#include <netkey/key.h>

#define AES_BLOCKLEN 16

extern lck_mtx_t *sadb_mutex;

int
esp_aes_schedlen(algo)
	const struct esp_algorithm *algo;
{

	return sizeof(aes_ctx);
}

int
esp_aes_schedule(algo, sav)
	const struct esp_algorithm *algo;
	struct secasvar *sav;
{
	aes_ctx *ctx = (aes_ctx*)sav->sched;
	
	gen_tabs();
	aes_decrypt_key(_KEYBUF(sav->key_enc), _KEYLEN(sav->key_enc), &ctx->decrypt);
	aes_encrypt_key(_KEYBUF(sav->key_enc), _KEYLEN(sav->key_enc), &ctx->encrypt);
	
	return 0;
}


/* The following 2 functions decrypt or encrypt the contents of
 * the mbuf chain passed in keeping the IP and ESP header's in place,
 * along with the IV.
 * The code attempts to call the crypto code with the largest chunk
 * of data it can based on the amount of source data in
 * the current source mbuf and the space remaining in the current
 * destination mbuf.  The crypto code requires data to be a multiples
 * of 16 bytes.  A separate buffer is used when a 16 byte block spans
 * mbufs.
 *
 * m = mbuf chain
 * off = offset to ESP header
 * 
 * local vars for source:
 * soff = offset from beginning of the chain to the head of the
 *			current mbuf.
 * scut = last mbuf that contains headers to be retained
 * scutoff = offset to end of the headers in scut
 * s = the current mbuf
 * sn = current offset to data in s (next source data to process)
 *
 * local vars for dest:
 * d0 = head of chain
 * d = current mbuf
 * dn = current offset in d (next location to store result)
 */
 
 
int
esp_cbc_decrypt_aes(m, off, sav, algo, ivlen)
	struct mbuf *m;
	size_t off;
	struct secasvar *sav;
	const struct esp_algorithm *algo;
	int ivlen;
{
	struct mbuf *s;
	struct mbuf *d, *d0, *dp;
	int soff;	/* offset from the head of chain, to head of this mbuf */
	int sn, dn;	/* offset from the head of the mbuf, to meat */
	size_t ivoff, bodyoff;
	u_int8_t iv[AES_BLOCKLEN], *dptr;
	u_int8_t sbuf[AES_BLOCKLEN], *sp;
	struct mbuf *scut;
	int scutoff;
	int	i, len;

		
	if (ivlen != AES_BLOCKLEN) {
		ipseclog((LOG_ERR, "esp_cbc_decrypt %s: "
		    "unsupported ivlen %d\n", algo->name, ivlen));
		m_freem(m);
		return EINVAL;
	}

	if (sav->flags & SADB_X_EXT_OLD) {
		/* RFC 1827 */
		ivoff = off + sizeof(struct esp);
		bodyoff = off + sizeof(struct esp) + ivlen;
	} else {
		ivoff = off + sizeof(struct newesp);
		bodyoff = off + sizeof(struct newesp) + ivlen;
	}

	if (m->m_pkthdr.len < bodyoff) {
		ipseclog((LOG_ERR, "esp_cbc_decrypt %s: bad len %d/%lu\n",
		    algo->name, m->m_pkthdr.len, (unsigned long)bodyoff));
		m_freem(m);
		return EINVAL;
	}
	if ((m->m_pkthdr.len - bodyoff) % AES_BLOCKLEN) {
		ipseclog((LOG_ERR, "esp_cbc_decrypt %s: "
		    "payload length must be multiple of %d\n",
		    algo->name, AES_BLOCKLEN));
		m_freem(m);
		return EINVAL;
	}

	/* grab iv */
	m_copydata(m, ivoff, ivlen, iv);

	lck_mtx_unlock(sadb_mutex);
	s = m;
	soff = sn = dn = 0;
	d = d0 = dp = NULL;
	sp = dptr = NULL;
	
	/* skip header/IV offset */
	while (soff < bodyoff) {
		if (soff + s->m_len > bodyoff) {
			sn = bodyoff - soff;
			break;
		}

		soff += s->m_len;
		s = s->m_next;
	}
	scut = s;
	scutoff = sn;

	/* skip over empty mbuf */
	while (s && s->m_len == 0)
		s = s->m_next;
	
	while (soff < m->m_pkthdr.len) {
		/* source */
		if (sn + AES_BLOCKLEN <= s->m_len) {
			/* body is continuous */
			sp = mtod(s, u_int8_t *) + sn;
			len = s->m_len - sn;
			len -= len % AES_BLOCKLEN;	// full blocks only
		} else {
			/* body is non-continuous */
			m_copydata(s, sn, AES_BLOCKLEN, sbuf);
			sp = sbuf;
			len = AES_BLOCKLEN;			// 1 block only in sbuf
		}

		/* destination */
		if (!d || dn + AES_BLOCKLEN > d->m_len) {
			if (d)
				dp = d;
			MGET(d, M_DONTWAIT, MT_DATA);
			i = m->m_pkthdr.len - (soff + sn);
			if (d && i > MLEN) {
				MCLGET(d, M_DONTWAIT);
				if ((d->m_flags & M_EXT) == 0) {
					m_free(d);
					d = NULL;
				}
			}
			if (!d) {
				m_freem(m);
				if (d0)
					m_freem(d0);
				lck_mtx_lock(sadb_mutex);
				return ENOBUFS;
			}
			if (!d0)
				d0 = d;
			if (dp)
				dp->m_next = d;
			d->m_len = M_TRAILINGSPACE(d);
			d->m_len -= d->m_len % AES_BLOCKLEN;
			if (d->m_len > i)
				d->m_len = i;
			dptr = mtod(d, u_int8_t *);	
			dn = 0;
		}

		/* adjust len if greater than space available in dest */
		if (len > d->m_len - dn)
			len = d->m_len - dn;

		/* decrypt */
		aes_decrypt_cbc(sp, iv, len >> 4, dptr + dn, 
				(aes_decrypt_ctx*)(&(((aes_ctx*)sav->sched)->decrypt)));
		
		/* udpate offsets */
		sn += len;
		dn += len;
		
		// next iv
		bcopy(sp + len - AES_BLOCKLEN, iv, AES_BLOCKLEN);

		/* find the next source block */
		while (s && sn >= s->m_len) {
			sn -= s->m_len;
			soff += s->m_len;
			s = s->m_next;
		}

	}

	/* free un-needed source mbufs and add dest mbufs to chain */
	m_freem(scut->m_next);
	scut->m_len = scutoff;
	scut->m_next = d0;

	/* just in case */
	bzero(iv, sizeof(iv));
	bzero(sbuf, sizeof(sbuf));
	lck_mtx_lock(sadb_mutex);

	return 0;
}

int
esp_cbc_encrypt_aes(m, off, plen, sav, algo, ivlen)
	struct mbuf *m;
	size_t off;
	size_t plen;
	struct secasvar *sav;
	const struct esp_algorithm *algo;
	int ivlen;
{
	struct mbuf *s;
	struct mbuf *d, *d0, *dp;
	int soff;	/* offset from the head of chain, to head of this mbuf */
	int sn, dn;	/* offset from the head of the mbuf, to meat */
	size_t ivoff, bodyoff;
	u_int8_t *ivp, *dptr;
	u_int8_t sbuf[AES_BLOCKLEN], *sp;
	struct mbuf *scut;
	int scutoff;
	int i, len;

	if (ivlen != AES_BLOCKLEN) {
		ipseclog((LOG_ERR, "esp_cbc_encrypt %s: "
		    "unsupported ivlen %d\n", algo->name, ivlen));
		m_freem(m);
		return EINVAL;
	}

	if (sav->flags & SADB_X_EXT_OLD) {
		/* RFC 1827 */
		ivoff = off + sizeof(struct esp);
		bodyoff = off + sizeof(struct esp) + ivlen;
	} else {
		ivoff = off + sizeof(struct newesp);
		bodyoff = off + sizeof(struct newesp) + ivlen;
	}

	/* put iv into the packet */
	m_copyback(m, ivoff, ivlen, sav->iv);
	ivp = sav->iv;

	if (m->m_pkthdr.len < bodyoff) {
		ipseclog((LOG_ERR, "esp_cbc_encrypt %s: bad len %d/%lu\n",
		    algo->name, m->m_pkthdr.len, (unsigned long)bodyoff));
		m_freem(m);
		return EINVAL;
	}
	if ((m->m_pkthdr.len - bodyoff) % AES_BLOCKLEN) {
		ipseclog((LOG_ERR, "esp_cbc_encrypt %s: "
		    "payload length must be multiple of %lu\n",
		    algo->name, AES_BLOCKLEN));
		m_freem(m);
		return EINVAL;
	}
	lck_mtx_unlock(sadb_mutex);

	s = m;
	soff = sn = dn = 0;
	d = d0 = dp = NULL;
	sp = dptr = NULL;
	
	/* skip headers/IV */
	while (soff < bodyoff) {
		if (soff + s->m_len > bodyoff) {
			sn = bodyoff - soff;
			break;
		}

		soff += s->m_len;
		s = s->m_next;
	}
	scut = s;
	scutoff = sn;

	/* skip over empty mbuf */
	while (s && s->m_len == 0)
		s = s->m_next;
	
	while (soff < m->m_pkthdr.len) {
		/* source */
		if (sn + AES_BLOCKLEN <= s->m_len) {
			/* body is continuous */
			sp = mtod(s, u_int8_t *) + sn;
			len = s->m_len - sn;
			len -= len % AES_BLOCKLEN;	// full blocks only
		} else {
			/* body is non-continuous */
			m_copydata(s, sn, AES_BLOCKLEN, sbuf);
			sp = sbuf;
			len = AES_BLOCKLEN;			// 1 block only in sbuf
		}

		/* destination */
		if (!d || dn + AES_BLOCKLEN > d->m_len) {
			if (d)
				dp = d;
			MGET(d, M_DONTWAIT, MT_DATA);
			i = m->m_pkthdr.len - (soff + sn);
			if (d && i > MLEN) {
				MCLGET(d, M_DONTWAIT);
				if ((d->m_flags & M_EXT) == 0) {
					m_free(d);
					d = NULL;
				}
			}
			if (!d) {
				m_freem(m);
				if (d0)
					m_freem(d0);
				lck_mtx_lock(sadb_mutex);
				return ENOBUFS;
			}
			if (!d0)
				d0 = d;
			if (dp)
				dp->m_next = d;

			d->m_len = M_TRAILINGSPACE(d);
			d->m_len -= d->m_len % AES_BLOCKLEN;
			if (d->m_len > i)
				d->m_len = i;
			dptr = mtod(d, u_int8_t *);
			dn = 0;
		}
		
		/* adjust len if greater than space available */
		if (len > d->m_len - dn)
			len = d->m_len - dn;
		
		/* encrypt */
		aes_encrypt_cbc(sp, ivp, len >> 4, dptr + dn, 
			(aes_encrypt_ctx*)(&(((aes_ctx*)sav->sched)->encrypt)));

		/* update offsets */
		sn += len;
		dn += len;

		/* next iv */
		ivp = dptr + dn - AES_BLOCKLEN;	// last block encrypted
		
		/* find the next source block and skip empty mbufs */
		while (s && sn >= s->m_len) {
			sn -= s->m_len;
			soff += s->m_len;
			s = s->m_next;
		}

	}

	/* free un-needed source mbufs and add dest mbufs to chain */
	m_freem(scut->m_next);
	scut->m_len = scutoff;
	scut->m_next = d0;

	/* just in case */
	bzero(sbuf, sizeof(sbuf));
	lck_mtx_lock(sadb_mutex);
	key_sa_stir_iv(sav);

	return 0;
}

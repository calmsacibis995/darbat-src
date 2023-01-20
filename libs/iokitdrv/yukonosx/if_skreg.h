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
/*	$OpenBSD: if_skreg.h,v 1.28 2006/02/09 11:14:56 brad Exp $	*/

/*
 * Copyright (c) 1997, 1998, 1999, 2000
 *	Bill Paul <wpaul@ctr.columbia.edu>.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Bill Paul.
 * 4. Neither the name of the author nor the names of any co-contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Bill Paul AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL Bill Paul OR THE VOICES IN HIS HEAD
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: /c/ncvs/src/sys/pci/if_skreg.h,v 1.9 2000/04/22 02:16:37 wpaul Exp $
 * $FreeBSD: /c/ncvs/src/sys/pci/xmaciireg.h,v 1.3 2000/04/22 02:16:37 wpaul Exp $
 */

/*
 * Copyright (c) 2003 Nathan L. Binkert <binkertn@umich.edu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * GEnesis registers. The GEnesis chip has a 256-byte I/O window
 * but internally it has a 16K register space. This 16K space is
 * divided into 128-byte blocks. The first 128 bytes of the I/O
 * window represent the first block, which is permanently mapped
 * at the start of the window. The other 127 blocks can be mapped
 * to the second 128 bytes of the I/O window by setting the desired
 * block value in the RAP register in block 0. Not all of the 127
 * blocks are actually used. Most registers are 32 bits wide, but
 * there are a few 16-bit and 8-bit ones as well.
 */


#define u_int16_t	UInt16
#define u_int32_t	UInt32
#define u_int8_t	UInt8

/* Start of remappable register window. */
#define SK_WIN_BASE		0x0080

/* Size of a window */
#define SK_WIN_LEN		0x80

#define SK_WIN_MASK		0x3F80
#define SK_REG_MASK		0x7F

/* Compute the window of a given register (for the RAP register) */
#define SK_WIN(reg)		(((reg) & SK_WIN_MASK) / SK_WIN_LEN)

/* Compute the relative offset of a register within the window */
#define SK_REG(reg)		((reg) & SK_REG_MASK)

#define SK_PORT_A	0
#define SK_PORT_B	1

/*
 * Compute offset of port-specific register. Since there are two
 * ports, there are two of some GEnesis modules (e.g. two sets of
 * DMA queues, two sets of FIFO control registers, etc...). Normally,
 * the block for port 0 is at offset 0x0 and the block for port 1 is
 * at offset 0x80 (i.e. the next page over). However for the transmit
 * BMUs and RAMbuffers, there are two blocks for each port: one for
 * the sync transmit queue and one for the async queue (which we don't
 * use). However instead of ordering them like this:
 * TX sync 1 / TX sync 2 / TX async 1 / TX async 2
 * SysKonnect has instead ordered them like this:
 * TX sync 1 / TX async 1 / TX sync 2 / TX async 2
 * This means that when referencing the TX BMU and RAMbuffer registers,
 * we have to double the block offset (0x80 * 2) in order to reach the
 * second queue. This prevents us from using the same formula
 * (sk_port * 0x80) to compute the offsets for all of the port-specific
 * blocks: we need an extra offset for the BMU and RAMbuffer registers.
 * The simplest thing is to provide an extra argument to these macros:
 * the 'skip' parameter. The 'skip' value is the number of extra pages
 * for skip when computing the port0/port1 offsets. For most registers,
 * the skip value is 0; for the BMU and RAMbuffer registers, it's 1.
 */
#ifndef YUKONOSX
#define SK_IF_READ_4(sc_if, skip, reg)		\
	sk_win_read_4(sc_if->sk_softc, reg +	\
	((sc_if->sk_port * (skip + 1)) * SK_WIN_LEN))
#define SK_IF_READ_2(sc_if, skip, reg)		\
	sk_win_read_2(sc_if->sk_softc, reg + 	\
	((sc_if->sk_port * (skip + 1)) * SK_WIN_LEN))
#define SK_IF_READ_1(sc_if, skip, reg)		\
	sk_win_read_1(sc_if->sk_softc, reg +	\
	((sc_if->sk_port * (skip + 1)) * SK_WIN_LEN))

#define SK_IF_WRITE_4(sc_if, skip, reg, val)	\
	sk_win_write_4(sc_if->sk_softc,		\
	reg + ((sc_if->sk_port * (skip + 1)) * SK_WIN_LEN), val)
#define SK_IF_WRITE_2(sc_if, skip, reg, val)	\
	sk_win_write_2(sc_if->sk_softc,		\
	reg + ((sc_if->sk_port * (skip + 1)) * SK_WIN_LEN), val)
#define SK_IF_WRITE_1(sc_if, skip, reg, val)	\
	sk_win_write_1(sc_if->sk_softc,		\
	reg + ((sc_if->sk_port * (skip + 1)) * SK_WIN_LEN), val)
#else	/*YUKONOSX*/
#define SK_IF_READ_4(sc_if, skip, reg)		\
	sk_win_read_4(0, reg +	\
	((0 * (skip + 1)) * SK_WIN_LEN))
#define SK_IF_READ_2(sc_if, skip, reg)		\
	sk_win_read_2(0, reg + 	\
	((0 * (skip + 1)) * SK_WIN_LEN))
#define SK_IF_READ_1(sc_if, skip, reg)		\
	sk_win_read_1(0, reg +	\
	((0 * (skip + 1)) * SK_WIN_LEN))

#define SK_IF_WRITE_4(sc_if, skip, reg, val)	\
	sk_win_write_4(0,			\
	reg + ((0 * (skip + 1)) * SK_WIN_LEN), val)
#define SK_IF_WRITE_2(sc_if, skip, reg, val)	\
	sk_win_write_2(0,			\
	reg + (( 0 * (skip + 1)) * SK_WIN_LEN), val)
#define SK_IF_WRITE_1(sc_if, skip, reg, val)	\
	sk_win_write_1(0,			\
	reg + ((0 * (skip + 1)) * SK_WIN_LEN), val)
#endif	/*YUKONOSX*/

/* Power stuff, a la linux */
#define PC_VAUX_ENA             128     /* Switch VAUX Enable  */
#define PC_VAUX_DIS             64      /* Switch VAUX Disable */
#define PC_VCC_ENA              32      /* Switch VCC Enable  */
#define PC_VCC_DIS              16      /* Switch VCC Disable */
#define PC_VAUX_ON              8       /* Switch VAUX On  */
#define PC_VAUX_OFF             3       /* Switch VAUX Off */
#define PC_VCC_ON               2       /* Switch VCC On  */
#define PC_VCC_OFF              1       /* Switch VCC Off */

/* Block 0 registers, permanently mapped at iobase. */
#define SK_RAP		0x0000
#define SK_CSR		0x0004
#define SK_LED		0x0006
#define SK_POWER        0x0007  /* CEG, from Linux, power reg (Yukon only) */
#define SK_ISR		0x0008	/* interrupt source */
#define SK_IMR		0x000C	/* interrupt mask */
#define SK_IESR		0x0010	/* interrupt hardware error source */
#define SK_IEMR		0x0014  /* interrupt hardware error mask */
#define SK_ISSR		0x0018	/* special interrupt source */



#define SK_XM_IMR0	0x0020
#define SK_XM_ISR0	0x0028
#define SK_XM_PHYADDR0	0x0030
#define SK_XM_PHYDATA0	0x0034
#define SK_XM_IMR1	0x0040
#define SK_XM_ISR1	0x0048
#define SK_XM_PHYADDR1	0x0050
#define SK_XM_PHYDATA1	0x0054
#define SK_BMU_RX_CSR0	0x0060
#define SK_BMU_RX_CSR1	0x0064
#define SK_BMU_TXS_CSR0	0x0068
#define SK_BMU_TXA_CSR0	0x006C
#define SK_BMU_TXS_CSR1	0x0070
#define SK_BMU_TXA_CSR1	0x0074

/* SK_CSR register */
#define SK_CSR_SW_RESET			0x0001
#define SK_CSR_SW_UNRESET		0x0002
#define SK_CSR_MASTER_RESET		0x0004
#define SK_CSR_MASTER_UNRESET		0x0008
#define SK_CSR_MASTER_STOP		0x0010
#define SK_CSR_MASTER_DONE		0x0020
#define SK_CSR_SW_IRQ_CLEAR		0x0040
#define SK_CSR_SW_IRQ_SET		0x0080
#define SK_CSR_SLOTSIZE			0x0100 /* 1 == 64 bits, 0 == 32 */
#define SK_CSR_BUSCLOCK			0x0200 /* 1 == 33/66 MHz, = 33 */

/* SK_LED register */
#define SK_LED_GREEN_OFF		0x01
#define SK_LED_GREEN_ON			0x02

/* SK_ISR register */
#define SK_ISR_TX2_AS_CHECK		0x00000001
#define SK_ISR_TX2_AS_EOF		0x00000002
#define SK_ISR_TX2_AS_EOB		0x00000004
#define SK_ISR_TX2_S_CHECK		0x00000008
#define SK_ISR_TX2_S_EOF		0x00000010
#define SK_ISR_TX2_S_EOB		0x00000020
#define SK_ISR_TX1_AS_CHECK		0x00000040
#define SK_ISR_TX1_AS_EOF		0x00000080
#define SK_ISR_TX1_AS_EOB		0x00000100
#define SK_ISR_TX1_S_CHECK		0x00000200
#define SK_ISR_TX1_S_EOF		0x00000400
#define SK_ISR_TX1_S_EOB		0x00000800
#define SK_ISR_RX2_CHECK		0x00001000
#define SK_ISR_RX2_EOF			0x00002000
#define SK_ISR_RX2_EOB			0x00004000
#define SK_ISR_RX1_CHECK		0x00008000
#define SK_ISR_RX1_EOF			0x00010000
#define SK_ISR_RX1_EOB			0x00020000
#define SK_ISR_LINK2_OFLOW		0x00040000
#define SK_ISR_MAC2			0x00080000
#define SK_ISR_LINK1_OFLOW		0x00100000
#define SK_ISR_MAC1			0x00200000
#define SK_ISR_TIMER			0x00400000
#define SK_ISR_EXTERNAL_REG		0x00800000
#define SK_ISR_SW			0x01000000
#define SK_ISR_I2C_RDY			0x02000000
#define SK_ISR_TX2_TIMEO		0x04000000
#define SK_ISR_TX1_TIMEO		0x08000000
#define SK_ISR_RX2_TIMEO		0x10000000
#define SK_ISR_RX1_TIMEO		0x20000000
#define SK_ISR_RSVD			0x40000000
#define SK_ISR_HWERR			0x80000000

/* SK_IMR register */
#define SK_IMR_TX2_AS_CHECK		0x00000001
#define SK_IMR_TX2_AS_EOF		0x00000002
#define SK_IMR_TX2_AS_EOB		0x00000004
#define SK_IMR_TX2_S_CHECK		0x00000008
#define SK_IMR_TX2_S_EOF		0x00000010
#define SK_IMR_TX2_S_EOB		0x00000020
#define SK_IMR_TX1_AS_CHECK		0x00000040
#define SK_IMR_TX1_AS_EOF		0x00000080
#define SK_IMR_TX1_AS_EOB		0x00000100
#define SK_IMR_TX1_S_CHECK		0x00000200
#define SK_IMR_TX1_S_EOF		0x00000400
#define SK_IMR_TX1_S_EOB		0x00000800
#define SK_IMR_RX2_CHECK		0x00001000
#define SK_IMR_RX2_EOF			0x00002000
#define SK_IMR_RX2_EOB			0x00004000
#define SK_IMR_RX1_CHECK		0x00008000
#define SK_IMR_RX1_EOF			0x00010000
#define SK_IMR_RX1_EOB			0x00020000
#define SK_IMR_LINK2_OFLOW		0x00040000
#define SK_IMR_MAC2			0x00080000
#define SK_IMR_LINK1_OFLOW		0x00100000
#define SK_IMR_MAC1			0x00200000
#define SK_IMR_TIMER			0x00400000
#define SK_IMR_EXTERNAL_REG		0x00800000
#define SK_IMR_SW			0x01000000
#define SK_IMR_I2C_RDY			0x02000000
#define SK_IMR_TX2_TIMEO		0x04000000
#define SK_IMR_TX1_TIMEO		0x08000000
#define SK_IMR_RX2_TIMEO		0x10000000
#define SK_IMR_RX1_TIMEO		0x20000000
#define SK_IMR_RSVD			0x40000000
#define SK_IMR_HWERR			0x80000000

#define SK_INTRS1	\
	(SK_IMR_RX1_EOF|SK_IMR_TX1_S_EOF|SK_IMR_MAC1)

#define SK_INTRS2	\
	(SK_IMR_RX2_EOF|SK_IMR_TX2_S_EOF|SK_IMR_MAC2)

/* SK_IESR register */
#define SK_IESR_PAR_RX2			0x00000001
#define SK_IESR_PAR_RX1			0x00000002
#define SK_IESR_PAR_MAC2		0x00000004
#define SK_IESR_PAR_MAC1		0x00000008
#define SK_IESR_PAR_WR_RAM		0x00000010
#define SK_IESR_PAR_RD_RAM		0x00000020
#define SK_IESR_NO_TSTAMP_MAC2		0x00000040
#define SK_IESR_NO_TSTAMO_MAC1		0x00000080
#define SK_IESR_NO_STS_MAC2		0x00000100
#define SK_IESR_NO_STS_MAC1		0x00000200
#define SK_IESR_IRQ_STS			0x00000400
#define SK_IESR_MASTERERR		0x00000800

/* SK_IEMR register */
#define SK_IEMR_PAR_RX2			0x00000001
#define SK_IEMR_PAR_RX1			0x00000002
#define SK_IEMR_PAR_MAC2		0x00000004
#define SK_IEMR_PAR_MAC1		0x00000008
#define SK_IEMR_PAR_WR_RAM		0x00000010
#define SK_IEMR_PAR_RD_RAM		0x00000020
#define SK_IEMR_NO_TSTAMP_MAC2		0x00000040
#define SK_IEMR_NO_TSTAMO_MAC1		0x00000080
#define SK_IEMR_NO_STS_MAC2		0x00000100
#define SK_IEMR_NO_STS_MAC1		0x00000200
#define SK_IEMR_IRQ_STS			0x00000400
#define SK_IEMR_MASTERERR		0x00000800

/* Block 2 */
#define SK_MAC0_0	0x0100
#define SK_MAC0_1	0x0104
#define SK_MAC1_0	0x0108
#define SK_MAC1_1	0x010C
#define SK_MAC2_0	0x0110
#define SK_MAC2_1	0x0114
#define SK_CONNTYPE	0x0118
#define SK_PMDTYPE	0x0119
#define SK_CONFIG	0x011A
#define SK_CHIPVER	0x011B
#define SK_EPROM0	0x011C
#define SK_EPROM1	0x011D		/* yukon/genesis */
#define	SK_Y2_CLKGATE	0x011D		/* yukon 2 */
#define SK_EPROM2	0x011E		/* yukon/genesis */
#define SK_Y2_HWRES	0x011E		/* yukon 2 */
#define SK_EPROM3	0x011F
#define SK_EP_ADDR	0x0120
#define SK_EP_DATA	0x0124
#define SK_EP_LOADCTL	0x0128
#define SK_EP_LOADTST	0x0129
#define SK_TIMERINIT	0x0130
#define SK_TIMER	0x0134
#define SK_TIMERCTL	0x0138
#define SK_TIMERTST	0x0139
#define SK_IMTIMERINIT	0x0140
#define SK_IMTIMER	0x0144
#define SK_IMTIMERCTL	0x0148
#define SK_IMTIMERTST	0x0149
#define SK_IMMR		0x014C
#define SK_IHWEMR	0x0150
#define SK_TESTCTL1	0x0158
#define SK_TESTCTL2	0x0159
#define SK_GPIO		0x015C
#define SK_I2CHWCTL	0x0160
#define SK_I2CHWDATA	0x0164
#define SK_I2CHWIRQ	0x0168
#define SK_I2CSW	0x016C
#define SK_BLNKINIT	0x0170
#define SK_BLNKCOUNT	0x0174
#define SK_BLNKCTL	0x0178
#define SK_BLNKSTS	0x0179
#define SK_BLNKTST	0x017A

/* Values for SK_CHIPVER */
#define SK_GENESIS		0x0A
#define SK_YUKON		0xB0
#define SK_YUKON_LITE		0xB1
#define SK_YUKON_LP		0xB2
#define SK_YUKON_XL		0xB3
#define SK_YUKON_EC_U		0xB4
#define SK_YUKON_EC		0xB6
#define SK_YUKON_FE		0xB7

#define SK_YUKON_FAMILY(x) ((x) & 0xB0)
#define SK_IS_GENESIS(sc) \
    ((sc)->sk_type == SK_GENESIS)
#define SK_IS_YUKON(sc) \
    ((sc)->sk_type >= SK_YUKON && (sc)->sk_type <= SK_YUKON_FE)
#define SK_IS_YUKON2(sc) \
    ((sc)->sk_type >= SK_YUKON_XL && (sc)->sk_type <= SK_YUKON_FE)

/* Known revisions in SK_CONFIG */
#define SK_YUKON_LITE_REV_A0	0x0 /* invented, see test in skc_attach */
#define SK_YUKON_LITE_REV_A1	0x3
#define SK_YUKON_LITE_REV_A3	0x7

#define SK_YUKON_XL_REV_A0	0x0
#define SK_YUKON_XL_REV_A1	0x1
#define SK_YUKON_XL_REV_A2	0x2
#define SK_YUKON_XL_REV_A3	0x3

#define SK_YUKON_EC_REV_A1	0x0
#define SK_YUKON_EC_REV_A2	0x1
#define SK_YUKON_EC_REV_A3	0x2

#define SK_YUKON_EC_U_REV_A0	0x1
#define SK_YUKON_EC_U_REV_A1	0x2

#define SK_IMCTL_STOP	0x02
#define SK_IMCTL_START	0x04

/* Number of ticks per usec for interrupt moderation */
#define SK_IMTIMER_TICKS_GENESIS	53
#define SK_IMTIMER_TICKS_YUKON		78
#define SK_IMTIMER_TICKS_YUKON_EC	125
#define SK_IM_USECS(x)		((x) * imtimer_ticks)

/*
 * The SK_EPROM0 register contains a byte that describes the
 * amount of SRAM mounted on the NIC. The value also tells if
 * the chips are 64K or 128K. This affects the RAMbuffer address
 * offset that we need to use.
 */
#define SK_RAMSIZE_512K_64	0x1
#define SK_RAMSIZE_1024K_128	0x2
#define SK_RAMSIZE_1024K_64	0x3
#define SK_RAMSIZE_2048K_128	0x4

#define SK_RBOFF_0		0x0
#define SK_RBOFF_80000		0x80000

/*
 * SK_EEPROM1 contains the PHY type, which may be XMAC for
 * fiber-based cards or BCOM for 1000baseT cards with a Broadcom
 * PHY.
 */
#define SK_PHYTYPE_XMAC		0       /* integeated XMAC II PHY */
#define SK_PHYTYPE_BCOM		1       /* Broadcom BCM5400 */
#define SK_PHYTYPE_LONE		2       /* Level One LXT1000 */
#define SK_PHYTYPE_NAT		3       /* National DP83891 */
#define SK_PHYTYPE_MARV_COPPER	4       /* Marvell 88E1011S */
#define SK_PHYTYPE_MARV_FIBER	5       /* Marvell 88E1011S (fiber) */

/*
 * PHY addresses.
 */
#define SK_PHYADDR_XMAC		0x0
#define SK_PHYADDR_BCOM		0x1
#define SK_PHYADDR_LONE		0x3
#define SK_PHYADDR_NAT		0x0
#define SK_PHYADDR_MARV		0x0

#define SK_CONFIG_SINGLEMAC	0x01
#define SK_CONFIG_DIS_DSL_CLK	0x02

#define SK_PMD_1000BASETX_ALT	0x31
#define SK_PMD_1000BASECX	0x43
#define SK_PMD_1000BASELX	0x4C
#define SK_PMD_1000BASESX	0x53
#define SK_PMD_1000BASETX	0x54

/* GPIO bits */
#define SK_GPIO_DAT0		0x00000001
#define SK_GPIO_DAT1		0x00000002
#define SK_GPIO_DAT2		0x00000004
#define SK_GPIO_DAT3		0x00000008
#define SK_GPIO_DAT4		0x00000010
#define SK_GPIO_DAT5		0x00000020
#define SK_GPIO_DAT6		0x00000040
#define SK_GPIO_DAT7		0x00000080
#define SK_GPIO_DAT8		0x00000100
#define SK_GPIO_DAT9		0x00000200
#define SK_GPIO_DIR0		0x00010000
#define SK_GPIO_DIR1		0x00020000
#define SK_GPIO_DIR2		0x00040000
#define SK_GPIO_DIR3		0x00080000
#define SK_GPIO_DIR4		0x00100000
#define SK_GPIO_DIR5		0x00200000
#define SK_GPIO_DIR6		0x00400000
#define SK_GPIO_DIR7		0x00800000
#define SK_GPIO_DIR8		0x01000000
#define SK_GPIO_DIR9           0x02000000

#define	SK_Y2_CLKGATE_LINK2_INACTIVE	0x80	/* port 2 inactive */
#define	SK_Y2_CLKGATE_LINK2_GATE_DIS	0x40	/* disable clock gate, 2 */
#define	SK_Y2_CLKGATE_LINK2_CORE_DIS	0x20	/* disable core clock, 2 */
#define	SK_Y2_CLKGATE_LINK2_PCI_DIS	0x10	/* disable pci clock, 2 */
#define	SK_Y2_CLKGATE_LINK1_INACTIVE	0x08	/* port 1 inactive */
#define	SK_Y2_CLKGATE_LINK1_GATE_DIS	0x04	/* disable clock gate, 1 */
#define	SK_Y2_CLKGATE_LINK1_CORE_DIS	0x02	/* disable core clock, 1 */
#define	SK_Y2_CLKGATE_LINK1_PCI_DIS	0x01	/* disable pci clock, 1 */

#define	SK_Y2_HWRES_LINK_1	0x01
#define	SK_Y2_HWRES_LINK_2	0x02
#define	SK_Y2_HWRES_LINK_MASK	(SK_Y2_HWRES_LINK_1 | SK_Y2_HWRES_LINK_2)
#define	SK_Y2_HWRES_LINK_DUAL	(SK_Y2_HWRES_LINK_1 | SK_Y2_HWRES_LINK_2)

/* Block 3 Ram interface and MAC arbiter registers */
#define SK_RAMADDR	0x0180
#define SK_RAMDATA0	0x0184
#define SK_RAMDATA1	0x0188
#define SK_TO0		0x0190
#define SK_TO1		0x0191
#define SK_TO2		0x0192
#define SK_TO3		0x0193
#define SK_TO4		0x0194
#define SK_TO5		0x0195
#define SK_TO6		0x0196
#define SK_TO7		0x0197
#define SK_TO8		0x0198
#define SK_TO9		0x0199
#define SK_TO10		0x019A
#define SK_TO11		0x019B
#define SK_RITIMEO_TMR	0x019C
#define SK_RAMCTL	0x01A0
#define SK_RITIMER_TST	0x01A2

#define SK_RAMCTL_RESET		0x0001
#define SK_RAMCTL_UNRESET	0x0002
#define SK_RAMCTL_CLR_IRQ_WPAR	0x0100
#define SK_RAMCTL_CLR_IRQ_RPAR	0x0200

/* Mac arbiter registers */
#define SK_MINIT_RX1	0x01B0
#define SK_MINIT_RX2	0x01B1
#define SK_MINIT_TX1	0x01B2
#define SK_MINIT_TX2	0x01B3
#define SK_MTIMEO_RX1	0x01B4
#define SK_MTIMEO_RX2	0x01B5
#define SK_MTIMEO_TX1	0x01B6
#define SK_MTIEMO_TX2	0x01B7
#define SK_MACARB_CTL	0x01B8
#define SK_MTIMER_TST	0x01BA
#define SK_RCINIT_RX1	0x01C0
#define SK_RCINIT_RX2	0x01C1
#define SK_RCINIT_TX1	0x01C2
#define SK_RCINIT_TX2	0x01C3
#define SK_RCTIMEO_RX1	0x01C4
#define SK_RCTIMEO_RX2	0x01C5
#define SK_RCTIMEO_TX1	0x01C6
#define SK_RCTIMEO_TX2	0x01C7
#define SK_RECOVERY_CTL	0x01C8
#define SK_RCTIMER_TST	0x01CA

/* Packet arbiter registers */
#define SK_RXPA1_TINIT	0x01D0
#define SK_RXPA2_TINIT	0x01D4
#define SK_TXPA1_TINIT	0x01D8
#define SK_TXPA2_TINIT	0x01DC
#define SK_RXPA1_TIMEO	0x01E0
#define SK_RXPA2_TIMEO	0x01E4
#define SK_TXPA1_TIMEO	0x01E8
#define SK_TXPA2_TIMEO	0x01EC
#define SK_PKTARB_CTL	0x01F0
#define SK_PKTATB_TST	0x01F2

#define SK_PKTARB_TIMEOUT	0x2000

#define SK_PKTARBCTL_RESET		0x0001
#define SK_PKTARBCTL_UNRESET		0x0002
#define SK_PKTARBCTL_RXTO1_OFF		0x0004
#define SK_PKTARBCTL_RXTO1_ON		0x0008
#define SK_PKTARBCTL_RXTO2_OFF		0x0010
#define SK_PKTARBCTL_RXTO2_ON		0x0020
#define SK_PKTARBCTL_TXTO1_OFF		0x0040
#define SK_PKTARBCTL_TXTO1_ON		0x0080
#define SK_PKTARBCTL_TXTO2_OFF		0x0100
#define SK_PKTARBCTL_TXTO2_ON		0x0200
#define SK_PKTARBCTL_CLR_IRQ_RXTO1	0x0400
#define SK_PKTARBCTL_CLR_IRQ_RXTO2	0x0800
#define SK_PKTARBCTL_CLR_IRQ_TXTO1	0x1000
#define SK_PKTARBCTL_CLR_IRQ_TXTO2	0x2000

#define SK_MINIT_XMAC_B2	54
#define SK_MINIT_XMAC_C1	63

#define SK_MACARBCTL_RESET	0x0001
#define SK_MACARBCTL_UNRESET	0x0002
#define SK_MACARBCTL_FASTOE_OFF	0x0004
#define SK_MACARBCRL_FASTOE_ON	0x0008

#define SK_RCINIT_XMAC_B2	54
#define SK_RCINIT_XMAC_C1	0

#define SK_RECOVERYCTL_RX1_OFF	0x0001
#define SK_RECOVERYCTL_RX1_ON	0x0002
#define SK_RECOVERYCTL_RX2_OFF	0x0004
#define SK_RECOVERYCTL_RX2_ON	0x0008
#define SK_RECOVERYCTL_TX1_OFF	0x0010
#define SK_RECOVERYCTL_TX1_ON	0x0020
#define SK_RECOVERYCTL_TX2_OFF	0x0040
#define SK_RECOVERYCTL_TX2_ON	0x0080

#define SK_RECOVERY_XMAC_B2				\
	(SK_RECOVERYCTL_RX1_ON|SK_RECOVERYCTL_RX2_ON|	\
	SK_RECOVERYCTL_TX1_ON|SK_RECOVERYCTL_TX2_ON)

#define SK_RECOVERY_XMAC_C1				\
	(SK_RECOVERYCTL_RX1_OFF|SK_RECOVERYCTL_RX2_OFF|	\
	SK_RECOVERYCTL_TX1_OFF|SK_RECOVERYCTL_TX2_OFF)

/* Block 4 -- TX Arbiter MAC 1 */
#define SK_TXAR1_TIMERINIT	0x0200
#define SK_TXAR1_TIMERVAL	0x0204
#define SK_TXAR1_LIMITINIT	0x0208
#define SK_TXAR1_LIMITCNT	0x020C
#define SK_TXAR1_COUNTERCTL	0x0210
#define SK_TXAR1_COUNTERTST	0x0212
#define SK_TXAR1_COUNTERSTS	0x0212

/* Block 5 -- TX Arbiter MAC 2 */
#define SK_TXAR2_TIMERINIT	0x0280
#define SK_TXAR2_TIMERVAL	0x0284
#define SK_TXAR2_LIMITINIT	0x0288
#define SK_TXAR2_LIMITCNT	0x028C
#define SK_TXAR2_COUNTERCTL	0x0290
#define SK_TXAR2_COUNTERTST	0x0291
#define SK_TXAR2_COUNTERSTS	0x0292

#define SK_TXARCTL_OFF		0x01
#define SK_TXARCTL_ON		0x02
#define SK_TXARCTL_RATECTL_OFF	0x04
#define SK_TXARCTL_RATECTL_ON	0x08
#define SK_TXARCTL_ALLOC_OFF	0x10
#define SK_TXARCTL_ALLOC_ON	0x20
#define SK_TXARCTL_FSYNC_OFF	0x40
#define SK_TXARCTL_FSYNC_ON	0x80

/* Block 6 -- External registers */
#define SK_EXTREG_BASE	0x300
#define SK_EXTREG_END	0x37C

/* Block 7 -- PCI config registers */
#define SK_PCI_BASE	0x0380
#define SK_PCI_END	0x03FC

/* Compute offset of mirrored PCI register */
#define SK_PCI_REG(reg)		((reg) + SK_PCI_BASE)

/* Block 8 -- RX queue 1 */
#define SK_RXQ1_BUFCNT		0x0400
#define SK_RXQ1_BUFCTL		0x0402
#define SK_RXQ1_NEXTDESC	0x0404
#define SK_RXQ1_RXBUF_LO	0x0408
#define SK_RXQ1_RXBUF_HI	0x040C
#define SK_RXQ1_RXSTAT		0x0410
#define SK_RXQ1_TIMESTAMP	0x0414
#define SK_RXQ1_CSUM1		0x0418
#define SK_RXQ1_CSUM2		0x041A
#define SK_RXQ1_CSUM1_START	0x041C
#define SK_RXQ1_CSUM2_START	0x041E
#define SK_RXQ1_CURADDR_LO	0x0420
#define SK_RXQ1_CURADDR_HI	0x0424
#define SK_RXQ1_CURCNT_LO	0x0428
#define SK_RXQ1_CURCNT_HI	0x042C
#define SK_RXQ1_CURBYTES	0x0430
#define SK_RXQ1_BMU_CSR		0x0434
#define SK_RXQ1_WATERMARK	0x0438
#define SK_RXQ1_FLAG		0x043A
#define SK_RXQ1_TEST1		0x043C
#define SK_RXQ1_TEST2		0x0440
#define SK_RXQ1_TEST3		0x0444
/* yukon-2 only */
#define SK_RXQ1_Y2_WM		0x0440
#define SK_RXQ1_Y2_AL		0x0442
#define SK_RXQ1_Y2_RSP		0x0444
#define SK_RXQ1_Y2_RSL		0x0446
#define SK_RXQ1_Y2_RP		0x0448
#define SK_RXQ1_Y2_RL		0x044A
#define SK_RXQ1_Y2_WP		0x044C
#define SK_RXQ1_Y2_WSP		0x044D
#define SK_RXQ1_Y2_WL		0x044E
#define SK_RXQ1_Y2_WSL		0x044F
/* yukon-2 only (prefetch unit) */
#define SK_RXQ1_Y2_PREF_CSR	0x0450
#define SK_RXQ1_Y2_PREF_LIDX	0x0454
#define SK_RXQ1_Y2_PREF_ADDRLO	0x0458
#define SK_RXQ1_Y2_PREF_ADDRHI	0x045C
#define SK_RXQ1_Y2_PREF_GETIDX	0x0460
#define SK_RXQ1_Y2_PREF_PUTIDX	0x0464
#define SK_RXQ1_Y2_PREF_FIFOWP	0x0470
#define SK_RXQ1_Y2_PREF_FIFORP	0x0474
#define SK_RXQ1_Y2_PREF_FIFOWM	0x0478
#define SK_RXQ1_Y2_PREF_FIFOLV	0x047C

/* Block 9 -- RX queue 2 */
#define SK_RXQ2_BUFCNT		0x0480
#define SK_RXQ2_BUFCTL		0x0482
#define SK_RXQ2_NEXTDESC	0x0484
#define SK_RXQ2_RXBUF_LO	0x0488
#define SK_RXQ2_RXBUF_HI	0x048C
#define SK_RXQ2_RXSTAT		0x0490
#define SK_RXQ2_TIMESTAMP	0x0494
#define SK_RXQ2_CSUM1		0x0498
#define SK_RXQ2_CSUM2		0x049A
#define SK_RXQ2_CSUM1_START	0x049C
#define SK_RXQ2_CSUM2_START	0x049E
#define SK_RXQ2_CURADDR_LO	0x04A0
#define SK_RXQ2_CURADDR_HI	0x04A4
#define SK_RXQ2_CURCNT_LO	0x04A8
#define SK_RXQ2_CURCNT_HI	0x04AC
#define SK_RXQ2_CURBYTES	0x04B0
#define SK_RXQ2_BMU_CSR		0x04B4
#define SK_RXQ2_WATERMARK	0x04B8
#define SK_RXQ2_FLAG		0x04BA
#define SK_RXQ2_TEST1		0x04BC
#define SK_RXQ2_TEST2		0x04C0
#define SK_RXQ2_TEST3		0x04C4
/* yukon-2 only */
#define SK_RXQ2_Y2_WM		0x04C0
#define SK_RXQ2_Y2_AL		0x04C2
#define SK_RXQ2_Y2_RSP		0x04C4
#define SK_RXQ2_Y2_RSL		0x04C6
#define SK_RXQ2_Y2_RP		0x04C8
#define SK_RXQ2_Y2_RL		0x04CA
#define SK_RXQ2_Y2_WP		0x04CC
#define SK_RXQ2_Y2_WSP		0x04CD
#define SK_RXQ2_Y2_WL		0x04CE
#define SK_RXQ2_Y2_WSL		0x04CF
/* yukon-2 only (prefetch unit) */
#define SK_RXQ2_Y2_PREF_CSR	0x04D0
#define SK_RXQ2_Y2_PREF_LIDX	0x04D4
#define SK_RXQ2_Y2_PREF_ADDRLO	0x04D8
#define SK_RXQ2_Y2_PREF_ADDRHI	0x04DC
#define SK_RXQ2_Y2_PREF_GETIDX	0x04E0
#define SK_RXQ2_Y2_PREF_PUTIDX	0x04E4
#define SK_RXQ2_Y2_PREF_FIFOWP	0x04F0
#define SK_RXQ2_Y2_PREF_FIFORP	0x04F4
#define SK_RXQ2_Y2_PREF_FIFOWM	0x04F8
#define SK_RXQ2_Y2_PREF_FIFOLV	0x04FC

#define SK_RXBMU_CLR_IRQ_ERR		0x00000001
#define SK_RXBMU_CLR_IRQ_EOF		0x00000002
#define SK_RXBMU_CLR_IRQ_EOB		0x00000004
#define SK_RXBMU_CLR_IRQ_PAR		0x00000008
#define SK_RXBMU_RX_START		0x00000010
#define SK_RXBMU_RX_STOP		0x00000020
#define SK_RXBMU_POLL_OFF		0x00000040
#define SK_RXBMU_POLL_ON		0x00000080
#define SK_RXBMU_TRANSFER_SM_RESET	0x00000100
#define SK_RXBMU_TRANSFER_SM_UNRESET	0x00000200
#define SK_RXBMU_DESCWR_SM_RESET	0x00000400
#define SK_RXBMU_DESCWR_SM_UNRESET	0x00000800
#define SK_RXBMU_DESCRD_SM_RESET	0x00001000
#define SK_RXBMU_DESCRD_SM_UNRESET	0x00002000
#define SK_RXBMU_SUPERVISOR_SM_RESET	0x00004000
#define SK_RXBMU_SUPERVISOR_SM_UNRESET	0x00008000
#define SK_RXBMU_PFI_SM_RESET		0x00010000
#define SK_RXBMU_PFI_SM_UNRESET		0x00020000
#define SK_RXBMU_FIFO_RESET		0x00040000
#define SK_RXBMU_FIFO_UNRESET		0x00080000
#define SK_RXBMU_DESC_RESET		0x00100000
#define SK_RXBMU_DESC_UNRESET		0x00200000
#define SK_RXBMU_SUPERVISOR_IDLE	0x01000000

#define SK_RXBMU_ONLINE		\
	(SK_RXBMU_TRANSFER_SM_UNRESET|SK_RXBMU_DESCWR_SM_UNRESET|	\
	SK_RXBMU_DESCRD_SM_UNRESET|SK_RXBMU_SUPERVISOR_SM_UNRESET|	\
	SK_RXBMU_PFI_SM_UNRESET|SK_RXBMU_FIFO_UNRESET|			\
	SK_RXBMU_DESC_UNRESET)

#define SK_RXBMU_OFFLINE		\
	(SK_RXBMU_TRANSFER_SM_RESET|SK_RXBMU_DESCWR_SM_RESET|	\
	SK_RXBMU_DESCRD_SM_RESET|SK_RXBMU_SUPERVISOR_SM_RESET|	\
	SK_RXBMU_PFI_SM_RESET|SK_RXBMU_FIFO_RESET|		\
	SK_RXBMU_DESC_RESET)

/* Block 12 -- TX sync queue 1 */
#define SK_TXQS1_BUFCNT		0x0600
#define SK_TXQS1_BUFCTL		0x0602
#define SK_TXQS1_NEXTDESC	0x0604
#define SK_TXQS1_RXBUF_LO	0x0608
#define SK_TXQS1_RXBUF_HI	0x060C
#define SK_TXQS1_RXSTAT		0x0610
#define SK_TXQS1_CSUM_STARTVAL	0x0614
#define SK_TXQS1_CSUM_STARTPOS	0x0618
#define SK_TXQS1_CSUM_WRITEPOS	0x061A
#define SK_TXQS1_CURADDR_LO	0x0620
#define SK_TXQS1_CURADDR_HI	0x0624
#define SK_TXQS1_CURCNT_LO	0x0628
#define SK_TXQS1_CURCNT_HI	0x062C
#define SK_TXQS1_CURBYTES	0x0630
#define SK_TXQS1_BMU_CSR	0x0634
#define SK_TXQS1_WATERMARK	0x0638
#define SK_TXQS1_FLAG		0x063A
#define SK_TXQS1_TEST1		0x063C
#define SK_TXQS1_TEST2		0x0640
#define SK_TXQS1_TEST3		0x0644
/* yukon-2 only */
#define SK_TXQS1_Y2_WM		0x0640
#define SK_TXQS1_Y2_AL		0x0642
#define SK_TXQS1_Y2_RSP		0x0644
#define SK_TXQS1_Y2_RSL		0x0646
#define SK_TXQS1_Y2_RP		0x0648
#define SK_TXQS1_Y2_RL		0x064A
#define SK_TXQS1_Y2_WP		0x064C
#define SK_TXQS1_Y2_WSP		0x064D
#define SK_TXQS1_Y2_WL		0x064E
#define SK_TXQS1_Y2_WSL		0x064F
/* yukon-2 only (prefetch unit) */
#define SK_TXQS1_Y2_PREF_CSR	0x0650
#define SK_TXQS1_Y2_PREF_LIDX	0x0654
#define SK_TXQS1_Y2_PREF_ADDRLO	0x0658
#define SK_TXQS1_Y2_PREF_ADDRHI	0x065C
#define SK_TXQS1_Y2_PREF_GETIDX	0x0660
#define SK_TXQS1_Y2_PREF_PUTIDX	0x0664
#define SK_TXQS1_Y2_PREF_FIFOWP	0x0670
#define SK_TXQS1_Y2_PREF_FIFORP	0x0674
#define SK_TXQS1_Y2_PREF_FIFOWM	0x0678
#define SK_TXQS1_Y2_PREF_FIFOLV	0x067C

/* Block 13 -- TX async queue 1 */
#define SK_TXQA1_BUFCNT		0x0680
#define SK_TXQA1_BUFCTL		0x0682
#define SK_TXQA1_NEXTDESC	0x0684
#define SK_TXQA1_RXBUF_LO	0x0688
#define SK_TXQA1_RXBUF_HI	0x068C
#define SK_TXQA1_RXSTAT		0x0690
#define SK_TXQA1_CSUM_STARTVAL	0x0694
#define SK_TXQA1_CSUM_STARTPOS	0x0698
#define SK_TXQA1_CSUM_WRITEPOS	0x069A
#define SK_TXQA1_CURADDR_LO	0x06A0
#define SK_TXQA1_CURADDR_HI	0x06A4
#define SK_TXQA1_CURCNT_LO	0x06A8
#define SK_TXQA1_CURCNT_HI	0x06AC
#define SK_TXQA1_CURBYTES	0x06B0
#define SK_TXQA1_BMU_CSR	0x06B4
#define SK_TXQA1_WATERMARK	0x06B8
#define SK_TXQA1_FLAG		0x06BA
#define SK_TXQA1_TEST1		0x06BC
#define SK_TXQA1_TEST2		0x06C0
#define SK_TXQA1_TEST3		0x06C4
/* yukon-2 only */
#define SK_TXQA1_Y2_WM		0x06C0
#define SK_TXQA1_Y2_AL		0x06C2
#define SK_TXQA1_Y2_RSP		0x06C4
#define SK_TXQA1_Y2_RSL		0x06C6
#define SK_TXQA1_Y2_RP		0x06C8
#define SK_TXQA1_Y2_RL		0x06CA
#define SK_TXQA1_Y2_WP		0x06CC
#define SK_TXQA1_Y2_WSP		0x06CD
#define SK_TXQA1_Y2_WL		0x06CE
#define SK_TXQA1_Y2_WSL		0x06CF
/* yukon-2 only (prefetch unit) */
#define SK_TXQA1_Y2_PREF_CSR	0x06D0
#define SK_TXQA1_Y2_PREF_LIDX	0x06D4
#define SK_TXQA1_Y2_PREF_ADDRLO	0x06D8
#define SK_TXQA1_Y2_PREF_ADDRHI	0x06DC
#define SK_TXQA1_Y2_PREF_GETIDX	0x06E0
#define SK_TXQA1_Y2_PREF_PUTIDX	0x06E4
#define SK_TXQA1_Y2_PREF_FIFOWP	0x06F0
#define SK_TXQA1_Y2_PREF_FIFORP	0x06F4
#define SK_TXQA1_Y2_PREF_FIFOWM	0x06F8
#define SK_TXQA1_Y2_PREF_FIFOLV	0x06FC

/* Block 14 -- TX sync queue 2 */
#define SK_TXQS2_BUFCNT		0x0700
#define SK_TXQS2_BUFCTL		0x0702
#define SK_TXQS2_NEXTDESC	0x0704
#define SK_TXQS2_RXBUF_LO	0x0708
#define SK_TXQS2_RXBUF_HI	0x070C
#define SK_TXQS2_RXSTAT		0x0710
#define SK_TXQS2_CSUM_STARTVAL	0x0714
#define SK_TXQS2_CSUM_STARTPOS	0x0718
#define SK_TXQS2_CSUM_WRITEPOS	0x071A
#define SK_TXQS2_CURADDR_LO	0x0720
#define SK_TXQS2_CURADDR_HI	0x0724
#define SK_TXQS2_CURCNT_LO	0x0728
#define SK_TXQS2_CURCNT_HI	0x072C
#define SK_TXQS2_CURBYTES	0x0730
#define SK_TXQS2_BMU_CSR	0x0734
#define SK_TXQS2_WATERMARK	0x0738
#define SK_TXQS2_FLAG		0x073A
#define SK_TXQS2_TEST1		0x073C
#define SK_TXQS2_TEST2		0x0740
#define SK_TXQS2_TEST3		0x0744
/* yukon-2 only */
#define SK_TXQS2_Y2_WM		0x0740
#define SK_TXQS2_Y2_AL		0x0742
#define SK_TXQS2_Y2_RSP		0x0744
#define SK_TXQS2_Y2_RSL		0x0746
#define SK_TXQS2_Y2_RP		0x0748
#define SK_TXQS2_Y2_RL		0x074A
#define SK_TXQS2_Y2_WP		0x074C
#define SK_TXQS2_Y2_WSP		0x074D
#define SK_TXQS2_Y2_WL		0x074E
#define SK_TXQS2_Y2_WSL		0x074F
/* yukon-2 only (prefetch unit) */
#define SK_TXQS2_Y2_PREF_CSR	0x0750
#define SK_TXQS2_Y2_PREF_LIDX	0x0754
#define SK_TXQS2_Y2_PREF_ADDRLO	0x0758
#define SK_TXQS2_Y2_PREF_ADDRHI	0x075C
#define SK_TXQS2_Y2_PREF_GETIDX	0x0760
#define SK_TXQS2_Y2_PREF_PUTIDX	0x0764
#define SK_TXQS2_Y2_PREF_FIFOWP	0x0770
#define SK_TXQS2_Y2_PREF_FIFORP	0x0774
#define SK_TXQS2_Y2_PREF_FIFOWM	0x0778
#define SK_TXQS2_Y2_PREF_FIFOLV	0x077C

/* Block 15 -- TX async queue 2 */
#define SK_TXQA2_BUFCNT		0x0780
#define SK_TXQA2_BUFCTL		0x0782
#define SK_TXQA2_NEXTDESC	0x0784
#define SK_TXQA2_RXBUF_LO	0x0788
#define SK_TXQA2_RXBUF_HI	0x078C
#define SK_TXQA2_RXSTAT		0x0790
#define SK_TXQA2_CSUM_STARTVAL	0x0794
#define SK_TXQA2_CSUM_STARTPOS	0x0798
#define SK_TXQA2_CSUM_WRITEPOS	0x079A
#define SK_TXQA2_CURADDR_LO	0x07A0
#define SK_TXQA2_CURADDR_HI	0x07A4
#define SK_TXQA2_CURCNT_LO	0x07A8
#define SK_TXQA2_CURCNT_HI	0x07AC
#define SK_TXQA2_CURBYTES	0x07B0
#define SK_TXQA2_BMU_CSR	0x07B4
#define SK_TXQA2_WATERMARK	0x07B8
#define SK_TXQA2_FLAG		0x07BA
#define SK_TXQA2_TEST1		0x07BC
#define SK_TXQA2_TEST2		0x07C0
#define SK_TXQA2_TEST3		0x07C4
/* yukon-2 only */
#define SK_TXQA2_Y2_WM		0x07C0
#define SK_TXQA2_Y2_AL		0x07C2
#define SK_TXQA2_Y2_RSP		0x07C4
#define SK_TXQA2_Y2_RSL		0x07C6
#define SK_TXQA2_Y2_RP		0x07C8
#define SK_TXQA2_Y2_RL		0x07CA
#define SK_TXQA2_Y2_WP		0x07CC
#define SK_TXQA2_Y2_WSP		0x07CD
#define SK_TXQA2_Y2_WL		0x07CE
#define SK_TXQA2_Y2_WSL		0x07CF
/* yukon-2 only (prefetch unit) */
#define SK_TXQA2_Y2_PREF_CSR	0x07D0
#define SK_TXQA2_Y2_PREF_LIDX	0x07D4
#define SK_TXQA2_Y2_PREF_ADDRLO	0x07D8
#define SK_TXQA2_Y2_PREF_ADDRHI	0x07DC
#define SK_TXQA2_Y2_PREF_GETIDX	0x07E0
#define SK_TXQA2_Y2_PREF_PUTIDX	0x07E4
#define SK_TXQA2_Y2_PREF_FIFOWP	0x07F0
#define SK_TXQA2_Y2_PREF_FIFORP	0x07F4
#define SK_TXQA2_Y2_PREF_FIFOWM	0x07F8
#define SK_TXQA2_Y2_PREF_FIFOLV	0x07FC

#define SK_TXBMU_CLR_IRQ_ERR		0x00000001
#define SK_TXBMU_CLR_IRQ_EOF		0x00000002
#define SK_TXBMU_CLR_IRQ_EOB		0x00000004
#define SK_TXBMU_TX_START		0x00000010
#define SK_TXBMU_TX_STOP		0x00000020
#define SK_TXBMU_POLL_OFF		0x00000040
#define SK_TXBMU_POLL_ON		0x00000080
#define SK_TXBMU_TRANSFER_SM_RESET	0x00000100
#define SK_TXBMU_TRANSFER_SM_UNRESET	0x00000200
#define SK_TXBMU_DESCWR_SM_RESET	0x00000400
#define SK_TXBMU_DESCWR_SM_UNRESET	0x00000800
#define SK_TXBMU_DESCRD_SM_RESET	0x00001000
#define SK_TXBMU_DESCRD_SM_UNRESET	0x00002000
#define SK_TXBMU_SUPERVISOR_SM_RESET	0x00004000
#define SK_TXBMU_SUPERVISOR_SM_UNRESET	0x00008000
#define SK_TXBMU_PFI_SM_RESET		0x00010000
#define SK_TXBMU_PFI_SM_UNRESET		0x00020000
#define SK_TXBMU_FIFO_RESET		0x00040000
#define SK_TXBMU_FIFO_UNRESET		0x00080000
#define SK_TXBMU_DESC_RESET		0x00100000
#define SK_TXBMU_DESC_UNRESET		0x00200000
#define SK_TXBMU_SUPERVISOR_IDLE	0x01000000

#define SK_TXBMU_ONLINE		\
	(SK_TXBMU_TRANSFER_SM_UNRESET|SK_TXBMU_DESCWR_SM_UNRESET|	\
	SK_TXBMU_DESCRD_SM_UNRESET|SK_TXBMU_SUPERVISOR_SM_UNRESET|	\
	SK_TXBMU_PFI_SM_UNRESET|SK_TXBMU_FIFO_UNRESET|			\
	SK_TXBMU_DESC_UNRESET)

#define SK_TXBMU_OFFLINE		\
	(SK_TXBMU_TRANSFER_SM_RESET|SK_TXBMU_DESCWR_SM_RESET|	\
	SK_TXBMU_DESCRD_SM_RESET|SK_TXBMU_SUPERVISOR_SM_RESET|	\
	SK_TXBMU_PFI_SM_RESET|SK_TXBMU_FIFO_RESET|		\
	SK_TXBMU_DESC_RESET)

/* Block 16 -- Receive RAMbuffer 1 */
#define SK_RXRB1_START		0x0800
#define SK_RXRB1_END		0x0804
#define SK_RXRB1_WR_PTR		0x0808
#define SK_RXRB1_RD_PTR		0x080C
#define SK_RXRB1_UTHR_PAUSE	0x0810
#define SK_RXRB1_LTHR_PAUSE	0x0814
#define SK_RXRB1_UTHR_HIPRIO	0x0818
#define SK_RXRB1_UTHR_LOPRIO	0x081C
#define SK_RXRB1_PKTCNT		0x0820
#define SK_RXRB1_LVL		0x0824
#define SK_RXRB1_CTLTST		0x0828

/* Block 17 -- Receive RAMbuffer 2 */
#define SK_RXRB2_START		0x0880
#define SK_RXRB2_END		0x0884
#define SK_RXRB2_WR_PTR		0x0888
#define SK_RXRB2_RD_PTR		0x088C
#define SK_RXRB2_UTHR_PAUSE	0x0890
#define SK_RXRB2_LTHR_PAUSE	0x0894
#define SK_RXRB2_UTHR_HIPRIO	0x0898
#define SK_RXRB2_UTHR_LOPRIO	0x089C
#define SK_RXRB2_PKTCNT		0x08A0
#define SK_RXRB2_LVL		0x08A4
#define SK_RXRB2_CTLTST		0x08A8

/* Block 20 -- Sync. Transmit RAMbuffer 1 */
#define SK_TXRBS1_START		0x0A00
#define SK_TXRBS1_END		0x0A04
#define SK_TXRBS1_WR_PTR	0x0A08
#define SK_TXRBS1_RD_PTR	0x0A0C
#define SK_TXRBS1_PKTCNT	0x0A20
#define SK_TXRBS1_LVL		0x0A24
#define SK_TXRBS1_CTLTST	0x0A28

/* Block 21 -- Async. Transmit RAMbuffer 1 */
#define SK_TXRBA1_START		0x0A80
#define SK_TXRBA1_END		0x0A84
#define SK_TXRBA1_WR_PTR	0x0A88
#define SK_TXRBA1_RD_PTR	0x0A8C
#define SK_TXRBA1_PKTCNT	0x0AA0
#define SK_TXRBA1_LVL		0x0AA4
#define SK_TXRBA1_CTLTST	0x0AA8

/* Block 22 -- Sync. Transmit RAMbuffer 2 */
#define SK_TXRBS2_START		0x0B00
#define SK_TXRBS2_END		0x0B04
#define SK_TXRBS2_WR_PTR	0x0B08
#define SK_TXRBS2_RD_PTR	0x0B0C
#define SK_TXRBS2_PKTCNT	0x0B20
#define SK_TXRBS2_LVL		0x0B24
#define SK_TXRBS2_CTLTST	0x0B28

/* Block 23 -- Async. Transmit RAMbuffer 2 */
#define SK_TXRBA2_START		0x0B80
#define SK_TXRBA2_END		0x0B84
#define SK_TXRBA2_WR_PTR	0x0B88
#define SK_TXRBA2_RD_PTR	0x0B8C
#define SK_TXRBA2_PKTCNT	0x0BA0
#define SK_TXRBA2_LVL		0x0BA4
#define SK_TXRBA2_CTLTST	0x0BA8

#define SK_RBCTL_RESET		0x00000001
#define SK_RBCTL_UNRESET	0x00000002
#define SK_RBCTL_OFF		0x00000004
#define SK_RBCTL_ON		0x00000008
#define SK_RBCTL_STORENFWD_OFF	0x00000010
#define SK_RBCTL_STORENFWD_ON	0x00000020

/* Block 24 -- RX MAC FIFO 1 regisrers and LINK_SYNC counter */
#define SK_RXF1_END		0x0C00
#define SK_RXF1_WPTR		0x0C04
#define SK_RXF1_RPTR		0x0C0C
#define SK_RXF1_PKTCNT		0x0C10
#define SK_RXF1_LVL		0x0C14
#define SK_RXF1_MACCTL		0x0C18
#define SK_RXF1_CTL		0x0C1C
#define SK_RXLED1_CNTINIT	0x0C20
#define SK_RXLED1_COUNTER	0x0C24
#define SK_RXLED1_CTL		0x0C28
#define SK_RXLED1_TST		0x0C29
#define SK_LINK_SYNC1_CINIT	0x0C30
#define SK_LINK_SYNC1_COUNTER	0x0C34
#define SK_LINK_SYNC1_CTL	0x0C38
#define SK_LINK_SYNC1_TST	0x0C39
#define SK_LINKLED1_CTL		0x0C3C

#define SK_FIFO_END		0x3F

/* Receive MAC FIFO 1 (Yukon Only) */
#define SK_RXMF1_END		0x0C40
#define SK_RXMF1_THRESHOLD	0x0C44
#define SK_RXMF1_CTRL_TEST	0x0C48
#define SK_RXMF1_WRITE_PTR	0x0C60
#define SK_RXMF1_WRITE_LEVEL	0x0C68
#define SK_RXMF1_READ_PTR	0x0C70
#define SK_RXMF1_READ_LEVEL	0x0C78

#define SK_RFCTL_WR_PTR_TST_ON	0x00004000	/* Write pointer test on*/
#define SK_RFCTL_WR_PTR_TST_OFF	0x00002000	/* Write pointer test off */
#define SK_RFCTL_WR_PTR_STEP	0x00001000	/* Write pointer increment */
#define SK_RFCTL_RD_PTR_TST_ON	0x00000400	/* Read pointer test on */
#define SK_RFCTL_RD_PTR_TST_OFF	0x00000200	/* Read pointer test off */
#define SK_RFCTL_RD_PTR_STEP	0x00000100	/* Read pointer increment */
#define SK_RFCTL_RX_FIFO_FLUSH  0x00000080      /* Linux: fifo flush */
#define SK_RFCTL_RX_FIFO_OVER	0x00000040	/* Clear IRQ RX FIFO Overrun */
#define SK_RFCTL_FRAME_RX_DONE	0x00000010	/* Clear IRQ Frame RX Done */
#define SK_RFCTL_OPERATION_ON	0x00000008	/* Operational mode on */
#define SK_RFCTL_OPERATION_OFF	0x00000004	/* Operational mode off */
#define SK_RFCTL_RESET_CLEAR	0x00000002	/* MAC FIFO Reset Clear */
#define SK_RFCTL_RESET_SET	0x00000001	/* MAC FIFO Reset Set */


/* Block 25 -- RX MAC FIFO 2 regisrers and LINK_SYNC counter */
#define SK_RXF2_END		0x0C80
#define SK_RXF2_WPTR		0x0C84
#define SK_RXF2_RPTR		0x0C8C
#define SK_RXF2_PKTCNT		0x0C90
#define SK_RXF2_LVL		0x0C94
#define SK_RXF2_MACCTL		0x0C98
#define SK_RXF2_CTL		0x0C9C
#define SK_RXLED2_CNTINIT	0x0CA0
#define SK_RXLED2_COUNTER	0x0CA4
#define SK_RXLED2_CTL		0x0CA8
#define SK_RXLED2_TST		0x0CA9
#define SK_LINK_SYNC2_CINIT	0x0CB0
#define SK_LINK_SYNC2_COUNTER	0x0CB4
#define SK_LINK_SYNC2_CTL	0x0CB8
#define SK_LINK_SYNC2_TST	0x0CB9
#define SK_LINKLED2_CTL		0x0CBC

#define SK_RXMACCTL_CLR_IRQ_NOSTS	0x00000001
#define SK_RXMACCTL_CLR_IRQ_NOTSTAMP	0x00000002
#define SK_RXMACCTL_TSTAMP_OFF		0x00000004
#define SK_RXMACCTL_RSTAMP_ON		0x00000008
#define SK_RXMACCTL_FLUSH_OFF		0x00000010
#define SK_RXMACCTL_FLUSH_ON		0x00000020
#define SK_RXMACCTL_PAUSE_OFF		0x00000040
#define SK_RXMACCTL_PAUSE_ON		0x00000080
#define SK_RXMACCTL_AFULL_OFF		0x00000100
#define SK_RXMACCTL_AFULL_ON		0x00000200
#define SK_RXMACCTL_VALIDTIME_PATCH_OFF	0x00000400
#define SK_RXMACCTL_VALIDTIME_PATCH_ON	0x00000800
#define SK_RXMACCTL_RXRDY_PATCH_OFF	0x00001000
#define SK_RXMACCTL_RXRDY_PATCH_ON	0x00002000
#define SK_RXMACCTL_STS_TIMEO		0x00FF0000
#define SK_RXMACCTL_TSTAMP_TIMEO	0xFF000000

#define SK_RXLEDCTL_ENABLE		0x0001
#define SK_RXLEDCTL_COUNTER_STOP	0x0002
#define SK_RXLEDCTL_COUNTER_START	0x0004

#define SK_LINKLED_OFF			0x0001
#define SK_LINKLED_ON			0x0002
#define SK_LINKLED_LINKSYNC_OFF		0x0004
#define SK_LINKLED_LINKSYNC_ON		0x0008
#define SK_LINKLED_BLINK_OFF		0x0010
#define SK_LINKLED_BLINK_ON		0x0020

/* Block 26 -- TX MAC FIFO 1 regisrers  */
#define SK_TXF1_END		0x0D00
#define SK_TXF1_WPTR		0x0D04
#define SK_TXF1_RPTR		0x0D0C
#define SK_TXF1_PKTCNT		0x0D10
#define SK_TXF1_LVL		0x0D14
#define SK_TXF1_MACCTL		0x0D18
#define SK_TXF1_CTL		0x0D1C
#define SK_TXLED1_CNTINIT	0x0D20
#define SK_TXLED1_COUNTER	0x0D24
#define SK_TXLED1_CTL		0x0D28
#define SK_TXLED1_TST		0x0D29

/* Receive MAC FIFO 1 (Yukon Only) */
#define SK_TXMF1_END		0x0D40
#define SK_TXMF1_THRESHOLD	0x0D44
#define SK_TXMF1_CTRL_TEST	0x0D48
#define SK_TXMF1_WRITE_PTR	0x0D60
#define SK_TXMF1_WRITE_SHADOW	0x0D64
#define SK_TXMF1_WRITE_LEVEL	0x0D68
#define SK_TXMF1_READ_PTR	0x0D70
#define SK_TXMF1_RESTART_PTR	0x0D74
#define SK_TXMF1_READ_LEVEL	0x0D78

#define SK_TFCTL_WR_PTR_TST_ON	0x00004000	/* Write pointer test on*/
#define SK_TFCTL_WR_PTR_TST_OFF	0x00002000	/* Write pointer test off */
#define SK_TFCTL_WR_PTR_STEP	0x00001000	/* Write pointer increment */
#define SK_TFCTL_RD_PTR_TST_ON	0x00000400	/* Read pointer test on */
#define SK_TFCTL_RD_PTR_TST_OFF	0x00000200	/* Read pointer test off */
#define SK_TFCTL_RD_PTR_STEP	0x00000100	/* Read pointer increment */
#define SK_TFCTL_TX_FIFO_UNDER	0x00000040	/* Clear IRQ TX FIFO Under */
#define SK_TFCTL_FRAME_TX_DONE	0x00000020	/* Clear IRQ Frame TX Done */
#define SK_TFCTL_IRQ_PARITY_ER	0x00000010	/* Clear IRQ Parity Error */
#define SK_TFCTL_OPERATION_ON	0x00000008	/* Operational mode on */
#define SK_TFCTL_OPERATION_OFF	0x00000004	/* Operational mode off */
#define SK_TFCTL_RESET_CLEAR	0x00000002	/* MAC FIFO Reset Clear */
#define SK_TFCTL_RESET_SET	0x00000001	/* MAC FIFO Reset Set */

/* Block 27 -- TX MAC FIFO 2 regisrers  */
#define SK_TXF2_END		0x0D80
#define SK_TXF2_WPTR		0x0D84
#define SK_TXF2_RPTR		0x0D8C
#define SK_TXF2_PKTCNT		0x0D90
#define SK_TXF2_LVL		0x0D94
#define SK_TXF2_MACCTL		0x0D98
#define SK_TXF2_CTL		0x0D9C
#define SK_TXLED2_CNTINIT	0x0DA0
#define SK_TXLED2_COUNTER	0x0DA4
#define SK_TXLED2_CTL		0x0DA8
#define SK_TXLED2_TST		0x0DA9

#define SK_TXMACCTL_XMAC_RESET		0x00000001
#define SK_TXMACCTL_XMAC_UNRESET	0x00000002
#define SK_TXMACCTL_LOOP_OFF		0x00000004
#define SK_TXMACCTL_LOOP_ON		0x00000008
#define SK_TXMACCTL_FLUSH_OFF		0x00000010
#define SK_TXMACCTL_FLUSH_ON		0x00000020
#define SK_TXMACCTL_WAITEMPTY_OFF	0x00000040
#define SK_TXMACCTL_WAITEMPTY_ON	0x00000080
#define SK_TXMACCTL_AFULL_OFF		0x00000100
#define SK_TXMACCTL_AFULL_ON		0x00000200
#define SK_TXMACCTL_TXRDY_PATCH_OFF	0x00000400
#define SK_TXMACCTL_RXRDY_PATCH_ON	0x00000800
#define SK_TXMACCTL_PKT_RECOVERY_OFF	0x00001000
#define SK_TXMACCTL_PKT_RECOVERY_ON	0x00002000
#define SK_TXMACCTL_CLR_IRQ_PERR	0x00008000
#define SK_TXMACCTL_WAITAFTERFLUSH	0x00010000

#define SK_TXLEDCTL_ENABLE		0x0001
#define SK_TXLEDCTL_COUNTER_STOP	0x0002
#define SK_TXLEDCTL_COUNTER_START	0x0004

#define SK_FIFO_RESET		0x00000001
#define SK_FIFO_UNRESET		0x00000002
#define SK_FIFO_OFF		0x00000004
#define SK_FIFO_ON		0x00000008

/* Block 28 -- Descriptor Poll Timer */
#define SK_DPT_INIT		0x0e00	/* Initial value 24 bits */
#define SK_DPT_TIMER		0x0e04	/* Mul of 78.12MHz clk (24b) */

#define SK_DPT_TIMER_CTRL	0x0e08	/* Timer Control 16 bits */
#define SK_DPT_TCTL_STOP	0x0001	/* Stop Timer */
#define SK_DPT_TCTL_START	0x0002	/* Start Timer */

#define SK_DPT_TIMER_TEST	0x0e0a	/* Timer Test 16 bits */
#define SK_DPT_TTEST_STEP	0x0001	/* Timer Decrement */
#define SK_DPT_TTEST_OFF	0x0002	/* Test Mode Off */
#define SK_DPT_TTEST_ON		0x0004	/* Test Mode On */

/* Block 29 -- reserved */

/* Block 30 -- GMAC/GPHY Control Registers (Yukon Only)*/
#define SK_GMAC_CTRL		0x0f00	/* GMAC Control Register */
#define SK_GPHY_CTRL		0x0f04	/* GPHY Control Register */
#define SK_GMAC_ISR		0x0f08	/* GMAC Interrupt Source Register */
#define SK_GMAC_IMR		0x0f08	/* GMAC Interrupt Mask Register */
#define SK_LINK_CTRL		0x0f10	/* Link Control Register (LCR) */
#define SK_WOL_CTRL		0x0f20	/* Wake on LAN Control Register */
#define SK_MAC_ADDR_LOW		0x0f24	/* Mack Address Registers LOW */
#define SK_MAC_ADDR_HIGH	0x0f28	/* Mack Address Registers HIGH */
#define SK_PAT_READ_PTR		0x0f2c	/* Pattern Read Pointer Register */
#define SK_PAT_LEN_REG0		0x0f30	/* Pattern Length Register 0 */
#define SK_PAT_LEN0		0x0f30	/* Pattern Length 0 */
#define SK_PAT_LEN1		0x0f31	/* Pattern Length 1 */
#define SK_PAT_LEN2		0x0f32	/* Pattern Length 2 */
#define SK_PAT_LEN3		0x0f33	/* Pattern Length 3 */
#define SK_PAT_LEN_REG1		0x0f34	/* Pattern Length Register 1 */
#define SK_PAT_LEN4		0x0f34	/* Pattern Length 4 */
#define SK_PAT_LEN5		0x0f35	/* Pattern Length 5 */
#define SK_PAT_LEN6		0x0f36	/* Pattern Length 6 */
#define SK_PAT_LEN7		0x0f37	/* Pattern Length 7 */
#define SK_PAT_CTR_REG0		0x0f38	/* Pattern Counter Register 0 */
#define SK_PAT_CTR0		0x0f38	/* Pattern Counter 0 */
#define SK_PAT_CTR1		0x0f39	/* Pattern Counter 1 */
#define SK_PAT_CTR2		0x0f3a	/* Pattern Counter 2 */
#define SK_PAT_CTR3		0x0f3b	/* Pattern Counter 3 */
#define SK_PAT_CTR_REG1		0x0f3c	/* Pattern Counter Register 1 */
#define SK_PAT_CTR4		0x0f3c	/* Pattern Counter 4 */
#define SK_PAT_CTR5		0x0f3d	/* Pattern Counter 5 */
#define SK_PAT_CTR6		0x0f3e	/* Pattern Counter 6 */
#define SK_PAT_CTR7		0x0f3f	/* Pattern Counter 7 */

#define SK_GMAC_LOOP_ON		0x00000020	/* Loopback mode for testing */
#define SK_GMAC_LOOP_OFF	0x00000010	/* purposes */
#define SK_GMAC_PAUSE_ON	0x00000008	/* enable forward of pause */
#define SK_GMAC_PAUSE_OFF	0x00000004	/* signal to GMAC */
#define SK_GMAC_RESET_CLEAR	0x00000002	/* Clear GMAC Reset */
#define SK_GMAC_RESET_SET	0x00000001	/* Set GMAC Reset */

#define SK_GPHY_SEL_BDT		0x10000000	/* Select Bidirectional xfer */
#define SK_GPHY_INT_POL_HI	0x08000000	/* IRQ Polarity Active */
#define SK_GPHY_75_OHM		0x04000000	/* Use 75 Ohm Termination */
#define SK_GPHY_DIS_FC		0x02000000	/* Disable Auto Fiber/Copper */
#define SK_GPHY_DIS_SLEEP	0x01000000	/* Disable Energy Detect */
#define SK_GPHY_HWCFG_M_3	0x00800000	/* HWCFG_MODE[3] */
#define SK_GPHY_HWCFG_M_2	0x00400000	/* HWCFG_MODE[2] */
#define SK_GPHY_HWCFG_M_1	0x00200000	/* HWCFG_MODE[1] */
#define SK_GPHY_HWCFG_M_0	0x00100000	/* HWCFG_MODE[0] */
#define SK_GPHY_ANEG_0		0x00080000	/* ANEG[0] */
#define SK_GPHY_ENA_XC		0x00040000	/* Enable MDI Crossover */
#define SK_GPHY_DIS_125		0x00020000	/* Disable 125MHz Clock */
#define SK_GPHY_ANEG_3		0x00010000	/* ANEG[3] */
#define SK_GPHY_ANEG_2		0x00008000	/* ANEG[2] */
#define SK_GPHY_ANEG_1		0x00004000	/* ANEG[1] */
#define SK_GPHY_ENA_PAUSE	0x00002000	/* Enable Pause */
#define SK_GPHY_PHYADDR_4	0x00001000	/* Bit 4 of Phy Addr */
#define SK_GPHY_PHYADDR_3	0x00000800	/* Bit 3 of Phy Addr */
#define SK_GPHY_PHYADDR_2	0x00000400	/* Bit 2 of Phy Addr */
#define SK_GPHY_PHYADDR_1	0x00000200	/* Bit 1 of Phy Addr */
#define SK_GPHY_PHYADDR_0	0x00000100	/* Bit 0 of Phy Addr */
#define SK_GPHY_RESET_CLEAR	0x00000002	/* Clear GPHY Reset */
#define SK_GPHY_RESET_SET	0x00000001	/* Set GPHY Reset */

#define SK_GPHY_COPPER		(SK_GPHY_HWCFG_M_0 | SK_GPHY_HWCFG_M_1 | \
				 SK_GPHY_HWCFG_M_2 | SK_GPHY_HWCFG_M_3 )
#define SK_GPHY_FIBER		(SK_GPHY_HWCFG_M_0 | SK_GPHY_HWCFG_M_1 | \
				 SK_GPHY_HWCFG_M_2 )
#define SK_GPHY_ANEG_ALL	(SK_GPHY_ANEG_0 | SK_GPHY_ANEG_1 | \
				 SK_GPHY_ANEG_2 | SK_GPHY_ANEG_3 )

#define SK_GMAC_INT_TX_OFLOW	0x20	/* Transmit Counter Overflow */
#define SK_GMAC_INT_RX_OFLOW	0x10	/* Receiver Overflow */
#define SK_GMAC_INT_TX_UNDER	0x08	/* Transmit FIFO Underrun */
#define SK_GMAC_INT_TX_DONE	0x04	/* Transmit Complete */
#define SK_GMAC_INT_RX_OVER	0x02	/* Receive FIFO Overrun */
#define SK_GMAC_INT_RX_DONE	0x01	/* Receive Complete */

#define SK_LINK_RESET_CLEAR	0x0002	/* Link Reset Clear */
#define SK_LINK_RESET_SET	0x0001	/* Link Reset Set */

/* Block 31 -- reserved */

/* Block 32-33 -- Pattern Ram */
#define SK_WOL_PRAM		0x1000

/* Block 0x22 - 0x3f -- reserved */

/* Block 0x40 to 0x4F -- XMAC 1 registers */
#define SK_XMAC1_BASE	0x2000

/* Block 0x50 to 0x5F -- MARV 1 registers */
#define SK_MARV1_BASE	0x2800

/* Block 0x60 to 0x6F -- XMAC 2 registers */
#define SK_XMAC2_BASE	0x3000

/* Block 0x70 to 0x7F -- MARV 2 registers */
#define SK_MARV2_BASE	0x3800

/* Compute relative offset of an XMAC register in the XMAC window(s). */
#define SK_XMAC_REG(sc, reg)	(((reg) * 2) + SK_XMAC1_BASE + \
	(((sc)->sk_port) * (SK_XMAC2_BASE - SK_XMAC1_BASE)))

#if 0
#define SK_XM_READ_4(sc, reg)						\
	((sk_win_read_2(sc->sk_softc,					\
	      SK_XMAC_REG(sc, reg)) & 0xFFFF) |		\
	 ((sk_win_read_2(sc->sk_softc,					\
	      SK_XMAC_REG(sc, reg + 2)) & 0xFFFF) << 16))

#define SK_XM_WRITE_4(sc, reg, val)					\
	sk_win_write_2(sc->sk_softc, SK_XMAC_REG(sc, reg),		\
		       ((val) & 0xFFFF));				\
	sk_win_write_2(sc->sk_softc, SK_XMAC_REG(sc, reg + 2),		\
		       ((val) >> 16) & 0xFFFF)
#else
#define SK_XM_READ_4(sc, reg)		\
	sk_win_read_4(sc->sk_softc, SK_XMAC_REG(sc, reg))

#define SK_XM_WRITE_4(sc, reg, val)	\
	sk_win_write_4(sc->sk_softc, SK_XMAC_REG(sc, reg), (val))
#endif

#define SK_XM_READ_2(sc, reg)		\
	sk_win_read_2(sc->sk_softc, SK_XMAC_REG(sc, reg))

#define SK_XM_WRITE_2(sc, reg, val)	\
	sk_win_write_2(sc->sk_softc, SK_XMAC_REG(sc, reg), val)

#define SK_XM_SETBIT_4(sc, reg, x)	\
	SK_XM_WRITE_4(sc, reg, (SK_XM_READ_4(sc, reg)) | (x))

#define SK_XM_CLRBIT_4(sc, reg, x)	\
	SK_XM_WRITE_4(sc, reg, (SK_XM_READ_4(sc, reg)) & ~(x))

#define SK_XM_SETBIT_2(sc, reg, x)	\
	SK_XM_WRITE_2(sc, reg, (SK_XM_READ_2(sc, reg)) | (x))

#define SK_XM_CLRBIT_2(sc, reg, x)	\
	SK_XM_WRITE_2(sc, reg, (SK_XM_READ_2(sc, reg)) & ~(x))

#ifndef YUKONOSX
/* Compute relative offset of an MARV register in the MARV window(s). */
#define SK_YU_REG(sc, reg) \
	((reg) + SK_MARV1_BASE + \
	(((sc)->sk_port) * (SK_MARV2_BASE - SK_MARV1_BASE)))

#define SK_YU_READ_4(sc, reg)		\
	sk_win_read_4((sc)->sk_softc, SK_YU_REG((sc), (reg)))

#define SK_YU_READ_2(sc, reg)		\
	sk_win_read_2((sc)->sk_softc, SK_YU_REG((sc), (reg)))

#define SK_YU_WRITE_4(sc, reg, val)	\
	sk_win_write_4((sc)->sk_softc, SK_YU_REG((sc), (reg)), (val))

#define SK_YU_WRITE_2(sc, reg, val)	\
	sk_win_write_2((sc)->sk_softc, SK_YU_REG((sc), (reg)), (val))

#define SK_YU_SETBIT_4(sc, reg, x)	\
	SK_YU_WRITE_4(sc, reg, (SK_YU_READ_4(sc, reg)) | (x))

#define SK_YU_CLRBIT_4(sc, reg, x)	\
	SK_YU_WRITE_4(sc, reg, (SK_YU_READ_4(sc, reg)) & ~(x))

#define SK_YU_SETBIT_2(sc, reg, x)	\
	SK_YU_WRITE_2(sc, reg, (SK_YU_READ_2(sc, reg)) | (x))

#define SK_YU_CLRBIT_2(sc, reg, x)	\
	SK_YU_WRITE_2(sc, reg, (SK_YU_READ_2(sc, reg)) & ~(x))
#else	/*YUKONOSX*/
/* Compute relative offset of an MARV register in the MARV window(s). */
#define SK_YU_REG(sc, reg) \
	((reg) + SK_MARV1_BASE + \
	((0) * (SK_MARV2_BASE - SK_MARV1_BASE)))

#define SK_YU_READ_4(sc, reg)		\
	sk_win_read_4(0, SK_YU_REG((sc), (reg)))

#define SK_YU_READ_2(sc, reg)		\
	sk_win_read_2(0, SK_YU_REG((sc), (reg)))

#define SK_YU_WRITE_4(sc, reg, val)	\
	sk_win_write_4(0, SK_YU_REG((sc), (reg)), (val))

#define SK_YU_WRITE_2(sc, reg, val)	\
	sk_win_write_2(0, SK_YU_REG((sc), (reg)), (val))

#define SK_YU_WRITE_1(sc, reg, val)	\
	sk_win_write_1(0, SK_YU_REG((sc), (reg)), (val))

#define SK_YU_SETBIT_4(sc, reg, x)	\
	SK_YU_WRITE_4(sc, reg, (SK_YU_READ_4(sc, reg)) | (x))

#define SK_YU_CLRBIT_4(sc, reg, x)	\
	SK_YU_WRITE_4(sc, reg, (SK_YU_READ_4(sc, reg)) & ~(x))

#define SK_YU_SETBIT_2(sc, reg, x)	\
	SK_YU_WRITE_2(sc, reg, (SK_YU_READ_2(sc, reg)) | (x))

#define SK_YU_CLRBIT_2(sc, reg, x)	\
	SK_YU_WRITE_2(sc, reg, (SK_YU_READ_2(sc, reg)) & ~(x))
#endif

/*
 * The default FIFO threshold on the XMAC II is 4 bytes. On
 * dual port NICs, this often leads to transmit underruns, so we
 * bump the threshold a little.
 */
#define SK_XM_TX_FIFOTHRESH	512

#define SK_PCI_VENDOR_ID	0x0000
#define SK_PCI_DEVICE_ID	0x0002
#define SK_PCI_COMMAND		0x0004
#define SK_PCI_STATUS		0x0006
#define SK_PCI_REVID		0x0008
#define SK_PCI_CLASSCODE	0x0009
#define SK_PCI_CACHELEN		0x000C
#define SK_PCI_LATENCY_TIMER	0x000D
#define SK_PCI_HEADER_TYPE	0x000E
#define SK_PCI_LOMEM		0x0010
#define SK_PCI_LOIO		0x0014
#define SK_PCI_SUBVEN_ID	0x002C
#define SK_PCI_SYBSYS_ID	0x002E
#define SK_PCI_BIOSROM		0x0030
#define SK_PCI_INTLINE		0x003C
#define SK_PCI_INTPIN		0x003D
#define SK_PCI_MINGNT		0x003E
#define SK_PCI_MINLAT		0x003F

/* device specific PCI registers */
#define SK_PCI_OURREG1		0x0040
#define SK_PCI_OURREG2		0x0044
#define SK_PCI_CAPID		0x0048 /* 8 bits */
#define SK_PCI_NEXTPTR		0x0049 /* 8 bits */
#define SK_PCI_PWRMGMTCAP	0x004A /* 16 bits */
#define SK_PCI_PWRMGMTCTRL	0x004C /* 16 bits */
#define SK_PCI_PME_EVENT	0x004F

#define SK_PSTATE_MASK		0x0003
#define SK_PSTATE_D0		0x0000
#define SK_PSTATE_D1		0x0001
#define SK_PSTATE_D2		0x0002
#define SK_PSTATE_D3		0x0003
#define SK_PME_EN		0x0010
#define SK_PME_STATUS		0x8000

#ifndef YUKONOSX
#define CSR_WRITE_4(sc, reg, val) \
	bus_space_write_4((sc)->sk_btag, (sc)->sk_bhandle, (reg), (val))
#define CSR_WRITE_2(sc, reg, val) \
	bus_space_write_2((sc)->sk_btag, (sc)->sk_bhandle, (reg), (val))
#define CSR_WRITE_1(sc, reg, val) \
	bus_space_write_1((sc)->sk_btag, (sc)->sk_bhandle, (reg), (val))
 
#define CSR_READ_4(sc, reg) \
	bus_space_read_4((sc)->sk_btag, (sc)->sk_bhandle, (reg))
#define CSR_READ_2(sc, reg) \
	bus_space_read_2((sc)->sk_btag, (sc)->sk_bhandle, (reg))
#define CSR_READ_1(sc, reg) \
	bus_space_read_1((sc)->sk_btag, (sc)->sk_bhandle, (reg))

#else
#define CSR_WRITE_4(sc, reg, val) \
	bus_space_write_4(0 ,csrBase, (reg), (val)) 
#define CSR_WRITE_2(sc, reg, val) \
	bus_space_write_2(0, csrBase, (reg), (val))
#define CSR_WRITE_1(sc, reg, val) \
	bus_space_write_1(0, csrBase, (reg), (val))

#define CSR_READ_4(sc, reg) \
	bus_space_read_4(0, csrBase, (reg))
#define CSR_READ_2(sc, reg) \
	bus_space_read_2(0, csrBase, (reg)) 
#define CSR_READ_1(sc, reg) \
	bus_space_read_1(0, csrBase, (reg)) 
#endif

struct sk_type {
	u_int16_t		sk_vid;
	u_int16_t		sk_did;
	char			*sk_name;
};

/* RX queue descriptor data structure */
struct sk_rx_desc {
	u_int32_t		sk_ctl;
	u_int32_t		sk_next;
	u_int32_t		sk_data_lo;
	u_int32_t		sk_data_hi;
	u_int32_t		sk_xmac_rxstat;
	u_int32_t		sk_timestamp;
	u_int16_t		sk_csum2;
	u_int16_t		sk_csum1;
	u_int16_t		sk_csum2_start;
	u_int16_t		sk_csum1_start;
};

#define SK_OPCODE_DEFAULT	0x00550000
#define SK_OPCODE_CSUM		0x00560000

#define SK_RXCTL_LEN		0x0000FFFF
#define SK_RXCTL_OPCODE		0x00FF0000
#define SK_RXCTL_TSTAMP_VALID	0x01000000
#define SK_RXCTL_STATUS_VALID	0x02000000
#define SK_RXCTL_DEV0		0x04000000
#define SK_RXCTL_EOF_INTR	0x08000000
#define SK_RXCTL_EOB_INTR	0x10000000
#define SK_RXCTL_LASTFRAG	0x20000000
#define SK_RXCTL_FIRSTFRAG	0x40000000
#define SK_RXCTL_OWN		0x80000000

#define SK_RXSTAT	\
	(SK_OPCODE_DEFAULT|SK_RXCTL_EOF_INTR|SK_RXCTL_LASTFRAG| \
	 SK_RXCTL_FIRSTFRAG|SK_RXCTL_OWN)

struct sk_tx_desc {
	u_int32_t		sk_ctl;
	u_int32_t		sk_next;
	u_int32_t		sk_data_lo;
	u_int32_t		sk_data_hi;
	u_int32_t		sk_xmac_txstat;
	u_int16_t		sk_rsvd0;
	u_int16_t		sk_csum_startval;
	u_int16_t		sk_csum_startpos;
	u_int16_t		sk_csum_writepos;
	u_int32_t		sk_rsvd1;
};

#define SK_TXCTL_LEN		0x0000FFFF
#define SK_TXCTL_OPCODE		0x00FF0000
#define SK_TXCTL_SW		0x01000000
#define SK_TXCTL_NOCRC		0x02000000
#define SK_TXCTL_STORENFWD	0x04000000
#define SK_TXCTL_EOF_INTR	0x08000000
#define SK_TXCTL_EOB_INTR	0x10000000
#define SK_TXCTL_LASTFRAG	0x20000000
#define SK_TXCTL_FIRSTFRAG	0x40000000
#define SK_TXCTL_OWN		0x80000000

#define SK_TXSTAT	\
	(SK_OPCODE_DEFAULT|SK_TXCTL_EOF_INTR|SK_TXCTL_LASTFRAG|SK_TXCTL_OWN)

#define SK_RXBYTES(x)		(x) & 0x0000FFFF;
#define SK_TXBYTES		SK_RXBYTES

#define SK_TX_RING_CNT		512
#define SK_RX_RING_CNT		256

/*
 * Jumbo buffer stuff. Note that we must allocate more jumbo
 * buffers than there are descriptors in the receive ring. This
 * is because we don't know how long it will take for a packet
 * to be released after we hand it off to the upper protocol
 * layers. To be safe, we allocate 1.5 times the number of
 * receive descriptors.
 */
#ifdef __sparc64__
#define SK_JSLOTS		54
#else
#define SK_JSLOTS		384
#endif

#define SK_JRAWLEN	(ETHER_MAX_LEN_JUMBO + ETHER_ALIGN)
#define SK_JLEN		SK_JRAWLEN
#define SK_MCLBYTES	SK_JLEN
#define SK_JPAGESZ	PAGE_SIZE
#define SK_RESID	(SK_JPAGESZ - (SK_JLEN * SK_JSLOTS) % SK_JPAGESZ)
#define SK_JMEM		((SK_JLEN * SK_JSLOTS) + SK_RESID)

#define SK_MAXUNIT	256
#define SK_TIMEOUT	1000

/* YUKON registers */

/* General Purpose Status Register (GPSR) */
#define YUKON_GPSR		0x0000

#define YU_GPSR_SPEED		0x8000	/* speed 0 - 10Mbps, 1 - 100Mbps */
#define YU_GPSR_DUPLEX		0x4000	/* 0 - half duplex, 1 - full duplex */
#define YU_GPSR_FCTL_TX		0x2000	/* flow control */
#define YU_GPSR_LINK		0x1000	/* link status (down/up) */
#define YU_GPSR_PAUSE		0x0800	/* flow control enable/disable */
#define YU_GPSR_TX_IN_PROG	0x0400	/* transmit in progress */
#define YU_GPSR_EXCESS_COL	0x0200	/* excessive collisions occurred */
#define YU_GPSR_LATE_COL	0x0100	/* late collision occurred */
#define YU_GPSR_MII_PHY_STC	0x0020	/* MII PHY status change */
#define YU_GPSR_GIG_SPEED	0x0010	/* Gigabit Speed (0 - use speed bit) */
#define YU_GPSR_PARTITION	0x0008	/* partition mode */
#define YU_GPSR_FCTL_RX		0x0004	/* flow control enable/disable */
#define YU_GPSR_PROMS_EN	0x0002	/* promiscuous mode enable/disable */

/* General Purpose Control Register (GPCR) */
#define YUKON_GPCR		0x0004

#define YU_GPCR_FCTL_TX		0x2000	/* Transmit flow control 802.3x */
#define YU_GPCR_TXEN		0x1000	/* Transmit Enable */
#define YU_GPCR_RXEN		0x0800	/* Receive Enable */
#define YU_GPCR_LPBK		0x0200	/* Loopback Enable */
#define YU_GPCR_PAR		0x0100	/* Partition Enable */
#define YU_GPCR_GIG		0x0080	/* Gigabit Speed */
#define YU_GPCR_FLP		0x0040	/* Force Link Pass */
#define YU_GPCR_DUPLEX		0x0020	/* Duplex Enable */
#define YU_GPCR_FCTL_RX		0x0010	/* Receive flow control 802.3x */
#define YU_GPCR_SPEED		0x0008	/* Port Speed */
#define YU_GPCR_DPLX_EN		0x0004	/* Enable Auto-Update for duplex */
#define YU_GPCR_FCTL_EN		0x0002	/* Enabel Auto-Update for 802.3x */
#define YU_GPCR_SPEED_EN	0x0001	/* Enable Auto-Update for speed */

/* Transmit Control Register (TCR) */
#define YUKON_TCR		0x0008

#define YU_TCR_FJ		0x8000	/* force jam / flow control */
#define YU_TCR_CRCD		0x4000	/* insert CRC (0 - enable) */
#define YU_TCR_PADD		0x2000	/* pad packets to 64b (0 - enable) */
#define YU_TCR_COLTH		0x1c00	/* collision threshold */

/* Receive Control Register (RCR) */
#define YUKON_RCR		0x000c

#define YU_RCR_UFLEN		0x8000	/* unicast filter enable */
#define YU_RCR_MUFLEN		0x4000	/* multicast filter enable */
#define YU_RCR_CRCR		0x2000	/* remove CRC */
#define YU_RCR_PASSFC		0x1000	/* pass flow control packets */

/* Transmit Flow Control Register (TFCR) */
#define YUKON_TFCR		0x0010	/* Pause Time */

/* Transmit Parameter Register (TPR) */
#define YUKON_TPR		0x0014

#define YU_TPR_JAM_LEN(x)	(((x) & 0x3) << 14)
#define YU_TPR_JAM_IPG(x)	(((x) & 0x1f) << 9)
#define YU_TPR_JAM2DATA_IPG(x)	(((x) & 0x1f) << 4)

/* Serial Mode Register (SMR) */
#define YUKON_SMR		0x0018

#define YU_SMR_DATA_BLIND(x)	(((x) & 0x1f) << 11)
#define YU_SMR_LIMIT4		0x0400	/* reset after 16 / 4 collisions */
#define YU_SMR_MFL_JUMBO	0x0100	/* max frame length for jumbo frames */
#define YU_SMR_MFL_VLAN		0x0200	/* max frame length + vlan tag */
#define YU_SMR_IPG_DATA(x)	((x) & 0x1f)

/* Source Address Low #1 (SAL1) */
#define YUKON_SAL1		0x001c	/* SA1[15:0] */

/* Source Address Middle #1 (SAM1) */
#define YUKON_SAM1		0x0020	/* SA1[31:16] */

/* Source Address High #1 (SAH1) */
#define YUKON_SAH1		0x0024	/* SA1[47:32] */

/* Source Address Low #2 (SAL2) */
#define YUKON_SAL2		0x0028	/* SA2[15:0] */

/* Source Address Middle #2 (SAM2) */
#define YUKON_SAM2		0x002c	/* SA2[31:16] */

/* Source Address High #2 (SAH2) */
#define YUKON_SAH2		0x0030	/* SA2[47:32] */

/* Multicatst Address Hash Register 1 (MCAH1) */
#define YUKON_MCAH1		0x0034

/* Multicatst Address Hash Register 2 (MCAH2) */
#define YUKON_MCAH2		0x0038

/* Multicatst Address Hash Register 3 (MCAH3) */
#define YUKON_MCAH3		0x003c

/* Multicatst Address Hash Register 4 (MCAH4) */
#define YUKON_MCAH4		0x0040

/* Transmit Interrupt Register (TIR) */
#define YUKON_TIR		0x0044

#define YU_TIR_OUT_UNICAST	0x0001	/* Num Unicast Packets Transmitted */
#define YU_TIR_OUT_BROADCAST	0x0002	/* Num Broadcast Packets Transmitted */
#define YU_TIR_OUT_PAUSE	0x0004	/* Num Pause Packets Transmitted */
#define YU_TIR_OUT_MULTICAST	0x0008	/* Num Multicast Packets Transmitted */
#define YU_TIR_OUT_OCTETS	0x0030	/* Num Bytes Transmitted */
#define YU_TIR_OUT_64_OCTETS	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_127_OCTETS	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_255_OCTETS	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_511_OCTETS	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_1023_OCTETS	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_1518_OCTETS	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_MAX_OCTETS	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_SPARE	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_COLLISIONS	0x0000	/* Num Packets Transmitted */
#define YU_TIR_OUT_LATE		0x0000	/* Num Packets Transmitted */

/* Receive Interrupt Register (RIR) */
#define YUKON_RIR		0x0048

/* Transmit and Receive Interrupt Register (TRIR) */
#define YUKON_TRIR		0x004c

/* Transmit Interrupt Mask Register (TIMR) */
#define YUKON_TIMR		0x0050

/* Receive Interrupt Mask Register (RIMR) */
#define YUKON_RIMR		0x0054

/* Transmit and Receive Interrupt Mask Register (TRIMR) */
#define YUKON_TRIMR		0x0058

/* SMI Control Register (SMICR) */
#define YUKON_SMICR		0x0080

#define YU_SMICR_PHYAD(x)	(((x) & 0x1f) << 11)
#define YU_SMICR_REGAD(x)	(((x) & 0x1f) << 6)
#define YU_SMICR_OPCODE		0x0020	/* opcode (0 - write, 1 - read) */
#define YU_SMICR_OP_READ	0x0020	/* opcode read */
#define YU_SMICR_OP_WRITE	0x0000	/* opcode write */
#define YU_SMICR_READ_VALID	0x0010	/* read valid */
#define YU_SMICR_BUSY		0x0008	/* busy (writing) */

/* SMI Data Register (SMIDR) */
#define YUKON_SMIDR		0x0084

/* PHY Addres Register (PAR) */
#define YUKON_PAR		0x0088

#define YU_PAR_MIB_CLR		0x0020	/* MIB Counters Clear Mode */
#define YU_PAR_LOAD_TSTCNT	0x0010	/* Load count 0xfffffff0 into cntr */

/*
 * Registers and data structures for the XaQti Corporation XMAC II
 * Gigabit Ethernet MAC. Datasheet is available from http://www.xaqti.com.
 * The XMAC can be programmed for 16-bit or 32-bit register access modes.
 * The SysKonnect gigabit ethernet adapters use 16-bit mode, so that's
 * how the registers are laid out here.
 */

#define XM_DEVICEID		0x00E0AE20
#define XM_XAQTI_OUI		0x00E0AE

#define XM_XMAC_REV(x)		(((x) & 0x000000E0) >> 5)

#define XM_XMAC_REV_B2		0x0
#define XM_XMAC_REV_C1		0x1

#define XM_MMUCMD		0x0000
#define XM_POFF			0x0008
#define XM_BURST		0x000C
#define XM_VLAN_TAGLEV1		0x0010
#define XM_VLAN_TAGLEV2		0x0014
#define XM_TXCMD		0x0020
#define XM_TX_RETRYLIMIT	0x0024
#define XM_TX_SLOTTIME		0x0028
#define XM_TX_IPG		0x003C
#define XM_RXCMD		0x0030
#define XM_PHY_ADDR		0x0034
#define XM_PHY_DATA		0x0038
#define XM_GPIO			0x0040
#define XM_IMR			0x0044
#define XM_ISR			0x0048
#define XM_HWCFG		0x004C
#define XM_TX_LOWAT		0x0060
#define XM_TX_HIWAT		0x0062
#define XM_TX_REQTHRESH_LO	0x0064
#define XM_TX_REQTHRESH_HI	0x0066
#define XM_TX_REQTHRESH		XM_TX_REQTHRESH_LO
#define XM_PAUSEDST0		0x0068
#define XM_PAUSEDST1		0x006A
#define XM_PAUSEDST2		0x006C
#define XM_CTLPARM_LO		0x0070
#define XM_CTLPARM_HI		0x0072
#define XM_CTLPARM		XM_CTLPARM_LO
#define XM_OPCODE_PAUSE_TIMER	0x0074
#define XM_TXSTAT_LIFO		0x0078

/*
 * Perfect filter registers. The XMAC has a table of 16 perfect
 * filter entries, spaced 8 bytes apart. This is in addition to
 * the station address registers, which appear below.
 */
#define XM_RXFILT_BASE		0x0080
#define XM_RXFILT_END		0x0107
#define XM_RXFILT_MAX		16
#define XM_RXFILT_ENTRY(ent)		(XM_RXFILT_BASE + ((ent * 8)))

/* Primary station address. */
#define XM_PAR0			0x0108
#define XM_PAR1			0x010A
#define XM_PAR2			0x010C

/* 64-bit multicast hash table registers */
#define XM_MAR0			0x0110
#define XM_MAR1			0x0112
#define XM_MAR2			0x0114
#define XM_MAR3			0x0116
#define XM_RX_LOWAT		0x0118
#define XM_RX_HIWAT		0x011A
#define XM_RX_REQTHRESH_LO	0x011C
#define XM_RX_REQTHRESH_HI	0x011E
#define XM_RX_REQTHRESH		XM_RX_REQTHRESH_LO
#define XM_DEVID_LO		0x0120
#define XM_DEVID_HI		0x0122
#define XM_DEVID		XM_DEVID_LO
#define XM_MODE_LO		0x0124
#define XM_MODE_HI		0x0126
#define XM_MODE			XM_MODE_LO
#define XM_LASTSRC0		0x0128
#define XM_LASTSRC1		0x012A
#define XM_LASTSRC2		0x012C
#define XM_TSTAMP_READ		0x0130
#define XM_TSTAMP_LOAD		0x0134
#define XM_STATS_CMD		0x0200
#define XM_RXCNT_EVENT_LO	0x0204
#define XM_RXCNT_EVENT_HI	0x0206
#define XM_RXCNT_EVENT		XM_RXCNT_EVENT_LO
#define XM_TXCNT_EVENT_LO	0x0208
#define XM_TXCNT_EVENT_HI	0x020A
#define XM_TXCNT_EVENT		XM_TXCNT_EVENT_LO
#define XM_RXCNT_EVMASK_LO	0x020C
#define XM_RXCNT_EVMASK_HI	0x020E
#define XM_RXCNT_EVMASK		XM_RXCNT_EVMASK_LO
#define XM_TXCNT_EVMASK_LO	0x0210
#define XM_TXCNT_EVMASK_HI	0x0212
#define XM_TXCNT_EVMASK		XM_TXCNT_EVMASK_LO

/* Statistics command register */
#define XM_STATCMD_CLR_TX	0x0001
#define XM_STATCMD_CLR_RX	0x0002
#define XM_STATCMD_COPY_TX	0x0004
#define XM_STATCMD_COPY_RX	0x0008
#define XM_STATCMD_SNAP_TX	0x0010
#define XM_STATCMD_SNAP_RX	0x0020

/* TX statistics registers */
#define XM_TXSTATS_PKTSOK	0x280
#define XM_TXSTATS_BYTESOK_HI	0x284
#define XM_TXSTATS_BYTESOK_LO	0x288
#define XM_TXSTATS_BCASTSOK	0x28C
#define XM_TXSTATS_MCASTSOK	0x290
#define XM_TXSTATS_UCASTSOK	0x294
#define XM_TXSTATS_GIANTS	0x298
#define XM_TXSTATS_BURSTCNT	0x29C
#define XM_TXSTATS_PAUSEPKTS	0x2A0
#define XM_TXSTATS_MACCTLPKTS	0x2A4
#define XM_TXSTATS_SINGLECOLS	0x2A8
#define XM_TXSTATS_MULTICOLS	0x2AC
#define XM_TXSTATS_EXCESSCOLS	0x2B0
#define XM_TXSTATS_LATECOLS	0x2B4
#define XM_TXSTATS_DEFER	0x2B8
#define XM_TXSTATS_EXCESSDEFER	0x2BC
#define XM_TXSTATS_UNDERRUN	0x2C0
#define XM_TXSTATS_CARRIERSENSE	0x2C4
#define XM_TXSTATS_UTILIZATION	0x2C8
#define XM_TXSTATS_64		0x2D0
#define XM_TXSTATS_65_127	0x2D4
#define XM_TXSTATS_128_255	0x2D8
#define XM_TXSTATS_256_511	0x2DC
#define XM_TXSTATS_512_1023	0x2E0
#define XM_TXSTATS_1024_MAX	0x2E4

/* RX statistics registers */
#define XM_RXSTATS_PKTSOK	0x300
#define XM_RXSTATS_BYTESOK_HI	0x304
#define XM_RXSTATS_BYTESOK_LO	0x308
#define XM_RXSTATS_BCASTSOK	0x30C
#define XM_RXSTATS_MCASTSOK	0x310
#define XM_RXSTATS_UCASTSOK	0x314
#define XM_RXSTATS_PAUSEPKTS	0x318
#define XM_RXSTATS_MACCTLPKTS	0x31C
#define XM_RXSTATS_BADPAUSEPKTS	0x320
#define XM_RXSTATS_BADMACCTLPKTS	0x324
#define XM_RXSTATS_BURSTCNT	0x328
#define XM_RXSTATS_MISSEDPKTS	0x32C
#define XM_RXSTATS_FRAMEERRS	0x330
#define XM_RXSTATS_OVERRUN	0x334
#define XM_RXSTATS_JABBER	0x338
#define XM_RXSTATS_CARRLOSS	0x33C
#define XM_RXSTATS_INRNGLENERR	0x340
#define XM_RXSTATS_SYMERR	0x344
#define XM_RXSTATS_SHORTEVENT	0x348
#define XM_RXSTATS_RUNTS	0x34C
#define XM_RXSTATS_GIANTS	0x350
#define XM_RXSTATS_CRCERRS	0x354
#define XM_RXSTATS_CEXTERRS	0x35C
#define XM_RXSTATS_UTILIZATION	0x360
#define XM_RXSTATS_64		0x368
#define XM_RXSTATS_65_127	0x36C
#define XM_RXSTATS_128_255	0x370
#define XM_RXSTATS_256_511	0x374
#define XM_RXSTATS_512_1023	0x378
#define XM_RXSTATS_1024_MAX	0x37C

#define XM_MMUCMD_TX_ENB	0x0001
#define XM_MMUCMD_RX_ENB	0x0002
#define XM_MMUCMD_GMIILOOP	0x0004
#define XM_MMUCMD_RATECTL	0x0008
#define XM_MMUCMD_GMIIFDX	0x0010
#define XM_MMUCMD_NO_MGMT_PRMB	0x0020
#define XM_MMUCMD_SIMCOL	0x0040
#define XM_MMUCMD_FORCETX	0x0080
#define XM_MMUCMD_LOOPENB	0x0200
#define XM_MMUCMD_IGNPAUSE	0x0400
#define XM_MMUCMD_PHYBUSY	0x0800
#define XM_MMUCMD_PHYDATARDY	0x1000

#define XM_TXCMD_AUTOPAD	0x0001
#define XM_TXCMD_NOCRC		0x0002
#define XM_TXCMD_NOPREAMBLE	0x0004
#define XM_TXCMD_NOGIGAMODE	0x0008
#define XM_TXCMD_SAMPLELINE	0x0010
#define XM_TXCMD_ENCBYPASS	0x0020
#define XM_TXCMD_XMITBK2BK	0x0040
#define XM_TXCMD_FAIRSHARE	0x0080

#define XM_RXCMD_DISABLE_CEXT	0x0001
#define XM_RXCMD_STRIPPAD	0x0002
#define XM_RXCMD_SAMPLELINE	0x0004
#define XM_RXCMD_SELFRX		0x0008
#define XM_RXCMD_STRIPFCS	0x0010
#define XM_RXCMD_TRANSPARENT	0x0020
#define XM_RXCMD_IPGCAPTURE	0x0040
#define XM_RXCMD_BIGPKTOK	0x0080
#define XM_RXCMD_LENERROK	0x0100

#define XM_GPIO_GP0_SET		0x0001
#define XM_GPIO_RESETSTATS	0x0004
#define XM_GPIO_RESETMAC	0x0008
#define XM_GPIO_FORCEINT	0x0020
#define XM_GPIO_ANEGINPROG	0x0040

#define XM_IMR_RX_EOF		0x0001
#define XM_IMR_TX_EOF		0x0002
#define XM_IMR_TX_UNDERRUN	0x0004
#define XM_IMR_RX_OVERRUN	0x0008
#define XM_IMR_TX_STATS_OFLOW	0x0010
#define XM_IMR_RX_STATS_OFLOW	0x0020
#define XM_IMR_TSTAMP_OFLOW	0x0040
#define XM_IMR_AUTONEG_DONE	0x0080
#define XM_IMR_NEXTPAGE_RDY	0x0100
#define XM_IMR_PAGE_RECEIVED	0x0200
#define XM_IMR_LP_REQCFG	0x0400
#define XM_IMR_GP0_SET		0x0800
#define XM_IMR_FORCEINTR	0x1000
#define XM_IMR_TX_ABORT		0x2000
#define XM_IMR_LINKEVENT	0x4000

#define XM_INTRS	\
	(~(XM_IMR_GP0_SET|XM_IMR_AUTONEG_DONE|XM_IMR_TX_UNDERRUN))

#define XM_ISR_RX_EOF		0x0001
#define XM_ISR_TX_EOF		0x0002
#define XM_ISR_TX_UNDERRUN	0x0004
#define XM_ISR_RX_OVERRUN	0x0008
#define XM_ISR_TX_STATS_OFLOW	0x0010
#define XM_ISR_RX_STATS_OFLOW	0x0020
#define XM_ISR_TSTAMP_OFLOW	0x0040
#define XM_ISR_AUTONEG_DONE	0x0080
#define XM_ISR_NEXTPAGE_RDY	0x0100
#define XM_ISR_PAGE_RECEIVED	0x0200
#define XM_ISR_LP_REQCFG	0x0400
#define XM_ISR_GP0_SET		0x0800
#define XM_ISR_FORCEINTR	0x1000
#define XM_ISR_TX_ABORT		0x2000
#define XM_ISR_LINKEVENT	0x4000

#define XM_HWCFG_GENEOP		0x0008
#define XM_HWCFG_SIGSTATCKH	0x0004
#define XM_HWCFG_GMIIMODE	0x0001

#define XM_MODE_FLUSH_RXFIFO	0x00000001
#define XM_MODE_FLUSH_TXFIFO	0x00000002
#define XM_MODE_BIGENDIAN	0x00000004
#define XM_MODE_RX_PROMISC	0x00000008
#define XM_MODE_RX_NOBROAD	0x00000010
#define XM_MODE_RX_NOMULTI	0x00000020
#define XM_MODE_RX_NOUNI	0x00000040
#define XM_MODE_RX_BADFRAMES	0x00000080
#define XM_MODE_RX_CRCERRS	0x00000100
#define XM_MODE_RX_GIANTS	0x00000200
#define XM_MODE_RX_INRANGELEN	0x00000400
#define XM_MODE_RX_RUNTS	0x00000800
#define XM_MODE_RX_MACCTL	0x00001000
#define XM_MODE_RX_USE_PERFECT	0x00002000
#define XM_MODE_RX_USE_STATION	0x00004000
#define XM_MODE_RX_USE_HASH	0x00008000
#define XM_MODE_RX_ADDRPAIR	0x00010000
#define XM_MODE_PAUSEONHI	0x00020000
#define XM_MODE_PAUSEONLO	0x00040000
#define XM_MODE_TIMESTAMP	0x00080000
#define XM_MODE_SENDPAUSE	0x00100000
#define XM_MODE_SENDCONTINUOUS	0x00200000
#define XM_MODE_LE_STATUSWORD	0x00400000
#define XM_MODE_AUTOFIFOPAUSE	0x00800000
#define XM_MODE_EXPAUSEGEN	0x02000000
#define XM_MODE_RX_INVERSE	0x04000000

#define XM_RXSTAT_MACCTL	0x00000001
#define XM_RXSTAT_ERRFRAME	0x00000002
#define XM_RXSTAT_CRCERR	0x00000004
#define XM_RXSTAT_GIANT		0x00000008
#define XM_RXSTAT_RUNT		0x00000010
#define XM_RXSTAT_FRAMEERR	0x00000020
#define XM_RXSTAT_INRANGEERR	0x00000040
#define XM_RXSTAT_CARRIERERR	0x00000080
#define XM_RXSTAT_COLLERR	0x00000100
#define XM_RXSTAT_802_3		0x00000200
#define XM_RXSTAT_CARREXTERR	0x00000400
#define XM_RXSTAT_BURSTMODE	0x00000800
#define XM_RXSTAT_UNICAST	0x00002000
#define XM_RXSTAT_MULTICAST	0x00004000
#define XM_RXSTAT_BROADCAST	0x00008000
#define XM_RXSTAT_VLAN_LEV1	0x00010000
#define XM_RXSTAT_VLAN_LEV2	0x00020000
#define XM_RXSTAT_LEN		0xFFFC0000

/*
 * XMAC PHY registers, indirectly accessed through
 * XM_PHY_ADDR and XM_PHY_REG.
 */

#define XM_PHY_BMCR		0x0000	/* control */
#define XM_PHY_BMSR		0x0001	/* status */
#define XM_PHY_VENID		0x0002	/* vendor id */
#define XM_PHY_DEVID		0x0003	/* device id */
#define XM_PHY_ANAR		0x0004	/* autoneg advertisenemt */
#define XM_PHY_LPAR		0x0005	/* link partner ability */
#define XM_PHY_ANEXP		0x0006	/* autoneg expansion */
#define XM_PHY_NEXTP		0x0007	/* nextpage */
#define XM_PHY_LPNEXTP		0x0008	/* link partner's nextpage */
#define XM_PHY_EXTSTS		0x000F	/* extented status */
#define XM_PHY_RESAB		0x0010	/* resolved ability */

#define XM_BMCR_DUPLEX		0x0100
#define XM_BMCR_RENEGOTIATE	0x0200
#define XM_BMCR_AUTONEGENBL	0x1000
#define XM_BMCR_LOOPBACK	0x4000
#define XM_BMCR_RESET		0x8000

#define XM_BMSR_EXTCAP		0x0001
#define XM_BMSR_LINKSTAT	0x0004
#define XM_BMSR_AUTONEGABLE	0x0008
#define XM_BMSR_REMFAULT	0x0010
#define XM_BMSR_AUTONEGDONE	0x0020
#define XM_BMSR_EXTSTAT		0x0100

#define XM_VENID_XAQTI		0xD14C
#define XM_DEVID_XMAC		0x0002

#define XM_ANAR_FULLDUPLEX	0x0020
#define XM_ANAR_HALFDUPLEX	0x0040
#define XM_ANAR_PAUSEBITS	0x0180
#define XM_ANAR_REMFAULTBITS	0x1800
#define XM_ANAR_ACK		0x4000
#define XM_ANAR_NEXTPAGE	0x8000

#define XM_LPAR_FULLDUPLEX	0x0020
#define XM_LPAR_HALFDUPLEX	0x0040
#define XM_LPAR_PAUSEBITS	0x0180
#define XM_LPAR_REMFAULTBITS	0x1800
#define XM_LPAR_ACK		0x4000
#define XM_LPAR_NEXTPAGE	0x8000

#define XM_PAUSE_NOPAUSE	0x0000
#define XM_PAUSE_SYMPAUSE	0x0080
#define XM_PAUSE_ASYMPAUSE	0x0100
#define XM_PAUSE_BOTH		0x0180

#define XM_REMFAULT_LINKOK	0x0000
#define XM_REMFAULT_LINKFAIL	0x0800
#define XM_REMFAULT_OFFLINE	0x1000
#define XM_REMFAULT_ANEGERR	0x1800

#define XM_ANEXP_GOTPAGE	0x0002
#define XM_ANEXP_NEXTPAGE_SELF	0x0004
#define XM_ANEXP_NEXTPAGE_LP	0x0008

#define XM_NEXTP_MESSAGE	0x07FF
#define XM_NEXTP_TOGGLE		0x0800
#define XM_NEXTP_ACK2		0x1000
#define XM_NEXTP_MPAGE		0x2000
#define XM_NEXTP_ACK1		0x4000
#define XM_NEXTP_NPAGE		0x8000

#define XM_LPNEXTP_MESSAGE	0x07FF
#define XM_LPNEXTP_TOGGLE	0x0800
#define XM_LPNEXTP_ACK2		0x1000
#define XM_LPNEXTP_MPAGE	0x2000
#define XM_LPNEXTP_ACK1		0x4000
#define XM_LPNEXTP_NPAGE	0x8000

#define XM_EXTSTS_HALFDUPLEX	0x4000
#define XM_EXTSTS_FULLDUPLEX	0x8000

#define XM_RESAB_PAUSEMISMATCH	0x0008
#define XM_RESAB_ABLMISMATCH	0x0010
#define XM_RESAB_FDMODESEL	0x0020
#define XM_RESAB_HDMODESEL	0x0040
#define XM_RESAB_PAUSEBITS	0x0180



#undef u_int16_t	
#undef u_int32_t
#undef u_int8_t



/*      B0_Y2_SP_ISRC2  32 bit  Special Interrupt Source Reg 2 */
/*      B0_Y2_SP_ISRC3  32 bit  Special Interrupt Source Reg 3 */
/*      B0_Y2_SP_EISR   32 bit  Enter ISR Reg */
/*      B0_Y2_SP_LISR   32 bit  Leave ISR Reg */
enum {
        Y2_IS_HW_ERR    = 1<<31,        /* Interrupt HW Error */
        Y2_IS_STAT_BMU  = 1<<30,        /* Status BMU Interrupt */
        Y2_IS_ASF       = 1<<29,        /* ASF subsystem Interrupt */

        Y2_IS_POLL_CHK  = 1<<27,        /* Check IRQ from polling unit */
        Y2_IS_TWSI_RDY  = 1<<26,        /* IRQ on end of TWSI Tx */
        Y2_IS_IRQ_SW    = 1<<25,        /* SW forced IRQ        */
        Y2_IS_TIMINT    = 1<<24,        /* IRQ from Timer       */

        Y2_IS_IRQ_PHY2  = 1<<12,        /* Interrupt from PHY 2 */
        Y2_IS_IRQ_MAC2  = 1<<11,        /* Interrupt from MAC 2 */
        Y2_IS_CHK_RX2   = 1<<10,        /* Descriptor error Rx 2 */
        Y2_IS_CHK_TXS2  = 1<<9,         /* Descriptor error TXS 2 */
        Y2_IS_CHK_TXA2  = 1<<8,         /* Descriptor error TXA 2 */

        Y2_IS_IRQ_PHY1  = 1<<4,         /* Interrupt from PHY 1 */
        Y2_IS_IRQ_MAC1  = 1<<3,         /* Interrupt from MAC 1 */
        Y2_IS_CHK_RX1   = 1<<2,         /* Descriptor error Rx 1 */
        Y2_IS_CHK_TXS1  = 1<<1,         /* Descriptor error TXS 1 */
        Y2_IS_CHK_TXA1  = 1<<0,         /* Descriptor error TXA 1 */

        Y2_IS_BASE      = Y2_IS_HW_ERR | Y2_IS_STAT_BMU |
                          Y2_IS_POLL_CHK | Y2_IS_TWSI_RDY |
                          Y2_IS_IRQ_SW | Y2_IS_TIMINT,
        Y2_IS_PORT_1    = Y2_IS_IRQ_PHY1 | Y2_IS_IRQ_MAC1 |
                          Y2_IS_CHK_RX1 | Y2_IS_CHK_TXA1 | Y2_IS_CHK_TXS1,
        Y2_IS_PORT_2    = Y2_IS_IRQ_PHY2 | Y2_IS_IRQ_MAC2 |
                          Y2_IS_CHK_RX2 | Y2_IS_CHK_TXA2 | Y2_IS_CHK_TXS2,
};

/*
 * Marvel-PHY Registers, indirect addressed over GMAC
 */
enum {
	PHY_MARV_CTRL           = 0x00,/* 16 bit r/w    PHY Control Register */
        PHY_MARV_STAT           = 0x01,/* 16 bit r/o    PHY Status Register */
        PHY_MARV_ID0            = 0x02,/* 16 bit r/o    PHY ID0 Register */
        PHY_MARV_ID1            = 0x03,/* 16 bit r/o    PHY ID1 Register */
        PHY_MARV_AUNE_ADV       = 0x04,/* 16 bit r/w    Auto-Neg. Advertisement */
        PHY_MARV_AUNE_LP        = 0x05,/* 16 bit r/o    Link Part Ability Reg */
        PHY_MARV_AUNE_EXP       = 0x06,/* 16 bit r/o    Auto-Neg. Expansion Reg */
        PHY_MARV_NEPG           = 0x07,/* 16 bit r/w    Next Page Register */
        PHY_MARV_NEPG_LP        = 0x08,/* 16 bit r/o    Next Page Link Partner */
        /* Marvel-specific registers */
        PHY_MARV_1000T_CTRL     = 0x09,/* 16 bit r/w    1000Base-T Control Reg */
        PHY_MARV_1000T_STAT     = 0x0a,/* 16 bit r/o    1000Base-T Status Reg */
        PHY_MARV_EXT_STAT       = 0x0f,/* 16 bit r/o    Extended Status Reg */
        PHY_MARV_PHY_CTRL       = 0x10,/* 16 bit r/w    PHY Specific Ctrl Reg */
        PHY_MARV_PHY_STAT       = 0x11,/* 16 bit r/o    PHY Specific Stat Reg */
        PHY_MARV_INT_MASK       = 0x12,/* 16 bit r/w    Interrupt Mask Reg */
        PHY_MARV_INT_STAT       = 0x13,/* 16 bit r/o    Interrupt Status Reg */
        PHY_MARV_EXT_CTRL       = 0x14,/* 16 bit r/w    Ext. PHY Specific Ctrl */
        PHY_MARV_RXE_CNT        = 0x15,/* 16 bit r/w    Receive Error Counter */
        PHY_MARV_EXT_ADR        = 0x16,/* 16 bit r/w    Ext. Ad. for Cable Diag. */
        PHY_MARV_PORT_IRQ       = 0x17,/* 16 bit r/o    Port 0 IRQ (88E1111 only) */
        PHY_MARV_LED_CTRL       = 0x18,/* 16 bit r/w    LED Control Reg */
        PHY_MARV_LED_OVER       = 0x19,/* 16 bit r/w    Manual LED Override Reg */
        PHY_MARV_EXT_CTRL_2     = 0x1a,/* 16 bit r/w    Ext. PHY Specific Ctrl 2 */
        PHY_MARV_EXT_P_STAT     = 0x1b,/* 16 bit r/w    Ext. PHY Spec. Stat Reg */
        PHY_MARV_CABLE_DIAG     = 0x1c,/* 16 bit r/o    Cable Diagnostic Reg */
        PHY_MARV_PAGE_ADDR      = 0x1d,/* 16 bit r/w    Extended Page Address Reg */
        PHY_MARV_PAGE_DATA      = 0x1e,/* 16 bit r/w    Extended Page Data Reg */

/* for 10/100 Fast Ethernet PHY (88E3082 only) */
        PHY_MARV_FE_LED_PAR     = 0x16,/* 16 bit r/w    LED Parallel Select Reg. */
        PHY_MARV_FE_LED_SER     = 0x17,/* 16 bit r/w    LED Stream Select S. LED */
        PHY_MARV_FE_VCT_TX      = 0x1a,/* 16 bit r/w    VCT Reg. for TXP/N Pins */
        PHY_MARV_FE_VCT_RX      = 0x1b,/* 16 bit r/o    VCT Reg. for RXP/N Pins */
        PHY_MARV_FE_SPEC_2      = 0x1c,/* 16 bit r/w    Specific Control Reg. 2 */
};

enum {
        PHY_M_IS_AN_ERROR       = 1<<15, /* Auto-Negotiation Error */
        PHY_M_IS_LSP_CHANGE     = 1<<14, /* Link Speed Changed */
        PHY_M_IS_DUP_CHANGE     = 1<<13, /* Duplex Mode Changed */
        PHY_M_IS_AN_PR          = 1<<12, /* Page Received */
        PHY_M_IS_AN_COMPL       = 1<<11, /* Auto-Negotiation Completed */
        PHY_M_IS_LST_CHANGE     = 1<<10, /* Link Status Changed */
        PHY_M_IS_SYMB_ERROR     = 1<<9, /* Symbol Error */
        PHY_M_IS_FALSE_CARR     = 1<<8, /* False Carrier */
        PHY_M_IS_FIFO_ERROR     = 1<<7, /* FIFO Overflow/Underrun Error */
        PHY_M_IS_MDI_CHANGE     = 1<<6, /* MDI Crossover Changed */
        PHY_M_IS_DOWNSH_DET     = 1<<5, /* Downshift Detected */
        PHY_M_IS_END_CHANGE     = 1<<4, /* Energy Detect Changed */

        PHY_M_IS_DTE_CHANGE     = 1<<2, /* DTE Power Det. Status Changed */
        PHY_M_IS_POL_CHANGE     = 1<<1, /* Polarity Changed */
        PHY_M_IS_JABBER         = 1<<0, /* Jabber */

        PHY_M_DEF_MSK           = PHY_M_IS_LSP_CHANGE | PHY_M_IS_LST_CHANGE
                                 | PHY_M_IS_FIFO_ERROR,
        PHY_M_AN_MSK           = PHY_M_IS_AN_ERROR | PHY_M_IS_AN_COMPL,
};

#define PHY_M_PS_SPEED_MSK  (3<<14) /* Bit 15..14: Speed Mask */
#define PHY_M_PS_SPEED_1000 (1<<15) /*             10 = 1000 Mbps */
#define PHY_M_PS_SPEED_100  (1<<14) /*             01 =  100 Mbps */
#define PHY_M_PS_SPEED_10   (0)     /*             00 =   10 Mbps */
#define PHY_M_PS_FULL_DUP   (1<<13) /* Full Duplex */
#define PHY_M_PS_SPDUP_RES  (1<<11) /* Speed & Duplex Resolved */
#define PHY_M_PS_LINK_UP    (1<<10) /* Link Up */

#define PHY_M_PC_EN_DET     (2<<8)  /* Energy Detect (Mode 1) */
#define PHY_M_PC_EN_DET_MSK (3<<8)  /* Bit  9.. 8: Energy Detect Mask */
#define PHY_M_PC_MDIX_MSK   (3<<5)  /* Bit  6.. 5: MDI/MDIX Config. Mask */

#define PHY_M_PC_MDI_XMODE(x)   (((x)<<5) & PHY_M_PC_MDIX_MSK)

#define PHY_M_PC_MAN_MDI       0    /* 00 = Manual MDI configuration */
#define PHY_M_PC_MAN_MDIX      1    /* 01 = Manual MDIX configuration */
#define PHY_M_PC_ENA_AUTO      3    /* 11 = Enable Automatic Crossover */


/* Phy Ext Ctrl */


#define PHY_M_EC_ENA_BC_EXT (1<<15) /* Enable Block Carr. Ext. (88E1111 only) */
#define PHY_M_EC_ENA_LIN_LB (1<<14) /* Enable Line Loopback (88E1111 only) */

#define PHY_M_EC_DIS_LINK_P (1<<12) /* Disable Link Pulses (88E1111 only) */
#define PHY_M_EC_M_DSC_MSK  (3<<10) /* Bit 11..10:     Master Downshift Counter */
                                     /* (88E1011 only) */
#define PHY_M_EC_S_DSC_MSK  (3<<8)  /* Bit  9.. 8:       Slave  Downshift Counter */
                                     /* (88E1011 only) */
#define PHY_M_EC_M_DSC_MSK2 (7<<9)  /* Bit 11.. 9:       Master Downshift Counter */
                                     /* (88E1111 only) */
#define PHY_M_EC_DOWN_S_ENA (1<<8)  /* Downshift Enable (88E1111 only) */
                                     /* !!! Errata in spec. (1 = disable) */
#define PHY_M_EC_RX_TIM_CT  (1<<7)  /* RGMII Rx Timing Control*/
#define PHY_M_EC_MAC_S_MSK  (7<<4)  /* Bit  6.. 4:       Def. MAC interface speed */
#define PHY_M_EC_FIB_AN_ENA (1<<3) /* Fiber Auto-Neg. Enable (88E1011S only) */
#define PHY_M_EC_DTE_D_ENA  (1<<2) /* DTE Detect Enable (88E1111 only) */
#define PHY_M_EC_TX_TIM_CT  (1<<1) /* RGMII Tx Timing Control */
#define PHY_M_EC_TRANS_DIS  (1<<0) /* Transmitter Disable (88E1111 only) */};
 
#define PHY_M_EC_M_DSC(x)       ((x)<<10 & PHY_M_EC_M_DSC_MSK)
                                        /* 00=1x; 01=2x; 10=3x; 11=4x */
#define PHY_M_EC_S_DSC(x)       ((x)<<8 & PHY_M_EC_S_DSC_MSK)
                                         /* 00=dis; 01=1x; 10=2x; 11=3x */
#define PHY_M_EC_DSC_2(x)       ((x)<<9 & PHY_M_EC_M_DSC_MSK2)
                                         /* 000=1x; 001=2x; 010=3x; 011=4x */
#define PHY_M_EC_MAC_S(x)       ((x)<<4 & PHY_M_EC_MAC_S_MSK)
                                         /* 01X=0; 110=2.5; 111=25 (MHz) */

#define MAC_TX_CLK_0_MHZ    (2)
#define MAC_TX_CLK_2_5_MHZ  (6)
#define MAC_TX_CLK_25_MHZ   (7)

/* PHY_MARV_CTL */

#define PHY_CT_RESET    (1<<15) /* Bit 15: (sc)clear all PHY related regs */
#define PHY_CT_LOOP     (1<<14) /* Bit 14:     enable Loopback over PHY */
#define PHY_CT_SPS_LSB  (1<<13) /* Bit 13:     Speed select, lower bit */
#define PHY_CT_ANE      (1<<12) /* Bit 12:     Auto-Negotiation Enabled */
#define PHY_CT_PDOWN    (1<<11) /* Bit 11:     Power Down Mode */
#define PHY_CT_ISOL     (1<<10) /* Bit 10:     Isolate Mode */
#define PHY_CT_RE_CFG   (1<<9) /* Bit  9:      (sc) Restart Auto-Negotiation */
#define PHY_CT_DUP_MD   (1<<8) /* Bit  8:      Duplex Mode */
#define PHY_CT_COL_TST  (1<<7) /* Bit  7:      Collision Test enabled */
#define PHY_CT_SPS_MSB  (1<<6) /* Bit  6:      Speed select, upper bit */



/* Linux Queues */

/* Queue Register Offsets, use Q_ADDR() to access */
enum {
        B8_Q_REGS = 0x0400, /* base of Queue registers */
        Q_D     = 0x00, /* 8*32 bit     Current Descriptor */
        Q_DA_L  = 0x20, /* 32 bit       Current Descriptor Address Low dWord */
        Q_DA_H  = 0x24, /* 32 bit       Current Descriptor Address High dWord */
        Q_AC_L  = 0x28, /* 32 bit       Current Address Counter Low dWord */
        Q_AC_H  = 0x2c, /* 32 bit       Current Address Counter High dWord */
        Q_BC    = 0x30, /* 32 bit       Current Byte Counter */
        Q_CSR   = 0x34, /* 32 bit       BMU Control/Status Register */
        Q_F     = 0x38, /* 32 bit       Flag Register */
        Q_T1    = 0x3c, /* 32 bit       Test Register 1 */
        Q_T1_TR = 0x3c, /*  8 bit       Test Register 1 Transfer SM */
        Q_T1_WR = 0x3d, /*  8 bit       Test Register 1 Write Descriptor SM */
        Q_T1_RD = 0x3e, /*  8 bit       Test Register 1 Read Descriptor SM */
        Q_T1_SV = 0x3f, /*  8 bit       Test Register 1 Supervisor SM */
        Q_T2    = 0x40, /* 32 bit       Test Register 2 */
        Q_T3    = 0x44, /* 32 bit       Test Register 3 */

/* Yukon-2 */
        Q_DONE  = 0x24, /* 16 bit       Done Index              (Yukon-2 only) */
        Q_WM    = 0x40, /* 16 bit       FIFO Watermark */
        Q_AL    = 0x42, /*  8 bit       FIFO Alignment */
        Q_RSP   = 0x44, /* 16 bit       FIFO Read Shadow Pointer */
        Q_RSL   = 0x46, /*  8 bit       FIFO Read Shadow Level */
        Q_RP    = 0x48, /*  8 bit       FIFO Read Pointer */
        Q_RL    = 0x4a, /*  8 bit       FIFO Read Level */
        Q_WP    = 0x4c, /*  8 bit       FIFO Write Pointer */
        Q_WSP   = 0x4d, /*  8 bit       FIFO Write Shadow Pointer */
        Q_WL    = 0x4e, /*  8 bit       FIFO Write Level */
        Q_WSL   = 0x4f, /*  8 bit       FIFO Write Shadow Level */
};

#define Q_ADDR(reg, offs) (B8_Q_REGS + (reg) + (offs))


/* BMU Control Status Registers */
/*      B0_R1_CSR               32 bit  BMU Ctrl/Stat Rx Queue 1 */
/*      B0_R2_CSR               32 bit  BMU Ctrl/Stat Rx Queue 2 */
/*      B0_XA1_CSR              32 bit  BMU Ctrl/Stat Sync Tx Queue 1 */
/*      B0_XS1_CSR              32 bit  BMU Ctrl/Stat Async Tx Queue 1 */
/*      B0_XA2_CSR              32 bit  BMU Ctrl/Stat Sync Tx Queue 2 */
/*      B0_XS2_CSR              32 bit  BMU Ctrl/Stat Async Tx Queue 2 */
/*      Q_CSR                   32 bit  BMU Control/Status Register */

/* Rx BMU Control / Status Registers (Yukon-2) */
enum {
        BMU_IDLE        = 1<<31, /* BMU Idle State */
        BMU_RX_TCP_PKT  = 1<<30, /* Rx TCP Packet (when RSS Hash enabled) */
        BMU_RX_IP_PKT   = 1<<29, /* Rx IP  Packet (when RSS Hash enabled) */

        BMU_ENA_RX_RSS_HASH = 1<<15, /* Enable  Rx RSS Hash */
        BMU_DIS_RX_RSS_HASH = 1<<14, /* Disable Rx RSS Hash */
        BMU_ENA_RX_CHKSUM = 1<<13, /* Enable  Rx TCP/IP Checksum Check */
        BMU_DIS_RX_CHKSUM = 1<<12, /* Disable Rx TCP/IP Checksum Check */
        BMU_CLR_IRQ_PAR = 1<<11, /* Clear IRQ on Parity errors (Rx) */
        BMU_CLR_IRQ_TCP = 1<<11, /* Clear IRQ on TCP segment. error (Tx) */
        BMU_CLR_IRQ_CHK = 1<<10, /* Clear IRQ Check */
        BMU_STOP        = 1<<9, /* Stop  Rx/Tx Queue */
        BMU_START       = 1<<8, /* Start Rx/Tx Queue */
        BMU_FIFO_OP_ON  = 1<<7, /* FIFO Operational On */
        BMU_FIFO_OP_OFF = 1<<6, /* FIFO Operational Off */
        BMU_FIFO_ENA    = 1<<5, /* Enable FIFO */
        BMU_FIFO_RST    = 1<<4, /* Reset  FIFO */
        BMU_OP_ON       = 1<<3, /* BMU Operational On */
        BMU_OP_OFF      = 1<<2, /* BMU Operational Off */
        BMU_RST_CLR     = 1<<1, /* Clear BMU Reset (Enable) */
        BMU_RST_SET     = 1<<0, /* Set   BMU Reset */

        BMU_CLR_RESET   = BMU_FIFO_RST | BMU_OP_OFF | BMU_RST_CLR,
        BMU_OPER_INIT   = BMU_CLR_IRQ_PAR | BMU_CLR_IRQ_CHK | BMU_START |
                          BMU_FIFO_ENA | BMU_OP_ON,

        BMU_WM_DEFAULT = 0x600,
};

/* Tx BMU Control / Status Registers (Yukon-2) */
/* Bit 31: same as for Rx */
enum {
        BMU_TX_IPIDINCR_ON      = 1<<13, /* Enable  IP ID Increment */
        BMU_TX_IPIDINCR_OFF     = 1<<12, /* Disable IP ID Increment */
        BMU_TX_CLR_IRQ_TCP      = 1<<11, /* Clear IRQ on TCP segment length mismatch */
};



/* Queue Prefetch Unit Offsets, use Y2_QADDR() to address (Yukon-2 only)*/
/* PREF_UNIT_CTRL       32 bit  Prefetch Control register */
enum {
        PREF_UNIT_OP_ON         = 1<<3, /* prefetch unit operational */
        PREF_UNIT_OP_OFF        = 1<<2, /* prefetch unit not operational */
        PREF_UNIT_RST_CLR       = 1<<1, /* Clear Prefetch Unit Reset */
        PREF_UNIT_RST_SET       = 1<<0, /* Set   Prefetch Unit Reset */
};

/* Queue Prefetch Unit Offsets, use Y2_QADDR() to address (Yukon-2 only)*/
enum {
        Y2_B8_PREF_REGS         = 0x0450,

        PREF_UNIT_CTRL          = 0x00, /* 32 bit       Control register */
        PREF_UNIT_LAST_IDX      = 0x04, /* 16 bit       Last Index */
        PREF_UNIT_ADDR_LO       = 0x08, /* 32 bit       List start addr, low part */
        PREF_UNIT_ADDR_HI       = 0x0c, /* 32 bit       List start addr, high part*/
        PREF_UNIT_GET_IDX       = 0x10, /* 16 bit       Get Index */
        PREF_UNIT_PUT_IDX       = 0x14, /* 16 bit       Put Index */
        PREF_UNIT_FIFO_WP       = 0x20, /*  8 bit       FIFO write pointer */
        PREF_UNIT_FIFO_RP       = 0x24, /*  8 bit       FIFO read pointer */
        PREF_UNIT_FIFO_WM       = 0x28, /*  8 bit       FIFO watermark */
        PREF_UNIT_FIFO_LEV      = 0x2c, /*  8 bit       FIFO level */

        PREF_UNIT_MASK_IDX      = 0x0fff,
};
#define Y2_QADDR(q,reg)         (Y2_B8_PREF_REGS + (q) + (reg))

/* Receive and Transmit Queues */
enum {
        Q_R1    = 0x0000,       /* Receive Queue 1 */
        Q_R2    = 0x0080,       /* Receive Queue 2 */
        Q_XS1   = 0x0200,       /* Synchronous Transmit Queue 1 */
        Q_XA1   = 0x0280,       /* Asynchronous Transmit Queue 1 */
        Q_XS2   = 0x0300,       /* Synchronous Transmit Queue 2 */
        Q_XA2   = 0x0380,       /* Asynchronous Transmit Queue 2 */
};





enum csr_regs {
        B0_RAP          = 0x0000,
        B0_CTST         = 0x0004,
        B0_Y2LED        = 0x0005,
        B0_POWER_CTRL   = 0x0007,
        B0_ISRC         = 0x0008,
        B0_IMSK         = 0x000c,
        B0_HWE_ISRC     = 0x0010,
        B0_HWE_IMSK     = 0x0014,

        /* Special ISR registers (Yukon-2 only) */
        B0_Y2_SP_ISRC2  = 0x001c,
        B0_Y2_SP_ISRC3  = 0x0020,
        B0_Y2_SP_EISR   = 0x0024,
        B0_Y2_SP_LISR   = 0x0028,
        B0_Y2_SP_ICR    = 0x002c,

        B2_MAC_1        = 0x0100,
        B2_MAC_2        = 0x0108,
        B2_MAC_3        = 0x0110,
        B2_CONN_TYP     = 0x0118,
        B2_PMD_TYP      = 0x0119,
        B2_MAC_CFG      = 0x011a,
        B2_CHIP_ID      = 0x011b,
        B2_E_0          = 0x011c,

        B2_Y2_CLK_GATE  = 0x011d,
        B2_Y2_HW_RES    = 0x011e,
        B2_E_3          = 0x011f,
        B2_Y2_CLK_CTRL  = 0x0120,

        B2_TI_INI       = 0x0130,
        B2_TI_VAL       = 0x0134,
        B2_TI_CTRL      = 0x0138,
        B2_TI_TEST      = 0x0139,

        B2_TST_CTRL1    = 0x0158,
        B2_TST_CTRL2    = 0x0159,
        B2_GP_IO        = 0x015c,

        B2_I2C_CTRL     = 0x0160,
        B2_I2C_DATA     = 0x0164,
        B2_I2C_IRQ      = 0x0168,
        B2_I2C_SW       = 0x016c,

        B3_RAM_ADDR     = 0x0180,
        B3_RAM_DATA_LO  = 0x0184,
        B3_RAM_DATA_HI  = 0x0188,

/* RAM Interface Registers */
/* Yukon-2: use RAM_BUFFER() to access the RAM buffer */
/*
 * The HW-Spec. calls this registers Timeout Value 0..11. But this names are
 * not usable in SW. Please notice these are NOT real timeouts, these are
 * the number of qWords transferred continuously.
 */
#define RAM_BUFFER(port, reg)   (reg | (port <<6))

        B3_RI_WTO_R1    = 0x0190,
        B3_RI_WTO_XA1   = 0x0191,
        B3_RI_WTO_XS1   = 0x0192,
        B3_RI_RTO_R1    = 0x0193,
        B3_RI_RTO_XA1   = 0x0194,
        B3_RI_RTO_XS1   = 0x0195,
        B3_RI_WTO_R2    = 0x0196,
        B3_RI_WTO_XA2   = 0x0197,
        B3_RI_WTO_XS2   = 0x0198,
        B3_RI_RTO_R2    = 0x0199,
        B3_RI_RTO_XA2   = 0x019a,
        B3_RI_RTO_XS2   = 0x019b,
        B3_RI_TO_VAL    = 0x019c,
        B3_RI_CTRL      = 0x01a0,
        B3_RI_TEST      = 0x01a2,
        B3_MA_TOINI_RX1 = 0x01b0,
        B3_MA_TOINI_RX2 = 0x01b1,
        B3_MA_TOINI_TX1 = 0x01b2,
        B3_MA_TOINI_TX2 = 0x01b3,
        B3_MA_TOVAL_RX1 = 0x01b4,
        B3_MA_TOVAL_RX2 = 0x01b5,
        B3_MA_TOVAL_TX1 = 0x01b6,
        B3_MA_TOVAL_TX2 = 0x01b7,
        B3_MA_TO_CTRL   = 0x01b8,
        B3_MA_TO_TEST   = 0x01ba,
        B3_MA_RCINI_RX1 = 0x01c0,
        B3_MA_RCINI_RX2 = 0x01c1,
        B3_MA_RCINI_TX1 = 0x01c2,
        B3_MA_RCINI_TX2 = 0x01c3,
        B3_MA_RCVAL_RX1 = 0x01c4,
        B3_MA_RCVAL_RX2 = 0x01c5,
        B3_MA_RCVAL_TX1 = 0x01c6,
        B3_MA_RCVAL_TX2 = 0x01c7,
        B3_MA_RC_CTRL   = 0x01c8,
        B3_MA_RC_TEST   = 0x01ca,
        B3_PA_TOINI_RX1 = 0x01d0,
        B3_PA_TOINI_RX2 = 0x01d4,
        B3_PA_TOINI_TX1 = 0x01d8,
        B3_PA_TOINI_TX2 = 0x01dc,
        B3_PA_TOVAL_RX1 = 0x01e0,
        B3_PA_TOVAL_RX2 = 0x01e4,
        B3_PA_TOVAL_TX1 = 0x01e8,
        B3_PA_TOVAL_TX2 = 0x01ec,
        B3_PA_CTRL      = 0x01f0,
        B3_PA_TEST      = 0x01f2,

        Y2_CFG_SPC      = 0x1c00,
};


enum {
        B6_EXT_REG      = 0x0300,/* External registers (GENESIS only) */
        B7_CFG_SPC      = 0x0380,/* copy of the Configuration register */
        B8_RQ1_REGS     = 0x0400,/* Receive Queue 1 */
        B8_RQ2_REGS     = 0x0480,/* Receive Queue 2 */
        B8_TS1_REGS     = 0x0600,/* Transmit sync queue 1 */
        B8_TA1_REGS     = 0x0680,/* Transmit async queue 1 */
        B8_TS2_REGS     = 0x0700,/* Transmit sync queue 2 */
        B8_TA2_REGS     = 0x0780,/* Transmit sync queue 2 */
        B16_RAM_REGS    = 0x0800,/* RAM Buffer Registers */
};

/* RAM Buffer Register Offsets */
enum {

        RB_START        = 0x00,/* 32 bit        RAM Buffer Start Address */
        RB_END  = 0x04,/* 32 bit        RAM Buffer End Address */
        RB_WP   = 0x08,/* 32 bit        RAM Buffer Write Pointer */
        RB_RP   = 0x0c,/* 32 bit        RAM Buffer Read Pointer */
        RB_RX_UTPP      = 0x10,/* 32 bit        Rx Upper Threshold, Pause Packet */
        RB_RX_LTPP      = 0x14,/* 32 bit        Rx Lower Threshold, Pause Packet */
        RB_RX_UTHP      = 0x18,/* 32 bit        Rx Upper Threshold, High Prio */
        RB_RX_LTHP      = 0x1c,/* 32 bit        Rx Lower Threshold, High Prio */
        /* 0x10 - 0x1f: reserved at Tx RAM Buffer Registers */
        RB_PC   = 0x20,/* 32 bit        RAM Buffer Packet Counter */
        RB_LEV  = 0x24,/* 32 bit        RAM Buffer Level Register */
        RB_CTRL = 0x28,/* 32 bit        RAM Buffer Control Register */
        RB_TST1 = 0x29,/*  8 bit        RAM Buffer Test Register 1 */
        RB_TST2 = 0x2a,/*  8 bit        RAM Buffer Test Register 2 */
};

#define RB_ADDR(offs, queue) (B16_RAM_REGS + (queue) + (offs))


/* RAM Buffer Register Offsets, use RB_ADDR(Queue, Offs) to access */
/*      RB_START                32 bit  RAM Buffer Start Address */
/*      RB_END                  32 bit  RAM Buffer End Address */
/*      RB_WP                   32 bit  RAM Buffer Write Pointer */
/*      RB_RP                   32 bit  RAM Buffer Read Pointer */
/*      RB_RX_UTPP              32 bit  Rx Upper Threshold, Pause Pack */
/*      RB_RX_LTPP              32 bit  Rx Lower Threshold, Pause Pack */
/*      RB_RX_UTHP              32 bit  Rx Upper Threshold, High Prio */
/*      RB_RX_LTHP              32 bit  Rx Lower Threshold, High Prio */
/*      RB_PC                   32 bit  RAM Buffer Packet Counter */
/*      RB_LEV                  32 bit  RAM Buffer Level Register */

#define RB_MSK  0x0007ffff      /* Bit 18.. 0:  RAM Buffer Pointer Bits */
/*      RB_TST2                  8 bit  RAM Buffer Test Register 2 */
/*      RB_TST1                  8 bit  RAM Buffer Test Register 1 */

/*      RB_CTRL                  8 bit  RAM Buffer Control Register */
enum {
        RB_ENA_STFWD    = 1<<5, /* Enable  Store & Forward */
        RB_DIS_STFWD    = 1<<4, /* Disable Store & Forward */
        RB_ENA_OP_MD    = 1<<3, /* Enable  Operation Mode */
        RB_DIS_OP_MD    = 1<<2, /* Disable Operation Mode */
        RB_RST_CLR      = 1<<1, /* Clear RAM Buf STM Reset */
        RB_RST_SET      = 1<<0, /* Set   RAM Buf STM Reset */
};


enum {
        LNK_SYNC_INI    = 0x0c30,/* 32 bit      Link Sync Cnt Init Value */
        LNK_SYNC_VAL    = 0x0c34,/* 32 bit      Link Sync Cnt Current Value */
        LNK_SYNC_CTRL   = 0x0c38,/*  8 bit      Link Sync Cnt Control Register */
        LNK_SYNC_TST    = 0x0c39,/*  8 bit      Link Sync Cnt Test Register */

        LNK_LED_REG     = 0x0c3c,/*  8 bit      Link LED Register */

/* Receive GMAC FIFO (YUKON and Yukon-2) */

        RX_GMF_EA       = 0x0c40,/* 32 bit      Rx GMAC FIFO End Address */
        RX_GMF_AF_THR   = 0x0c44,/* 32 bit      Rx GMAC FIFO Almost Full Thresh. */
        RX_GMF_CTRL_T   = 0x0c48,/* 32 bit      Rx GMAC FIFO Control/Test */
        RX_GMF_FL_MSK   = 0x0c4c,/* 32 bit      Rx GMAC FIFO Flush Mask */
        RX_GMF_FL_THR   = 0x0c50,/* 32 bit      Rx GMAC FIFO Flush Threshold */
        RX_GMF_TR_THR   = 0x0c54,/* 32 bit      Rx Truncation Threshold (Yukon-2) */
        RX_GMF_UP_THR   = 0x0c58,/*  8 bit      Rx Upper Pause Thr (Yukon-EC_U) */
        RX_GMF_LP_THR   = 0x0c5a,/*  8 bit      Rx Lower Pause Thr (Yukon-EC_U) */
        RX_GMF_VLAN     = 0x0c5c,/* 32 bit      Rx VLAN Type Register (Yukon-2) */
        RX_GMF_WP       = 0x0c60,/* 32 bit      Rx GMAC FIFO Write Pointer */

        RX_GMF_WLEV     = 0x0c68,/* 32 bit      Rx GMAC FIFO Write Level */

        RX_GMF_RP       = 0x0c70,/* 32 bit      Rx GMAC FIFO Read Pointer */

        RX_GMF_RLEV     = 0x0c78,/* 32 bit      Rx GMAC FIFO Read Level */
};


/*      RX_GMF_CTRL_T   32 bit  Rx GMAC FIFO Control/Test */
enum {
	RX_TRUNC_ON     = 1<<27,        /* enable  packet truncation */
	RX_TRUNC_OFF    = 1<<26,        /* disable packet truncation */
	RX_VLAN_STRIP_ON = 1<<25,       /* enable  VLAN stripping */
	RX_VLAN_STRIP_OFF = 1<<24,      /* disable VLAN stripping */
	
	GMF_WP_TST_ON   = 1<<14,        /* Write Pointer Test On */
	GMF_WP_TST_OFF  = 1<<13,        /* Write Pointer Test Off */
	GMF_WP_STEP     = 1<<12,        /* Write Pointer Step/Increment */
	
	GMF_RP_TST_ON   = 1<<10,        /* Read Pointer Test On */
	GMF_RP_TST_OFF  = 1<<9,         /* Read Pointer Test Off */
	GMF_RP_STEP     = 1<<8,         /* Read Pointer Step/Increment */
	GMF_RX_F_FL_ON  = 1<<7,         /* Rx FIFO Flush Mode On */
	GMF_RX_F_FL_OFF = 1<<6,         /* Rx FIFO Flush Mode Off */
	GMF_CLI_RX_FO   = 1<<5,         /* Clear IRQ Rx FIFO Overrun */
	GMF_CLI_RX_C    = 1<<4,         /* Clear IRQ Rx Frame Complete */
	
	GMF_OPER_ON     = 1<<3,         /* Operational Mode On */
	GMF_OPER_OFF    = 1<<2,         /* Operational Mode Off */
	GMF_RST_CLR     = 1<<1,         /* Clear GMAC FIFO Reset */
	GMF_RST_SET     = 1<<0,         /* Set   GMAC FIFO Reset */
	
	RX_GMF_FL_THR_DEF = 0xa,        /* flush threshold (default) */
	
	GMF_RX_CTRL_DEF = GMF_OPER_ON | GMF_RX_F_FL_ON,
};


enum {
        BASE_GMAC_1     = 0x2800,/* GMAC 1 registers */
        BASE_GMAC_2     = 0x3800,/* GMAC 2 registers */
};

/* Yukon PHY related registers */
#define SK_GMAC_REG(port,reg) \
        (BASE_GMAC_1 + (port) * (BASE_GMAC_2-BASE_GMAC_1) + (reg))
#define GM_PHY_RETRIES  100

/* GMAC registers  */
/* Port Registers */
enum {
        GM_GP_STAT      = 0x0000,   /* 16 bit r/o   General Purpose Status */
        GM_GP_CTRL      = 0x0004,   /* 16 bit r/w   General Purpose Control */
        GM_TX_CTRL      = 0x0008,   /* 16 bit r/w   Transmit Control Reg. */
        GM_RX_CTRL      = 0x000c,   /* 16 bit r/w   Receive Control Reg. */
        GM_TX_FLOW_CTRL = 0x0010,   /* 16 bit r/w   Transmit Flow-Control */
        GM_TX_PARAM     = 0x0014,   /* 16 bit r/w   Transmit Parameter Reg. */
        GM_SERIAL_MODE  = 0x0018,   /* 16 bit r/w   Serial Mode Register */

/* Source Address Registers */
        GM_SRC_ADDR_1L  = 0x001c,   /* 16 bit r/w   Source Address 1 (low) */
        GM_SRC_ADDR_1M  = 0x0020,   /* 16 bit r/w   Source Address 1 (middle) */
        GM_SRC_ADDR_1H  = 0x0024,   /* 16 bit r/w   Source Address 1 (high) */
        GM_SRC_ADDR_2L  = 0x0028,   /* 16 bit r/w   Source Address 2 (low) */
        GM_SRC_ADDR_2M  = 0x002c,   /* 16 bit r/w   Source Address 2 (middle) */
        GM_SRC_ADDR_2H  = 0x0030,   /* 16 bit r/w   Source Address 2 (high) */

/* Multicast Address Hash Registers */
        GM_MC_ADDR_H1   = 0x0034,   /* 16 bit r/w   Multicast Address Hash 1 */
        GM_MC_ADDR_H2   = 0x0038,   /* 16 bit r/w   Multicast Address Hash 2 */
        GM_MC_ADDR_H3   = 0x003c,   /* 16 bit r/w   Multicast Address Hash 3 */
        GM_MC_ADDR_H4   = 0x0040,   /* 16 bit r/w   Multicast Address Hash 4 */

/* Interrupt Source Registers */
        GM_TX_IRQ_SRC   = 0x0044,   /* 16 bit r/o   Tx Overflow IRQ Source */
        GM_RX_IRQ_SRC   = 0x0048,   /* 16 bit r/o   Rx Overflow IRQ Source */
        GM_TR_IRQ_SRC   = 0x004c,   /* 16 bit r/o   Tx/Rx Over. IRQ Source */

/* Interrupt Mask Registers */
        GM_TX_IRQ_MSK   = 0x0050,   /* 16 bit r/w   Tx Overflow IRQ Mask */
        GM_RX_IRQ_MSK   = 0x0054,   /* 16 bit r/w   Rx Overflow IRQ Mask */
        GM_TR_IRQ_MSK   = 0x0058,   /* 16 bit r/w   Tx/Rx Over. IRQ Mask */

/* Serial Management Interface (SMI) Registers */
        GM_SMI_CTRL     = 0x0080,   /* 16 bit r/w   SMI Control Register */
        GM_SMI_DATA     = 0x0084,   /* 16 bit r/w   SMI Data Register */
        GM_PHY_ADDR     = 0x0088,   /* 16 bit r/w   GPHY Address Register */
};


/* GMAC Bit Definitions */
/*      GM_GP_STAT      16 bit r/o      General Purpose Status Register */
enum {
        GM_GPSR_SPEED           = 1<<15, /* Bit 15:     Port Speed (1 = 100 Mbps) */
        GM_GPSR_DUPLEX          = 1<<14, /* Bit 14:     Duplex Mode (1 = Full) */
        GM_GPSR_FC_TX_DIS       = 1<<13, /* Bit 13:     Tx Flow-Control Mode Disabled */
        GM_GPSR_LINK_UP         = 1<<12, /* Bit 12:     Link Up Status */
        GM_GPSR_PAUSE           = 1<<11, /* Bit 11:     Pause State */
        GM_GPSR_TX_ACTIVE       = 1<<10, /* Bit 10:     Tx in Progress */
        GM_GPSR_EXC_COL         = 1<<9, /* Bit  9:      Excessive Collisions Occured */
        GM_GPSR_LAT_COL         = 1<<8, /* Bit  8:      Late Collisions Occured */

        GM_GPSR_PHY_ST_CH       = 1<<5, /* Bit  5:      PHY Status Change */
        GM_GPSR_GIG_SPEED       = 1<<4, /* Bit  4:      Gigabit Speed (1 = 1000 Mbps) */
        GM_GPSR_PART_MODE       = 1<<3, /* Bit  3:      Partition mode */
        GM_GPSR_FC_RX_DIS       = 1<<2, /* Bit  2:      Rx Flow-Control Mode Disabled */
        GM_GPSR_PROM_EN         = 1<<1, /* Bit  1:      Promiscuous Mode Enabled */
};

/* Different PHY Types */
enum {
        PHY_ADDR_MARV   = 0,
};


/* Advertisement register bits */
enum {
        PHY_AN_NXT_PG   = 1<<15, /* Bit 15:     Request Next Page */
        PHY_AN_ACK      = 1<<14, /* Bit 14:     (ro) Acknowledge Received */
        PHY_AN_RF       = 1<<13, /* Bit 13:     Remote Fault Bits */

        PHY_AN_PAUSE_ASYM = 1<<11,/* Bit 11:    Try for asymmetric */
        PHY_AN_PAUSE_CAP = 1<<10, /* Bit 10:    Try for pause */
        PHY_AN_100BASE4 = 1<<9, /* Bit 9:       Try for 100mbps 4k packets */
        PHY_AN_100FULL  = 1<<8, /* Bit 8:       Try for 100mbps full-duplex */
        PHY_AN_100HALF  = 1<<7, /* Bit 7:       Try for 100mbps half-duplex */
        PHY_AN_10FULL   = 1<<6, /* Bit 6:       Try for 10mbps full-duplex */
        PHY_AN_10HALF   = 1<<5, /* Bit 5:       Try for 10mbps half-duplex */
        PHY_AN_CSMA     = 1<<0, /* Bit 0:       Only selector supported */
        PHY_AN_SEL      = 0x1f, /* Bit 4..0:    Selector Field, 00001=Ethernet*/
        PHY_AN_FULL     = PHY_AN_100FULL | PHY_AN_10FULL | PHY_AN_CSMA,
        PHY_AN_ALL      = PHY_AN_10HALF | PHY_AN_10FULL |
                          PHY_AN_100HALF | PHY_AN_100FULL,
};


/** Marvell-Specific */
enum {
        PHY_M_AN_NXT_PG = 1<<15, /* Request Next Page */
        PHY_M_AN_ACK    = 1<<14, /* (ro)        Acknowledge Received */
        PHY_M_AN_RF     = 1<<13, /* Remote Fault */

        PHY_M_AN_ASP    = 1<<11, /* Asymmetric Pause */
        PHY_M_AN_PC     = 1<<10, /* MAC Pause implemented */
        PHY_M_AN_100_T4 = 1<<9, /* Not cap. 100Base-T4 (always 0) */
        PHY_M_AN_100_FD = 1<<8, /* Advertise 100Base-TX Full Duplex */
        PHY_M_AN_100_HD = 1<<7, /* Advertise 100Base-TX Half Duplex */
        PHY_M_AN_10_FD  = 1<<6, /* Advertise 10Base-TX Full Duplex */
        PHY_M_AN_10_HD  = 1<<5, /* Advertise 10Base-TX Half Duplex */
        PHY_M_AN_SEL_MSK =0x1f<<4,      /* Bit  4.. 0: Selector Field Mask */
};


/*****  PHY_MARV_1000T_CTRL     16 bit r/w      1000Base-T Control Reg *****/
enum {
        PHY_M_1000C_TEST        = 7<<13,/* Bit 15..13:  Test Modes */
        PHY_M_1000C_MSE = 1<<12, /* Manual Master/Slave Enable */
        PHY_M_1000C_MSC = 1<<11, /* M/S Configuration (1=Master) */
        PHY_M_1000C_MPD = 1<<10, /* Multi-Port Device */
        PHY_M_1000C_AFD = 1<<9, /* Advertise Full Duplex */
        PHY_M_1000C_AHD = 1<<8, /* Advertise Half Duplex */
};


enum {
        PULS_NO_STR     = 0,/* no pulse stretching */
        PULS_21MS       = 1,/* 21 ms to 42 ms */
        PULS_42MS       = 2,/* 42 ms to 84 ms */
        PULS_84MS       = 3,/* 84 ms to 170 ms */
        PULS_170MS      = 4,/* 170 ms to 340 ms */
        PULS_340MS      = 5,/* 340 ms to 670 ms */
        PULS_670MS      = 6,/* 670 ms to 1.3 s */
        PULS_1300MS     = 7,/* 1.3 s to 2.7 s */
};


/*****  PHY_MARV_LED_CTRL       16 bit r/w      LED Control Reg *****/
enum {
        PHY_M_LEDC_DIS_LED      = 1<<15, /* Disable LED */
        PHY_M_LEDC_PULS_MSK     = 7<<12,/* Bit 14..12: Pulse Stretch Mask */
        PHY_M_LEDC_F_INT        = 1<<11, /* Force Interrupt */
        PHY_M_LEDC_BL_R_MSK     = 7<<8,/* Bit 10.. 8: Blink Rate Mask */
        PHY_M_LEDC_DP_C_LSB     = 1<<7, /* Duplex Control (LSB, 88E1111 only) */
        PHY_M_LEDC_TX_C_LSB     = 1<<6, /* Tx Control (LSB, 88E1111 only) */
        PHY_M_LEDC_LK_C_MSK     = 7<<3,/* Bit  5.. 3: Link Control Mask */
                                        /* (88E1111 only) */
};

enum {
        PHY_M_LEDC_LINK_MSK     = 3<<3,/* Bit  4.. 3: Link Control Mask */
                                                                        /* (88E1011 only) */
        PHY_M_LEDC_DP_CTRL      = 1<<2, /* Duplex Control */
        PHY_M_LEDC_DP_C_MSB     = 1<<2, /* Duplex Control (MSB, 88E1111 only) */
        PHY_M_LEDC_RX_CTRL      = 1<<1, /* Rx Activity / Link */
        PHY_M_LEDC_TX_CTRL      = 1<<0, /* Tx Activity / Link */
        PHY_M_LEDC_TX_C_MSB     = 1<<0, /* Tx Control (MSB, 88E1111 only) */
};

#define PHY_M_LED_PULS_DUR(x)   (((x)<<12) & PHY_M_LEDC_PULS_MSK)


enum {
        BLINK_42MS      = 0,/* 42 ms */
        BLINK_84MS      = 1,/* 84 ms */
        BLINK_170MS     = 2,/* 170 ms */
        BLINK_340MS     = 3,/* 340 ms */
        BLINK_670MS     = 4,/* 670 ms */
};


#define PHY_M_LED_BLINK_RT(x)   (((x)<<8) & PHY_M_LEDC_BL_R_MSK)

enum {
        MO_LED_NORM     = 0,
        MO_LED_BLINK    = 1,
        MO_LED_OFF      = 2,
        MO_LED_ON       = 3,
};


/*****  PHY_MARV_LED_OVER       16 bit r/w      Manual LED Override Reg *****/
#define PHY_M_LED_MO_SGMII(x)   ((x)<<14) /* Bit 15..14:  SGMII AN Timer */
                                                                                /* Bit 13..12:  reserved */
#define PHY_M_LED_MO_DUP(x)     ((x)<<10) /* Bit 11..10:  Duplex */
#define PHY_M_LED_MO_10(x)      ((x)<<8) /* Bit  9.. 8:  Link 10 */
#define PHY_M_LED_MO_100(x)     ((x)<<6) /* Bit  7.. 6:  Link 100 */
#define PHY_M_LED_MO_1000(x)    ((x)<<4) /* Bit  5.. 4:  Link 1000 */
#define PHY_M_LED_MO_RX(x)      ((x)<<2) /* Bit  3.. 2:  Rx */
#define PHY_M_LED_MO_TX(x)      ((x)<<0) /* Bit  1.. 0:  Tx */


/*      GM_SMI_CTRL                     16 bit r/w      SMI Control Register */
enum {
        GM_SMI_CT_PHY_A_MSK     = 0x1f<<11,/* Bit 15..11:       PHY Device Address */
        GM_SMI_CT_REG_A_MSK     = 0x1f<<6,/* Bit 10.. 6:        PHY Register Address */
        GM_SMI_CT_OP_RD         = 1<<5, /* Bit  5:      OpCode Read (0=Write)*/
        GM_SMI_CT_RD_VAL        = 1<<4, /* Bit  4:      Read Valid (Read completed) */
        GM_SMI_CT_BUSY          = 1<<3, /* Bit  3:      Busy (Operation in progress) */
};

#define GM_SMI_CT_PHY_AD(x)     (((x)<<11) & GM_SMI_CT_PHY_A_MSK)
#define GM_SMI_CT_REG_AD(x)     (((x)<<6) & GM_SMI_CT_REG_A_MSK)


/* GMAC and GPHY Control Registers (YUKON only) */
enum {
        GMAC_CTRL       = 0x0f00,/* 32 bit      GMAC Control Reg */
        GPHY_CTRL       = 0x0f04,/* 32 bit      GPHY Control Reg */
        GMAC_IRQ_SRC    = 0x0f08,/*  8 bit      GMAC Interrupt Source Reg */
        GMAC_IRQ_MSK    = 0x0f0c,/*  8 bit      GMAC Interrupt Mask Reg */
        GMAC_LINK_CTRL  = 0x0f10,/* 16 bit      Link Control Reg */

/* Wake-up Frame Pattern Match Control Registers (YUKON only) */

        WOL_REG_OFFS    = 0x20,/* HW-Bug: Address is + 0x20 against spec. */

        WOL_CTRL_STAT   = 0x0f20,/* 16 bit      WOL Control/Status Reg */
        WOL_MATCH_CTL   = 0x0f22,/*  8 bit      WOL Match Control Reg */
        WOL_MATCH_RES   = 0x0f23,/*  8 bit      WOL Match Result Reg */
        WOL_MAC_ADDR    = 0x0f24,/* 32 bit      WOL MAC Address */
        WOL_PATT_PME    = 0x0f2a,/*  8 bit      WOL PME Match Enable (Yukon-2) */
        WOL_PATT_ASFM   = 0x0f2b,/*  8 bit      WOL ASF Match Enable (Yukon-2) */
        WOL_PATT_RPTR   = 0x0f2c,/*  8 bit      WOL Pattern Read Pointer */

/* WOL Pattern Length Registers (YUKON only) */

        WOL_PATT_LEN_LO = 0x0f30,/* 32 bit      WOL Pattern Length 3..0 */
        WOL_PATT_LEN_HI = 0x0f34,/* 24 bit      WOL Pattern Length 6..4 */

/* WOL Pattern Counter Registers (YUKON only) */


        WOL_PATT_CNT_0  = 0x0f38,/* 32 bit      WOL Pattern Counter 3..0 */
        WOL_PATT_CNT_4  = 0x0f3c,/* 24 bit      WOL Pattern Counter 6..4 */
};


/*      GPHY_CTRL               32 bit  GPHY Control Reg (YUKON only) */
enum {
        GPC_SEL_BDT     = 1<<28, /* Select Bi-Dir. Transfer for MDC/MDIO */
        GPC_INT_POL_HI  = 1<<27, /* IRQ Polarity is Active HIGH */
        GPC_75_OHM      = 1<<26, /* Use 75 Ohm Termination instead of 50 */
        GPC_DIS_FC      = 1<<25, /* Disable Automatic Fiber/Copper Detection */
        GPC_DIS_SLEEP   = 1<<24, /* Disable Energy Detect */
        GPC_HWCFG_M_3   = 1<<23, /* HWCFG_MODE[3] */
        GPC_HWCFG_M_2   = 1<<22, /* HWCFG_MODE[2] */
        GPC_HWCFG_M_1   = 1<<21, /* HWCFG_MODE[1] */
        GPC_HWCFG_M_0   = 1<<20, /* HWCFG_MODE[0] */
        GPC_ANEG_0      = 1<<19, /* ANEG[0] */
        GPC_ENA_XC      = 1<<18, /* Enable MDI crossover */
        GPC_DIS_125     = 1<<17, /* Disable 125 MHz clock */
        GPC_ANEG_3      = 1<<16, /* ANEG[3] */
        GPC_ANEG_2      = 1<<15, /* ANEG[2] */
        GPC_ANEG_1      = 1<<14, /* ANEG[1] */
        GPC_ENA_PAUSE   = 1<<13, /* Enable Pause (SYM_OR_REM) */
        GPC_PHYADDR_4   = 1<<12, /* Bit 4 of Phy Addr */
        GPC_PHYADDR_3   = 1<<11, /* Bit 3 of Phy Addr */
        GPC_PHYADDR_2   = 1<<10, /* Bit 2 of Phy Addr */
        GPC_PHYADDR_1   = 1<<9,  /* Bit 1 of Phy Addr */
        GPC_PHYADDR_0   = 1<<8,  /* Bit 0 of Phy Addr */
                                                /* Bits  7..2:  reserved */
        GPC_RST_CLR     = 1<<1, /* Clear GPHY Reset */
        GPC_RST_SET     = 1<<0, /* Set   GPHY Reset */
};


/*      GMAC_CTRL               32 bit  GMAC Control Reg (YUKON only) */
enum {
        GMC_H_BURST_ON  = 1<<7, /* Half Duplex Burst Mode On */
        GMC_H_BURST_OFF = 1<<6, /* Half Duplex Burst Mode Off */
        GMC_F_LOOPB_ON  = 1<<5, /* FIFO Loopback On */
        GMC_F_LOOPB_OFF = 1<<4, /* FIFO Loopback Off */
        GMC_PAUSE_ON    = 1<<3, /* Pause On */
        GMC_PAUSE_OFF   = 1<<2, /* Pause Off */
        GMC_RST_CLR     = 1<<1, /* Clear GMAC Reset */
        GMC_RST_SET     = 1<<0, /* Set   GMAC Reset */
};



/*      GM_GP_CTRL      16 bit r/w      General Purpose Control Register */
enum {
        GM_GPCR_PROM_ENA        = 1<<14,        /* Bit 14:      Enable Promiscuous Mode */
        GM_GPCR_FC_TX_DIS       = 1<<13, /* Bit 13:     Disable Tx Flow-Control Mode */
        GM_GPCR_TX_ENA          = 1<<12, /* Bit 12:     Enable Transmit */
        GM_GPCR_RX_ENA          = 1<<11, /* Bit 11:     Enable Receive */
        GM_GPCR_BURST_ENA       = 1<<10, /* Bit 10:     Enable Burst Mode */
        GM_GPCR_LOOP_ENA        = 1<<9, /* Bit  9:      Enable MAC Loopback Mode */
        GM_GPCR_PART_ENA        = 1<<8, /* Bit  8:      Enable Partition Mode */
        GM_GPCR_GIGS_ENA        = 1<<7, /* Bit  7:      Gigabit Speed (1000 Mbps) */
        GM_GPCR_FL_PASS         = 1<<6, /* Bit  6:      Force Link Pass */
        GM_GPCR_DUP_FULL        = 1<<5, /* Bit  5:      Full Duplex Mode */
        GM_GPCR_FC_RX_DIS       = 1<<4, /* Bit  4:      Disable Rx Flow-Control Mode */
        GM_GPCR_SPEED_100       = 1<<3,   /* Bit  3:    Port Speed 100 Mbps */
        GM_GPCR_AU_DUP_DIS      = 1<<2, /* Bit  2:      Disable Auto-Update Duplex */
        GM_GPCR_AU_FCT_DIS      = 1<<1, /* Bit  1:      Disable Auto-Update Flow-C. */
        GM_GPCR_AU_SPD_DIS      = 1<<0, /* Bit  0:      Disable Auto-Update Speed */
};

#define GM_GPCR_SPEED_1000      (GM_GPCR_GIGS_ENA | GM_GPCR_SPEED_100)
#define GM_GPCR_AU_ALL_DIS      (GM_GPCR_AU_DUP_DIS | GM_GPCR_AU_FCT_DIS|GM_GPCR_AU_SPD_DIS)


/*      GM_PHY_ADDR                             16 bit r/w      GPHY Address Register */
enum {
        GM_PAR_MIB_CLR  = 1<<5, /* Bit  5:      Set MIB Clear Counter Mode */
        GM_PAR_MIB_TST  = 1<<4, /* Bit  4:      MIB Load Counter (Test Mode) */
};

/* MIB Counters */
#define GM_MIB_CNT_BASE 0x0100          /* Base Address of MIB Counters */
#define GM_MIB_CNT_SIZE 44              /* Number of MIB Counters */


/*      GM_TX_CTRL                      16 bit r/w      Transmit Control Register */
enum {
        GM_TXCR_FORCE_JAM       = 1<<15, /* Bit 15:     Force Jam / Flow-Control */
        GM_TXCR_CRC_DIS         = 1<<14, /* Bit 14:     Disable insertion of CRC */
        GM_TXCR_PAD_DIS         = 1<<13, /* Bit 13:     Disable padding of packets */
        GM_TXCR_COL_THR_MSK     = 1<<10, /* Bit 12..10: Collision Threshold */
};

#define TX_COL_THR(x)           (((x)<<10) & GM_TXCR_COL_THR_MSK)
#define TX_COL_DEF              0x04


/*      GM_RX_CTRL                      16 bit r/w      Receive Control Register */
enum {
        GM_RXCR_UCF_ENA = 1<<15, /* Bit 15:     Enable Unicast filtering */
        GM_RXCR_MCF_ENA = 1<<14, /* Bit 14:     Enable Multicast filtering */
        GM_RXCR_CRC_DIS = 1<<13, /* Bit 13:     Remove 4-byte CRC */
        GM_RXCR_PASS_FC = 1<<12, /* Bit 12:     Pass FC packets to FIFO */
};

/*      GM_TX_PARAM             16 bit r/w      Transmit Parameter Register */
enum {
        GM_TXPA_JAMLEN_MSK      = 0x03<<14,     /* Bit 15..14:  Jam Length */
        GM_TXPA_JAMIPG_MSK      = 0x1f<<9,      /* Bit 13..9:   Jam IPG */
        GM_TXPA_JAMDAT_MSK      = 0x1f<<4,      /* Bit  8..4:   IPG Jam to Data */
        GM_TXPA_BO_LIM_MSK      = 0x0f,         /* Bit  3.. 0: Backoff Limit Mask */

        TX_JAM_LEN_DEF          = 0x03,
        TX_JAM_IPG_DEF          = 0x0b,
        TX_IPG_JAM_DEF          = 0x1c,
        TX_BOF_LIM_DEF          = 0x04,
};

#define TX_JAM_LEN_VAL(x)       (((x)<<14) & GM_TXPA_JAMLEN_MSK)
#define TX_JAM_IPG_VAL(x)       (((x)<<9)  & GM_TXPA_JAMIPG_MSK)
#define TX_IPG_JAM_DATA(x)      (((x)<<4)  & GM_TXPA_JAMDAT_MSK)
#define TX_BACK_OFF_LIM(x)      ((x) & GM_TXPA_BO_LIM_MSK)


/*      GM_SERIAL_MODE                  16 bit r/w      Serial Mode Register */
enum {
        GM_SMOD_DATABL_MSK      = 0x1f<<11, /* Bit 15..11:      Data Blinder (r/o) */
        GM_SMOD_LIMIT_4         = 1<<10, /* Bit 10:     4 consecutive Tx trials */
        GM_SMOD_VLAN_ENA        = 1<<9, /* Bit  9:      Enable VLAN  (Max. Frame Len) */
        GM_SMOD_JUMBO_ENA       = 1<<8, /* Bit  8:      Enable Jumbo (Max. Frame Len) */
         GM_SMOD_IPG_MSK        = 0x1f  /* Bit 4..0:    Inter-Packet Gap (IPG) */
};

#define DATA_BLIND_VAL(x)       (((x)<<11) & GM_SMOD_DATABL_MSK)
#define DATA_BLIND_DEF          0x04

#define IPG_DATA_VAL(x)         (x & GM_SMOD_IPG_MSK)
#define IPG_DATA_DEF            0x1e


#define ETH_DATA_LEN    1500            /* Max. octets in payload        */



/* Receive Frame Status Encoding */
enum {
        GMR_FS_LEN      = 0xffff<<16, /* Bit 31..16:    Rx Frame Length */
        GMR_FS_VLAN     = 1<<13, /* VLAN Packet */
        GMR_FS_JABBER   = 1<<12, /* Jabber Packet */
        GMR_FS_UN_SIZE  = 1<<11, /* Undersize Packet */
        GMR_FS_MC       = 1<<10, /* Multicast Packet */
        GMR_FS_BC       = 1<<9,  /* Broadcast Packet */
        GMR_FS_RX_OK    = 1<<8,  /* Receive OK (Good Packet) */
        GMR_FS_GOOD_FC  = 1<<7,  /* Good Flow-Control Packet */
        GMR_FS_BAD_FC   = 1<<6,  /* Bad  Flow-Control Packet */
        GMR_FS_MII_ERR  = 1<<5,  /* MII Error */
        GMR_FS_LONG_ERR = 1<<4,  /* Too Long Packet */
        GMR_FS_FRAGMENT = 1<<3,  /* Fragment */

        GMR_FS_CRC_ERR  = 1<<1,  /* CRC Error */
        GMR_FS_RX_FF_OV = 1<<0,  /* Rx FIFO Overflow */

        GMR_FS_ANY_ERR  = GMR_FS_RX_FF_OV | GMR_FS_CRC_ERR |
                          GMR_FS_FRAGMENT | GMR_FS_LONG_ERR |
                          GMR_FS_MII_ERR | GMR_FS_BAD_FC | GMR_FS_GOOD_FC |
                          GMR_FS_UN_SIZE | GMR_FS_JABBER,
};


/* Transmit GMAC FIFO (YUKON only) */
enum {
        TX_GMF_EA       = 0x0d40,/* 32 bit      Tx GMAC FIFO End Address */
        TX_GMF_AE_THR   = 0x0d44,/* 32 bit      Tx GMAC FIFO Almost Empty Thresh.*/
        TX_GMF_CTRL_T   = 0x0d48,/* 32 bit      Tx GMAC FIFO Control/Test */

        TX_GMF_WP       = 0x0d60,/* 32 bit      Tx GMAC FIFO Write Pointer */
        TX_GMF_WSP      = 0x0d64,/* 32 bit      Tx GMAC FIFO Write Shadow Ptr. */
        TX_GMF_WLEV     = 0x0d68,/* 32 bit      Tx GMAC FIFO Write Level */

        TX_GMF_RP       = 0x0d70,/* 32 bit      Tx GMAC FIFO Read Pointer */
        TX_GMF_RSTP     = 0x0d74,/* 32 bit      Tx GMAC FIFO Restart Pointer */
        TX_GMF_RLEV     = 0x0d78,/* 32 bit      Tx GMAC FIFO Read Level */
};



/*      B0_CTST                 16 bit  Control/Status register */
enum {
        Y2_VMAIN_AVAIL  = 1<<17,/* VMAIN available (YUKON-2 only) */
        Y2_VAUX_AVAIL   = 1<<16,/* VAUX available (YUKON-2 only) */
        Y2_ASF_ENABLE   = 1<<13,/* ASF Unit Enable (YUKON-2 only) */
        Y2_ASF_DISABLE  = 1<<12,/* ASF Unit Disable (YUKON-2 only) */
        Y2_CLK_RUN_ENA  = 1<<11,/* CLK_RUN Enable  (YUKON-2 only) */
        Y2_CLK_RUN_DIS  = 1<<10,/* CLK_RUN Disable (YUKON-2 only) */
        Y2_LED_STAT_ON  = 1<<9, /* Status LED On  (YUKON-2 only) */
        Y2_LED_STAT_OFF = 1<<8, /* Status LED Off (YUKON-2 only) */

        CS_ST_SW_IRQ    = 1<<7, /* Set IRQ SW Request */
        CS_CL_SW_IRQ    = 1<<6, /* Clear IRQ SW Request */
        CS_STOP_DONE    = 1<<5, /* Stop Master is finished */
        CS_STOP_MAST    = 1<<4, /* Command Bit to stop the master */
        CS_MRST_CLR     = 1<<3, /* Clear Master reset   */
        CS_MRST_SET     = 1<<2, /* Set Master reset     */
        CS_RST_CLR      = 1<<1, /* Clear Software reset */
        CS_RST_SET      = 1,    /* Set   Software reset */
};


/*      B0_LED                   8 Bit  LED register */
enum {
/* Bit  7.. 2:  reserved */
        LED_STAT_ON     = 1<<1, /* Status LED on        */
        LED_STAT_OFF    = 1,    /* Status LED off       */
};


/* ASF Subsystem Registers (Yukon-2 only) */
enum {
        B28_Y2_SMB_CONFIG  = 0x0e40,/* 32 bit   ASF SMBus Config Register */
        B28_Y2_SMB_CSD_REG = 0x0e44,/* 32 bit   ASF SMB Control/Status/Data */
        B28_Y2_ASF_IRQ_V_BASE=0x0e60,/* 32 bit  ASF IRQ Vector Base */

        B28_Y2_ASF_STAT_CMD= 0x0e68,/* 32 bit   ASF Status and Command Reg */
        B28_Y2_ASF_HOST_COM= 0x0e6c,/* 32 bit   ASF Host Communication Reg */
        B28_Y2_DATA_REG_1  = 0x0e70,/* 32 bit   ASF/Host Data Register 1 */
        B28_Y2_DATA_REG_2  = 0x0e74,/* 32 bit   ASF/Host Data Register 2 */
        B28_Y2_DATA_REG_3  = 0x0e78,/* 32 bit   ASF/Host Data Register 3 */
        B28_Y2_DATA_REG_4  = 0x0e7c,/* 32 bit   ASF/Host Data Register 4 */
};


/* B28_Y2_ASF_STAT_CMD          32 bit  ASF Status and Command Reg */
enum {
        Y2_ASF_OS_PRES  = 1<<4, /* ASF operation system present */
        Y2_ASF_RESET    = 1<<3, /* ASF system in reset state */
        Y2_ASF_RUNNING  = 1<<2, /* ASF system operational */
        Y2_ASF_CLR_HSTI = 1<<1, /* Clear ASF IRQ */
        Y2_ASF_IRQ      = 1<<0, /* Issue an IRQ to ASF system */

        Y2_ASF_UC_STATE = 3<<2, /* ASF uC State */
        Y2_ASF_CLK_HALT = 0,    /* ASF system clock stopped */
};


/*      B2_TST_CTRL1     8 bit  Test Control Register 1 */
enum {
        TST_FRC_DPERR_MR = 1<<7, /* force DATAPERR on MST RD */
        TST_FRC_DPERR_MW = 1<<6, /* force DATAPERR on MST WR */
        TST_FRC_DPERR_TR = 1<<5, /* force DATAPERR on TRG RD */
        TST_FRC_DPERR_TW = 1<<4, /* force DATAPERR on TRG WR */
        TST_FRC_APERR_M  = 1<<3, /* force ADDRPERR on MST */
        TST_FRC_APERR_T  = 1<<2, /* force ADDRPERR on TRG */
        TST_CFG_WRITE_ON = 1<<1, /* Enable  Config Reg WR */
        TST_CFG_WRITE_OFF= 1<<0, /* Disable Config Reg WR */
};


/*      GMAC_IRQ_SRC     8 bit  GMAC Interrupt Source Reg (YUKON only) */
/*      GMAC_IRQ_MSK     8 bit  GMAC Interrupt Mask   Reg (YUKON only) */
enum {
        GM_IS_TX_CO_OV  = 1<<5, /* Transmit Counter Overflow IRQ */
        GM_IS_RX_CO_OV  = 1<<4, /* Receive Counter Overflow IRQ */
        GM_IS_TX_FF_UR  = 1<<3, /* Transmit FIFO Underrun */
        GM_IS_TX_COMPL  = 1<<2, /* Frame Transmission Complete */
        GM_IS_RX_FF_OR  = 1<<1, /* Receive FIFO Overrun */
        GM_IS_RX_COMPL  = 1<<0, /* Frame Reception Complete */

#define GMAC_DEF_MSK     GM_IS_TX_FF_UR

/*      GMAC_LINK_CTRL  16 bit  GMAC Link Control Reg (YUKON only) */
                                                /* Bits 15.. 2: reserved */
        GMLC_RST_CLR    = 1<<1, /* Clear GMAC Link Reset */
        GMLC_RST_SET    = 1<<0, /* Set   GMAC Link Reset */


/*      WOL_CTRL_STAT   16 bit  WOL Control/Status Reg */
        WOL_CTL_LINK_CHG_OCC            = 1<<15,
        WOL_CTL_MAGIC_PKT_OCC           = 1<<14,
        WOL_CTL_PATTERN_OCC             = 1<<13,
        WOL_CTL_CLEAR_RESULT            = 1<<12,
        WOL_CTL_ENA_PME_ON_LINK_CHG     = 1<<11,
        WOL_CTL_DIS_PME_ON_LINK_CHG     = 1<<10,
        WOL_CTL_ENA_PME_ON_MAGIC_PKT    = 1<<9,
        WOL_CTL_DIS_PME_ON_MAGIC_PKT    = 1<<8,
        WOL_CTL_ENA_PME_ON_PATTERN      = 1<<7,
        WOL_CTL_DIS_PME_ON_PATTERN      = 1<<6,
        WOL_CTL_ENA_LINK_CHG_UNIT       = 1<<5,
        WOL_CTL_DIS_LINK_CHG_UNIT       = 1<<4,
        WOL_CTL_ENA_MAGIC_PKT_UNIT      = 1<<3,
        WOL_CTL_DIS_MAGIC_PKT_UNIT      = 1<<2,
        WOL_CTL_ENA_PATTERN_UNIT        = 1<<1,
        WOL_CTL_DIS_PATTERN_UNIT        = 1<<0,
};


/*      B2_TI_CTRL               8 bit  Timer control */
/*      B2_IRQM_CTRL     8 bit  IRQ Moderation Timer Control */
enum {
        TIM_START       = 1<<2, /* Start Timer */
        TIM_STOP        = 1<<1, /* Stop  Timer */
        TIM_CLR_IRQ     = 1<<0, /* Clear Timer IRQ (!IRQM) */
};


/*      B28_DPT_CTRL     8 bit  Descriptor Poll Timer Ctrl Reg */
enum {
        DPT_START       = 1<<1,
        DPT_STOP        = 1<<0,
};

/* Descriptor Poll Timer Registers */
enum {
        B28_DPT_INI     = 0x0e00, /* 24 bit  Descriptor Poll Timer Init Val */
        B28_DPT_VAL     = 0x0e04, /* 24 bit  Descriptor Poll Timer Curr Val */
        B28_DPT_CTRL    = 0x0e08, /*  8 bit  Descriptor Poll Timer Ctrl Reg */

        B28_DPT_TST     = 0x0e0a, /*  8 bit  Descriptor Poll Timer Test Reg */
};


/* Time Stamp Timer Registers (YUKON only) */
enum {
        GMAC_TI_ST_VAL  = 0x0e14,/* 32 bit      Time Stamp Timer Curr Val */
        GMAC_TI_ST_CTRL = 0x0e18,/*  8 bit      Time Stamp Timer Ctrl Reg */
        GMAC_TI_ST_TST  = 0x0e1a,/*  8 bit      Time Stamp Timer Test Reg */
};


/*      GMAC_TI_ST_CTRL  8 bit  Time Stamp Timer Ctrl Reg (YUKON only) */
enum {
        GMT_ST_START    = 1<<2, /* Start Time Stamp Timer */
        GMT_ST_STOP     = 1<<1, /* Stop  Time Stamp Timer */
        GMT_ST_CLR_IRQ  = 1<<0, /* Clear Time Stamp Timer IRQ */
};



/*      TXA_CTRL                 8 bit  Tx Arbiter Control Register */
enum {
        TXA_ENA_FSYNC   = 1<<7, /* Enable  force of sync Tx queue */
        TXA_DIS_FSYNC   = 1<<6, /* Disable force of sync Tx queue */
        TXA_ENA_ALLOC   = 1<<5, /* Enable  alloc of free bandwidth */
        TXA_DIS_ALLOC   = 1<<4, /* Disable alloc of free bandwidth */
        TXA_START_RC    = 1<<3, /* Start sync Rate Control */
        TXA_STOP_RC     = 1<<2, /* Stop  sync Rate Control */
        TXA_ENA_ARB     = 1<<1, /* Enable  Tx Arbiter */
        TXA_DIS_ARB     = 1<<0, /* Disable Tx Arbiter */
};


/*
 *      Bank 4 - 5
 */
/* Transmit Arbiter Registers MAC 1 and 2, use SK_REG() to access */
enum {
        TXA_ITI_INI     = 0x0200,/* 32 bit      Tx Arb Interval Timer Init Val*/
        TXA_ITI_VAL     = 0x0204,/* 32 bit      Tx Arb Interval Timer Value */
        TXA_LIM_INI     = 0x0208,/* 32 bit      Tx Arb Limit Counter Init Val */
        TXA_LIM_VAL     = 0x020c,/* 32 bit      Tx Arb Limit Counter Value */
        TXA_CTRL        = 0x0210,/*  8 bit      Tx Arbiter Control Register */
        TXA_TEST        = 0x0211,/*  8 bit      Tx Arbiter Test Register */
        TXA_STAT        = 0x0212,/*  8 bit      Tx Arbiter Status Register */
};


/*      B3_RI_CTRL              16 bit  RAM Interface Control Register */
enum {
        RI_CLR_RD_PERR  = 1<<9, /* Clear IRQ RAM Read Parity Err */
        RI_CLR_WR_PERR  = 1<<8, /* Clear IRQ RAM Write Parity Err*/

        RI_RST_CLR      = 1<<1, /* Clear RAM Interface Reset */
        RI_RST_SET      = 1<<0, /* Set   RAM Interface Reset */
};

#define SK_RI_TO_53     36              /* RAM interface timeout */



/* Hardware error interrupt mask for Yukon 2 */
enum {
        Y2_IS_TIST_OV   = 1<<29,/* Time Stamp Timer overflow interrupt */
        Y2_IS_SENSOR    = 1<<28, /* Sensor interrupt */
        Y2_IS_MST_ERR   = 1<<27, /* Master error interrupt */
        Y2_IS_IRQ_STAT  = 1<<26, /* Status exception interrupt */
        Y2_IS_PCI_EXP   = 1<<25, /* PCI-Express interrupt */
        Y2_IS_PCI_NEXP  = 1<<24, /* PCI-Express error similar to PCI error */
                                                /* Link 2 */
        Y2_IS_PAR_RD2   = 1<<13, /* Read RAM parity error interrupt */
        Y2_IS_PAR_WR2   = 1<<12, /* Write RAM parity error interrupt */
        Y2_IS_PAR_MAC2  = 1<<11, /* MAC hardware fault interrupt */
        Y2_IS_PAR_RX2   = 1<<10, /* Parity Error Rx Queue 2 */
        Y2_IS_TCP_TXS2  = 1<<9, /* TCP length mismatch sync Tx queue IRQ */
        Y2_IS_TCP_TXA2  = 1<<8, /* TCP length mismatch async Tx queue IRQ */
                                                /* Link 1 */
        Y2_IS_PAR_RD1   = 1<<5, /* Read RAM parity error interrupt */
        Y2_IS_PAR_WR1   = 1<<4, /* Write RAM parity error interrupt */
        Y2_IS_PAR_MAC1  = 1<<3, /* MAC hardware fault interrupt */
        Y2_IS_PAR_RX1   = 1<<2, /* Parity Error Rx Queue 1 */
        Y2_IS_TCP_TXS1  = 1<<1, /* TCP length mismatch sync Tx queue IRQ */
        Y2_IS_TCP_TXA1  = 1<<0, /* TCP length mismatch async Tx queue IRQ */

        Y2_HWE_L1_MASK  = Y2_IS_PAR_RD1 | Y2_IS_PAR_WR1 | Y2_IS_PAR_MAC1 |
                          Y2_IS_PAR_RX1 | Y2_IS_TCP_TXS1| Y2_IS_TCP_TXA1,
        Y2_HWE_L2_MASK  = Y2_IS_PAR_RD2 | Y2_IS_PAR_WR2 | Y2_IS_PAR_MAC2 |
                          Y2_IS_PAR_RX2 | Y2_IS_TCP_TXS2| Y2_IS_TCP_TXA2,

        Y2_HWE_ALL_MASK = Y2_IS_TIST_OV | Y2_IS_MST_ERR | Y2_IS_IRQ_STAT |
                          Y2_IS_PCI_EXP |
                          Y2_HWE_L1_MASK | Y2_HWE_L2_MASK,
};




/* Status BMU Registers (Yukon-2 only)*/
enum {
        STAT_CTRL       = 0x0e80,/* 32 bit      Status BMU Control Reg */
        STAT_LAST_IDX   = 0x0e84,/* 16 bit      Status BMU Last Index */

        STAT_LIST_ADDR_LO= 0x0e88,/* 32 bit     Status List Start Addr (low) */
        STAT_LIST_ADDR_HI= 0x0e8c,/* 32 bit     Status List Start Addr (high) */
        STAT_TXA1_RIDX  = 0x0e90,/* 16 bit      Status TxA1 Report Index Reg */
        STAT_TXS1_RIDX  = 0x0e92,/* 16 bit      Status TxS1 Report Index Reg */
        STAT_TXA2_RIDX  = 0x0e94,/* 16 bit      Status TxA2 Report Index Reg */
        STAT_TXS2_RIDX  = 0x0e96,/* 16 bit      Status TxS2 Report Index Reg */
        STAT_TX_IDX_TH  = 0x0e98,/* 16 bit      Status Tx Index Threshold Reg */
        STAT_PUT_IDX    = 0x0e9c,/* 16 bit      Status Put Index Reg */

/* FIFO Control/Status Registers (Yukon-2 only)*/
        STAT_FIFO_WP    = 0x0ea0,/*  8 bit      Status FIFO Write Pointer Reg */
        STAT_FIFO_RP    = 0x0ea4,/*  8 bit      Status FIFO Read Pointer Reg */
        STAT_FIFO_RSP   = 0x0ea6,/*  8 bit      Status FIFO Read Shadow Ptr */
        STAT_FIFO_LEVEL = 0x0ea8,/*  8 bit      Status FIFO Level Reg */
        STAT_FIFO_SHLVL = 0x0eaa,/*  8 bit      Status FIFO Shadow Level Reg */
        STAT_FIFO_WM    = 0x0eac,/*  8 bit      Status FIFO Watermark Reg */
        STAT_FIFO_ISR_WM= 0x0ead,/*  8 bit      Status FIFO ISR Watermark Reg */

/* Level and ISR Timer Registers (Yukon-2 only)*/
        STAT_LEV_TIMER_INI= 0x0eb0,/* 32 bit    Level Timer Init. Value Reg */
        STAT_LEV_TIMER_CNT= 0x0eb4,/* 32 bit    Level Timer Counter Reg */
        STAT_LEV_TIMER_CTRL= 0x0eb8,/*  8 bit   Level Timer Control Reg */
        STAT_LEV_TIMER_TEST= 0x0eb9,/*  8 bit   Level Timer Test Reg */
        STAT_TX_TIMER_INI  = 0x0ec0,/* 32 bit   Tx Timer Init. Value Reg */
        STAT_TX_TIMER_CNT  = 0x0ec4,/* 32 bit   Tx Timer Counter Reg */
        STAT_TX_TIMER_CTRL = 0x0ec8,/*  8 bit   Tx Timer Control Reg */
        STAT_TX_TIMER_TEST = 0x0ec9,/*  8 bit   Tx Timer Test Reg */
        STAT_ISR_TIMER_INI = 0x0ed0,/* 32 bit   ISR Timer Init. Value Reg */
        STAT_ISR_TIMER_CNT = 0x0ed4,/* 32 bit   ISR Timer Counter Reg */
        STAT_ISR_TIMER_CTRL= 0x0ed8,/*  8 bit   ISR Timer Control Reg */
        STAT_ISR_TIMER_TEST= 0x0ed9,/*  8 bit   ISR Timer Test Reg */
};



/*      STAT_CTRL       32 bit  Status BMU control register (Yukon-2 only) */
enum {
        SC_STAT_CLR_IRQ = 1<<4, /* Status Burst IRQ clear */
        SC_STAT_OP_ON   = 1<<3, /* Operational Mode On */
        SC_STAT_OP_OFF  = 1<<2, /* Operational Mode Off */
        SC_STAT_RST_CLR = 1<<1, /* Clear Status Unit Reset (Enable) */
        SC_STAT_RST_SET = 1<<0, /* Set   Status Unit Reset */
};


/* B2_Y2_CLK_CTRL       32 bit  Clock Frequency Control Register (Yukon-2/EC) */
enum {
        Y2_CLK_DIV_VAL_MSK      = 0xff<<16,/* Bit 23..16: Clock Divisor Value */
#define Y2_CLK_DIV_VAL(x)       (((x)<<16) & Y2_CLK_DIV_VAL_MSK)
        Y2_CLK_DIV_VAL2_MSK     = 7<<21,   /* Bit 23..21: Clock Divisor Value */
        Y2_CLK_SELECT2_MSK      = 0x1f<<16,/* Bit 20..16: Clock Select */
#define Y2_CLK_DIV_VAL_2(x)     (((x)<<21) & Y2_CLK_DIV_VAL2_MSK)
#define Y2_CLK_SEL_VAL_2(x)     (((x)<<16) & Y2_CLK_SELECT2_MSK)
        Y2_CLK_DIV_ENA          = 1<<1, /* Enable  Core Clock Division */
        Y2_CLK_DIV_DIS          = 1<<0, /* Disable Core Clock Division */
};


/* Control flags */
enum {
        UDPTCP  = 1<<0,
        CALSUM  = 1<<1,
        WR_SUM  = 1<<2,
        INIT_SUM= 1<<3,
        LOCK_SUM= 1<<4,
        INS_VLAN= 1<<5,
        FRC_STAT= 1<<6,
        EOP     = 1<<7,
};


enum {
        HW_OWNER        = 1<<7,
        OP_TCPWRITE     = 0x11,
        OP_TCPSTART     = 0x12,
        OP_TCPINIT      = 0x14,
        OP_TCPLCK       = 0x18,
        OP_TCPCHKSUM    = OP_TCPSTART,
        OP_TCPIS        = OP_TCPINIT | OP_TCPSTART,
        OP_TCPLW        = OP_TCPLCK | OP_TCPWRITE,
        OP_TCPLSW       = OP_TCPLCK | OP_TCPSTART | OP_TCPWRITE,
        OP_TCPLISW      = OP_TCPLCK | OP_TCPINIT | OP_TCPSTART | OP_TCPWRITE,

        OP_ADDR64       = 0x21,
        OP_VLAN         = 0x22,
        OP_ADDR64VLAN   = OP_ADDR64 | OP_VLAN,
        OP_LRGLEN       = 0x24,
        OP_LRGLENVLAN   = OP_LRGLEN | OP_VLAN,
        OP_BUFFER       = 0x40,
        OP_PACKET       = 0x41,
        OP_LARGESEND    = 0x43,

/* YUKON-2 STATUS opcodes defines */
        OP_RXSTAT       = 0x60,
        OP_RXTIMESTAMP  = 0x61,
        OP_RXVLAN       = 0x62,
        OP_RXCHKS       = 0x64,
        OP_RXCHKSVLAN   = OP_RXCHKS | OP_RXVLAN,
        OP_RXTIMEVLAN   = OP_RXTIMESTAMP | OP_RXVLAN,
        OP_RSS_HASH     = 0x65,
        OP_TXINDEXLE    = 0x68,
};


enum {
        LINKLED_OFF          = 0x01,
        LINKLED_ON           = 0x02,
        LINKLED_LINKSYNC_OFF = 0x04,
        LINKLED_LINKSYNC_ON  = 0x08,
        LINKLED_BLINK_OFF    = 0x10,
        LINKLED_BLINK_ON     = 0x20,
};



/*
 * MIB Counters base address definitions (low word) -
 * use offset 4 for access to high word (32 bit r/o)
 */
enum {
        GM_RXF_UC_OK  = GM_MIB_CNT_BASE + 0,    /* Unicast Frames Received OK */
        GM_RXF_BC_OK    = GM_MIB_CNT_BASE + 8,  /* Broadcast Frames Received OK */
        GM_RXF_MPAUSE   = GM_MIB_CNT_BASE + 16, /* Pause MAC Ctrl Frames Received */
        GM_RXF_MC_OK    = GM_MIB_CNT_BASE + 24, /* Multicast Frames Received OK */
        GM_RXF_FCS_ERR  = GM_MIB_CNT_BASE + 32, /* Rx Frame Check Seq. Error */
        /* GM_MIB_CNT_BASE + 40:        reserved */
        GM_RXO_OK_LO    = GM_MIB_CNT_BASE + 48, /* Octets Received OK Low */
        GM_RXO_OK_HI    = GM_MIB_CNT_BASE + 56, /* Octets Received OK High */
        GM_RXO_ERR_LO   = GM_MIB_CNT_BASE + 64, /* Octets Received Invalid Low */
        GM_RXO_ERR_HI   = GM_MIB_CNT_BASE + 72, /* Octets Received Invalid High */
        GM_RXF_SHT      = GM_MIB_CNT_BASE + 80, /* Frames <64 Byte Received OK */
        GM_RXE_FRAG     = GM_MIB_CNT_BASE + 88, /* Frames <64 Byte Received with FCS Err */
        GM_RXF_64B      = GM_MIB_CNT_BASE + 96, /* 64 Byte Rx Frame */
        GM_RXF_127B     = GM_MIB_CNT_BASE + 104,        /* 65-127 Byte Rx Frame */
        GM_RXF_255B     = GM_MIB_CNT_BASE + 112,        /* 128-255 Byte Rx Frame */
        GM_RXF_511B     = GM_MIB_CNT_BASE + 120,        /* 256-511 Byte Rx Frame */
        GM_RXF_1023B    = GM_MIB_CNT_BASE + 128,        /* 512-1023 Byte Rx Frame */
        GM_RXF_1518B    = GM_MIB_CNT_BASE + 136,        /* 1024-1518 Byte Rx Frame */
        GM_RXF_MAX_SZ   = GM_MIB_CNT_BASE + 144,        /* 1519-MaxSize Byte Rx Frame */
        GM_RXF_LNG_ERR  = GM_MIB_CNT_BASE + 152,        /* Rx Frame too Long Error */
        GM_RXF_JAB_PKT  = GM_MIB_CNT_BASE + 160,        /* Rx Jabber Packet Frame */
        /* GM_MIB_CNT_BASE + 168:       reserved */
        GM_RXE_FIFO_OV  = GM_MIB_CNT_BASE + 176,        /* Rx FIFO overflow Event */
        /* GM_MIB_CNT_BASE + 184:       reserved */
        GM_TXF_UC_OK    = GM_MIB_CNT_BASE + 192,        /* Unicast Frames Xmitted OK */
        GM_TXF_BC_OK    = GM_MIB_CNT_BASE + 200,        /* Broadcast Frames Xmitted OK */
        GM_TXF_MPAUSE   = GM_MIB_CNT_BASE + 208,        /* Pause MAC Ctrl Frames Xmitted */
        GM_TXF_MC_OK    = GM_MIB_CNT_BASE + 216,        /* Multicast Frames Xmitted OK */
        GM_TXO_OK_LO    = GM_MIB_CNT_BASE + 224,        /* Octets Transmitted OK Low */
        GM_TXO_OK_HI    = GM_MIB_CNT_BASE + 232,        /* Octets Transmitted OK High */
        GM_TXF_64B      = GM_MIB_CNT_BASE + 240,        /* 64 Byte Tx Frame */
        GM_TXF_127B     = GM_MIB_CNT_BASE + 248,        /* 65-127 Byte Tx Frame */
        GM_TXF_255B     = GM_MIB_CNT_BASE + 256,        /* 128-255 Byte Tx Frame */
        GM_TXF_511B     = GM_MIB_CNT_BASE + 264,        /* 256-511 Byte Tx Frame */
        GM_TXF_1023B    = GM_MIB_CNT_BASE + 272,        /* 512-1023 Byte Tx Frame */
        GM_TXF_1518B    = GM_MIB_CNT_BASE + 280,        /* 1024-1518 Byte Tx Frame */
        GM_TXF_MAX_SZ   = GM_MIB_CNT_BASE + 288,        /* 1519-MaxSize Byte Tx Frame */

        GM_TXF_COL      = GM_MIB_CNT_BASE + 304,        /* Tx Collision */
        GM_TXF_LAT_COL  = GM_MIB_CNT_BASE + 312,        /* Tx Late Collision */
        GM_TXF_ABO_COL  = GM_MIB_CNT_BASE + 320,        /* Tx aborted due to Exces. Col. */
        GM_TXF_MUL_COL  = GM_MIB_CNT_BASE + 328,        /* Tx Multiple Collision */
        GM_TXF_SNG_COL  = GM_MIB_CNT_BASE + 336,        /* Tx Single Collision */
        GM_TXE_FIFO_UR  = GM_MIB_CNT_BASE + 344,        /* Tx FIFO Underrun Event */
};


/*      Q_F                             32 bit  Flag Register */
enum {
        F_ALM_FULL      = 1<<27, /* Rx FIFO: almost full */
        F_EMPTY         = 1<<27, /* Tx FIFO: empty flag */
        F_FIFO_EOF      = 1<<26, /* Tag (EOF Flag) bit in FIFO */
        F_WM_REACHED    = 1<<25, /* Watermark reached */
        F_M_RX_RAM_DIS  = 1<<24, /* MAC Rx RAM Read Port disable */
        F_FIFO_LEVEL    = 0x1fL<<16, /* Bit 23..16:     # of Qwords in FIFO */
        F_WATER_MARK    = 0x0007ffL, /* Bit 10.. 0:     Watermark */
};

#ifndef _TIMER_SA1100_H_
#define _TIMER_SA1100_H_

#define SA1100_TIMERS_PHYS  0x90000000

#define OST_MR0_OFFSET	    0x000
#define OST_MR1_OFFSET	    0x004
#define OST_MR2_OFFSET	    0x008
#define OST_MR3_OFFSET	    0x00c
#define OST_CR_OFFSET	    0x010
#define OST_SR_OFFSET	    0x014
#define OST_WER_OFFSET	    0x018
#define OST_IER_OFFSET	    0x01C

extern uintptr_t SA1100_TIMERS_VADDR;

#define SA1100_OS_TIMER_OSCR     (*(volatile uintptr_t *)(SA1100_TIMERS_VADDR + OST_CR_OFFSET ))
#define SA1100_OS_TIMER_OIER     (*(volatile uintptr_t *)(SA1100_TIMERS_VADDR + OST_IER_OFFSET))

#define SA1100_OS_TIMER_OSMR0    (*(volatile uintptr_t *)(SA1100_TIMERS_VADDR + OST_MR0_OFFSET))
#define SA1100_OS_TIMER_OSMR1    (*(volatile uintptr_t *)(SA1100_TIMERS_VADDR + OST_MR1_OFFSET))
#define SA1100_OS_TIMER_OSMR2    (*(volatile uintptr_t *)(SA1100_TIMERS_VADDR + OST_MR2_OFFSET))
#define SA1100_OS_TIMER_OSMR3    (*(volatile uintptr_t *)(SA1100_TIMERS_VADDR + OST_MR3_OFFSET))

#define SA1100_OS_TIMER_OSSR     (*(volatile uintptr_t *)(SA1100_TIMERS_VADDR + OST_SR_OFFSET ))

#define IRQ_OSTMR0	26	/* OS timer match register 0 IRQ, used by L4 ticks */
#define IRQ_OSTMR1	27	/* OS timer match register 1 IRQ, we use it to detect rollover */
#define IRQ_OSTMR2	28	/* OS timer match register 2 IRQ  we use to sleep() */


#define TIMER_RATE	3686400	/* Timer freq in Hz */

/* Allows for 253 years before overflow */
#define TICKS_TO_US(ticks)	((ticks) * 625 / 2304)
#define US_TO_TICKS(us)		((us) * 2304 / 625)

#endif

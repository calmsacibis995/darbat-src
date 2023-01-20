#ifndef _TIMER_GT64XXX_H_
#define _TIMER_GT64XXX_H_

#define GT64XXX_IO_AREA		0x14000000

#define GT_T0_OFFSET		0x850
#define GT_T1_OFFSET		0x854
#define GT_T2_OFFSET		0x858
#define GT_T3_OFFSET		0x85C
#define GT_TC_OFFSET		0x864

#define GT_INT_CAUSE		0xc18
#define GT_INT_MASK		0xc1c

#define GT_TIMERS_PHYS	    (GT64XXX_IO_AREA)
extern uintptr_t GT_TIMERS_VADDR;

#define GT_TIMER_0	    (volatile uint32_t *)(GT_TIMERS_VADDR + GT_T0_OFFSET)
#define GT_TIMER_1	    (volatile uint32_t *)(GT_TIMERS_VADDR + GT_T1_OFFSET)
#define GT_TIMER_2	    (volatile uint32_t *)(GT_TIMERS_VADDR + GT_T2_OFFSET)
#define GT_TIMER_3	    (volatile uint32_t *)(GT_TIMERS_VADDR + GT_T3_OFFSET)
#define GT_TIMER_CONTROL    (volatile uint32_t *)(GT_TIMERS_VADDR + GT_TC_OFFSET)

#define GT_INTERRUPT_CAUSE  (volatile uint32_t *)(GT_TIMERS_VADDR + GT_INT_CAUSE)
#define GT_INTERRUPT_MASK   (volatile uint32_t *)(GT_TIMERS_VADDR + GT_INT_MASK)

/* XXX U4600 specific interrupt numbers / frequencies */
#define IRQ_GT		5

#define TIMER_RATE	50000000 /* Timer freq in Hz */

/* Allows for > 10000 years before overflow */
#define TICKS_TO_US(ticks)	((ticks) / 50)
#define US_TO_TICKS(us)		((us) * 50)

#define REVERSE_ENDIAN

#ifdef REVERSE_ENDIAN
# define gt_read(adr)	    ({		\
	uint32_t x = *(adr);		\
	x = (x >> 24) |			\
	    ((x >> 8) & 0x00ff00) |	\
	    ((x << 8) & 0xff0000) |	\
	    (x << 24);			\
	x;				\
})
# define gt_write(adr, d)   {		\
	uint32_t x = d;			\
	x = (x >> 24) |			\
	    ((x >> 8) & 0xff00) |	\
	    ((x << 8) & 0xff0000) |	\
	    (x << 24);			\
	*(adr) = x;			\
}
#else
# define gt_read(adr)	    *(adr)
# define gt_write(adr, x)   *(adr) = x
#endif

#endif

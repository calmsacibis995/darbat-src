/* XXX make this more generic */

#define PIT_FREQ    1193180

/* Allows for 9.8 years before overflow */
#define TICKS_TO_US(ticks)	((ticks) * 50000 / 59659)
#define US_TO_TICKS(us)		((us) * 59659 / 50000)

#define PIT_CNT_0   0x40
#define PIT_CNT_1   0x41
#define PIT_CNT_2   0x42
#define PIT_MCR	    0x43

struct {
	uint8_t bcd_mode    : 1;
	uint8_t mode	    : 3;
	uint8_t latch	    : 2;
	uint8_t counter_sel : 2;
} i8254_mcr_t;

#define BINARY		0x0
#define BCD		0x1

#define LATCH_COUNTER	0x0
#define LATCH_MSB	0x1
#define LATCH_LSB	0x2
#define LATCH_LSB_MSB	0x3

#define COUNTER_SEL_0	0x0
#define COUNTER_SEL_1	0x1
#define COUNTER_SEL_2	0x2
#define COUNTER_SEL_READBACK	0x3

#define MODE_COUNTDOWN	0x0
#define MODE_ONESHOT	0x1
#define MODE_RATEGEN	0x2
#define MODE_SQUARE	0x3
#define MODE_STROBE_SW	0x4
#define MODE_STROBE_HW	0x5

/*
0x34 = 00110100
0	- binary
010	- rategen
11	- latch_lsb_msb
00	- counter 0
*/

/*
0x32 = 00110010
0	- binary
001	- oneshot
11	- latch_lsb_msb
00	- counter 0
*/

#define STROBE_SW_MODE	0x38

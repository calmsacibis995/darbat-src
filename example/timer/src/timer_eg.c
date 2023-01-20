/*
 * Australian Public Licence B (OZPLB)
 * 
 * Version 1-0
 * 
 * Copyright (c) 2004 National ICT Australia
 * 
 * All rights reserved. 
 * 
 * Developed by: Embedded, Real-time and Operating Systems Program (ERTOS)
 *               National ICT Australia
 *               http://www.ertos.nicta.com.au
 * 
 * Permission is granted by National ICT Australia, free of charge, to
 * any person obtaining a copy of this software and any associated
 * documentation files (the "Software") to deal with the Software without
 * restriction, including (without limitation) the rights to use, copy,
 * modify, adapt, merge, publish, distribute, communicate to the public,
 * sublicense, and/or sell, lend or rent out copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimers.
 * 
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimers in the documentation and/or other materials provided
 *       with the distribution.
 * 
 *     * Neither the name of National ICT Australia, nor the names of its
 *       contributors, may be used to endorse or promote products derived
 *       from this Software without specific prior written permission.
 * 
 * EXCEPT AS EXPRESSLY STATED IN THIS LICENCE AND TO THE FULL EXTENT
 * PERMITTED BY APPLICABLE LAW, THE SOFTWARE IS PROVIDED "AS-IS", AND
 * NATIONAL ICT AUSTRALIA AND ITS CONTRIBUTORS MAKE NO REPRESENTATIONS,
 * WARRANTIES OR CONDITIONS OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO ANY REPRESENTATIONS, WARRANTIES OR CONDITIONS
 * REGARDING THE CONTENTS OR ACCURACY OF THE SOFTWARE, OR OF TITLE,
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, NONINFRINGEMENT,
 * THE ABSENCE OF LATENT OR OTHER DEFECTS, OR THE PRESENCE OR ABSENCE OF
 * ERRORS, WHETHER OR NOT DISCOVERABLE.
 * 
 * TO THE FULL EXTENT PERMITTED BY APPLICABLE LAW, IN NO EVENT SHALL
 * NATIONAL ICT AUSTRALIA OR ITS CONTRIBUTORS BE LIABLE ON ANY LEGAL
 * THEORY (INCLUDING, WITHOUT LIMITATION, IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY CLAIM, LOSS, DAMAGES OR OTHER
 * LIABILITY, INCLUDING (WITHOUT LIMITATION) LOSS OF PRODUCTION OR
 * OPERATION TIME, LOSS, DAMAGE OR CORRUPTION OF DATA OR RECORDS; OR LOSS
 * OF ANTICIPATED SAVINGS, OPPORTUNITY, REVENUE, PROFIT OR GOODWILL, OR
 * OTHER ECONOMIC LOSS; OR ANY SPECIAL, INCIDENTAL, INDIRECT,
 * CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES, ARISING OUT OF OR IN
 * CONNECTION WITH THIS LICENCE, THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS WITH THE SOFTWARE, EVEN IF NATIONAL ICT AUSTRALIA OR ITS
 * CONTRIBUTORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH CLAIM, LOSS,
 * DAMAGES OR OTHER LIABILITY.
 * 
 * If applicable legislation implies representations, warranties, or
 * conditions, or imposes obligations or liability on National ICT
 * Australia or one of its contributors in respect of the Software that
 * cannot be wholly or partly excluded, restricted or modified, the
 * liability of National ICT Australia or the contributor is limited, to
 * the full extent permitted by the applicable legislation, at its
 * option, to:
 * a.  in the case of goods, any one or more of the following:
 * i.  the replacement of the goods or the supply of equivalent goods;
 * ii.  the repair of the goods;
 * iii. the payment of the cost of replacing the goods or of acquiring
 *  equivalent goods;
 * iv.  the payment of the cost of having the goods repaired; or
 * b.  in the case of services:
 * i.  the supplying of the services again; or
 * ii.  the payment of the cost of having the services supplied again.
 * 
 * The construction, validity and performance of this licence is governed
 * by the laws in force in New South Wales, Australia.
 */
/*
  Author: Ben Leslie
  Created: Wed Nov  3 2004 
*/

#include <stdio.h>
#include <timer/timer.h>
#include <inttypes.h>
#include <assert.h>
#include <l4/kdebug.h>
#include <stdlib.h>

#ifndef ARCH_IA32
#define SPIN_I 9999
#define SPIN_MOD 1000
#else
#define SPIN_I 999999
#define SPIN_MOD 100000
#endif

int
main(int argc, char **argv)
{
	timer_t timer, timer2;
	timer_t timer_ret;
	int r, i;
	uint64_t t_2, t_1;
	uint64_t remaining;

	timer_init();

	printf("Timer example begin!\n");

	t_1 = timer_current_time();
	t_2 = timer_current_time();

	printf("Get time overhead: %" PRId64 "\n", t_2 - t_1);
	
	/* Create a timer */
	timer = timer_create();
	assert(timer != NULL);

	/* Timer test 1 -- A simple wait.. */
	t_1 = timer_current_time();
	r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
	assert(r != -1);
	if (timer_expired(timer) != 1) {
		printf("timer->wakeup: %" PRId64 " %" PRId64 "\n", timer->wakeup_time, timer_current_time());
		assert(timer_expired(timer) != 1);
	}
	remaining = timer_remaining(timer);
	if (remaining <= 0 || remaining > MILLISECS(10)) {
		printf("Remaining: %" PRId64 " timer->wakeup %" PRId64 " current_timer %" PRId64 "\n", 
		       remaining, timer->wakeup_time, timer_current_time());
		assert(remaining > 0 && remaining <= MILLISECS(10));
	}

	/* Wait for interrupt */
	timer_ret = timer_wait();
	printf("timer_ret: %p\n", timer_ret);
	assert(timer_ret == timer);
	t_2 = timer_current_time();

	printf("Was waiting for 10ms, actual: %" PRId64 " t_2: %" PRId64 \
	       " timer->wakeup_timer: %" PRId64 " diff: %" PRId64 "\n", 
	       t_2 - t_1, t_2, timer->wakeup_time, t_2 - timer->wakeup_time);


	printf("===> TEST 1 PASSED\n");

	/* Timer test 2 -- Setup timeout, but spin past the end of it */

	r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
	assert(r != -1);

	printf("Spinning ");
	for(i=0; i < SPIN_I; i++) {
		if ((i % SPIN_MOD) == 0) {
			printf(".");
		};
	}
	printf("\n Spin over.. wakeup now!\n");
	t_1 = timer_current_time();
	timer_wait();
	t_2 = timer_current_time();
	printf("Was waiting for 10ms, but should wake up fast: %" PRId64 "\n", t_2 - t_1);

	printf("===> TEST 2 PASSED\n");

	/* Timer test 3 -- two outstanding timers */
	timer2 = timer_create();
	assert(timer2 != NULL);
	timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
	timer_request(timer2, MILLISECS(100), TIMER_ONESHOT);
	/* Wait for the first timeout */
	timer_wait();
	t_1 = timer_current_time();
	/* Wait for the second timeout */
	timer_wait();
	t_2 = timer_current_time();

	printf("t_1: %" PRId64 " timer->wakeup: %" PRId64 " diff: %" PRId64 "\n", 
	       t_1, timer->wakeup_time, t_1 - timer->wakeup_time);

	printf("t_2: %" PRId64 " timer2->wakeup: %" PRId64 " diff: %" PRId64 "\n", 
	       t_2, timer2->wakeup_time, t_2 - timer2->wakeup_time);


	printf("===> TEST 3 PASSED\n");
	/* Timer test 4 -- calling timer request twice should update the time */
	{
		uint64_t original_wakeup;
		r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
		assert(r == 0);
		original_wakeup = timer->wakeup_time;
		for(i=0; i < SPIN_I; i++) {
			if ((i % SPIN_MOD) == 0) {
				printf(".");
			};
		}
		r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
		assert(r == 0);
		timer_wait();
		t_1 = timer_current_time();
		printf("\nUpdate test..: orig wakeup %" PRId64 " new wakeup: %" PRId64 " actual wakeup %" PRId64 "\n",
		       original_wakeup, timer->wakeup_time, t_1);
	}
	printf("===> TEST 4 PASSED\n");


	/* Timer test 5 -- set a timer, and then cancel it */
	{
		uint64_t original_wakeup;
		r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
		assert(r == 0);
		original_wakeup = timer->wakeup_time;
		r = timer_cancel(timer);
		assert(r == 0);
		r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
		assert(r == 0);
		timer_wait();
		t_1 = timer_current_time();
		printf("Cancel test..: orig wakeup %" PRId64 " new wakeup: %" PRId64 " actual wakeup %" PRId64 "\n",
		       original_wakeup, timer->wakeup_time, t_1);
	}
	printf("===> TEST 5 PASSED\n");

	/* Timer test 6 -- setup 2 two timers and then cancel the first one */
	{
		uint64_t original_wakeup;
		r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
		assert(r == 0);
		original_wakeup = timer->wakeup_time;

		r = timer_request(timer2, MILLISECS(50), TIMER_ONESHOT);
		assert(r == 0);

		r = timer_cancel(timer);
		assert(r == 0);

		timer_wait();
		t_1 = timer_current_time();
		printf("Cancel test(2)..: orig wakeup %" PRId64 " new wakeup: %" PRId64 " actual wakeup %" PRId64 "\n",
		       original_wakeup, timer2->wakeup_time, t_1);
	}
	printf("===> TEST 6 PASSED\n");

	/* Timer test 7 -- as for test 6, but delete rather than just cancel */
	{
		uint64_t original_wakeup;
		r = timer_request(timer, MILLISECS(10), TIMER_ONESHOT);
		assert(r == 0);
		original_wakeup = timer->wakeup_time;

		r = timer_request(timer2, MILLISECS(50), TIMER_ONESHOT);
		assert(r == 0);

		r = timer_delete(timer);
		assert(r == 0);
		timer_wait();
		t_1 = timer_current_time();
		printf("Delete test..: orig wakeup %" PRId64 " new wakeup: %" PRId64 " actual wakeup %" PRId64 "\n",
		       original_wakeup, timer2->wakeup_time, t_1);
	}
	printf("===> TEST 7 PASSED\n");

	/* Timer test n-1 -- lots of outstanding timers */
	{
#define TIMERS 10
		timer_t timers[TIMERS];
		uint64_t times[TIMERS];
		uint64_t timeouts[TIMERS] = {MILLISECS(40), MILLISECS(50), MILLISECS(500),
					     MILLISECS(75), MILLISECS(60), MILLISECS(60),
					     MILLISECS(100), MILLISECS(140), MILLISECS(120),
					     MILLISECS(200)};
		for (i=0; i < TIMERS; i++) {
			timers[i] = timer_create();
			timers[i]->data = i;
			assert(timers[i] != 0);
		}

		for (i=0; i < TIMERS; i++) {
			timer_request(timers[i], timeouts[i], TIMER_ONESHOT);
		}
		for (i=0; i < TIMERS; i++) {
			timer_ret = timer_wait();
			times[timer_ret->data] = timer_current_time();
		}
		
		for (i=0; i < TIMERS; i++) {
			printf("%d: Timeout: %" PRId64 " Actual: %" PRId64 " Predicted: %" PRId64 " Difference: %" PRId64 "\n",
			       i, timeouts[i], times[i], timers[i]->wakeup_time, times[i] - timers[i]->wakeup_time);
		}
	}
	printf("===> TEST 8 PASSED\n");

	/* Periodic Tests */


	timer = timer_create();  /* We delete it in the delete test */
	r = timer_request(timer, MILLISECS(10), TIMER_PERIODIC);
	assert(r == 0);
	{
#define PERIOD_TIMES 20
		uint64_t times[PERIOD_TIMES];
		
		for (i=0; i < PERIOD_TIMES; i++) {
			timer_ret = timer_wait();
			times[i] = timer_current_time();
			assert(timer_ret == timer);
		}
		for (i=0; i < PERIOD_TIMES; i++) {
			printf("%d -- woke at: %" PRId64 , i, times[i]);
			if (i > 0) {
				printf("  diff: %" PRId64, times[i] - times[i-1]);
				printf("  avg-diff: %" PRId64 "\n", (times[i] - times[0]) / (i));
			} else {
				printf("\n");
			}
		}

	}

	/* Absolute one-shot tests */

	printf("TIMER TEST PASSED\n");
	return 12;
}

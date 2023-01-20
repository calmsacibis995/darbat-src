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
  Created: Tue Nov  9 2004 
*/

#include <stdio.h>
#include <assert.h>
#include <naming/naming.h>
#include <l4/thread.h>
#include <l4/kdebug.h>

int
main(int argc, char **argv)
{
	naming_notify_t notify, notify_ret, notify2;
	int r;

	printf("Naming example startup\n");

	/* Test 1 -- Insert and Lookup */
	r = naming_insert("testname", 0x37);
	assert(r == 0);
	assert(naming_lookup("testname") == 0x37);
	printf("===> TEST 1 PASSED\n");

	/* Test 2 -- Lookup a non existant item */
	assert(naming_lookup("noexist") == 0x0);
	printf("===> TEST 2 PASSED\n");


	/* Test 3 -- Delete */
	r = naming_delete("testname");
	assert(r == 0);
	assert(naming_lookup("testname") == 0x0);
	printf("===> TEST 3 PASSED\n");

	/* Test 4 -- Reinsert */
	r  = naming_insert("testname", 0x25);
	assert(r == 0);
	assert(naming_lookup("testname") == 0x25);
	printf("===> TEST 4 PASSED\n");

	/* Test 5 -- Insert already existing */
	r = naming_insert("testname", 0x15);
	assert(r != 0);
	assert(naming_lookup("testname") == 0x25);
	printf("===> TEST 5 PASSED\n");


	/* Test 6 -- Insert a few more names */
	r = naming_insert("2", 2);
	assert(r == 0);
	r = naming_insert("3", 3);
	assert(r == 0);
	r = naming_insert("4", 4);
	assert(r == 0);
	r = naming_insert("5", 5);
	assert(r == 0);

	assert(naming_lookup("2") == 2);
	assert(naming_lookup("3") == 3);
	assert(naming_lookup("4") == 4);
	assert(naming_lookup("5") == 5);

	printf("===> TEST 6 PASSED\n");

	/* Test 7 -- Delete some names, leave others */
	r = naming_delete("4");
	assert(r == 0);
	r = naming_delete("2");
	assert(r == 0);
	assert(naming_lookup("2") == 0);
	assert(naming_lookup("3") == 3);
	assert(naming_lookup("4") == 0);
	assert(naming_lookup("5") == 5);

	printf("===> TEST 7 PASSED\n");

	/* Test 8 -- Delete non-existing */
	r = naming_delete("20");
	assert(r != 0);

	printf("===> TEST 8 PASSED\n");

	/* Test 9 -- Modify */
	r = naming_modify("testname", 0x50);
	assert(r == 0);
	assert(naming_lookup("testname") == 0x50);

	printf("===> TEST 9 PASSED\n");

	/* Test 10 -- Modify non existing */
	r = naming_modify("noexist", 0x50);
	assert(r != 0);
	printf("===> TEST 10 PASSED\n");

	/* Test 11 -- Notify a non-existing thing */
	notify = naming_notify("foobar", NAMING_NOTIFY_INSERT);
	assert(notify != NULL);
	r = naming_insert("foobar", 0x25);
	assert(r == 0);
	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify);
	printf("===> TEST 11 PASSED\n");
	
	/* Test 12 -- Notify an existing thing */
	notify2 = naming_notify("foobar", NAMING_NOTIFY_INSERT);
	assert(notify != NULL);
	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify2);
	printf("===> TEST 12 PASSED\n");

	/* Test 13 -- delete a name that has create notifiers, and then recreate */
	r = naming_delete("foobar");
	assert(r == 0);
	r = naming_insert("foobar", 0x25);
	assert(r == 0);

	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify || notify_ret == notify2);
	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify || notify_ret == notify2);
	printf("===> TEST 13 PASSED\n");
	
	/* Test 14 -- cancel notification */
	r = naming_cancel(notify);
	assert(r == 0);
	naming_cancel(notify2);
	assert(r == 0);
	printf("===> TEST 14 PASSED\n");

	/* Test 15 -- multiple notifications + modify */
	notify = naming_notify("foobar", NAMING_NOTIFY_INSERT | NAMING_NOTIFY_MODIFY | NAMING_NOTIFY_DELETE);
	assert(notify != NULL);
	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify);

	notify2 = naming_notify("foobar", NAMING_NOTIFY_MODIFY);
	assert(notify2 != NULL);

	r = naming_modify("foobar", 0x12);
	assert(r == 0);

	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify || notify_ret == notify2);
	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify || notify_ret == notify2);
	printf("===> TEST 15 PASSED\n");

	/* Test 16 -- multiple notificats + delete */
	naming_cancel(notify2);
	assert(r == 0);
	notify2 = naming_notify("foobar", NAMING_NOTIFY_DELETE);
	assert(notify2 != NULL);

	r = naming_delete("foobar");
	assert(r == 0);

	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify || notify_ret == notify2);
	notify_ret = naming_wait(NULL);
	assert(notify_ret == notify || notify_ret == notify2);
	printf("===> TEST 16 PASSED\n");

	/* Test 17 -- try a poll when nothing should be available */
	notify2 = naming_notify("not_exist", NAMING_NOTIFY_INSERT);
	notify_ret = naming_poll(NULL);
	assert(notify_ret == NULL);
	printf("===> TEST 17 PASSED\n");
	
	printf("Naming works!\n");
}

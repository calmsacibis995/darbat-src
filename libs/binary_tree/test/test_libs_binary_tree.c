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
#include <stddef.h>
#include <string.h>
#include <check.h>
#include "test_libs_binary_tree.h"

static struct bin_tree *
setup_balanced_tree(void)
{
	struct bin_tree *bin_tree;
	static int data[16];
	int i;
	
	for ( i=0; i<16; i++ )
		data[i] = i;
		
	bin_tree = binary_tree_new();
	fail_unless(binary_tree_insert(bin_tree, "h", &data[8]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "d", &data[4]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "l", &data[12]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "b", &data[2]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "f", &data[6]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "j", &data[10]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "n", &data[14]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "a", &data[1]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "c", &data[3]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "e", &data[5]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "g", &data[7]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "i", &data[9]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "k", &data[11]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "m", &data[13]) == 0, "Couldn't insert");
	fail_unless(binary_tree_insert(bin_tree, "o", &data[15]) == 0, "Couldn't insert");

	return bin_tree;
}

void
check_balanced_tree(struct bin_tree *bin_tree, char *chars)
{
	char key[2];
	int i;
	key[1] = '\0';
	for (i=0; i < strlen(chars); i++) {
		key[0] = chars[i];
		fail_unless(*((int*) binary_tree_lookup(bin_tree, key)) == chars[i] - 'a' + 1, "Didn't lookup right value");
	}
}

void
check_notin_tree(struct bin_tree *bin_tree, char *chars)
{
	static char key[2];
	int i;
	key[1] = '\0';
	for (i=0; i < strlen(chars); i++) {
		key[0] = chars[i];
		fail_unless(binary_tree_lookup(bin_tree, key) == 0, "Found key that shouldn't be in tree");
	}
}


START_TEST(test_binary_tree_remove)
{
	struct bin_tree *bin_tree;
	int data=1;

	bin_tree = binary_tree_new();

	/* Simple case */
	fail_unless(binary_tree_insert(bin_tree, "foo", &data) == 0, "Couldn't insert foo");
	fail_unless(*((int*) binary_tree_lookup(bin_tree, "foo")) == 1, "Didn't lookup right value");
	fail_unless(binary_tree_remove(bin_tree, "foo") == 0, "Didn't remove entry");
	fail_unless(binary_tree_lookup(bin_tree, "foo") == 0, "Still looked up value after remove");

	bin_tree = setup_balanced_tree();

	fail_unless(binary_tree_remove(bin_tree, "l") == 0, "Didn't remove entry");
	check_balanced_tree(bin_tree, "abcdefghijkmno");
	check_notin_tree(bin_tree, "l");

	fail_unless(binary_tree_remove(bin_tree, "k") == 0, "Didn't remove entry");
	check_balanced_tree(bin_tree, "abcdefghijmno");
	check_notin_tree(bin_tree, "lk");

	fail_unless(binary_tree_remove(bin_tree, "j") == 0, "Didn't remove entry");
	check_balanced_tree(bin_tree, "abcdefghimno");
	check_notin_tree(bin_tree, "lkj");

	fail_unless(binary_tree_remove(bin_tree, "i") == 0, "Didn't remove entry");
	check_balanced_tree(bin_tree, "abcdefghmno");
	check_notin_tree(bin_tree, "lkji");

	fail_unless(binary_tree_remove(bin_tree, "b") == 0, "Didn't remove entry");
	check_balanced_tree(bin_tree, "acdefghmno");
	check_notin_tree(bin_tree, "lkjib");

	fail_unless(binary_tree_remove(bin_tree, "h") == 0, "Didn't remove entry");
	check_balanced_tree(bin_tree, "acdefgmno");
	check_notin_tree(bin_tree, "lkjibh");

	fail_unless(binary_tree_remove(bin_tree, "d") == 0, "Didn't remove entry");
	check_balanced_tree(bin_tree, "acefgmno");
	check_notin_tree(bin_tree, "lkjibhd");
}
END_TEST


START_TEST(test_binary_tree_insert_duplicate)
{
	struct bin_tree *bin_tree;
	int data=1;

	bin_tree = binary_tree_new();

	fail_unless(binary_tree_insert(bin_tree, "foo", &data) == 0, "Couldn't insert foo");
	fail_unless(binary_tree_insert(bin_tree, "foo", &data) != 0, "Could insert foo, shouldn't be able to");
}
END_TEST


START_TEST(test_binary_tree_insert)
{
	struct bin_tree *bin_tree;
	int data[4], i;
	
	for ( i=0; i<4; i++ )
		data[i] = i;
		
	bin_tree = binary_tree_new();

	fail_unless(binary_tree_insert(bin_tree, "foo", &data[1]) == 0, "Couldn't insert foo");
	fail_unless(binary_tree_insert(bin_tree, "bar", &data[2]) == 0, "Couldn't insert bar");
	fail_unless(binary_tree_insert(bin_tree, "baz", &data[3]) == 0, "Couldn't insert baz");

	fail_unless(*((int*) binary_tree_lookup(bin_tree, "foo")) == 1, "Didn't lookup right value");
	fail_unless(*((int*) binary_tree_lookup(bin_tree, "bar")) == 2, "Didn't lookup right value");
	fail_unless(*((int*) binary_tree_lookup(bin_tree, "baz")) == 3, "Didn't lookup right value");

}
END_TEST


START_TEST(test_binary_tree_basic)
{
	/* TODO: Put your own test code here. */
	fail_unless(1 == 1, "Reality is on the blink again.");
}
END_TEST

Suite *
make_test_libs_binary_tree_suite(void)
{
	Suite *suite;
	TCase *tc;

	suite = suite_create("binary_tree tests");
	tc = tcase_create("Core"); 
	tcase_add_test(tc, test_binary_tree_basic);
	/* TODO: add other tests here */
	/* tcase_add_test(tc, test_binary_tree_new_test); */
	tcase_add_test(tc, test_binary_tree_insert);
	tcase_add_test(tc, test_binary_tree_insert_duplicate);
	tcase_add_test(tc, test_binary_tree_remove);

	suite_add_tcase(suite, tc);
	return suite;
}

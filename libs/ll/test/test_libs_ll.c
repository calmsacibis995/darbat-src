#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ll.h>
#include <check.h>
#include "test_libs_ll.h"

int check1[] = {1,2,3,4,5,10,11,12,13,14,-1};
int check2[] = {1,2,4,5,10,11,13,14,-1};

START_TEST(test_ll_basic)
{
	struct ll *ll = ll_new();
	struct ll *temp;
	void *val;
	int count;
	ll_add_front(ll, (void *) 5);
	ll_add_front(ll, (void *) 4);
	ll_add_front(ll, (void *) 3);
	ll_add_front(ll, (void *) 2);
	ll_add_front(ll, (void *) 1);

	ll_add_end(ll, (void *) 10);
	ll_add_end(ll, (void *) 11);
	ll_add_end(ll, (void *) 12);
	ll_add_end(ll, (void *) 13);
	ll_add_end(ll, (void *) 14);

	//printf("Printing all values...\n");
	for (count = 0, temp = ll->next; temp != ll; count ++, temp = temp->next) {
		fail_if(check1[count] == -1, "Too much data in list");
		fail_if(check1[count] != (uintptr_t) temp->data, "Wrong value in list");
	}

	for (temp = ll->next; temp != ll; temp = temp->next) {
		if (temp->data == (void *) 3 ||
		    temp->data == (void *) 12) {
			temp = ll_delete(temp);
		}
	}

	for (count = 0, temp = ll->next; temp != ll; count ++, temp = temp->next) {
		fail_if(check2[count] == -1, "Too much data in list");
		fail_if(check2[count] != (uintptr_t) temp->data, "Wrong value in list");
	}


	count = 0;
	while ((val = ll_pop(ll))) {
		fail_if(check2[count] == -1, "Too much data popped");
		fail_if(check2[count] != (uintptr_t) val, "Wrong value in list");
		count ++;
	}

	fail_unless(ll->next != NULL, "Data still in list after popping all");
	for (temp = ll->next; temp != ll; temp = temp->next) {
		printf("%d\n", (uintptr_t) temp->data);
	}
}
END_TEST

Suite *
make_test_libs_ll_suite(void)
{
	Suite *suite;
	TCase *tc;

	suite = suite_create("LL tests");
	tc = tcase_create("Core");
	tcase_add_test(tc, test_ll_basic);
	suite_add_tcase(suite, tc);
	return suite;
}


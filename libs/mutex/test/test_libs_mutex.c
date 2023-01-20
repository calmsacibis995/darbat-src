#include "test_libs_mutex.h"
#include <stddef.h>
#include <stdlib.h>
#include <mutex/mutex.h>
#include <check.h>

START_TEST(test_mutex_basic)
{
	/* Simple create mutex, release */
	mutex_t mtx = mutex_create();
	fail_unless(mtx != NULL, "Unable to create mutex");

	mutex_lock(mtx);
	mutex_unlock(mtx);
	free(mtx);
}
END_TEST

Suite *
make_test_libs_mutex_suite(void)
{
	Suite *suite;
	TCase *tc;

	suite = suite_create("mutex tests");
	tc = tcase_create("Core"); 
	tcase_add_test(tc, test_mutex_basic);
	/* TODO: add other tests here */
	/* tcase_add_test(tc, test_mutex_new_test); */
	suite_add_tcase(suite, tc);
	return suite;
}

/* Tests for the binary_tree library. */
#include <check.h>
#include <binary_tree/binary_tree.h>

Suite *make_test_libs_binary_tree_suite(void);
void check_notin_tree(struct bin_tree *, char *);
void check_balanced_tree(struct bin_tree *, char *);

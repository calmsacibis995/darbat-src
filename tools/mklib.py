#!/usr/bin/env python
import string
import sys
import os
import shutil
import tempfile

# Determine baz of tla
if os.system("which baz > /dev/null") == 0:
    TLA = "baz"
elif os.system("which tla > /dev/null") == 0:
    TLA = "tla"
else:
    TLA = ""

SCONSTRUCT_TEMPLATE = """# Stuff for regular Iguana build.
Import("env")
lib = env.KengeLibrary("%(libname)s", LIBS=["c"])
Return("lib")
"""

TESTER_H_TEMPLATE = """/* Tests for the %(libname)s library. */
#include <check.h>

Suite *make_test_libs_%(libname)s_suite(void);
"""

PROJECT_CONF_TEMPLATE = """[info]
Author: %(author)s
Copyright: %(copyright)s
Licence: %(licence)s
Category: library
SubCategory: %(subcategory)s
Description: %(description)s

[documentation]
Doxygen: yes
Explicit: yes
"""

TESTER_C_TEMPLATE = """
#include <check.h>
#include "test_libs_%(libname)s.h"

START_TEST(test_%(libname)s_basic)
{
	/* TODO: Put your own test code here. */
	fail_unless(1 == 0, "Reality is on the blink again.");
}
END_TEST

Suite *
make_test_libs_%(libname)s_suite(void)
{
	Suite *suite;
	TCase *tc;

	suite = suite_create("%(libname)s tests");
	tc = tcase_create("Core"); 
	tcase_add_test(tc, test_%(libname)s_basic);
	/* TODO: add other tests here */
	/* tcase_add_test(tc, test_%(libname)s_new_test); */
	suite_add_tcase(suite, tc);
	return suite;
}
"""

def get_input(label, default):
    data = raw_input("%s [%s] > " % (label, default))
    if data == "":
        return default
    else:
        return data

def check_directory(libname):
	# Verify that we're in the root by checking for a "libs" directory
	if not os.path.exists('libs') or not os.path.isdir('libs'):
		print "This tool should be run from the root Iguana checkout directory."
		sys.exit(1)
        if os.path.exists("libs/%s" % libname):
            print "Library %s already exists" % libname
            sys.exit(1)

def make_library(archive_name, libname):
	# Parts of a library:

        # Create a temporary directory for the library
        lib_base = tempfile.mkdtemp() + os.path.sep
        
	#lib_base = 'libs/%s/' % (libname)
	#os.mkdir(lib_base)

	for subdir in ['src', 'include', 'test', 'doc']:
		subdir = '%s%s' % (lib_base, subdir)
		os.mkdir(subdir)
	templater = {'libname': libname} # to avoid %locals()

	# Create the SConstruct
	file('%sSConstruct' % (lib_base), 'w').write(SCONSTRUCT_TEMPLATE % templater)

	# Create the test files.
	testdir = '%s%s/' % (lib_base, 'test')
	file('%stest_libs_%s.h' % (testdir, libname), 'w').write(TESTER_H_TEMPLATE % templater)
	file('%stest_libs_%s.c' % (testdir, libname), 'w').write(TESTER_C_TEMPLATE % templater)

        # Create project.conf
        # Need to get some information from the user
        templater["author"] = get_input("Author", os.getenv("USER"))
        templater["copyright"] = get_input("Copyright holder", "NICTA")
        templater["licence"] = get_input("Licence", "OzPLB")
        templater["subcategory"] = get_input("Category", "misc")
        templater["description"] = get_input("Description", "")
        
	file('%spackage.cfg' % (lib_base), 'w').write(PROJECT_CONF_TEMPLATE % templater)

        lib_dest = "libs/%s" % libname

        if archive_name.lower() != "no_archive":
            if TLA == "":
                print "Couldn't find baz or tla, creating library, but not adding to "
                print "revision control"
            elif TLA == "baz":
                if (os.system("cd %s; baz import -a %s" % (lib_base, archive_name))) != 0:
                    print "Getting into revision control failed"
                    shutil.rmtree(lib_base)
                    sys.exit(1)
        
        shutil.move(lib_base, lib_dest)

	print "Library '%s' created in directory %s" % (libname, lib_dest)

def sane_lib_name(some_name):
	sane_char = string.letters + string.digits + '_'
	for letter in some_name:
		if letter not in sane_char:
			return False
	return True

def print_usage():
	print "Usage: %s <archive_name> <lib_name>" % (sys.argv[0])
        print " archive_name should be a fully qualified arch archive, or"
        print "   noarchive, if you do not want to create the library in revisions"
        print "   control"
	print "Run this from the root Iguana directory."

def main():
	if len(sys.argv) != 3 or not sane_lib_name(sys.argv[2]) or \
			sys.argv[1].startswith('-h') or sys.argv[1].startswith('--h'):
		print_usage()
		sys.exit(0)
	check_directory(sys.argv[2])
	make_library(sys.argv[1], sys.argv[2])
	
if __name__ == '__main__':
	main()

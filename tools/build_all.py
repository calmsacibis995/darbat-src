#!/usr/bin/env python

import glob, os, popen2, sys
from select import select

target = "simulate_test"

if len(sys.argv) > 1:
    if sys.argv[1] == "build":
        target = ""
    else:
        target = sys.argv[1]

# This only works on Linux
def get_conf_name(filename):
    return os.path.splitext(os.path.split(filename)[-1])[0]

def build_conf(conf):
    build_line = "scons -Q conf=%s %s" % (conf, target)
    p = popen2.Popen4(build_line)
    output = p.fromchild.readlines()
    x = p.wait()
    if x == 0:
        print "%s: OK" % conf
    else:
        print "%s: FAILED, output in %s.output.err" % (conf, conf)
        open("%s.output.err" % conf, "w").writelines(output)

# Find all .conf files
all_confs = map(get_conf_name, glob.glob("*.conf") + glob.glob("configs/*.conf"))

for conf in all_confs:
    build_conf(conf)

import os

localkextroot = "plists/"
kextlist = ["System", "IOAHCIFamily", "IOHIDFamily", "IOUSBFamily", "AppleAHCIPort"]
src_path = "/System/Library/Extensions/"

iokit_root = "libs/iokitdrv/bin/"

commands = []

for root in kextlist:
    plist = os.popen("find " + src_path + root + ".kext -type f -name 'Info.plist' -print").read()
    kext = plist = plist.split('\n')
    plist.remove('')
    for p in plist:
        x = p.split(os.sep)
        # drivers have names kextname.kext/Contents/Info.plist for plist
        # and the code has kextname.kext/Contents/MacOS/SomeDriver
        # We want to differentiate by the name of the driver, since
        # everything is called Info.plist,  and we only have a flat namespace
        # in the boot image, the name is useless to us.  This is sometimes
        # not the case, so we search for a .kext suffix to get the name.  We
        # always search backwards so we pick up the innermost driver.
        #
        # Since each kext must come with an Info.plist, we abuse this
        # fact and copy the code here too.
        c = len(x) - 1
        name = None
        plugin = 0
        while c >= 0:
            tmp = x[c].split('.')
            if len(tmp) >= 2 and tmp[-1] == "kext":
                name = x[c].split('.')[0]
                break
            if len(tmp) >=2 and (tmp[-1] == "plugin" or \
                tmp[-1] == "bundle"):
                plugin = 1
                break
            c = c - 1
        if plugin == 1:
            continue    # Ignore plugins
        p = p.replace(src_path,"")
        #commands.append((name+".plist", p))
        p = iokit_root+p
        #print p
        if not os.path.exists(p):
            print "HOLY CRAP!"
#        /darbat/libs/iokitdrv/bin
#        print "got a thing \"",name,"\" \"",p,"\""
        #myplist = env.Command(["DarwinDriver" + name + ".plist"], [p], "cp $SOURCE $TARGET")
        # the kext is the base path of the kext, minus the Info.plist +
        # MacOS and kext name.
        kext = x
        kext.remove(x[-1])
        kpath = "".join(["%s/" % y for y in kext]) + "MacOS/" + name
        # try alternative path
        if not os.path.exists(kpath):
            kpath = "".join(["%s/" % y for y in kext]) + name

        # We can just copy the binary over since we can now
        # load universal binaries. -gl
        #mycode = env.Command(["DarwinDriver" + name], [kpath], "cp $SOURCE $TARGET")
        #env.add_files(myplist)
        # sucks since we have to test for existence here..
        if not os.path.exists(kpath):
            pass
            #print "not exist %s" % mycode
        else:
            print kpath
            p = iokit_root + kpath.replace(src_path,"")
            cpstring = "cp "+kpath+" "+p
            print cpstring
            os.system(cpstring)

            #env.add_files(mycode)

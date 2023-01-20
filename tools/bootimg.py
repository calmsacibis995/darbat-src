import os

GRUB_BIN = "tools/install/bin/grub"
GRUB_STAGE_1 = "tools/install/boot/grub/stage1"
GRUB_STAGE_2 = "tools/install/boot/grub/stage2"
GRUB_STAGE_FAT = "tools/install/boot/grub/fat_stage1_5"

ALIGNMENT=0x8000

def align(val):
    ovr = val % ALIGNMENT
    if (ovr):
        val = val + ALIGNMENT - ovr
    return val

def get_symbol_addr(binary, sym, env):
    for line in os.popen("%s %s" % (env["NM"], binary)).readlines():
        add, state, name = line[:-1].split()
        if name == sym:
            return add
    return None



menulist_serial = """
serial --port=0x3f8 --speed=115200
terminal --timeout=0 serial
"""

menulst_data = """
default 0
title = L4 NICTA::Darbat
kernel=%s/kickstart
"""

def BuildMenuLst(target, source, env):
    menulst = target[0]
    dir = env["ROOT"]
    
    menu = menulst_data % dir

    if env.machine.serial_console:
        menu = menulist_serial + menu
        
    for each in source:
        if "kickstart" not in each.abspath:
            basename  = os.path.basename(each.abspath)
            if basename.endswith(".reloc"):
                basename = basename[:-6]
            menu += "\nmodule=%s/%s" % (dir, basename)
    open(str(menulst), "w").write(menu)

def GrubFloppyImage(target, source, env):
    output_image = target[0]

    bmap = "%s/bmap" % env.builddir
    mtoolsrc = "%s/mtoolsrc" % env.builddir

    open(bmap, "w").write("(fd0) %s" % output_image)
    open(mtoolsrc, "w").write('drive a: file="%s"\n' % output_image)

    def mtoolcmd(str):
        os.system("MTOOLSRC=%s tools/install/bin/%s" % (mtoolsrc, str))

    def copy(file):
        # Hack! If file ends in .reloc, strip it!
        if file.abspath.endswith(".reloc"):
            filenm = file.abspath[:-6]
        elif file.abspath.endswith(".gz"):
            filenm = file.abspath[:-3]
        else:
            filenm = file.abspath
        mtoolcmd("mcopy -o %s a:/boot/grub/%s" % (file.abspath, os.path.basename(filenm)))

    # Disk constants
    secsize = 512
    heads = 16
    sectors = 63

    # This one for usb.img (no partition)
    # the size of the disk we want
    disksize = 64 * 1024 * 1024  # 64M disk  -- FIXME :)

    # Work out the number of tracks (give or take some rounding...)
    tracks  = disksize / (secsize * heads * sectors)
    numsectors = heads * sectors * tracks

    os.system("dd if=/dev/zero of=%s count=%d bs=%d" % (output_image, numsectors,secsize)) # Create image
    mtoolcmd("mformat -t %d -h %d -n %d a:" % (tracks,heads,sectors)) # Format c:
    mtoolcmd("mmd a:/boot")
    mtoolcmd("mmd a:/boot/grub")
    mtoolcmd("mcopy %s a:/boot/grub" % GRUB_STAGE_1)
    mtoolcmd("mcopy %s a:/boot/grub" % GRUB_STAGE_2)
    mtoolcmd("mcopy %s a:/boot/grub" % GRUB_STAGE_FAT)

    os.system("""echo "root (fd0)
              setup (fd0)" | %s --device-map=%s --batch
              """ % (GRUB_BIN, bmap))

    for each in source:
        print each
        copy(each)

def GrubBootImage(target, source, env):
    output_image = target[0]

    bmap = "%s/bmap" % env.builddir
    mtoolsrc = "%s/mtoolsrc" % env.builddir

    open(bmap, "w").write("(hd0) %s" % output_image)
    open(mtoolsrc, "w").write('drive c: file="%s" partition=1\n' % output_image)

    def mtoolcmd(str):
        os.system("MTOOLSRC=%s tools/install/bin/%s" % (mtoolsrc, str))

    def copy(file):
        # Hack! If file ends in .reloc, strip it!
        if file.abspath.endswith(".reloc"):
            filenm = file.abspath[:-6]
        elif file.abspath.endswith(".gz"):
            filenm = file.abspath[:-3]
        else:
            filenm = file.abspath
        mtoolcmd("mcopy -o %s c:/boot/grub/%s" % (file.abspath, os.path.basename(filenm)))

    # Disk constants
    secsize = 512
    heads = 16
    sectors = 63

    # this one for c.img (has a partition)
    # the size of the disk we want
    disksize = 64 * 1024 * 1024  # 64M disk

    # Work out the number of tracks (give or take some rounding...)
    tracks  = disksize / (secsize * heads * sectors)
    numsectors = heads * sectors * tracks
    

    os.system("dd if=/dev/zero of=%s count=%d bs=%d" % (output_image, numsectors, secsize)) # Create image
    mtoolcmd("mpartition -I -t %d -h %d -s %d c:" % (tracks, heads, sectors)) # Initialise table
    mtoolcmd("mpartition -c -t %d -h %d -s %d c:" % (tracks, heads, sectors)) # 
    
    mtoolcmd("mformat c:") # Format c:
    mtoolcmd("mmd c:/boot")
    mtoolcmd("mmd c:/boot/grub")
    mtoolcmd("mcopy %s c:/boot/grub" % GRUB_STAGE_1)
    mtoolcmd("mcopy %s c:/boot/grub" % GRUB_STAGE_2)
    mtoolcmd("mcopy %s c:/boot/grub" % GRUB_STAGE_FAT)

    os.system("""echo "geometry (hd0) 22 16 63
              root (hd0,0)
              setup (hd0)" | %s --device-map=%s --batch
              """ % (GRUB_BIN, bmap))

    for each in source:
        print each
        copy(each)




class BootImageBuilder:
    def __init__(self, arch, kernel, sigma0, rest, dite_cmd="dite"):
        self.arch = arch
        self.kernel = kernel
        self.sigma0 = sigma0
        self.rest = [(self.sigma0, 's')] + rest
        self.cmd = dite_cmd

    def __call__(self, target, source, env):
	kernel_kip = None
	if env.toolchain_name == "apple":
            kernel_kip = get_symbol_addr(self.kernel, "_kip", env)
	elif env.toolchain_name == "gnuelf":
            kernel_kip = get_symbol_addr(self.kernel, "kip", env)
	else:
	    raise "unknown toolchain"
        patch_kcp = ""
        extra_start = ""
        dite_dict = {'kernel_kip': kernel_kip, 'kernel': self.kernel, 'sigma0': self.sigma0}
        if self.arch == "arm":
            phy_kernel = "-p"
        elif self.arch == "ia32":
            phy_kernel = ""
            patch_kcp = "--kcp-mainmem-low=0x100000 --kcp-mainmem-high=0xff00000"
        elif self.arch == "mips64":
            phy_kernel = "-p"
            extra_start = " --elf-modify-virtaddr=0xffffffff80000000 --elf-modify-physaddr=0xffffffff80000000 --kcp-mainmem-low=0x0 --kcp-mainmem-high=0x4000000"
        elif self.arch == "alpha":
            phy_kernel = ""
            extra_start = " --elf-modify-physaddr=0xfffffc0000000000"
        elif self.arch == "powerpc64":
            phy_kernel = ""
            extra_start = ""
        dite_dict["phy_kernel"] = phy_kernel
        start_cmd = " --binfo-sexec -B -k -K 0x%(kernel_kip)s -M 0x%(kernel_kip)s %(phy_kernel)s %(kernel)s " % dite_dict
        end_cmd = " %s -o %s" % (patch_kcp, target[0])

        # Finish for now.. later we need to do more
        for (app, flag) in self.rest:
            extra = ""
            

            if flag == "i":
                extra = "-i"
            if flag == 's':
                extra = '-s'
            if flag == "raw":
                name = str(app).split("/")[-1]
                start_cmd += (" -R --name %s %s") % (name, app)
            elif flag == "l":
                start_cmd += (" --name vmlinux %s.reloc") % (app)
	    elif flag == "machohack":
		name = str(app).split("/")[-1]
		start_cmd += (" --name %s %s ") % (name, app)
            else:
                name = str(app).split("/")[-1].split(".")[0]
                start_cmd += (" --name %s %s %s.reloc") % (name, extra, app)

        # Make things less chatty!
        cmd = self.cmd + extra_start + start_cmd + end_cmd
	print "cmd is %s\n" % cmd
        r = os.system(cmd)
        if (r != 0):
            raise "Error running dite", cmd
            

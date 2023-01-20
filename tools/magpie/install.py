import os
import sys
import glob
import errno
import shutil
from optparse import OptionParser

PACKING_LIST_SEEDS = [
	('glob', '*.py'),
	('glob', 'cparser/*.py'),
	('glob', 'generator/*.py'),
	('glob', 'idlparser/*.py'),
	('glob', 'idltypes/*.py'),
	('all', 'include'),
	('glob', 'output/*.py'),
	('all', 'output/templates'),
	('glob', 'targets/*.py'),
	('glob', 'targets/shared/*.py'),
	('glob', 'targets/iguana/*.py'),
	('glob', 'test/*.py'),
	('all', 'test/input'),
	('all', 'test/expected_output'),
]

POST_INSTALL_MESSAGE = 'Remember to set your PATH to include the installation directory.'

FORBIDDEN_DIRS = ['.arch-ids']


def get_basedir(prefix):
	return '%s/magpie' % (prefix)

def m_makedir(path):
	try:
		os.makedirs(path)
	except OSError, e:
		if e.errno != errno.EEXIST:
			raise

def m_install(source, dest):
	shutil.copyfile(source, dest)
	shutil.copymode(source, dest)

def m_delete(filename):
	os.unlink(filename)

def install(prefix):
	installdir = get_basedir(prefix)
	print "Installing Magpie to %s." % (installdir)
	packing_list = make_packing_list()
	installed_files = []
	made_dirs = {}
	for source in packing_list:
		sourcedir, sourcefile = os.path.split(source)
		targetdir = os.path.join(installdir, sourcedir)
		target = os.path.join(targetdir, sourcefile)
		if targetdir not in made_dirs:
			print "* Create directory %s" % (targetdir)
			m_makedir(targetdir)
			made_dirs[targetdir] = True
		print "* Install %s" % (target)
		m_install(source, target)
		installed_files.append(target)
	install_log_filename = os.path.join(installdir, 'install.log')
	handle = open(install_log_filename, 'w')
	for item in installed_files:
		mtime = os.path.getmtime(item)
		print >>handle, mtime, item
	handle.close()
	print
	print "A list of all installed files has been written to %s." % (install_log_filename)
	print POST_INSTALL_MESSAGE
	print "Installation directory:", installdir

def uninstall(prefix, ignore_timestamps):
	installdir = get_basedir(prefix)
	install_log_filename = os.path.join(installdir, 'install.log')
	print "Uninstalling Magpie using installation log %s" % (install_log_filename)
	some_not_uninstalled = False
	for line in open(install_log_filename, 'r').readlines():
		line = line.rstrip()
		mtime, filename = line.split(' ', 1)
		mtime = float(mtime)
		try:
			new_mtime = os.path.getmtime(filename)
		except OSError, e:
			if e.errno == errno.ENOENT:
				# Already deleted, ignore
				continue
			else:
				raise
		if new_mtime > mtime and ignore_timestamps is False:
			print "Not uninstalling", filename, "because it has been changed since installation"
			some_not_uninstalled = True
		else:
			m_delete(filename)

	if some_not_uninstalled is False:
		# Remove the install log if we got everything.
		m_delete(install_log_filename)
	alldirs = []
	for dirpath, dirnames, filenames in os.walk(installdir):
		alldirs.append(dirpath)
	alldirs.sort(); alldirs.reverse()
	for dirname in alldirs:
		try:
			os.rmdir(dirname)
		except OSError, e:
			print "Couldn't remove directory '%s': %s" % (dirname, str(e))

def sane_walk(basepath):
	all_files = []
	for dirpath, dirname, filenames in os.walk(basepath):
		skipme = False
		for forbidden in FORBIDDEN_DIRS:
			if dirpath.endswith(forbidden):
				skipme = True
				break
		if not skipme:
			all_files.extend([os.path.join(dirpath, filename) for filename in filenames])
	return all_files

def make_packing_list():
	packing_list = []
	for method, data in PACKING_LIST_SEEDS:
		if method == 'glob':
			packing_list.extend(glob.glob(data))
		elif method == 'all':
			packing_list.extend(sane_walk(data))
	return packing_list

if __name__ == '__main__':
	parser = OptionParser()
	parser.add_option('--install', dest='action', action='store_const',
			const='install', help = 'Install Magpie', default='install')
	parser.add_option('--uninstall', dest='action', action='store_const',
			const='uninstall', help = 'Uninstall Magpie')
	parser.add_option('--make-packing-list', dest='action', action='store_const',
			const='packinglist', help = "Make a packing list for distribution")
	parser.add_option('-t', '--ignore-timestamps', dest='ignoretimes', action='store_true',
			default=False, help='Ignore timestamps when uninstalling')
	parser.add_option('--prefix', dest='prefix', action='store',
			default='/usr/local', help='Installation prefix (/usr/local)')
	opts, args = parser.parse_args()
	if opts.action == 'install':
		install(opts.prefix)
	elif opts.action == 'uninstall':
		uninstall(opts.prefix, opts.ignoretimes)
	elif opts.action == 'packinglist':
		for filename in make_packing_list():
			print filename

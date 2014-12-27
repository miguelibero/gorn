#!/usr/bin/env python
#-*- coding: UTF-8 -*-

import sys
import optparse
import ConfigParser
import subprocess
import xml.etree.ElementTree as ElementTree
import os
import re
import shutil

CONFIG_OPTIONS_SECTION = "options"
CONFIG_LIBRARIES_SECTION = "libraries"

parser = optparse.OptionParser(usage="usage: %prog [options] (build|debug|release|clean|update|run|uninstall)", version="%prog 1.0",
	description="builds the android project")

parser.add_option("-t", "--target", dest="target",
                  help="The android target to build")
parser.add_option("-a", "--arch", dest="arch",
                  help="The architectures to build")
parser.add_option("-e", "--emulator", dest="emulator",
                  help="The emulator name to run")
parser.add_option("-v", "--avdpath", dest="avdpath",
                  help="The path where the emulator config files are kept")
parser.add_option("-p", "--path", dest="path",
                  help="The path to the project")
parser.add_option("-m", "--mode", dest="mode",
                  help="The mode to build")
parser.add_option("-c", "--config", dest="config",
                  help="path to the config file")

defaultOptions = {
	"target": "android-8",
	"arch": "armeabi,armeabi-v7a,x86",
	"path": ".",
	"mode": "debug",
	"emulator": "emulator",
	"avdpath": "~/.android/avd",
	"config": "android_build.conf",
	"assetspath": "../assets"
}

(options, args) = parser.parse_args()
options = vars(options)
action = "build"
if len(args) > 0:
	action = args[0]

configPath = defaultOptions["config"]
if options["config"]:
	configPath = options["config"]

def hasoption(name, options):
	if name in options and options[name]:
		return True
	else:
		return False

#set options from config
config = ConfigParser.ConfigParser()
config.read(configPath)
if config.has_section(CONFIG_OPTIONS_SECTION):
	for option in config.options(CONFIG_OPTIONS_SECTION):
		if not hasoption(option, options):
			options[option] = config.get(CONFIG_OPTIONS_SECTION, option)

#set default options
for name, value in defaultOptions.items():
	if not hasoption(name, options):
		options[name] = value

#get libraries
libraries = {}
if config.has_section(CONFIG_LIBRARIES_SECTION):
	for name in config.options(CONFIG_LIBRARIES_SECTION):
		libraries[name] = config.get(CONFIG_LIBRARIES_SECTION, name)

#read AndroidManifest to find package and actvity
if not hasoption("package", options) or not hasoption("activity", options):
	try:
		tree = ElementTree.parse(options["path"]+"/AndroidManifest.xml")
		options["package"] = tree.getroot().get("package")
		for activity in tree.iter('activity'):
			for mainaction in activity.iter('action'):
				if mainaction.get("{http://schemas.android.com/apk/res/android}name") == "android.intent.action.MAIN":
					options["activity"] = activity.get("{http://schemas.android.com/apk/res/android}name")
	except:
		parser.error("Could not find AndroidManifest.xml in '%s'." % (options["path"]))

#fix arch option
if hasoption("arch", options):
	options["arch"] = options["arch"].replace(",", " ");

#find android home
if not hasoption("sdk_dir", options):
	options["sdk_dir"] = os.environ['ANDROID_HOME']

#fix avdpath
if hasoption("avdpath", options):
	options["avdpath"] = os.path.expanduser(options["avdpath"])

def findFiles(dir, files):
	regex = re.compile(files)
	dirmatches = []
	filematches = []
	for root, dirnames, filenames in os.walk(dir):
		for filename in filenames:
			if regex.match(filename):
				filematches.append(os.path.join(root, filename))
		for dirname in dirnames:
			if regex.match(dirname):
				dirmatches.append(os.path.join(root, dirname))
	return [dirmatches, filematches]

def deleteFiles(dir, files):
	dirmatches, filematches = findFiles(dir, files)
	for filepath in filematches:
		os.remove(filepath)
	for dirpath in dirmatches:
		if os.path.isdir(dirpath):
			shutil.rmtree(dirpath)

def cleanEclipseFiles():
	files = "(crunch|xargs)";
	deleteFiles(options["path"], files);
	for libPath in libraries.values():
		deleteFiles(libPath, files);

def findApk(mode):
	suffix = ".apk"
	if len(mode) > 0:
		suffix = "-"+mode+suffix;
	for root, dirs, files in os.walk(options["path"]+"/bin"):
		for file in files:
			if file.endswith(suffix):
				return os.path.join(root, file)
	raise Exception("Error could not find apk for mode '%s' in path '%s'" % (mode, options["path"]))

def findAvd(name):
	dir = name+".avd"
	for root, dirs, files in os.walk(options["avdpath"]):
		if dir in dirs:
			return True
	return False

def call(args):
	result = subprocess.call(args)
	if result is not 0:
		raise Exception("Error %d running %s" % (result, args))

def prepare():
	src = options["assetspath"]
	dst = options["path"]+"/assets"
	shutil.rmtree(dst)
	shutil.copytree(src, dst)

def update():
	call(["android", "update", "project", "--path", options["path"], "--subprojects", "--target", options["target"]])
	for libPath in libraries.values():
		call(["android", "update", "project", "--path", libPath, "--subprojects", "--target", options["target"]])
		call(["android", "update", "lib-project", "--path", libPath, "--target", options["target"]])

def clean():
	update()
	deleteFiles(options["path"]+"/obj", ".*");
	call(["ndk-build", "clean", "--directory", options["path"], "APP_ABI="+options["arch"]])
	call(["ant", "clean", "-buildfile", options["path"]+"/build.xml", "-Dsdk.dir="+options["sdk_dir"]])
	call(["rm", "-rf", options["path"]+"/obj/local/*"])
	for libPath in libraries.values():
		if os.path.isdir(libPath+"/jni"):
			call(["ndk-build", "clean", "--directory", libPath, "APP_ABI="+options["arch"]])
		call(["ant", "clean", "-buildfile", libPath+"/build.xml", "-Dsdk.dir="+options["sdk_dir"]])
		call(["rm", "-rf", libPath+"/obj/local/*"])

def build(mode):
	prepare()
	update()
	ndk = ["ndk-build", "--directory", options["path"], "APP_ABI="+options["arch"]]
	antCmd = None
	if mode == "debug":
		ndk.append("NDK_DEBUG=1")
		antCmd = "debug"
	elif mode == "release":
		ndk.append("NDK_DEBUG=0")
		antCmd = "release"
	call(ndk);
	if antCmd:
		call(["ant", antCmd, "-buildfile", options["path"]+"/build.xml", "-Dsdk.dir="+options["sdk_dir"]]);

def release():
	build("release")

def run():
	build("release")
	apkPath = findApk("release")
	call(["adb", "uninstall", options["package"]]);
	call(["adb", "install", "-r", apkPath]);
	start()

def build_install(mode):
	build(mode)
	apkPath = findApk(mode)
	call(["adb", "uninstall", options["package"]]);
	call(["adb", "install", "-r", apkPath]);

def debug():
	build_install("debug")
	call(["ndk-gdb", "--verbose", "--start", "--project="+options["path"], "NDK_DEBUG=1"]);

def gdb():
	os.chdir(options["path"])
	call(["ndk-gdb", "--start"]);

def start():
	call(["adb", "shell", "am", "start", "-a", "android.intent.action.MAIN", "-n", options["package"]+"/"+options["activity"]])

def uninstall():
	call(["adb", "uninstall", options["package"]]);

def emulator():
	if not findAvd(options["emulator"]):
		path = options["avdpath"]+"/"+options["emulator"]+".avd";
		os.makedirs(path)
		call(["android", "create", "avd", "--force", "-n", options["emulator"], "-t", options["target"], "-p", path])
		with open(path+"/config.ini", "a") as avdconfig:
			avdconfig.write("hw.gpu.enabled=yes")
	subprocess.Popen(["emulator", "-avd", options["emulator"]])

cleanEclipseFiles();

if action == "build":
	build(options["mode"])
elif action == "clean":
	clean()
elif action == "update":
	update()
elif action == "run":
	run()
elif action == "debug-install":
	build_install("debug")
elif action == "release-install":
	build_install("release")
elif action == "debug":
	debug()
elif action == "release":
	release()
elif action == "uninstall":
	uninstall()
elif action == "start":
	start()
elif action == "emulator":
	emulator()
elif action == "gdb":
	gdb()
else:
	parser.error("Unknown action '%s'." % (action))

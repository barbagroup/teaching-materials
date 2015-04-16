#!/usr/bin/env python

import os
import subprocess
import re

def versionNumber(shellOutput):
	splitList = re.split(r",|\s", shellOutput)
	for i, word in enumerate(splitList):
		if re.match(r'^\(*[Vv]*[0-9]+\.[0-9]+(|\.[0-9]+)[a-z]*\)*$', word):
			word = re.sub(r'[Vv\(\)]', '', word)
			return word

def checkCommand(command, minVersion="0"):
	FNULL = open(os.devnull, 'w')
	try:
		foundVersion = versionNumber(subprocess.check_output(command, stderr=FNULL))
		if foundVersion:
			print command[0] + " v" + foundVersion + " found.",
			if foundVersion < minVersion:
				print "Please upgrade to v" + minVersion + "."
			else:
				print ''
		else:
			print command[0] + " found. Unable to detect version number. Please check if later than v" + minVersion + "."
	except OSError:
		print command[0] + " not found. Please install v" + minVersion + "."
	FNULL.close()

def checkModule(module):
	try:
		__import__(module)
		print module + " found."
	except ImportError:
		print module + " not found. Please install."

def title(heading):
	print "-"*30 + "\n" + heading + "\n" + "-"*30

if __name__ == "__main__":

	title("Installed programs")
	checkCommand(["gcc", "--version"], "4.6")
	checkCommand(["nvcc", "--version"], "5.5")
	checkCommand(["swig", "-version"], "2.0")
	checkCommand(["gnuplot", "--version"], "4.4")
	checkCommand(["openssl", "version"], "1.0.1")
	checkCommand(["perl", "-v"], "5.0")
	checkCommand(["foo"], "0.0")
	
	title("Python modules")
	checkModule("numpy")
	checkModule("matplotlib")

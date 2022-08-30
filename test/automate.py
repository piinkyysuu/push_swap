import cmd
from re import sub
import subprocess
import random
from subprocess import call
import subprocess as sp
import sys

path = '/Users/thle/Desktop/projects/push_swap/'
push_swap = path + 'push_swap'
checker = path + 'checker'

class colors:
	reset = '\033[0m'
	bold = '\033[01m'
	disable = '\033[02m'
	underline = '\033[04m'
	reverse = '\033[07m'
	strikethrough = '\033[09m'
	invisible = '\033[08m'
	class fg:
		black = '\033[30m'
		red = '\033[31m'
		green = '\033[32m'
		orange = '\033[33m'
		blue = '\033[34m'
		purple = '\033[35m'
		cyan = '\033[36m'
		lightgrey = '\033[37m'
		darkgrey = '\033[90m'
		lightred = '\033[91m'
		lightgreen = '\033[92m'
		yellow = '\033[93m'
		lightblue = '\033[94m'
		pink = '\033[95m'
		lightcyan = '\033[96m'
	class bg:
		black = '\033[40m'
		red = '\033[41m'
		green = '\033[42m'
		orange = '\033[43m'
		blue = '\033[44m'
		purple = '\033[45m'
		cyan = '\033[46m'
		lightgrey = '\033[47m'

cmdArg = list(sys.argv)
lenCmdArg = len(cmdArg)

size = 0
lowInt = -2147483648
highInt = 2147483647

f = open("test_case", "w")
f.write("")
f.close()

maxRes = -1
minRes = 2147483647
sumRes = 0

def writeToFile(args):
	f = open("test_case", "a")
	f.write("Case " + str(x) + ": \n")
	f.write(args)
	f.write("\n\n")
	f.close()

def excutePrograms():
	data = subprocess.Popen([push_swap, args], stdout=subprocess.PIPE)
	output = data.stdout.read()
	data.stdout.close()
	line = output.decode("utf-8").count("\n")
	proc = subprocess.Popen([checker, args], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	proc.communicate(input=output)[0]
	res = proc.communicate()[0].decode("utf-8")
	proc.stdout.close()
	return (line, res.replace('\n', ''))

def printOutput(size, x, line, res):
	if res == 'KO':
		res = '\033[31m' + res + '\033[0m'
	else:
		res = '\033[32m' + res + '\033[0m'
	grade = 5
	print('{:2s}{:<5d}|{:>7d}{:3s}|{:3s}{:>4s}{:3s}|{:4d}'.format(' ', x, line, ' ', ' ', res, ' ', grade))
	for i in range(1, 36):
		print('_', end='')
	print('\n')

if size == 500:
	print("{:10s}{:s}".format(' ', '\033[01m' + '\033[43m' + "ADVANCED VERSION" + '\033[0m'))
for i in range(1, 36):
	print('_', end='')
print('\n')

loopAmount = 20

for x in range(1, loopAmount + 1):
	args = ' '.join(str(x) for x in random.sample(range(lowInt, highInt), size))
	writeToFile(args)
	result = excutePrograms()
	if result[0] > maxRes:
		maxRes = result[0]
	if result[0] < minRes:
		minRes = result[0]
	sumRes += result[0]
	printOutput(size, x, result[0], result[1])

print("maxRes: " + str(maxRes))
print("minRes: " + str(minRes))
print("avgRes: " + str(int(sumRes / loopAmount)))


def printVersion(size):
	if size == 3:
		return "SIMPLE VERSION [3]"
	if size == 5:
		return "SIMPLE VERSION [5]"
	if size == 100:
		return "MIDDLE VERSION [100]"
	if size == 500:
		return "ADVANCED VERSION [500]"

def getGrade(size, res):
	if size == 3:
		if res <= 3:
			return 5
		else
			return 0
	if size == 5
		if res <= 12:
			return 5
		else
			return 0
	if size == 100
		if res <= 700:
			return 5
		elif res <= 900:
			return 4
		elif res <= 1100:
			return 3
		elif res <= 1300:
			return 2
		elif res <= 1500:
			return 1
		else:
			return 0
	if size == 500
		if res <= 5500:
			return 5
		elif res <= 7000:
			return 4
		elif res <= 8500:
			return 3
		elif res <= 10000:
			return 2
		elif res <= 11500:
			return 1
		else:
			return 0


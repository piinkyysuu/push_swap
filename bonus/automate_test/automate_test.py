import subprocess
import random

import sys
sys.path.insert(0, '..')
from config import PUSH_SWAP, CHECKER

push_swap = PUSH_SWAP
checker = CHECKER

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

def writeToFile(args, x):
	f = open("test_case", "a")
	f.write("Case " + str(x) + ": \n")
	f.write(args)
	f.write("\n\n")
	f.close()

def excutePrograms(args):
	data = subprocess.Popen([push_swap, args], stdout=subprocess.PIPE)
	output = data.stdout.read()
	data.stdout.close()
	line = output.decode("utf-8").count("\n")
	proc = subprocess.Popen([checker, args], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	proc.communicate(input=output)[0]
	res = proc.communicate()[0].decode("utf-8")
	proc.stdout.close()
	return (line, res.replace('\n', ''))

def printOutput(size, x, line, res, grade):
	if res == 'KO' or grade == 0:
		res = '\033[31m' + res + '\033[0m'
	else:
		res = '\033[32m' + res + '\033[0m'
	print('{:2s}{:<5d}|{:>7d}{:3s}|{:3s}{:>4s}{:3s}|{:4d}'.format(' ', x, line, ' ', ' ', res, ' ', grade))

def printVersion(size):
	if size == 3:
		version = "SIMPLE VERSION [3]"
	if size == 5:
		version = "SIMPLE VERSION [5]"
	if size == 100:
		version = "MIDDLE VERSION [100]"
	if size == 500:
		version = "ADVANCED VERSION [500]"
	versionLen = (36 - len(version)) // 2
	print("{s:<{SHOWLEN}s}".format(s=" ", SHOWLEN=versionLen), end="")
	print('\u001b[38;5;100m' + version + '\033[0m')
	for i in range(1, 36):
		print('_', end='')
	print('\n')
	return version

def getGrade(size, res):
	if size == 3:
		if res <= 3:
			return 5
		else:
			return 0
	if size == 5:
		if res <= 12:
			return 5
		else:
			return 0
	if size == 100:
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
	if size == 500:
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

def startTests(size):
	lowInt = -2147483648
	highInt = 2147483647
	version = printVersion(size)
	loopAmount = 50
	sum = 0
	least = [0, 2147483647] #least[0] = case
	most = [0, -1]
	f = open("test_case", "a")
	f.write(version + "\n")
	f.close()
	permutationOfFiveNumbers = [
		"1 2 3 4 5",
		"1 2 3 5 4",
		"1 2 4 3 5",
		"1 2 4 5 3",
		"1 2 5 4 3",
		"1 2 5 3 4",
		"1 3 2 4 5",
		"1 3 2 5 4",
		"1 3 4 2 5",
		"1 3 4 5 2",
		"1 3 5 4 2",
		"1 3 5 2 4",
		"1 4 3 2 5",
		"1 4 3 5 2",
		"1 4 2 3 5",
		"1 4 2 5 3",
		"1 4 5 2 3",
		"1 4 5 3 2",
		"1 5 3 4 2",
		"1 5 3 2 4",
		"1 5 4 3 2",
		"1 5 4 2 3",
		"1 5 2 4 3",
		"1 5 2 3 4",
		"2 1 3 4 5",
		"2 1 3 5 4",
		"2 1 4 3 5",
		"2 1 4 5 3",
		"2 1 5 4 3",
		"2 1 5 3 4",
		"2 3 1 4 5",
		"2 3 1 5 4",
		"2 3 4 1 5",
		"2 3 4 5 1",
		"2 3 5 4 1",
		"2 3 5 1 4",
		"2 4 3 1 5",
		"2 4 3 5 1",
		"2 4 1 3 5",
		"2 4 1 5 3",
		"2 4 5 1 3",
		"2 4 5 3 1",
		"2 5 3 4 1",
		"2 5 3 1 4",
		"2 5 4 3 1",
		"2 5 4 1 3",
		"2 5 1 4 3",
		"2 5 1 3 4",
		"3 2 1 4 5",
		"3 2 1 5 4",
		"3 2 4 1 5",
		"3 2 4 5 1",
		"3 2 5 4 1",
		"3 2 5 1 4",
		"3 1 2 4 5",
		"3 1 2 5 4",
		"3 1 4 2 5",
		"3 1 4 5 2",
		"3 1 5 4 2",
		"3 1 5 2 4",
		"3 4 1 2 5",
		"3 4 1 5 2",
		"3 4 2 1 5",
		"3 4 2 5 1",
		"3 4 5 2 1",
		"3 4 5 1 2",
		"3 5 1 4 2",
		"3 5 1 2 4",
		"3 5 4 1 2",
		"3 5 4 2 1",
		"3 5 2 4 1",
		"3 5 2 1 4",
		"4 2 3 1 5",
		"4 2 3 5 1",
		"4 2 1 3 5",
		"4 2 1 5 3",
		"4 2 5 1 3",
		"4 2 5 3 1",
		"4 3 2 1 5",
		"4 3 2 5 1",
		"4 3 1 2 5",
		"4 3 1 5 2",
		"4 3 5 1 2",
		"4 3 5 2 1",
		"4 1 3 2 5",
		"4 1 3 5 2",
		"4 1 2 3 5",
		"4 1 2 5 3",
		"4 1 5 2 3",
		"4 1 5 3 2",
		"4 5 3 1 2",
		"4 5 3 2 1",
		"4 5 1 3 2",
		"4 5 1 2 3",
		"4 5 2 1 3",
		"4 5 2 3 1",
		"5 2 3 4 1",
		"5 2 3 1 4",
		"5 2 4 3 1",
		"5 2 4 1 3",
		"5 2 1 4 3",
		"5 2 1 3 4",
		"5 3 2 4 1",
		"5 3 2 1 4",
		"5 3 4 2 1",
		"5 3 4 1 2",
		"5 3 1 4 2",
		"5 3 1 2 4",
		"5 4 3 2 1",
		"5 4 3 1 2",
		"5 4 2 3 1",
		"5 4 2 1 3",
		"5 4 1 2 3",
		"5 4 1 3 2",
		"5 1 3 4 2",
		"5 1 3 2 4",
		"5 1 4 3 2",
		"5 1 4 2 3",
		"5 1 2 4 3",
		"5 1 2 3 4"
	]
	permutationOfThreeNumbers = [
		"1 3 2",
		"2 1 3",
		"2 3 1",
		"1 2 3",
		"3 2 1",
		"3 1 2"
	]
	i = 1
	if size == 3:
		for x in permutationOfThreeNumbers:
			args = x
			writeToFile(args, i)
			result = excutePrograms(args)
			result = excutePrograms(args)
			if result[0] < least[1]:
				least[1] = result[0]
				least[0] = i
			if result[0] > most[1]:
				most[1] = result[0]
				most[0] = i
			sum = sum + result[0]
			printOutput(size, i, result[0], result[1], getGrade(size, result[0]))
			i = i + 1
		avg = sum // 9
	elif size == 5:
		for x in permutationOfFiveNumbers:
			args = x
			writeToFile(args, i)
			result = excutePrograms(args)
			result = excutePrograms(args)
			if result[0] < least[1]:
				least[1] = result[0]
				least[0] = i
			if result[0] > most[1]:
				most[1] = result[0]
				most[0] = i
			sum = sum + result[0]
			printOutput(size, i, result[0], result[1], getGrade(size, result[0]))
			i = i + 1
		avg = sum // 120
	else:
		for x in range(1, loopAmount + 1):
			args = ' '.join(str(x) for x in random.sample(range(lowInt, highInt), size))
			writeToFile(args, x)
			result = excutePrograms(args)
			if result[0] < least[1]:
				least[1] = result[0]
				least[0] = x
			if result[0] > most[1]:
				most[1] = result[0]
				most[0] = x
			sum = sum + result[0]
			printOutput(size, x, result[0], result[1], getGrade(size, result[0]))
		avg = sum // loopAmount

	print("{:<16s}: {:<5d} [Case:{:3d}]".format("Worst Scenario", most[1], most[0]))
	print("{:<16s}: {:<5d} [Case:{:3d}]".format("Best Scenario", least[1], least[0]))
	print("{:<16s}: {:<5d}".format("Average", avg))
	print("{:<16s}: {:<5d}".format("Score", getGrade(size, avg)))

if __name__ == '__main__':
	f = open("test_case", "w")
	f.write("")
	f.close()
	version = [3, 5, 100, 500]
	startTests(3)
	print("\n\n")
	startTests(5)
	print("\n\n")
	startTests(100)
	print("\n\n")
	startTests(500)
	print("\n\n")

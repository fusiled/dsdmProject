#!/usr/bin/python2


import sys

result = 0
length = len(str(sys.argv[1]))
for i in xrange(0,length):
#	print "add "+str(int(sys.argv[1][length-i-1])*2**(length - i -1))
	result = result + int(sys.argv[1][i])* 2**(length - i-1)
print result

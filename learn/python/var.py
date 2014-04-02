#!/usr/bin/python
i = 8
print i
i = i*2
print i
i += 1
print i
i *= 2
print i
print i-3

s = "------------"
print s
s += "++++++++++++"
print s

print i,s

print i is s
s = i
print i is s

import math
print math.pi
print "PI is {0:.2f} , 'e' is {1:.9f}".format(math.pi, math.e)

import random
for _ in range(1, 10):
	print random.randint(1, 9)


vdec = 1234567
print "dec: ", vdec
vbin = 0b110101110111
print "bin: ", vbin
voct = 0o12345
print "oct: ", voct
vhex = 0xA234
print "hex: ", vhex

print "bin(1234): ", bin(1234)
print "oct(1234): ", oct(1234)
print "hex(1234): ", hex(1234)

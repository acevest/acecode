#!/usr/bin/python
# -*- coding: utf-8 -*-
# 注意要加冒号
number = 23
guess = int(raw_input('Enter an integer:'))

if guess == number:
	print 'Yes'
elif guess < number:
	print 'No, Lower'
else:
	print 'No, Higher'

if True:
	print 'Done'

while True:
	guess = int(raw_input("Enter an Integer:"));

	if guess == number:
		print "Yes It's", number;
		break;
	elif guess < number:
		print "Too Low...";
	else:
		print "Too Hight...";


while False:
	print "False...";
else:
	print "while else...";

# for 的 else 会在for结束后执行 
for i in range(1,5):
	print i;
else:
	print "for else";

# 但是遇到break就不会执行了
for i in range(1,5):
	if i == 2:
		continue;
	print i;
	if i == 3:
		break;
else:
	print "for else";


i = 0
while i < 10 :
	print i, #加逗号和不加逗号的区别就是，加逗号后不会强制换行
	i += 1

i = 0
while i< 10 :
	print i
	i += 1

#range(start, end, step)
for i in range(100, -100, -10) :
	print i,


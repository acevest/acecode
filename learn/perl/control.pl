#!/usr/bin/perl
# -------------------------------------
#   File Name:	control.pl
#      Author:	Zhao Yanbai
#             	Sat Sep 25 23:12:02 2010
# Description:	none
# -------------------------------------
use strict;

# if 与 unless
# if 是条件为真执行
# unless 是条件为假执行

$_ = "puppy is someone...";
if(/puppy/){
	print "true: $_\n";
}

unless(/wahahhaa/){
	print "false: $_\n";
}


# while 与 until
# while 是条件为真执行循环体
# until 是条件为假执行

my $a;
my $b;

$a = 1;
$b = 100;

until($a > $b){
	$a *= 2;
	print "a:$a\tb:$b\n";
}


# 以下两个语句是等价的
if($a>100){
	print "first style...\n";
}
print "second style\n" if $a>100;
# 同理
$b = 1234 unless $a < 100;
print "B:$b\n";
$b /= 2 until $b < 10;
print "B:$b\n";

my @c = (1, 2, 3, 4, 9, 8, 7, 6, 5);
print "$_ " foreach @c; # 这种情况只能使用$_
print "\n";

# elsif
if($a == 1){
	print "$a\n";
}elsif($a == 2){
	print "$a\n";
}else{
	print "$a\n";
}

my $i;
for($i=0; $i<100; $i +=2){
	print "$i ";
}
print "\n";
for (1 .. 10) {
	print "$_ ";
}
print "\n";

$i=0;
while(1){
	if($i>10){
		last; # 相当于break
	}
	print "$i ";
	$i++;
}
print "\n";

$i=0;
while(1){
	if($i<10){
		$i++;
		next; # 相当于continue
	}
	print "$i\n";
	last;
}


# redo
my $x;
for($x=0; $x<5; ){ 
	$x++;
	redo if $x==4;
	print "$x ";
}
print "\n";

#!/usr/bin/perl
# -------------------------------------
#   File Name:	sorthash.pl
#      Author:	Zhao Yanbai
#             	Fri Sep 24 12:57:21 2010
# Description:	对hash按value排序
# 		如果value相等则按key逆序排列
# -------------------------------------
use strict;

my %hash;
my @item = ("ccc", "bbb", "aaa", "ccc", "bbb", "bbb", "bbb", "aaa");
foreach (@item){
	$hash{$_}++;
}

foreach (sort { $hash{$b} <=> $hash{$a} or $b cmp $a } keys %hash){
	print "$_\t: $hash{$_}\n";
}

#!/usr/bin/perl
# -------------------------------------
#   File Name:	sub.pl
#      Author:	Zhao Yanbai
#             	Wed Sep  8 16:08:17 2010
# Description:	none
# -------------------------------------

use strict;


&hello_sub;
&hello_sub("aaa");
&hello_sub("aaa", "bbb");
&hello_sub("aaa", "bbb", "ccc");

my $ret;
$ret = &max(123, 456);
print "ret: $ret\n";
$ret = &max(789, 456);
print "ret: $ret\n";
$ret = &max("abcd", "efgh");
print "ret: $ret\n";
$ret = &max(123, "321", $ret); 
print "ret: $ret\n";

$ret = &get_max;
print "ret: $ret\n";
$ret = &get_max(1,3,5,12345,98763,237, 0x123, 0x99999, 0777);
print "ret: $ret\n";
$ret = &get_max(026, 0x3, 14);
print "ret: $ret\n";

my @a;
@a = &func();
print "@a";
print "\n";

sub hello_sub{
	print "hello sub\n";
	if($_[0]){
		print @_;
		print "\n";
	}
}

sub max{
	if(@_ != 2){
		print "Warning: should two arguments in max!\n";
	}
	my($a, $b) = @_;
	($a>$b)?$a:$b;
}

sub get_max{
	my $max = shift @_;
	foreach (@_){
		$max = ($max>$_)? $max : $_;
	}
	$max;
}

sub func{
	my @arr = (1, 2, 3, 4, 5, 6, 7);
	@arr = reverse @arr;
}

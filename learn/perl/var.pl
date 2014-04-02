#!/usr/bin/perl
# -------------------------------------
#   File Name:	var.pl
#      Author:	Zhao Yanbai
#             	Mon Sep  6 10:31:25 2010
# Description:	none
# -------------------------------------

print "hello " x 3;
print "\n";

@array = qw /aaa bbb ccc ddd eee fff/;
foreach $var (@array){
	print $var . " ";
}
print "\n" . $array[2] . " " . $array[$#array] . "\n";
reverse @array;
print "@array";
print "\n";
@array = reverse @array;
print "@array";
print "\n";

push @array, "push_a";
push @array, "push_b";
print "@array";
print "\n";
$var = pop @array;
print "var: $var\n";
print "@array";
print "\n";

unshift @array, "1111";
unshift @array, "****";
print "@array";
print "\n";
$var = shift @array;
print "var: $var\n";
print "@array";
print "\n";



@num = qw !1 5 7 3 6 0 2 8!;
@num = sort @num;
print "@num";
print "\n";


$var_a = "AAA";
$var_b = "BBB";
print "var_a: $var_a\tvar_b:$var_b\n";
($var_a, $var_b) = ($var_b, $var_a);
print "var_a: $var_a\tvar_b:$var_b\n";

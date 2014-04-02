#!/usr/bin/perl
# -------------------------------------
#   File Name:	hash.pl
#      Author:	Zhao Yanbai
#             	Thu Sep 16 16:23:44 2010
# Description:	none
# -------------------------------------
use strict;

my %hash_a = ("aaa", "a", "bbb", "b", "ddd", "c", "ccc", "d");
print $hash_a{"aaa"} . " ";
print $hash_a{"bbb"} . " ";
print $hash_a{"ddd"} . " ";
print $hash_a{"ccc"} . "\n";

my %hash_b = ( "aaa" => 1, "bbb" => 2, "ddd" => 3, "ccc" => 4);
print $hash_b{"aaa"} . " ";
print $hash_b{"bbb"} . " ";
print $hash_b{"ddd"} . " ";
print $hash_b{"ccc"} . "\n";


my %hash_c;
my %hash_d;
my $var;
$hash_c{"test"} = "wahahahahahahah......";
$hash_c{"pi"} = 3.141592653589793;

my @k;
my @v;
@k = keys %hash_c;
@v = values %hash_c;
print "keys:\t";
foreach $var (@k) {
	print "[" . $var . "] ";
}
print "\nvalues:\t";
foreach $var (@v) {
	print "[" . $var . "] ";
}
print "\n";

my $key;
my $val;
print "<key, value>:\t";
while(($key, $val) = each %hash_c) {
	print "<$key, $val> ";
}
print "\n";
print "keys: ";
foreach $key (keys %hash_b) {
	print "$key ";
}
print "\nsort keys: ";
foreach $key (sort keys %hash_b) {
	print "$key ";
}
print "\n";

if(exists $hash_b{"ddd"}) {
	print "exists....\n";
	delete $hash_b{"ddd"};
}
print "keys left: ";
foreach $var (keys %hash_b) {
	print "$var ";
}
print "\n";

%hash_d = reverse %hash_c;
my @array_d = %hash_d;
foreach $var (@array_d) {
	print $var . "\n";
}



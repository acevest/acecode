#!/usr/bin/perl
# -------------------------------------
#   File Name:	io.pl
#      Author:	Zhao Yanbai
#             	Wed Sep  8 21:24:41 2010
# Description:	none
# -------------------------------------

use strict;

print "io_a\n";
&io_a;
print "io_b\n";
&io_b;

sub io_a{
	my $line;
	while(defined($line=<STDIN>)){
		print "io_a: $line";
	}
}

sub io_b{
	while(<STDIN>){
		print "io_b: $_";
	}
}

#!/usr/bin/perl
# -------------------------------------
#   File Name:	build.pl
#      Author:	Zhao Yanbai
#             	Thu Oct 14 15:59:14 2010
# Description:	none
# -------------------------------------
use strict;
my $file = $ARGV[0];
if(!$file){
	print "Please specify the file name...\n";
}else{
	system ("lex -o $file.c $file");
	system ("gcc -o $file.bin $file.c");
}

#!/usr/bin/perl -w
# 将一个文件夹下的UTF-8编码的文件转换成gb2312
use Encode;
use Encode::CN;
use Encode::Detect::Detector;
$dirname = $ARGV[0];
if(!$dirname)
{
	print "Please add your Directory path\n";
	exit;
}

opendir ( DIR, $dirname) || die "Error in opening dir $dirname\n";
while( ($filename = readdir(DIR))){
		if($filename eq "." || $filename eq ".."){
			next;
		}
		$filename = $dirname . "/" . $filename;
		open INF, "<$filename";
		$line = "";
		while(<INF>){
			$line = $line . $_;
		}
		close INF;
		
		print "Processing... $filename\n" unless (detect($line) =~ /gb/);
		$line=encode("gbk",decode("utf-8",$line)) unless (detect($line) =~ /gb/);
		open OUTF, ">$filename";
		print OUTF $line;
		close OUTF;


		open INF, "<$filename";
		$line = "";
		while(<INF>){
			$line = $line . $_;
		}
		close INF;
		unlink($filename) unless (detect($line) =~ /gb/);
}
closedir(DIR);

#!/usr/bin/perl
# -------------------------------------
#   File Name:	regexp.pl
#      Author:	Zhao Yanbai
#             	Fri Sep 17 09:45:34 2010
# Description:	none
# -------------------------------------
use strict;

$_ = "puppy is learning perl...";
if(/perl/){
	print "matched...\n";
}

my $var = "regular expression";
if($var !~ /aular/){
	print "not matched...\n";
}else{
	print "matched...\n";
}

my @array = split(/ /, $var);
foreach $var (@array){
	print "$var, ";
}
print "\n";

# 当然//其实是m//的简写，大可以这样m() m {} m[] m## m^^
# 例如/\/\//可以写成这样m%//%更清晰
if(m^puppy^) {
	print "matched...\n";
}

# 元字符
# . 匹配除 \n 以外的所有单个字符
# 量词
# * 匹配前一个项目0到多次
# + 匹配前一个项目1到多次
# ? 表示前一个项目可有可无
# | 择一匹配
# - 指定范围

# 字符集简写
# \d ＝[0-9]
# \w ＝[A-Za-z0-9_] 不会匹配一个单词，只会匹配单词里的一个字符,常/\w+/
# \s ＝[\f\t\n\r ] 注意后面还有一个空格


# 反义简写
# \D = [^\d]
# \W = [^\w]
# \S = [^\s]

# [\d\D] 意思是匹配任何数字和非数字，是匹配任意字符的常见做法
# [^\d\D] 是啥玩意儿也不匹配


# 选项修饰符
# i 不区分大小写
# s 匹配任意字符,它会让 . 干[\d\D]该干的事，也就是说让 . 也能匹配 \n
# x 表示可以在正则表达式中随意加上空白,在perl里注释也算空白，所以只要加上x
#    就可以在模式里加上注释
# 可以将选项修饰符组合起来，匹配与其先后顺序无关
$_ = "Puppy ....";
my $reg = "puppy";
if(m#$reg#i) {
	print "matched \"$_\" with regular expression: /$reg/\n";
}

$_ = "hello world\nhello perl\nhello puppy\nhello";
$reg = "worl.*puppy";
if(/$reg/s){
	print "matched \"$_\" with regular expression: /$reg/\n";
}

$_ = "hello world\nhello perl\nhello PUpPY\nhello";
if(m{
	lo
	\s*
	world
	.*
	puppy
}six){
	printf "matched \"$_\"\n";
}

# 锚点
# ^ 用来标记字符串的开头,/^puppy/会匹配以puppy开关的字符串,如"aapuppyaa"
#   会匹配失败
# $ 用来标记字符串的结束
# \b 是单词边界锚点
# \B 非单词边界锚点

# 匹配变量
$_ = "Hello there, puppy...";
if(/\s(\w+)\.\.\./){	#()里的对应$1 如果有多个括号分别对应$1 $2 ...
	print "the world: $1\n";
}
if(/(\w+)\s(\S+,)\s(\w+)\.\.\./){
	print "the worlds:$1 $2 $3\n";
}

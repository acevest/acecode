/*
 *--------------------------------------------------------------------------
 *   File Name:	string.all.tolower.cc
 * 
 * Create Date: Sat Aug 22 00:07:32 2009
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 		Information Security Research Center Of
 * 		Harbin Engineering University
 * 
 * Description:	none
 * 
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s;
	s = "sdfad\r\nsfDFADERswaaDD\r\nDDadf;fsa@#$@#%^%\r\n";

	for(string::size_type pos=0; pos<s.length(); pos++)
	{
		cout<<s[pos];
		s[pos] = tolower(s[pos]);
	}
	for(string::size_type pos=0; pos<s.length(); pos++)
		cout<<s[pos];

	return 0;
}

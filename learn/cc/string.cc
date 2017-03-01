/*
 * ------------------------------------------------------------------------
 *   File Name: string.cc
 *      Author: Zhao Yanbai
 *              2017-01-02 12:04:22 Monday CST
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<iostream>
#include<string>
using namespace std;

int main(int argc, char *argv[]) {

	string s = "Hello World!!\n";
	decltype(s.size()) punct_cnt = 0;

	for(auto c : s) {
		cout << c;
		if(ispunct(c)) {
			punct_cnt++;
		}
	}

	cout << punct_cnt << " punctuation characters in " << s;

	for(auto &c : s) {
		c = toupper(c);
	}

	cout << s;

	return 0;
}

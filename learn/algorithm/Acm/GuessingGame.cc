/*
 *--------------------------------------------------------------------------
 *   File Name:	GuessingGame.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Oct 25 21:16:07 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
/*Guessing Game
 * Description
 *
 * Stan and Ollie are playing a guessing game. Stan thinks of a number between 1 and 10 and Ollie guesses what the number might be. After each guess, Stan indicates whether Ollie's guess is too high, too low, or right on.
 *
 * After playing several rounds, Ollie has become suspicious that Stan cheats; that is, that he changes the number between Ollie's guesses. To prepare his case against Stan, Ollie has recorded a transcript of several games. You are to determine whether or not each transcript proves that Stan is cheating.
 *
 * Input
 *
 * Standard input consists of several transcripts. Each transcript consists of a number of paired guesses and responses. A guess is a line containing single integer between 1 and 10, and a response is a line containing "too high", "too low", or "right on". Each game ends with "right on". A line containing 0 follows the last transcript.
 *
 * Output
 *
 * For each game, output a line "Stan is dishonest" if Stan's responses are inconsistent with the final guess and response. Otherwise, print "Stan may be honest".
 *
 * Sample Input
 *
 * 10
 * too high
 * 3
 * too low
 * 4
 * too high
 * 2
 * right on
 * 5
 * too low
 * 7
 * too high
 * 6
 * right on
 * 0
 *
 * Sample Output
 *
 * Stan is dishonest
 * Stan may be honest
 */
#include<iostream>
#include<string>
using namespace std;

int main() {

	int n;
	int start, end;
	string answer;

	start	= 0;
	end	= 11;

	while(cin>>n && n >0) {

		cin.ignore(); // 忽略掉cin>>n的回车
		getline(cin, answer);

		if(answer == "too high") {
			end = n < end ? n : end;
		} else if(answer == "too low") {
			start = n > start ? n : start;
		} else {
			if(start>=end || n<=start || n>=end)
				cout<<"Stan is dishonest"<<endl;
			else
				cout<<"Stan may be honest"<<endl;

			start	= 0;
			end	= 11;
		}
	}


	return 0;
}

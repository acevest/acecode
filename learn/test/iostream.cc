/*
 * ------------------------------------------------------------------------
 *   File Name: iostream.cc
 *      Author: Zhao Yanbai
 *              Mon Apr  9 13:56:56 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<iostream>
#include<iomanip>
using namespace std;

void line() {
    for(int i=0; i<64; i++) {
        cout<<"-";
    }
    cout<<endl;
}

int main(int argc, char *argv[]) {

    int n = 0x1234ABCD;

    cout<<"0x"<<hex<<n<<endl;
    cout<<"0x"<<n<<endl;
    cout<<uppercase;
    cout<<"0x"<<n<<endl;

    line();
    cout<<oct;
    cout<<n<<endl;

    line();
    cout<<dec;
    cout<<n<<endl;

    line();
    cout<<showpos;
    cout<<n<<endl;

    line();
    cout<<showbase;
    cout<<hex;
    cout<<n<<endl;
    cout<<nouppercase;
    cout<<n<<endl;

    line();
    cout<<noshowbase;
    cout<<"0x";
    cout<<setw(12);
    cout<<setfill('0');
    cout<<n<<endl;

	return 0;
}

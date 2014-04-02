/*
 * ------------------------------------------------------------------------
 *   File Name: const.array.cc
 *      Author: Zhao Yanbai
 *              Wed Apr  4 21:24:34 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<iostream>
using namespace std;

class A { 
public:
    static const int size = 10;
    int data[size];
    void printData() {
        int i;
        for(i=0; i<size; i++) {
            data[i] = i;
        }
        for(i=0; i<size; i++) {
            cout<<data[i]<<" ";
        }
        cout<<endl;
    }
};

int main(int argc, char *argv[]) {

    const int size = 1000;
    int data[size];
    A a;
    a.printData();
	return 0;
}

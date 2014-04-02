/*
 * ------------------------------------------------------------------------
 *   File Name: assert.cc
 *      Author: Zhao Yanbai
 *              Sat Apr  7 14:56:22 2012
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<iostream>
#if 1
#define NDEBUG
#endif
#include<cassert>

using namespace std;

int main(int argc, char *argv[]) {
    assert(0 && "NDEBUG was not defined");
    cout<<"NDEBUG was defined"<<endl;
	return 0;
}

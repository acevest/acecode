/*
 * ------------------------------------------------------------------------
 *   File Name: new.cc
 *      Author: Zhao Yanbai
 *              Sat Apr  7 14:41:52 2012
 * Description: 测试new是抛出异常还是返回0
 * ------------------------------------------------------------------------
 */
#include<iostream>
#include<exception>
#include<new> // set_new_handler
using namespace std;

// this function will be called again and again
// until there're enough memory to alloc
void no_mem() {
    static int n = 0;

    cout<<"No Memory:"<<n++<<endl;

    if(n == 10) {
        cout<<"Exit from no_mem()"<<endl;
        set_new_handler(NULL);  // cause a std::bad_alloc exception
    }
}

int main(int argc, char *argv[]) {
    try {
        long *p = new long [0xFFFFFFFF];
        cout<<p<<endl;
    } catch (exception &e) {
        cout<<e.what()<<endl;
    }


    set_new_handler(no_mem);

    try {
        long *p = new long [0xFFFFFFFF];
        cout<<p<<endl;
    } catch (std::bad_alloc &e) {
        cout<<e.what()<<endl;
    }


    try {
        long *p = new (nothrow) long [0xFFFFFFFF];
        cout<<"Not throw std::alloc and only return:"<<p<<endl;
    } catch (std::bad_alloc &e) {
        cout<<e.what()<<endl;
    }

	return 0;
}

/*
 * ------------------------------------------------------------------------
 *   File Name: const.return.cc
 *      Author: Zhao Yanbai
 *              Mon Apr  9 17:34:58 2012
 * Description: 如果一个函数返回一个常量的类对象值，那么这个函数的返回值
 *              不能是一个左值
 *              返回内部数据类型的值时，const是没有意义的.
 * ------------------------------------------------------------------------
 */
#include<iostream>
using namespace std;

class X {
public:
    X(int i_=0) : i(i_) { }
    void modify() {
        i++;
    }
private:
    int i;
};

X funcA() {
    return X();
}

const X funcB() {
    return X();
}

void funcC(X& x) {
    x.modify();
}

int main(int argc, char *argv[]) {

    funcA() = X(1);     // OK
    funcA().modify();   // OK

    // Error.
    // funcB() = X(1);
    // funcB().modify();

	return 0;
}

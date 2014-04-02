#include<a.h>
#include<iostream>

using namespace std;

int main()
{
	A a;
	a.seta(456);
	a.setb("Fa");
	A b(a);

	cout<<"AAAAA: "<<a.geta()<<" "<<a.getb()<<endl;
	cout<<"AAAAA: "<<b.geta()<<" "<<b.getb()<<endl;

	return 0;
}

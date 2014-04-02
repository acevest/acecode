/*
 *--------------------------------------------------------------------------
 *   File Name:	BinarySearch.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Jul 21 09:49:27 2010
 * 
 * Description:	
 * 	二分搜索算法
 * 
 *--------------------------------------------------------------------------
 */

#include<iostream>
using namespace std;


template <typename T>
int BinarySearch(T *set,const T &item, unsigned int size)
{

	int left, right, middle;	// 这里一定不能定义为unsigned int

	left	= 0;
	right	= size - 1;

	while(left <= right)
	{
		middle	= (left + right)/2;

		if(set[middle] == item)
			return	middle;
		else if(set[middle] < item)
			left	= middle + 1;
		else
			right	= middle - 1;
	}

	return -1;
}

int main()
{
	const int n = 100;
	int a[n];

	for(int i=0; i<n; i++)
		a[i] = i;


	cout<<"res: "<<BinarySearch(a,	32,	100)<<endl;
	cout<<"res: "<<BinarySearch(a,	100,	100)<<endl;
	cout<<"res: "<<BinarySearch(a,	0,	100)<<endl;
	cout<<"res: "<<BinarySearch(a,	102,	100)<<endl;
	cout<<"res: "<<BinarySearch(a,	-10,	100)<<endl;

	return 0;
}

/*
 *--------------------------------------------------------------------------
 *   File Name:	InsertionSort.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Sep 11 11:26:24 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<iostream>
using namespace std;

template <typename T>
void InsertionSort(T *data, int n)
{
	T tmp;
	int i, j;
	for(i=1; i<n; i++)
	{
		tmp = data[i];
		for(j=i-1; j>=0; j--)
		{
			if(tmp < data[j])
				data[j+1] = data[j];
			else
				break;
		}
		data[j+1] = tmp;
	}
}

int main()
{

	const int n = 100;
	int i, a[n];
	for(i=0; i<n; i++)
		a[i] = n-i;

	a[10] = 1234;
	a[11] = -1234;
	a[12] = 1024;
	a[13] = 99;
	a[14] = 99;
	a[15] = 99;


	InsertionSort(a, n);

	for(i=0; i<n; i++)
		cout<<a[i]<<" ";

	cout<<endl;
	return 0;
}

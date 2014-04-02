/*
 *--------------------------------------------------------------------------
 *   File Name:	QuickSort.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Feb 25 17:38:59 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

typedef int Data;

int Partition(Data *d, int s, int e)
{
	Data key = d[s];
	int i = s;
	int j = e-1;

	while(i<j)
	{
		while(i<j && key<=d[j]) j--;
		swap(d[i], d[j]);
		while(i<j && key>=d[i]) i++;
		swap(d[i], d[j]);
	}

	return i;
}

void QuickSort(Data *d, int s, int e)
{
	if(s>=e) return;

	int pos = Partition(d, s, e);
	QuickSort(d, s, pos-1);
	QuickSort(d, pos+1, e);
}


int main()
{
	const int maxsize = 100;
	Data	data[maxsize];

	srand(time(NULL));

	for(int i=0; i<maxsize; i++)
		data[i] = rand() % 100;

	for(int i=0; i<maxsize; i++)
		cout<<data[i]<<" ";
	cout<<endl;
		

	QuickSort(data, 0, maxsize);


	for(int i=0; i<maxsize; i++)
		cout<<data[i]<<" ";
	cout<<endl;


	return 0;
}

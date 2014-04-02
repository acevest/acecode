/*
 *--------------------------------------------------------------------------
 *   File Name:	SelectionSort.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sun Apr 17 12:54:44 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef int Data;

void SelectionSort(Data *data, const int size) {
	int i, j, pos;
	for(i=0; i<size-1; i++) {
		for(j=i+1,pos=i; j<size; j++) {
			if(data[j]<data[pos])
				pos = j;
		}
		swap(data[i], data[pos]);
	}
}

void Initialize(Data *data, const int size) {
	srand(time(NULL));
	for(int i=0; i<size; i++) {
		data[i] = rand() % 256;
	}
}

void Print(Data *data, const int size) {
	for(int i=0; i<size; i++) {
		cout<<data[i]<<" ";
	}
	cout<<endl;
}

int main() {
	const int size = 100;
	Data	data[size];

	Initialize(data, size);

	Print(data, size);

	SelectionSort(data, size);

	Print(data, size);

	return 0;
}

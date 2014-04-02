/*
 *--------------------------------------------------------------------------
 *   File Name:	InsertSort.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Apr 13 10:06:38 2011
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

void InsertionSort(Data *data, const int size) {
	int i, j, tmp;
	for(i=1; i<size; i++) {
		tmp = data[i];
		for(j= i-1; data[j]>tmp && j>=0; j--) {
			data[j+1] = data[j];
		}
		data[j+1] = tmp;
	}
}

void BinaryInsertionSort(Data *data, const int size) {
	int i, j, left, right, mid, tmp;
	for(i=1; i<size; i++) {
		left = 0;
		right = i-1;
		while(left<=right) {
			mid = (left+right)/2;
			if(data[mid]<=data[i])
				left=mid+1;
			else
				right=mid-1;
		}
		tmp = data[i];
		for(j=i-1; j>=left; j--) {
			data[j+1] = data[j];
		}
		data[left] = tmp;
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

	InsertionSort(data, size);
	BinaryInsertionSort(data, size);

	Print(data, size);

	return 0;
}

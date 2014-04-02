/*
 *--------------------------------------------------------------------------
 *   File Name:	BubbleSort.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Apr 15 15:46:34 2011
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

void BubbleSort(Data *data, const int size) {
	Data tmp;
	for(int i=0; i<size; i++) {
		for(int j=0; j<size-i-1; j++) {
			if(data[j]>data[j+1])
				swap(data[j], data[j+1]);	
		}
	}
}

void BubbleSortAdvanced(Data *data, const int size) {
	bool flag;
	for(int i=0; i<size; i++) {
		flag = true;
		for(int j=0; j<size-i-1; j++) {
			if(data[j]>data[j+1]) {
				flag = false;
				swap(data[j], data[j+1]);
			}
		}
		if(flag) break;
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
	const int size = 1000;
	Data	data[size];

	Initialize(data, size);

	Print(data, size);
#if 0
	BubbleSort(data, size);
#else
	BubbleSortAdvanced(data, size);
#endif

	Print(data, size);

	return 0;
}

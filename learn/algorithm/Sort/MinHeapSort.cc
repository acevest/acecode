/*
 *--------------------------------------------------------------------------
 *   File Name:	MinHeapSort.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Apr 18 10:57:15 2011
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

int getLeft(int n) { return 2*n+1; }
int getRight(int n){ return 2*(n+1); }

void HeapAdjust(Data *data, int s, int e) {
	int inx;
	while(s<e) {
		inx = getLeft(s);

		if(inx>=e)				break;

		if((inx+1)<e && data[inx]>data[inx+1])	inx++;

		if(data[s] <= data[inx])		break;

		swap(data[s], data[inx]);

		s = inx;
	}	
}
void HeapSort(Data *data, int size) {
	for(int i=size/2-1; i>=0; i--) {
		HeapAdjust(data, i, size);
	}

	for(int i=size-1; i>=0; i--) {
		cout<<data[0]<<" ";
		swap(data[0], data[i]);
		HeapAdjust(data, 0, i);
	}
	cout<<endl;
}
void Initialize(Data *data, int size) {
	srand(time(NULL));
	for(int i=0; i<size; i++) {
		data[i] = rand() % 256;
	}
}

void Print(Data *data, int size) {
	for(int i=0; i<size; i++) {
		cout<<data[i]<<" ";
	}
	cout<<endl;
}

int main() {
	const int size = 10;
	Data	data[size];

	Initialize(data, size);

	Print(data, size);

	HeapSort(data, size);


	return 0;
}

/*
 *--------------------------------------------------------------------------
 *   File Name:	Knapsack.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Sep 22 00:00:37 2010
 * 
 * Description:	给定c>0, Wi>0, Vi>0, 1<=i<=n要求找出一个n元向量(X1, X2, ...
 * 		Xn), 0<=Xi<=1, 1<=i<=n使Sum(WiXi, 1, n) <= c 且
 * 		Sum(ViXi, 1, n) 大家到最大
 *
 * 		思路很简单就是尽力装载单位价值最高的物品.
 * 
 *--------------------------------------------------------------------------
 */
#include<cmath>
#include<cassert>
#include<cstdlib>
#include<iostream>
using namespace std;

struct item {
	int	n;
	double	rv;
};

int items_cmp(const void *x, const void *y){
	const struct item *a, *b;
	a = (const struct item *)x;
	b = (const struct item *)y;
	double delta = a->rv - b->rv;
	if(fabs(delta) < 1E-5)
		return 0;
	else if(delta < 0)
		return -1;
	
	return 1;
}

void Knapsack(int n, double c, double *w, double *v, double *x){

	struct item *items = new struct item[n];

	for(int i=0; i<n; i++){
		assert(w[i] > 0.0);
		items[i].n = i;
		items[i].rv= v[i]/w[i];
	}

	qsort(items, n, sizeof(struct item), items_cmp);

	for(int i=0; i<n; i++){
		x[i] = 0;
	}

	
	for(int i=n-1; i>=0; i--){
		if(w[items[i].n] > c){
			x[items[i].n] = c/w[items[i].n];
			break;
		}else{
			x[items[i].n] = 1;
			c -= w[items[i].n];
		}
	}

	delete [] items;
}

int main(){

	const int n = 50;

	double	w[n], v[n], x[n];


	for(int i=0; i<n; i++){
		w[i] = (double)(i+1);
		v[i] = (double)(i+1);
	}

	for(int i=0; i<10; i++){
		Knapsack(n, i*200, w, v, x);
		for(int j=0; j<n; j++)
			cout<<x[j]<<" ";
		cout<<endl;
	}


	cout<<"------------------"<<endl;

	w[3] = 20;
	v[3] = 400;

	w[7] = 11;
	v[7] = 420;

	w[48] = 20;
	v[48] = 1500;


	Knapsack(n, 60.0, w, v, x);
	for(int i=0; i<n; i++)
		cout<<x[i]<<" ";

	cout<<endl;

	return 0;
}




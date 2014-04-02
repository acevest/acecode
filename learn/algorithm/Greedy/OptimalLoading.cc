/*
 *--------------------------------------------------------------------------
 *   File Name:	OptimalLoading.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Sep 23 14:11:59 2010
 * 
 * Description: 最优装载问题：
 * 		有一批集装箱要装上一艘载重为c的船,其中集装箱i的重量为Wi,
 * 		要求在装载体积不限的情况下将尽可能多的集装箱装上船.
 *
 * 		给定c>0 Wi>0, 1<=i<=n,要求找出一个(X1, X2, ... Xn)的n元
 * 		向量，其中Xi={0,1}, 1<=i<=n使
 * 			Sum(WiXi, 1, n) <= c 且
 * 			Sum(Xi, 1, n) 最大
 *
 *		思路：
 *			重量轻的先装
 *--------------------------------------------------------------------------
 */
#include<cmath>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cassert>
struct item {
	int	inx;
	double	weight;
};

int items_cmp(const void *x, const void *y){
	const struct item *a, *b;
	a = (const struct item *)x;
	b = (const struct item *)y;
	double delta = a->weight - b->weight;
	if(fabs(delta) < 1E-5)
		return 0;
	else if(delta < 0)
		return -1;
	
	return 1;
}

void OptimalLoading(int n, double c, double *w, int *x){
	assert(n>0 && c>0 && w!=NULL && x!= NULL);

	struct item *items = new struct item[n];
	for(int i=0; i<n; i++){
		x[i] = 0;
		items[i].inx	= i;
		items[i].weight	= w[i];
	}
	
	qsort(items, n, sizeof(struct item), items_cmp);


	for(int i=0; i<n; i++){
		if(c<items[i].weight)
			break;

		x[items[i].inx] = 1;
		c -= items[i].weight;
	}

	delete items;
}

int main()
{

	const int n = 50;
	double	w[n];
	int	x[n];
	srand((unsigned int)time(NULL));
	for(int i=0; i<n; i++){
		w[i] = ((double)(rand()%1000))/((double)(rand()%9+1));
	}
	
	OptimalLoading(n, 100, w, x);

	for(int i=0; i<n; i++){
		printf("%.2f%c ", w[i], x[i]==1?'#':' ');
	}

	printf("\n");

	return 0;
}

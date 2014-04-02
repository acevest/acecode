/*
 *--------------------------------------------------------------------------
 *   File Name:	FullPermutation.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Jul 19 15:14:43 2010
 * 
 * Description:
 *
 * 	全排列的算法
 *
 * 	设要全排列的集合为R={r1, r2, ..., rn}. Ri = R - ri.
 * 	对集合X进行全排列记为P(X). (ri)P(X)表示在全排列P(X)的每一个排列前
 * 面都加上ri得到的排列.
 * 	则R的全排列定义如下:
 * 		当n==1时: P(R) = (r) 
 * 		当n >1时: P(R) = {(r1)P(1), (r2)P(2), ...., (rn)P(n)}
 *--------------------------------------------------------------------------
 */


#include<iostream>
using namespace std;

template <typename T>
void Swap(T &a, T &b)
{
	T c;
	c = a;
	a = b;
	b = c;
}


template <typename T>
void P(T *set, int b, int e)
{
	if(b == e)
	{
		for(int i=0; i<e; i++)
			cout<<set[i];
		cout<<endl;

		return ;
	}


	for(int i=b; i<e; i++)
	{
		Swap(set[b], set[i]);
		P(set, b+1, e);
		Swap(set[b], set[i]);
	}
}

int main()
{

	const int n = 3;
	char a[n];
	for(int i=0; i<n; i++)
		a[i] = 'a' + i;

	P(a, 0, n);

	return 0;
}

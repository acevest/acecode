/*
 *--------------------------------------------------------------------------
 *   File Name:	Knapsack_01.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Sep 11 10:33:28 2010
 * 
 * Description:
 * 	给定n种物品和一个背包，n种物品的重量为Wi,价值为Vi,背的容量为c,
 * 	问应如何装载物品，才能使其价值最大
 * 	即：
 * 		给定c>0, Wi>0, Vi>0, 0<=i<=n-1,要求找出一个n元0-1向量
 * 	(X0, X1, ..., Xn-1), Xi属于{0,1} 使
 * 		W0X0+W1X1+...Wn-1Xn-1<=c
 * 	且	V0X0+V1X1+...Wn-1Xn-1达到最大
 *
 *
 *
 * 	设F(i,sz)背包容量为sz,可选的物品为i, i+1, ... n-1
 * 		 + max{F(i+1,sz), F(i+1, sz-Wi)+Vi} (sz>=Wi)
 *	F(i,sz) = |
 * 		 + F(i+1,sz) (0<=sz<Wi)
 *		 + Vn-1 (sz>=Wi-1)
 *	F(n-1,sz)=|
 *		 + 0 (0<=sz<Wn-1)
 *--------------------------------------------------------------------------
 */
#include<cstring>
#include<cassert>
#include<iostream>
using namespace std;

void Knapsack_01_DP(int n, int c, int *w, int *v, int **f){

}

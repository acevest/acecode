/*
 *--------------------------------------------------------------------------
 *   File Name:	PickingBalls.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Tue Oct 26 14:04:28 2010
 * 
 * Description:	
 *
 * 	对于前半段
 * 	C(m,n+1) = ((m-n)/(n+1))*C(m,n)
 *	   m!				    m!
 * 	-------------- = ((m-n)/(n+1)) ---------------
 *	(m-n-1)!(n+1)!			  (m-n)!n!
 *
 *	C(i,j) = ((i-j+1)/j)*C(i,j-1)
 *--------------------------------------------------------------------------
 */
/*Picking Balls
 * TimeLimit: 1 Second   MemoryLimit: 32 Megabyte
 * Description
 *
 * Balls of N different colors are put inside a box. There are Mi balls of color i. What is the possibility of taking K balls out of the box and exactly Pj of them are of color j for each j = 1, 2, ..., N.
 *
 * Input
 *
 * Input contains several cases, each of which occupies 3 lines. The first line contains two non-negative integers N and K. The next line has N positive integers M1, M2, .... Mn, followed by a line with N non-negative integers P1, P2, .... Pn. It is guaranteed that K = P1 + P2 + ... + Pn. You may also assume that the total number of balls in any of the cases does not exceed 50.
 *
 * Subsequent test cases are separated with a single blank line. The input is terminated with two -1's. This case is not to be processed.
 *
 * Output
 *
 * One number on a single line for each case - the possibility. Round to 5 digits after the decimal point.
 *
 * Sample Input
 *
 *
 * 3 3
 * 2 2 2
 * 1 1 1
 *
 * 2 1
 * 2 1
 * 0 1
 *
 * -1 -1
 *
 *  Sample Output
 *
 *
 *  0.40000
 *  0.33333
 */

#include<stdio.h>
#include<string.h>
#define	SIZE	52
typedef long long T;	/* 伤了，unsigned long long 就是Wrong Answer... */
T c[SIZE][SIZE];

int main() {

	T	i, j, mid;
	int	N, K;
	int	M[SIZE],P[SIZE];
	int	sum;
	double	ret;

	memset(c, 0, SIZE*SIZE*sizeof(T));

	for(i=0; i<SIZE; i++) {
		c[i][0] = 1;
		c[i][i] = 1;
	}

	for(i=1; i<SIZE; i++) {
		mid = i/2 + 1; 
		for(j=1; j<mid; j++) {
			c[i][i-j] = c[i][j] = ((i-j+1)/(j*1.0))*c[i][j-1];
		}
	}

	
	while(1) {
		scanf("%d%d", &N, &K);

		if(N==-1 && K==-1) break;

		for(i=0, sum=0; i<N; i++) {
			scanf("%d", M+i);
			sum += M[i];
		}

		for(i=0; i<N; i++)
			scanf("%d", P+i);

		ret = (double)1.0/c[sum][K];

		for(i=0; i<N; i++)
			ret *= c[M[i]][P[i]];

		
		printf("%.5lf\n", ret);
	}

	return 0;
}

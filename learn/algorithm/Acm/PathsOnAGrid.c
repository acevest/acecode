/*
 *--------------------------------------------------------------------------
 *   File Name:	PathsOnAGrid.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 28 10:26:49 2010
 * 
 * Description:	
 *
 * 	m!	   m*m-1*m-2...*m-n+1
 * ------------ = ------------------
 *  (m-n)!n!	   	n!
 * 
 * 从(0,0) 到(m, n)的不同最短路径数为C(m+n, m)
 *--------------------------------------------------------------------------
 */

#include<stdio.h>

double C(double m, double n) {
	double i, j;
	double ret = 1;
	if(n == 0) return 1;
	for(i=1, j=m; i<=n; i++, j--)
		ret *= 1.0*j/i;

	return ret;
}

int main() {

	double m, n;

	while(1) {
		scanf("%lf%lf", &m, &n);
		if(m==0 && n==0) break;

		/* C(m+n, m) == C(m+n, n) */
		printf("%.0lf\n", m<n ? C(m+n, m) : C(m+n, n));
	}


	return 0;
}

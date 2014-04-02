/*
 *--------------------------------------------------------------------------
 *   File Name:	DivisorSummation.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Tue Oct 26 10:25:35 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
/*Divisor Summation
 * TimeLimit: 5 Second   MemoryLimit: 32 Megabyte
 * Totalsubmit: 1267   Accepted: 318  
 * Description
 *
 * Give a natural number n (1 <= n <= 500000), please tell the summation of all its proper divisors.
 *
 * Definition: A proper divisor of a natural number is the divisor that is strictly less than the number.
 *
 * e.g. number 20 has 5 proper divisors: 1, 2, 4, 5, 10, and the divisor summation is: 1 + 2 + 4 + 5 + 10 = 22.
 *
 * Input
 *
 * An integer stating the number of test cases, and that many lines follow each containing one integer between 1 and 500000.
 *
 * Output
 *
 * One integer each line: the divisor summation of the integer given respectively.
 *
 * Sample Input
 *
 *
 * 3
 * 2
 * 10
 * 20 
 * Sample Output
 *
 *
 * 1
 * 8
 * 22
 */
#include<stdio.h>
#include<string.h>

#define	SIZE 500004
int	sum[SIZE];
int main() {

	int cases,n;
	int i, j;

	memset((void *)sum, 0, SIZE*sizeof(int));

	for(i=1; i<SIZE; i++) {
		for(j=2; j*i<SIZE; j++) {
			sum[j*i] += i;
		}
	}

	scanf("%d", &cases);

	while(cases--) {
		scanf("%d", &n);
		printf("%d\n", sum[n]);
	}

	return 0;
}

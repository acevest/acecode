/*
 *--------------------------------------------------------------------------
 *   File Name:	Encoding.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Tue Oct 26 13:14:17 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
/*Encoding
 * TimeLimit: 1 Second   MemoryLimit: 32 Megabyte
 * Description
 *
 * Given a string containing only 'A' - 'Z', we could encode it using the following method:
 *
 * 1. Each sub-string containing k same characters should be encoded to "kX" where "X" is the only character in this sub-string.
 *
 * 2. If the length of the sub-string is 1, '1' should be ignored
 *
 * Input
 *
 * The first line contains an integer N (1 <= N <= 100) which indicates the number of test cases. The next N lines contain N strings. Each string consists of only 'A' - 'Z' and the length is less than 100.
 *
 * Output
 *
 * For each test case, output the encoded string in a line.
 *
 * Sample Input
 *
 * 2
 * ABC
 * ABBCCC
 *
 * Sample Output
 *
 * ABC
 * A2B3C
 */
#include<stdio.h>

#define	SIZE	128
char str[SIZE];

int main() {
	int	n;
	int	cases;
	char	*p;
	char	ch;

	scanf("%d", &cases);

	while(cases--) {
		scanf("%s", str);

		p = str;
		n = 0;
		ch = *p;

		if(!*p) continue;

		while(*p) {
			if(ch != *p) {
				if(n > 1) printf("%d", n);
				printf("%c", ch);
				ch = *p;
				n = 0;
			}

			n++;
			p++;
		}
		if(n > 1) printf("%d", n);
		printf("%c\n", ch);

	}

	return 0;
}

/*
 *--------------------------------------------------------------------------
 *   File Name:	Square.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Oct 25 14:27:15 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
/*		Square
 * Description
 *
 * Given a set of sticks of various lengths, is it possible to join them end-to-end to form a square?
 *
 * Input
 *
 * The first line of input contains N, the number of test cases. Each test case begins with an integer 4 <= M <= 20, the number of sticks. M integers follow; each gives the length of a stick - an integer between 1 and 10,000.
 *
 * Output
 *
 * For each case, output a line containing "yes" if is is possible to form a square; otherwise output "no".
 *
 * Sample Input
 *
 * 3
 * 4 1 1 1 1
 * 5 10 20 30 40 50
 * 8 1 7 2 6 4 4 3 5
 *
 * Sample Output
 *
 * yes
 * no
 * yes
 */
#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

#define	SIZE 80
int	N, M;
int	x[SIZE];
bool	b[SIZE];
int	edge_count = 0;
int	edge = 0;

bool DFS(int depth, int sum) {

	for(int i=depth; i<M; i++) {
		if(b[i]) continue;

		int	curt_edge = sum + x[i];

		if(curt_edge == edge) {
			b[i] = true;
			if(++edge_count == 3) return true;
			if(DFS(0, 0)) return true;
			--edge_count;
			b[i] = false;
		}else if(curt_edge < edge) {
			b[i] = true;
			if(DFS(i+1, curt_edge)) return true;
			b[i] = false;
		}
	}

	return false;
}

bool cmp(int a, int b){return a>b;}

int main() {
	int sum;

	cin>>N;
	while(N--) {

		cin>>M;

		sum = 0;
		for(int i=0; i<M; i++) {
			cin>>x[i];
			sum += x[i];
			b[i] = false;
		}

		if(sum % 4) {
			printf("no\n");
			continue;
		}

		edge = sum / 4;
		edge_count = 0;


		sort(x, x+M, cmp);

		printf("%s\n", DFS(0, 0) ? "yes" : "no");

	}

	return 0;
}

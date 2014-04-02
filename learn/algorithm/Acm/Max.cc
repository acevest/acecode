/*
 *--------------------------------------------------------------------------
 *   File Name:	Max.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Jan 27 13:08:02 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<iostream>
#include<cassert>
using namespace std;


#define	SZ	256
typedef int (*func)(int, int);

int	data[SZ];
func	op[SZ];
long long sum[SZ][SZ];

int add(int a, int b){return a+b;}
int mul(int a, int b){return a*b;}

int main()
{
	int N;
	char flag;
	while(cin>>N)
	{
		for(int i=0; i<N; i++)
		{
			cin>>data[i];
			sum[i][i] = data[i];
			if(i == N-1) break;
			cin>>flag;
			switch(flag)
			{
			case '*':
				op[i] = mul;
				break;
			case '+':
				op[i] = add;
				break;
			default:
				assert(0);
			}

		}


		for(int d=1; d<N; d++)
		{
			for(int i=0; i+d<N; i++)
			{
				int j = i+d;
				sum[i][j] = op[i](sum[i][i], sum[i+1][j]);
				for(int k=i+1; k<j; k++)
				{
					int t = op[k](sum[i][k], sum[k+1][j]);
					if(t>sum[i][j])
						sum[i][j] = t;
				}
			}
		}

#if 0
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++){
				cout<<sum[i][j]<<" ";
			}
			cout<<endl;
		}
#endif

		cout<<sum[0][N-1]<<endl;
	}

	return 0;
}

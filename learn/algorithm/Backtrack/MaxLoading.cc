/*
 *--------------------------------------------------------------------------
 *   File Name:	MaxLoading.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Feb 17 12:15:16 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
#include<cassert>
using namespace std;

const int N = 1024;
int w[N];	// Weight
int c;
int n;
int curw;	// current weight
int maxw;	// max weight
int x[N];	// result
int best[N];
int rest;

void Backtrack(int t)
{
	if(t>=n)
	{
		maxw = curw>maxw ? curw : maxw;
		for(int i=0; i<n; i++)
			best[i] = x[i];
	}
	else
	{
		rest -= w[t];

		if(curw+w[t] <= c && curw+w[t]+rest > maxw)
		{
			x[t] = 1;
			curw += w[t];
			Backtrack(t+1);
			curw -= w[t];
		}

		if(curw+rest > maxw)
		{
			x[t] = 0;
			Backtrack(t+1);
		}

		rest += w[t];
	}
}

int main()
{
	maxw = curw = 0;
	cin>>c;
	cin>>n;
	assert(n<N);
	for(int i=0; i<n; i++)
	{
		cin>>w[i];
		rest += w[i];
	}
	
	Backtrack(0);

	cout<<"MaxLoad Weight: "<<maxw<<endl;
	for(int i=0; i<n; i++)
	{
		cout<<best[i]<<" ";
	}
	cout<<endl;

	return 0;
}

/*
 *--------------------------------------------------------------------------
 *   File Name:	Equal.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Feb 17 16:03:45 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
using namespace std;

const int max_size = 1024;
const int N = 6;
int cases;
int n;
int subval;
int curtval;
int nsub;	// 已经数了多少份分片了
int data[max_size];


bool Backtrack(int t)
{
	if(nsub == N-1)
	{
		cout<<"yes"<<endl;
		return true;
	}
	else
	{
		for(int i=t; i<n; i++)
		{
			swap(data[t], data[i]);
			if(curtval+data[t]<=subval)
			{
				curtval += data[t];

				if(curtval == subval)
				{
					nsub++;
					curtval = 0;
				}


				if(Backtrack(t+1))
					return true;
			}
			swap(data[t], data[i]);
		}
	}

	if(t==0)
	{
		cout<<"no"<<endl;
	}
}

int main()
{
	int sum=0;

	cin>>cases;

	while(cases--)
	{
		cin>>n;
		sum = 0;
		for(int i=0; i<n; i++)
		{
			cin>>data[i];
			sum += data[i];
		}

		// 如果分成N份不能分成整数，则一定不行
		subval = sum / N;
		curtval = 0;
		if(subval*N != sum || n<6)
		{
			cout<<"no"<<endl;
			continue;
		}

		nsub = 0;
	
		Backtrack(0);

	}

	return 0;
}

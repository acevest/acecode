/*
 *--------------------------------------------------------------------------
 *   File Name:	MaxSubMulti.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Feb 26 13:43:20 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cassert>
using namespace std;

long long LevelOne(const int *d, unsigned int n)
{
	long long ret;
	long long max;
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=0, ret=1; j<n; j++)
		{
			ret *= ((i==j) ? 1 : d[j]);
			if(ret == 0) break;
		}
		max = (i==0 ? ret : max);
		max = (max<=ret ? ret : max);
	}

	return max;
}
long long LevelTwo(const int *d, unsigned int n)
{
	int *f = new int [n];
	int *r = new int [n];
	long long *p = new long long [n];
	long long max;

	assert(f!=0 && r!=0 && p!=0);

	long long fv=1, rv=1;
	for(int i=0; i<n; i++)
	{
		int j = n-i-1;
		fv *= d[i];
		rv *= d[j];
		f[i] = fv;
		r[j] = rv;
	}

	max = p[0] = r[1];
	for(int i=1; i<n; i++)
	{
		p[i] = f[i-1] * r[i+1];
		max = max<p[i] ? p[i] : max;
	}

	delete [] f;
	delete [] r;
	delete [] p;

	return max;
}

long long LevelThree(int *d, int n)
{
	int n_zero = 0;
	int n_neg = 0;
	int maxneg = 0;
	int minpos = 0;
	int maxnegi = 0;
	int minposi = 0;
	int zeroi = 0;
	int out;
	long long max = 1;

	for(int i=0; i<n; i++)
	{
		if(d[i] < 0)
		{
			n_neg++;
			if(maxneg == 0)
			{
				maxneg = d[i];
				maxnegi = i;
			}
			else if(maxneg<d[i])
			{
				maxneg = d[i];
				maxnegi = i;
			}
		}
		else if(d[i] == 0)
		{
			zeroi = i;
			if(++n_zero>1) return 0;
		}
		else
		{
			if(minpos == 0)
			{
				minpos = d[i];
				minposi = i;
			}
			else if(minpos > d[i])
			{
				minpos = d[i];
				minposi = i;
			}
		}
	}


	if(n_zero==1 && n_neg%2==1)
	{
		return 0;
	}
	else if(n_zero==1 && n_neg%2==0)
	{
		out = zeroi;
	}
	else if(n_zero==0 && n_neg%2==1)
	{
		out = maxnegi;
	}
	else if(n_zero==0 && n_neg%2==0)
	{
		out = minposi;
	}

	for(int i=0; i<n; i++)
	{
		max *= (i==out)?1:d[i];
	}
	return max;
}

int main()
{
	const int maxsize = 10;
	int data[maxsize];
	long long max1, max2, max3;

	srand(time(NULL));

	for(int i=0; i<maxsize; i++)
		data[i] = ((rand()%10<2) ? -1:1) * (rand()%10);

	for(int i=0; i<maxsize; i++)
		cout<<data[i]<<" ";
	cout<<endl;
		
	max1 = LevelOne(data, maxsize);
	max2 = LevelTwo(data, maxsize);
	max3 = LevelThree(data, maxsize);

	cout<<"max1: "<<max1<<endl;
	cout<<"max2: "<<max2<<endl;
	cout<<"max3: "<<max3<<endl;

	return 0;
}

/*
 *--------------------------------------------------------------------------
 *   File Name:	mutex_try_time.cc
 * 
 * Description:	多线程竞争互斥锁的情况下用pthread_mutex_trylock一次加解锁
 * 所用时间与同时竞争该锁的关系
 * 		
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Mon Jun 22 17:54:23 2009
 * Last Update: Mon Jun 22 17:54:23 2009
 * 
 *--------------------------------------------------------------------------
 */

#include<sys/time.h>
#include<iostream>
using namespace std;
const long long count = 100000000;
unsigned long long space_usec=0;
pthread_mutex_t mutex;
void *testThread(void *arg)
{
	unsigned long long i,usec;
	struct timeval tvBegin, tvEnd;
	i = 0;
	gettimeofday(&tvBegin, NULL);
	while(i++ < count)
	{
		if(pthread_mutex_trylock(&mutex) == 0)
			pthread_mutex_unlock(&mutex);
	}
	gettimeofday(&tvEnd, NULL);
	usec = (tvEnd.tv_sec - tvBegin.tv_sec) * 1000000
		+ tvEnd.tv_usec - tvBegin.tv_usec;
	//cout<<count<<" times lock and unlock total: "<<usec<<"usecs"<<endl;
	//cout<<usec*1000/count<<" necs per second"<<endl;
	//cout<<usec-space_usec<<"\t"<<space_usec<<endl;
	cout<<count<<"\t"
	    <<usec-space_usec<<"\t"
	    <<((usec-space_usec)*1000/count)<<endl;
}
int main()
{
	struct timeval tvBegin, tvEnd;
	long long i;
	unsigned long long sec, usec;

	i=0;
	gettimeofday(&tvBegin, NULL);
	while(i++ < count)
	{
	}
	gettimeofday(&tvEnd, NULL);
	usec = (tvEnd.tv_sec - tvBegin.tv_sec) * 1000000
		+ tvEnd.tv_usec - tvBegin.tv_usec;
	space_usec = usec;
	//cout<<count<<"  total: "<<usec<<"usecs"<<endl;
	//cout<<usec*1000/count<<" necs per second"<<endl;

	pthread_t pt;
	pthread_mutex_init(&mutex, NULL);
	for(int i=0; i<6; i++)
		pthread_create(&pt, NULL, testThread, NULL);


	while(1);
	return 0;
}

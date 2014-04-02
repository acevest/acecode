/*
 *--------------------------------------------------------------------------
 *   File Name:	mutex_time2.cc
 * 
 * Description:	多线程竞争互斥锁的情况下一次加解锁所用时间与同时竞争该锁的
 * 		线程数相关
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Thu Apr 30 14:46:25 2009
 * Last Update: Thu Apr 30 14:46:25 2009
 * 
 *--------------------------------------------------------------------------
 */

#include<sys/time.h>
#include<iostream>
using namespace std;
const int count = 100000000;
pthread_mutex_t mutex;
void *testThread(void *arg)
{
	unsigned long i,usec;
	struct timeval tvBegin, tvEnd;
	i = 0;
	gettimeofday(&tvBegin, NULL);
	while(i++ < count)
	{
		pthread_mutex_lock(&mutex);
		pthread_mutex_unlock(&mutex);
	}
	gettimeofday(&tvEnd, NULL);
	usec = (tvEnd.tv_sec - tvBegin.tv_sec) * 1000000
		+ tvEnd.tv_usec - tvBegin.tv_usec;
	cout<<count<<" times lock and unlock total: "<<usec<<"usecs"<<endl;
	cout<<usec*1000/count<<" necs per second"<<endl;
}
int main()
{
	struct timeval tvBegin, tvEnd;
	int i;
	unsigned long sec, usec;

	i=0;
	gettimeofday(&tvBegin, NULL);
	while(i++ < count)
	{/*
		int d;
		d++;d++;
		d++;
		d++;d++;//d++;*/
	}
	gettimeofday(&tvEnd, NULL);
	usec = (tvEnd.tv_sec - tvBegin.tv_sec) * 1000000
		+ tvEnd.tv_usec - tvBegin.tv_usec;
	cout<<count<<"  total: "<<usec<<"usecs"<<endl;
	cout<<usec*1000/count<<" necs per second"<<endl;

	pthread_t t1, t2, t3, t4;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, testThread, NULL);
/*	pthread_create(&t2, NULL, testThread, NULL);
	pthread_create(&t3, NULL, testThread, NULL);
	pthread_create(&t4, NULL, testThread, NULL);
*/


	while(1);
	return 0;
}

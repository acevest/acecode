/*
 *--------------------------------------------------------------------------
 *   File Name:	mutex_time.cc
 * 
 * Description:	测试互斥锁耗费的时间量
 * 		我的的笔记本上测试的结果是:一次加解锁的时间共是14ns
 * 		测试环境是:Fedora 10
 * 		笔记本型号:Thinkpad R61i 7742
 * 		其中CPU为: Intel(R) Core(TM)2 Duo CPU     T5550  @ 1.83GHz
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Thu Apr 30 14:07:08 2009
 * Last Update: Thu Apr 30 14:07:08 2009
 * 
 *--------------------------------------------------------------------------
 */


#include<sys/time.h>
#include<iostream>
using namespace std;
int testfun(){return 0;}
int main()
{
	struct timeval tvBegin, tvEnd;
	const long long count = 100000000;
	long long i;
	long long sec, usec;
	pthread_mutex_t mutex;

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

	pthread_mutex_init(&mutex, NULL);
	gettimeofday(&tvBegin, NULL);
	i = 0;
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


	return 0;
}

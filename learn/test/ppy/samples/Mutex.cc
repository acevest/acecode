/*
 *--------------------------------------------------------------------------
 *   File Name:	Mutex.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Mar 30 20:54:36 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include <iostream>
#include <pthread.h>
#include <ppy.h>

using namespace std;
using namespace ppy;

Mutex mt;

static int n = 0;
static int m = 0;
const int times = 1000000;

void *thread(void *arg) {

	int id = (int)arg;
	int i=times;

	try{
		while(i--) {
			mt.Lock();
			n++;
			mt.Unlock();
			m++;
		}
	} catch(const Exception& e) {
		cout<<"thread:"<<id<<" ";
		cout<<e.getDetail()<<endl;
	}

	return NULL;
}

int main() {

	const int threads = 4;
	pthread_t ptd[threads];
	for(int i=0; i<threads; i++) {
		pthread_create(ptd+i, NULL, thread, (void *)i);
	}

	for(int i=0; i<threads; i++) {
		pthread_join(ptd[i], NULL);
	}

	cout<<"result should be:"<<times*threads<<endl;
	cout<<"n is:"<<n<<endl;
	cout<<"m is:"<<m<<endl;

	return 0;
}

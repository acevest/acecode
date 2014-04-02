/*
 *--------------------------------------------------------------------------
 *   File Name:	Mutex.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Mar 21 23:46:47 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_MUTEX_H
#define	_PPY_MUTEX_H

#include <pthread.h>
#include "Exception.h"
class Mutex {
public:
	~Mutex();
	Mutex();
	void Lock();
	void Unlock();
	bool TryLock();
private:
	pthread_mutex_t m_mutex;
};


#endif //_PPY_MUTEX_H

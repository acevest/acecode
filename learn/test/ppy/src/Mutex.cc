/*
 *--------------------------------------------------------------------------
 *   File Name:	Mutex.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Mar 26 10:28:19 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include "Mutex.h"

using namespace ppy;

Mutex::~Mutex() {

	pthread_mutex_destroy(&m_mutex);

}

Mutex::Mutex() {

	int err = pthread_mutex_init(&m_mutex, 0);

	if(err != 0)
		PPY_GENERIC_EXCEPT(err);
}

void Mutex::Lock() {

	int err = pthread_mutex_lock(&m_mutex);

	if(err != 0)
		PPY_GENERIC_EXCEPT(err);
}

void Mutex::Unlock() {

	int err = pthread_mutex_unlock(&m_mutex);

	if(err != 0)
		PPY_GENERIC_EXCEPT(err);
}

bool Mutex::TryLock() {

	int err = pthread_mutex_trylock(&m_mutex);

	if(err == EBUSY)
		return false;

	if(err != 0)
		PPY_GENERIC_EXCEPT(err);

	return true;
}

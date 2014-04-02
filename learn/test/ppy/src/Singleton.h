/*
 *--------------------------------------------------------------------------
 *   File Name:	Singleton.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Mar 10 16:13:19 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_SINGLETON_H
#define	_PPY_SINGLETON_H
#include<cassert>
namespace ppy {

template <typename T>
class Singleton {
public:
	Singleton() {
		assert(pSingleton == 0);
		pSingleton = static_cast<T *>(this);
	}
	~Singleton() {
		assert(pSingleton != 0);
		pSingleton = 0;
	}
	static T* getSingletonPtr() {
			return pSingleton;
	}
	static T& getSingleton() {
		assert(pSingleton != 0);
		return *pSingleton;
	}
protected:
	static T *pSingleton;
};
	
template <typename T> T *Singleton <T>::pSingleton = 0;

}

#endif //_PPY_SINGLETON_H

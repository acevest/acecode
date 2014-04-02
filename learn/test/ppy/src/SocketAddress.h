/*
 *--------------------------------------------------------------------------
 *   File Name:	SocketAddress.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Mar 23 15:08:04 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_SOCKETADDRESS_H
#define	_PPY_SOCKETADDRESS_H

#include "Utility.h"

namespace ppy {
namespace net {

class SocketAddress {
public:
	virtual ~SocketAddress() {}

	virtual operator struct sockaddr *() = 0;

	virtual operator socklen_t () = 0;

	virtual int getFamily() = 0;

	virtual int getPort() = 0;

};


} // end namespace net
} // end namespace ppy


#endif //_PPY_SOCKETADDRESS_H

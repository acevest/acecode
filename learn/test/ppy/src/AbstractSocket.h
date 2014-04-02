/*
 *--------------------------------------------------------------------------
 *   File Name:	AbstractSocket.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Mar 30 21:33:55 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_ABSTRACTSOCKET_H
#define	_PPY_ABSTRACTSOCKET_H


#include "Exception.h"
#include "SocketAddress.h"

namespace ppy
{
namespace net
{

enum SocketType {
	INET_TCP,
	INET4_TCP = INET_TCP,
	INET_UDP,
	INET4_UDP = INET_UDP,
	INET6_TCP,
	INET6_UDP
};

class AbstractSocket {
public:
	virtual void Create(SocketType st) = 0;
	
	virtual void Bind(SocketAddress& sa) = 0;

	virtual void Connect(SocketAddress& sa, int timeout) = 0;

	virtual void Shutdown() throw() = 0;

	virtual void Close() throw() = 0;

}; // end class AbstractSocket

} // end namespace net
} // end namespace ppy

#endif //_PPY_ABSTRACTSOCKET_H

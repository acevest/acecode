/*
 *--------------------------------------------------------------------------
 *   File Name:	TcpSocket.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Mar 23 14:56:37 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_TCPSOCKET_H
#define	_PPY_TCPSOCKET_H

#include "Exception.h"
#include "SocketAddress.h"
#include "AbstractSocket.h"

namespace ppy
{
namespace net
{

class TcpSocket : public AbstractSocket {
public:
	/**
	 * Create a new Socket.
	 */
	TcpSocket();
	TcpSocket(int fd);
	/**
	 * Destruct this Socket.
	 */
	virtual ~TcpSocket();

	virtual void Create(SocketType st = INET_TCP);

	virtual void Bind(SocketAddress& sa);

	virtual void Listen(int backlog = SOMAXCONN);

	virtual TcpSocket *Accept();

	virtual void Connect(SocketAddress& sa, int timeout);

	virtual void Shutdown() throw();

	virtual void Close() throw();

	virtual void Disconnect() throw();

	bool	isConnected() const { return m_Connected; }

	void	setBlocking();
	void	setNonBlocking();

	virtual void	setTimeOut(long usec);
	virtual void	setTimeOut(const struct timeval& tv);

protected:
	int	m_Domain;
	int	m_Type;
	int	m_Socket;
	bool	m_Connected;	// 是否已经建立连接
	struct timeval m_TimeOut;
};


} // end namespace net
} // end namespace ppy

#endif //_PPY_TCPSOCKET_H

/*
 *--------------------------------------------------------------------------
 *   File Name:	TcpSocket.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Tue Mar 29 13:50:11 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include "TcpSocket.h"
#include "Utility.h"
#include <unistd.h>
#include <fcntl.h>

using namespace ppy::net;

TcpSocket::TcpSocket() :
m_Socket(-1),
m_Connected(false)
{
}

TcpSocket::TcpSocket(int fd) :
m_Socket(fd)
{
}

TcpSocket::~TcpSocket() {
	Close();
}

void TcpSocket::Create(SocketType st) {
	int domain;
	int type;
	int skfd;

	if(m_Socket != -1) Disconnect();

	switch(st) {
	case INET4_TCP:	domain=AF_INET;	type=SOCK_STREAM;break;
	case INET4_UDP:	domain=AF_INET;	type=SOCK_DGRAM; break;
	case INET6_TCP:	domain=AF_INET6;type=SOCK_STREAM;break;
	case INET6_UDP:	domain=AF_INET6;type=SOCK_DGRAM; break;
	default: PPY_ASSERT(0);
	}

	skfd = socket(domain, type, 0);

	if(skfd<0) PPY_GENERIC_EXCEPT(errno);

	m_Domain = domain;
	m_Type = type;
	m_Socket = skfd;

	int i;
	setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
}

void TcpSocket::Bind(SocketAddress& sa) {
	PPY_ASSERT(m_Socket != -1);
	PPY_ASSERT(sa.getFamily() == m_Domain());

	if(bind(m_Socket, sa, sa) == -1) {
		PPY_GENERIC_EXCEPT(errno);
	}
}

void TcpSocket::Listen(int backlog) {
	PPY_ASSERT(m_Socket != -1);

	if(listen(m_Socket, backlog) == -1) {
		PPY_GENERIC_EXCEPT(errno);
	}
}

TcpSocket *TcpSocket::Accept() {
	struct sockaddr sa;
	socklen_t sz;
	int fd = accept(m_Socket, &sa, &sz);
	if(fd == -1) {
		PPY_GENERIC_EXCEPT(errno);
	}

	TcpSocket *st = new TcpSocket(fd);
	st->m_Connected = true;

	return st;
}

void TcpSocket::Connect(SocketAddress& sa, int timeout) {
	//timeout 暂时先不支持
	int err = connect(m_Socket, sa, sa);
	if(err == -1) {
		PPY_GENERIC_EXCEPT(errno);
	}
}


void TcpSocket::Shutdown() throw() {
	if(m_Socket != -1)
		shutdown(m_Socket, SHUT_RDWR);
}

void TcpSocket::Close() throw() {
	if(m_Socket != -1) {
		close(m_Socket);
		m_Connected = false;
		m_Socket = -1;
	}
}
void TcpSocket::Disconnect() throw() {
	Shutdown();
	Close();
}

void TcpSocket::setBlocking() {
	int flags = fcntl(m_Socket, F_GETFL, 0);
	if(flags < 0) {
		PPY_GENERIC_EXCEPT(errno);
	}

	flags &= ~O_NONBLOCK;

	if(fcntl(m_Socket, F_GETFL, 0) < 0) {
		PPY_GENERIC_EXCEPT(errno);
	}
}

void TcpSocket::setNonBlocking() {
	int flags = fcntl(m_Socket, F_GETFL, 0);
	if(flags < 0) {
		PPY_GENERIC_EXCEPT(errno);
	}

	flags |= O_NONBLOCK;

	if(fcntl(m_Socket, F_GETFL, 0) < 0) {
		PPY_GENERIC_EXCEPT(errno);
	}
}

void TcpSocket::setTimeOut(long usec) {
	struct timeval tv;
	tv.tv_sec	= usec / 1000000;
	tv.tv_usec	= usec % 1000000;
	setTimeOut(tv);
}

void	TcpSocket::setTimeOut(const struct timeval& tv) {
	m_TimeOut = tv;
}

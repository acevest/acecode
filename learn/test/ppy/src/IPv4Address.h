/*
 *--------------------------------------------------------------------------
 *   File Name:	IPv4Address.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Mar 23 15:49:40 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PPY_IPV4ADDRESS_H
#define	_PPY_IPV4ADDRESS_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

#include "SocketAddress.h"

namespace ppy {
namespace net {

class IPv4Address : public SocketAddress {
public:
	IPv4Address();
	IPv4Address(in_addr_t saddr, in_port_t port);
	IPv4Address(struct in_addr& addr, in_port_t port);
	IPv4Address(const std::string ip, in_port_t port);
	IPv4Address(struct sockaddr *sa);

	bool setAddressBySockAddr(struct sockaddr *sa);
	bool setAddressByHost(const std::string host, in_port_t port);
	int getFamily();
	int getPort();
	operator struct sockaddr *();
	operator socklen_t ();
private:
	struct sockaddr_in m_addr;
};


}
}


#endif //_PPY_IPV4ADDRESS_H

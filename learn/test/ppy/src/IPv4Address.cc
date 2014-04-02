/*
 *--------------------------------------------------------------------------
 *   File Name:	IPv4Address.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Mar 23 15:56:30 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include "Utility.h"
#include "Exception.h"
#include "IPv4Address.h"

using namespace ppy::net;

IPv4Address::IPv4Address() {
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
}


IPv4Address::IPv4Address(in_addr_t saddr, in_port_t port) {
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);
	m_addr.sin_addr.s_addr = saddr;
}

IPv4Address::IPv4Address(struct in_addr& addr, in_port_t port) {
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);
	m_addr.sin_addr = addr;
}

IPv4Address::IPv4Address(const std::string ip, in_port_t port) {
	memset(&m_addr, 0, sizeof(m_addr));
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &m_addr.sin_addr.s_addr);
}

IPv4Address::IPv4Address(struct sockaddr *sa) {
	if(!setAddressBySockAddr(sa)) {
		PPY_EXCEPT(ppy::Exception::INVARG,
			   "failed to initialize the IPv4Address Object",
			   __FUNCTION__);
	}
}

bool IPv4Address::setAddressBySockAddr(struct sockaddr *sa) {
	PPY_ASSERT(sa != 0);

	sa_family_t saf = *((sa_family_t*)sa);
	if(saf != AF_INET)
		return false;
	memcpy(&m_addr, sa, sizeof(m_addr));

	return true;
}

int IPv4Address::getFamily() {
	return m_addr.sin_family;
}

int IPv4Address::getPort() {
	return m_addr.sin_port;
}


IPv4Address::operator struct sockaddr *() {
	return (struct sockaddr *)&m_addr;
}

IPv4Address::operator socklen_t () {
	return sizeof(m_addr);
}



/*
 *--------------------------------------------------------------------------
 *   File Name:	TcpSocketServer.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Mar 30 20:50:16 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include <iostream>
#include <ppy.h>

using namespace std;
using namespace ppy;
using namespace ppy::net;

int main() {

	try {

		TcpSocket server;
		IPv4Address ad;

		server.Create(INET4_TCP);

		server.Bind(ad);

		server.Listen();

	} catch (const GenericException& e) {
		cout<<e.getDetail()<<endl;
	}

	return 0;
}


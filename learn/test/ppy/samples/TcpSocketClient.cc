/*
 *--------------------------------------------------------------------------
 *   File Name:	TcpSocketClient.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Mar 31 10:32:11 2011
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

		TcpSocket client;
		IPv4Address svad("192.168.101.216", 80);

		client.Create(INET4_TCP);
		client.Connect(svad, 10);


	} catch (const GenericException& e) {
		cout<<e.getDetail()<<endl;
	}

	return 0;
}


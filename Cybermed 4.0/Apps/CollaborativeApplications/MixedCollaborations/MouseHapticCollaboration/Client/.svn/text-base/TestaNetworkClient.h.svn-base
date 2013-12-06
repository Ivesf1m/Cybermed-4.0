/*
 * TestaNetworkClient.h
 *
 *  Created on: Dec 15, 2009
 *      Author: bruno
 */

#ifndef TESTANETWORKCLIENT_H_
#define TESTANETWORKCLIENT_H_

#include <cybermed/cybDatagramSock.h>
#include <cybermed/cybUDPServer.h>
#include <cybermed/cybNodeAddress.h>
#include <cybermed/cybThread.h>


class TestaNetworkClient : public CybThread{
public:
	CybNodeAddress* address;
	CybUDPServer* server;

	TestaNetworkClient();

	virtual void run();

	virtual ~TestaNetworkClient();
};

#endif /* TESTANETWORKCLIENT_H_ */

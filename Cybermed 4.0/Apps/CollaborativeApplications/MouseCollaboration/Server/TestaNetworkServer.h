/*
 * TestaNetworkServer.h
 *
 *  Created on: Dec 16, 2009
 *      Author: bruno
 */

#ifndef TESTANETWORKSERVER_H_
#define TESTANETWORKSERVER_H_

#include <cybermed/cybUDPServer.h>
#include <cybermed/cybReceiverThread.h>
#include "cybermed/cybThread.h"

class TestaNetworkServer : public CybThread {

private:
	CybUDPServer* server;
	CybReceiverThread* receiver;

public:
	TestaNetworkServer();

	virtual void run();

	virtual ~TestaNetworkServer();
};

#endif /* TESTANETWORKSERVER_H_ */

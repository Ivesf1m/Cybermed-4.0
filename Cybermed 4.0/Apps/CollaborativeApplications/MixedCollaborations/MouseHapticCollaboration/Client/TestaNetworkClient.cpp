/*
 * TestaNetworkClient.cpp
 *
 *  Created on: Dec 15, 2009
 *      Author: bruno
 */

#include "TestaNetworkClient.h"

TestaNetworkClient::TestaNetworkClient() {
	server = new CybUDPServer(5000);
	address = new CybNodeAddress(5001, "localhost", AF_INET);
	this->init();
}

void TestaNetworkClient::run() {

	/*
	float rotation[3];
	float teste0 = rotation[0];
	float teste1 = rotation[1];
	float teste2 = rotation[2];


	rotation[0] = visual->getRotation()[0];
	rotation[1] = visual->getRotation()[1];
	rotation[2] = visual->getRotation()[2];
	*/

	char buffer[1];
	buffer[0] = 0;

	try {
		server->sendData(buffer, 1, address);
	} catch (CybCommunicationException ex) {

	}
}


TestaNetworkClient::~TestaNetworkClient() {
	this->stop();
	delete server;
}

int main () {
	TestaNetworkClient* testClient = new TestaNetworkClient();
	while(1) sleep(1);
}

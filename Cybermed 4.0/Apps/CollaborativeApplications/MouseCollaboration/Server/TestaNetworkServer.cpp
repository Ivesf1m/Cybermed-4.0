/*
 * TestaNetworkServer.cpp
 *
 *  Created on: Dec 16, 2009
 *      Author: bruno
 */

#include "TestaNetworkServer.h"

TestaNetworkServer::TestaNetworkServer() {
	server = new CybUDPServer(5001);
	receiver = new CybReceiverThread(server);

	receiver->setBufferSize(1);

	cout << "starting Receiver..." << endl;
	receiver->init();
	//receiver->start();
	cout << "Receiver started..." << endl;
	//this->init();
}

void TestaNetworkServer::run() {
	/*
	float rotation[3];
	float teste0 = 0;
	float teste1 = 0;
	float teste2 = 0;

	*/

	int result = 0;
	char buffer[1];

	try {
		result = server->receiveData(buffer, 1);
		cout << "result " << result << endl;
	} catch (CybCommunicationException e) {

	}

	cout << buffer[0] << endl;

	/*
	for (int i=0; i<3; i++)
			cout << rotation[i] << " ";

	cout << '\n' ;
	 */

}

TestaNetworkServer::~TestaNetworkServer() {
	this->stop();
	delete server;
}

int main() {
	TestaNetworkServer* testServer = new TestaNetworkServer();
	while(1) sleep(1);
}

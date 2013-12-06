/*
 * CybDefaultSenderThread.cpp
 *
 *  Created on: Jan 26, 2010
 *      Author: brunorasales
 */

#include "CybDefaultSenderThread.h"

CybDefaultSenderThread::CybDefaultSenderThread(CybNode* node, CybCollaborationIntegrant** integrants, int numberOfIntegrants): CybSenderThread(node) {
	this->integrants = integrants;
	this->numberOfIntegrants = numberOfIntegrants;
}

void CybDefaultSenderThread::run() {
	CybThread::lock();

	try
	{
		for (int i = 0; i < numberOfIntegrants; i++) {
			CybUDPServer* serverNode = (CybUDPServer*) node;
			CybParameters::getInstance()->lay
			serverNode->sendData( , , integrants[i]->getAddress();)
		}
	}

	catch(CybCommunicationException e)
	{
		e.showErrorMessage();
	}

	CybThread::unlock();
	CybThread::setIsHablitated(false);
}

CybDefaultSenderThread::~CybDefaultSenderThread() {
	// TODO Auto-generated destructor stub
}

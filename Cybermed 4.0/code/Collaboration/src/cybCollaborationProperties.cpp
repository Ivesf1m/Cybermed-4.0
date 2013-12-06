// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.
// *****************************************************************

#include "cybCollaborationProperties.h"

#define OBJECT_REQUEST_MANAGER 9
#define OBJECT_LEAVE_MANAGER 10
#define COLLAB_PROP_DATA 11


CybCollaborationProperties::CybCollaborationProperties(int objectManagerType, CybNode *node) {
	this->node = node;
	this->objectManagerType = objectManagerType;
	this->cybCore = CybParameters::getInstance();
	this->leader = false;

	switch (this->objectManagerType) {
		case FREE_OBJECT_MANAGER:
			this->objectFree = true;
			this->cybCore->setSceneEditable(true);
		break;

		case BLOCK_OBJECT_MANAGER:
			this->objectFree = false;
			this->cybCore->setSceneEditable(false);
		break;
	}
}

void CybCollaborationProperties::eventPerformed(char* buffer, CybNodeAddress address) {

	char type = buffer[0];

	int typeInt = type;

	switch(type) {
		case OBJECT_REQUEST_MANAGER:
			setObjectFree(false);
		break;

		case OBJECT_LEAVE_MANAGER:
			this->objectFree = true;
		break;

		case COLLAB_PROP_DATA:
		{
			//cout << "receiving collab prop data" << endl;
			int pos = 1;
			int managerType;
			memcpy(&managerType, buffer + pos, sizeof(int));
			this->objectManagerType = managerType;

			if (this->objectManagerType == FREE_OBJECT_MANAGER) {
				setObjectFree(true);
			} else {
				setObjectFree(false);
			}
		}
		break;

		default:
			if (type > 20) {
				networkEvent(type - 20, buffer+1, address);
			}
		break;
	}
}

void CybCollaborationProperties::networkEvent(char type, char* data, CybNodeAddress address) {

}

bool CybCollaborationProperties::requestObjectManager() {
	if (isObjectFree()) {
		serverRequestObjectManager();
		setObjectFree(true);
		return true;
	} else {
		return false;
	}
}

bool CybCollaborationProperties::serverRequestObjectManager() {
	char buffer[1];
	tIntegrantsList::iterator it;

	memset(buffer, 0, 1);

	buffer[0] = OBJECT_REQUEST_MANAGER;

	CybUDPServer *serverNode = (CybUDPServer*)node;
	
	for (it = integrants->begin(); it != integrants->end(); ++it) {
		CybNodeAddress* addr = (*it)->getAddress();
		try {
			serverNode->sendData(buffer, 1, addr);
		} catch (CybCommunicationException e) {
			e.showErrorMessage();
		}		
	}

}

void CybCollaborationProperties::serverLeaveObjectManager() {
	char buffer[1];
	tIntegrantsList::iterator it;

	memset(buffer, 0, 1);

	buffer[0] = OBJECT_LEAVE_MANAGER;

	CybUDPServer *serverNode = (CybUDPServer*)node;

	for (it = integrants->begin(); it != integrants->end(); ++it) {
		CybNodeAddress* addr = (*it)->getAddress();
		try {
		      serverNode->sendData(buffer, 1, addr);
		} catch (CybCommunicationException e) {
			e.showErrorMessage();
		}		
	}
}

void CybCollaborationProperties::sendCollaborationProperties(CybNodeAddress* address) {
	char buffer[100];
	int pos = 0;
	memset(buffer, 0, 100);

	buffer[pos++] = COLLAB_PROP_DATA;

	memcpy(buffer + pos, &objectManagerType, sizeof(int));
	pos += sizeof(int);

	// PQ é uma mensagem do server p/ o novato
	CybUDPServer *serverNode = (CybUDPServer*)node;
	serverNode->sendData(buffer, pos, address);
}

bool CybCollaborationProperties::isObjectFree() {
	return this->objectFree;
}

bool CybCollaborationProperties::isLeader() {
	return this->leader;
}

void CybCollaborationProperties::setLeader(bool leader) {
	this->leader = leader;
}

void CybCollaborationProperties::setObjectFree(bool free) {
	this->objectFree = free;
	cybCore->setSceneEditable(free);
}

void CybCollaborationProperties::setIntegrants(tIntegrantsList* integrants) {
	this->integrants = integrants;
}

// --------- novos 

int CybCollaborationProperties::getCommunicationType() {
	return this->communicationType;
}
	
void CybCollaborationProperties::setCommunicationType(int type) {
	this->communicationType = type;
}

void CybCollaborationProperties::send(int type, void* data, int dataSize) {
	char buffer[100];
	int pos = 0;
	tIntegrantsList::iterator it;

	memset(buffer, 0, 100);

	int typeFake = type + 20;

	buffer[pos++] = typeFake;
	pos += dataSize;

	CybUDPServer *serverNode = (CybUDPServer*)node;

	for (it = integrants->begin(); it != integrants->end(); ++it) {
		CybNodeAddress* addr = (*it)->getAddress();
		try {
			serverNode->sendData(buffer, pos, addr);
		} catch (CybCommunicationException e) {
			e.showErrorMessage();
		}	
	}
}

CybCollaborationProperties::~CybCollaborationProperties() {
	// TODO Auto-generated destructor stub
}

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

#include "cybHapticCollaboration.h"

//#ifdef CYBHAPTICS_H

CybHapticCollaboration::CybHapticCollaboration() {
}

CybHapticCollaboration::CybHapticCollaboration(int port, int communicationType, const char *multicastGroupIP) : CybCollaboration(port, communicationType, multicastGroupIP) {
//cout << "" << endl;
}

/** Constructor
 *
 */
CybHapticCollaboration::CybHapticCollaboration(int port, int objectManagerType, int communicationType, const char *multicastGroupIP) : CybCollaboration(port, objectManagerType, communicationType, multicastGroupIP) {

}

CybHapticCollaboration::CybHapticCollaboration(CybOpenHPhantom* phantom, int port, int communicationType, const char *multicastGroupIP) {
	if (phantom != NULL) {
		if (phantom->deviceIsEnable()) {
			this->node = CybNodeFactory::getNode(port, communicationType, multicastGroupIP);
			
			if (communicationType == MULTICAST) {
				CybMulticastPeer *serverNode = (CybMulticastPeer*) this->node;
				serverNode->setLoopbackOption(0);
			}
			this->properties->setCommunicationType(communicationType);
			this->receiver = new CybReceiverThread(node);
		}
	}
}

CybHapticCollaboration::CybHapticCollaboration(int port, CybCollaborationProperties* properties, int communicationType, const char *multicastGroupIP) : CybCollaboration(port, properties, communicationType, multicastGroupIP) {

}

CybInterator* CybHapticCollaboration::getMainInterator() {
	CybInterator* interator = CybHapticInterator::getInterator();
	interator->create(cybCore->getNumInterators() - 1);
	return interator;
}

void CybHapticCollaboration::interatorPositionEventPerformed(float x, float y, float z) {

	char buffer[250];
	char bufferPosition[50];

	memset(buffer, 0, 250);

	HLdouble* matrix = ((CybHapticInterator*) mainInterator)->getHapticMatrix();

	int pos = 0;

	buffer[pos++] = INTERATOR_POSITION_CHANGE;

	memcpy(buffer + pos, matrix, sizeof(HLdouble)*16);
	pos += sizeof(HLdouble)*16;

	sendDataToAll(buffer, pos, this->properties->getCommunicationType());
	//cout << performance->getNumPktsSent() << endl;
	//cout << "Bytes Size in haptic pkt: " << pos << endl;
}

/*
void CybHapticCollaboration::processInteratorPositionChangeMsg(char* buffer, string ipStr, short int port) {

	float x, y, z;
	int ipLen = ipStr.length();

	int pos = 1;
	HLdouble* hapticMatrix = new HLdouble[16];

	memcpy(hapticMatrix, buffer + pos, sizeof(HLdouble)*16);
	pos += sizeof(HLdouble)*16;

	for (it = integrants.begin(); it != integrants.end(); ++it) {
		CybNodeAddress *addr = (*it)->getAddress();
		int n = memcmp(addr->getIP(), ipStr.c_str(), ipLen);

		if (n == 0) {
			CybRemoteInterator* interator = (*it)->getInterator();

			if (interator->getInteratorType() == REMOTE_HAPTIC_INTERATOR) {
				//cout << "setHapticMatrix" << endl;
				CybRemoteHapticInterator * rHapticInterator = (CybRemoteHapticInterator*) interator;
				rHapticInterator->setHapticMatrix(hapticMatrix);
			}
		}
	}
	performance->countTrafficReceived(INTERATOR_POSITION_CHANGE, pos + sizeof(int));
}*/

void CybHapticCollaboration::interatorRotationEventPerformed(float x, float y, float z) {

}

void CybHapticCollaboration::processInteratorRotationChangeMsg(char* buffer, string ipStr, short int port) {

}

CybHapticCollaboration::~CybHapticCollaboration() {
	phantom->stopDevice();
}
//#endif

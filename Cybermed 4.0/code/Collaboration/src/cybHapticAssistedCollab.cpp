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

#include "cybHapticAssistedCollab.h"
//#ifdef CYBHAPTICS_H
CybHapticAssistedCollab::CybHapticAssistedCollab(int port, int communicationType, const char *multicastGroupIP) : CybHapticCollaboration(port, communicationType, multicastGroupIP) {

}

/** Constructor
 *
 */
CybHapticAssistedCollab::CybHapticAssistedCollab(int port, int objectManagerType, int communicationType, const char *multicastGroupIP) : CybHapticCollaboration(port, objectManagerType, communicationType, multicastGroupIP){

}

CybHapticAssistedCollab::CybHapticAssistedCollab(int port, CybCollaborationProperties* properties, int communicationType, const char *multicastGroupIP) : CybHapticCollaboration(port, properties, communicationType, multicastGroupIP) {

}

bool CybHapticAssistedCollab::createCollaboration(int idInteratorModel) {

	CybCollaboration::createCollaboration(idInteratorModel);
	phantom = (CybOpenHPhantom*) mainInterator->getDevice();

	phantom->setAnchorPosition(0, 0, 0);

	properties->setLeader(true);

}

bool CybHapticAssistedCollab::joinCollab(string name, int idInteratorModel, string serverIp, short int serverPort) {
	CybCollaboration::joinCollab(name, idInteratorModel, serverIp, serverPort);

	phantom = (CybOpenHPhantom*) mainInterator->getDevice();
	phantom->setAnchorPosition(0, 0, 0);
	phantom->setGuided(true);
}

void CybHapticAssistedCollab::processInteratorPositionChangeMsg(char* buffer, string ipStr, short int port) {
	//CybHapticCollaboration::processInteratorPositionChangeMsg(buffer, ipStr, port);
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
	//performance->countTrafficReceived(INTERATOR_POSITION_CHANGE, pos + sizeof(int));

	//if (!ipStr.compare("150.165.134.117"))
	if (!properties->isLeader())
		phantom->setAnchorPosition(hapticMatrix[12], hapticMatrix[13], hapticMatrix[14]);
}

CybHapticAssistedCollab::~CybHapticAssistedCollab() {
	// TODO Auto-generated destructor stub
}
//#endif

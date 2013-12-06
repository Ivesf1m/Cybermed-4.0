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

#ifndef CYBCOLLABORATIONPROPERTIES_H_
#define CYBCOLLABORATIONPROPERTIES_H_

//#include <cybermed/cybUDPServer.h>
#include "cybNodeFactory.h"
#include <cybermed/cybMulticastPeer.h>
#include <cybermed/cybReceiverThreadListener.h>
#include <cybermed/cybParameters.h>
#include "cybCollaborationIntegrant.h"

typedef list<CybCollaborationIntegrant*> tIntegrantsList;

#define FREE_OBJECT_MANAGER 0
#define BLOCK_OBJECT_MANAGER 1

/**
@class		CybCollaborationProperties
@file		cybCollaborationProperties.h
@short
Collaboration Properties class.

Stores the properties of the collaboration.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2010, May
*/
class CybCollaborationProperties : public CybReceiverThreadListener {
public:
	CybCollaborationProperties(int objectManagerType, CybNode *node);

	bool requestObjectManager();

	void leaveObjectManager();

	bool isObjectFree();

	bool isLeader();

	bool serverRequestObjectManager();

	void serverLeaveObjectManager();

	virtual void eventPerformed(char* buffer, CybNodeAddress address);

	virtual void networkEvent(char type, char* data, CybNodeAddress address);

	virtual void sendCollaborationProperties(CybNodeAddress* address);

	void setLeader(bool leader);

	void setObjectFree(bool free);

	void setIntegrants(tIntegrantsList* integrants);

	// ------ novos
	//void setNode(CybNode* node);

	int getCommunicationType();
	
	void setCommunicationType(int type);

	// --------

	void send(int type, void* data, int dataSize);

	virtual ~CybCollaborationProperties();


protected:
	tIntegrantsList* integrants;
	//CybUDPServer* serverNode;
	//CybMulticastPeer* serverNode;
	CybNode *node;
	CybParameters* cybCore;
	bool objectFree;
	int objectManagerType;
	bool leader;
	char* interatorModel;
	int communicationType;
private:

};

#endif /* CYBCOLLABORATIONPROPERTIES_H_ */

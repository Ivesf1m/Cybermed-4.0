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

#ifndef CYB_GLOVECOLLABORATION_H_
#define CYB_GLOVECOLLABORATION_H_

#include "cybCollaboration.h"


//#ifdef CYBGLOVE_H 
#include <cybermed/cybGlove.h>
#include <cybermed/cybGloveInterator.h>
#include <cybermed/cyb5DTGlove.h>
#include "cybModelCollaboration.h"
#include "cybRemoteGloveInterator.h"

/**
@class		CybHapticCollaboration
@file		cybHapticCollaboration.h
@short
Haptic Collaboration class.

Provides operations that can be used by every collaboration types

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2010, May
*/
class CybGloveCollaboration : public CybCollaboration {

private:
	//CybUDPServer* serverNode;
	string port;	

protected:
	CybGlove* glove;
	void sendData();
	tIntegrantsList getIntegrants();

public:
	CybGloveCollaboration(int port = PORT_DEFAULT, int communicationType = MULTICAST, const char *multicastGroupIP = "244.0.0.1");

	virtual CybInterator* getMainInterator();

	virtual void interatorPositionEventPerformed(float x, float y, float z);

	virtual void processInteratorRotationChangeMsg(char* buffer, string ipStr, short int port);

	virtual void interatorRotationEventPerformed(float x, float y, float z);	
	
	void setPortName(string portName);		

	virtual ~CybGloveCollaboration();

};
//#endif
#endif /* CYB_GLOVECOLLABORATION_H_ */

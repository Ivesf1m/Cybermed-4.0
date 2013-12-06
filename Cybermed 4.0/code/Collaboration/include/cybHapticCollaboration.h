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

#ifndef CYB_HAPTICCOLLABORATION_H_
#define CYB_HAPTICCOLLABORATION_H_

#include "cybCollaboration.h"

//#ifdef CYBHAPTICS_H
#include <cybermed/cybOpenHPhantom.h>
#include <cybermed/cybHapticInterator.h>
#include "cybRemoteHapticInterator.h"

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
class CybHapticCollaboration : public CybCollaboration {

private: CybNode* node;

protected:
	CybOpenHPhantom* phantom;
	void sendData();
	tIntegrantsList getIntegrants();

public:
	CybHapticCollaboration();
	
	CybHapticCollaboration(int port, int communicationType, const char *multicastGroupIP = "224.0.0.1");

	CybHapticCollaboration(CybOpenHPhantom* phantom, int port, int communicationType, const char *multicastGroupIP = "224.0.0.1");

	/** Constructor
	 *
	 */
	CybHapticCollaboration(int port, int objectManagerType, int communicationType, const char *multicastGroupIP = "224.0.0.1");

	CybHapticCollaboration(int port, CybCollaborationProperties* properties, int communicationType, const char *multicastGroupIP = "224.0.0.1");

	virtual CybInterator* getMainInterator();

	//virtual CybRemoteInterator* getRemoteInterator();

	virtual void interatorPositionEventPerformed(float x, float y, float z);

	//virtual  void processInteratorPositionChangeMsg(char* buffer, string ipStr, short int port);
	virtual void processInteratorRotationChangeMsg(char* buffer, string ipStr, short int port);

	virtual void interatorRotationEventPerformed(float x, float y, float z);

	virtual ~CybHapticCollaboration();

};
//#endif
#endif /* CYB_HAPTICCOLLABORATION_H_ */

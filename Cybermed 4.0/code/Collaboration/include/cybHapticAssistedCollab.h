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

#ifndef CYBHAPTICASSISTEDCOLLAB_H_
#define CYBHAPTICASSISTEDCOLLAB_H_

#include "cybHapticCollaboration.h"

//#ifdef CYBHAPTICS_H

#include <cybermed/cybHapticInterator.h>

/**
@class		CybHapticAssistedCollab
@file		cybHapticAssistedCollab.h
@short
Haptic Assisted Collaboration class.

Used to create a collaboration through haptic device with a tutor in the environment.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2010, May
*/
class CybHapticAssistedCollab: public CybHapticCollaboration {
public:
	CybHapticAssistedCollab(int port, int communicationType, const char *multicastGroupIP = "224.0.0.1");

	/** Constructor
	 *
	 */
	CybHapticAssistedCollab(int port, int objectManagerType, int communicationType, const char *multicastGroupIP = "224.0.0.1");

	/** Constructor
	 *
	 */
	CybHapticAssistedCollab(int port, CybCollaborationProperties* properties, int communicationType, const char *multicastGroupIP = "224.0.0.1");

	bool createCollaboration(int idInteratorModel);
	bool joinCollab(string name, int idInteratorModel, string serverIp, short int serverPort);
	virtual void processInteratorPositionChangeMsg(char* buffer, string ipStr, short int port);
	virtual ~CybHapticAssistedCollab();
};
//#endif

#endif /* CYBHAPTICASSISTEDCOLLAB_H_ */

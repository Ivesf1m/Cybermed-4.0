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

#ifndef COLLABORATIONINTEGRANT_H_
#define COLLABORATIONINTEGRANT_H_

#include "cybCollaborationIntegrant.h"
#include "cybRemoteInterator.h"
#include <cybermed/cybNodeAddress.h>

/**
@class		CybCollaborationIntegrant
@file		cybCollaborationIntegrant.h
@short
Collaboration integrant class.

Represents an integrant of the collaboration. It stores informations of the integrant to be used by the collaboration.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2010, May
*/

typedef enum tInteratorModel {
	MONKEY = 0,
	SPHERE = 1,
	NEDDLE = 2,
}tInteratorModel;

class CybCollaborationIntegrant {

private:
	string name;

	CybNodeAddress* address;

	CybRemoteInterator* interator;	
	
	char* interatorModel;
	
	int idInteratorModel;
	
public:

	/** Default Constructor */
	CybCollaborationIntegrant();

	/** Constructor
	 * @param char* name
	 * @param char* ipAddress ip address
	 * @param int port port number
	 */
	CybCollaborationIntegrant(string name, string ipAddress, const short port);

	/** Constructor
	 * @param CybNodeAddress* address
	 */
	CybCollaborationIntegrant(CybNodeAddress* address);

	/** Constructor
	 * @param char* name.
	 * @param CybNodeAddress* address.
	 */
	CybCollaborationIntegrant(string name, CybNodeAddress* address);

	/** Constructor
	 *
	 */
	CybCollaborationIntegrant(string ipAddress, const short port);

	/**
	 * Gets the name of the integrant.
	 * @return char* A pointer to the name of the integrant.
	 */
	string getName();

	/**
	 * Gets the address of the integrant.
	 * @return CybNodeAddress* A reference to the integrant's address.
	 */
	CybNodeAddress* getAddress();

	/**
	 *
	 */
	CybRemoteInterator* getInterator();
	
	char* getInteratorModel();
	
	int getIdInteratorModel();
	
	void setInteratorModel(int idInteratorModel);

	/**
	 * Sets the name of the integrant.
	 * @param char* name.
	 */
	void setName(string name);

	/**
	 * Sets the address of the integrant.
	 * @param CybNodeAddress* address.
	 */
	void setAddress(CybNodeAddress* address);

	/**
	 *
	 */
	void setInterator(CybRemoteInterator* interator);

	/** Destructor */
	virtual ~CybCollaborationIntegrant();
};

#endif /* COLLABORATIONINTEGRANT_H_ */

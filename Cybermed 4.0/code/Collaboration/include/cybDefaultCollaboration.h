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

#ifndef CYBDEFAULTCOLLABORATION_H_
#define CYBDEFAULTCOLLABORATION_H_

#include <cybermed/cybMouseInterator.h>
#include <cybermed/cybInteratorListener.h>
#include <cybermed/cybMouseListener.h>
#include <cybermed/cybReceiverThreadListener.h>

#include "cybCollaboration.h"


/**
@class		CybDefaultCollaboration
@file		cybDefaultCollaboration.h
@short
Mouse Collaboration class.

This class is used to make a collaboration through mouse device.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2010, May
*/
class CybDefaultCollaboration : public CybCollaboration {
public:
	CybDefaultCollaboration();

	/** Constructor
	 *
	 */
	CybDefaultCollaboration(int port, int communicationType = MULTICAST, const char *multicastGroupIP = "244.0.0.1");

	/** Constructor
	 *
	 */
	CybDefaultCollaboration(int port, int objectManagerType, int communicationType, const char *multicastGroupIP = "244.0.0.1");

	/** Constructor
	 *
	 */
	CybDefaultCollaboration(int port, CybCollaborationProperties* properties, int communicationType, const char *multicastGroupIP = "244.0.0.1");

	virtual CybInterator* getMainInterator();

	virtual ~CybDefaultCollaboration();

private:

};

#endif /* CYBDEFAULTCOLLABORATION_H_ */

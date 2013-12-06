// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#ifndef _CYBCOLLABORATIONPERFORMANCE_H
#define	_CYBCOLLABORATIONPERFORMANCE_H

#include <iostream>
#include <cstdio>

using namespace std;

class CybCollaborationPerformance {

private: int numBytesSent;
	 int numBytesReceived;

	 int numPktsReceived;
	 int numPktsSent;

	 int layerRotationPktS;
	 int layerRotationPktR;

	 int layerPositionPktS;
	 int layerPositionPktR;

	 int interatorPositionPktS;
	 int interatorPositionPktR;

	 int interatorRotationPktS;
	 int interatorRotationPktR;

	 int layerColorPktS;
	 int layerColorPktR;

public: CybCollaborationPerformance();

	// Access Methods
	
	int getNumBytesSent(void); 
        int getNumBytesReceived(void);

	int getNumPktsReceived(void);
	int getNumPktsSent(void);

	int getLayerRotationPktS(void);
	int getLayerRotationPktR(void);

	int getInteratorPositionPktS(void);
	int getInteratorPositionPktR(void);

	int getInteratorRotationPktS(void);
	int getIteratorRotationPktR(void);

	int getLayerColorPktS(void);
	int getLayerColorPktR(void);

	// Modifiers Methods

	void setNumBytesSent(int bytes); 
        void setNumBytesReceived(int bytes);

	void setNumPktsReceived();
	void setNumPktsSent();

	void setLayerPositionPktS();
	void setLayerPositionPktR();

	void setLayerRotationPktS();
	void setLayerRotationPktR();

	void setInteratorPositionPktS();
	void setInteratorPositionPktR();

	void setInteratorRotationPktS();
	void setInteratorRotationPktR();

	void setLayerColorPktS();
	void setLayerColorPktR();

	void countTrafficSent(char pktType, int bytes);
	
	void countTrafficReceived(char pktType, int bytes);

	void reportPerformance();

};
#endif

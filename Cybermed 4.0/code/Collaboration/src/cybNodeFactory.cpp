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

#include "cybNodeFactory.h"

CybNode* CybNodeFactory::getNode(int nodeType, int port, const char* IP) {

	CybNode* node = NULL;

	switch (nodeType) {
		case UNICAST_UDP: 
				 node = new CybUDPServer(port);
				 cout << "returning UDP!" << endl;
		break;

		case UNICAST_TCP: 
				 // node = new CybTCPServer(port);
				 cout << "returning TCP!" << endl;
		break;

		case MULTICAST:  node = new CybMulticastPeer(port, IP);
				 CybMulticastPeer *serverNode = (CybMulticastPeer *) node; 	
				 cout << "returning UDP!" << endl;
		break;	
	}
return node;
}

CybNodeFactory::~CybNodeFactory() {
	// TODO Auto-generated destructor stub
}

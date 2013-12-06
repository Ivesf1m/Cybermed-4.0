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
// ***********************************

#include "cybMulticastException.h"

CybMulticastException::CybMulticastException(int type)
{
	this->type = type;
}
        
CybMulticastException::~CybMulticastException(){
}

void CybMulticastException::showErrorMessage(){
	switch( type ){
		case 1: cout << "<ERROR: The multicast data couldn't be received.>" << endl;
		//exit(1);
		break;

		case 2: cout << "<ERROR: The multicast data couldn't be sent.>" << endl;
		//exit(1);
		break;

		case 3: cout << "<ERROR: Problem in joinGroup() call.>" << endl;
			exit(1);
		break;

		case 4: cout << "<ERROR: It is not possible receive multicast datagram without join a multicast group.>" << endl;
			exit(1);
		break;
	}
}

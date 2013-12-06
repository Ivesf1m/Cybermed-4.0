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

#include "cybServerMulticast.h"

CybServerMulticast::CybServerMulticast(const short uniPort, const short multiPort, const char* group): CybUDPServer(uniPort)
{
	this->multiSock = new CybDatagramSock(); // multicast
	this->multiAddr = new CybNodeAddress(multiPort, group, AF_INET);
}

void CybServerMulticast::sendMulticastData(void* data, int size) throw (CybMulticastException)
{
    int result = 0;
    result = sendto(this->multiSock->getSock(), data, size, 0, (struct sockaddr *)multiAddr->getAddr(), multiAddr->getAddrSizeValue());
    if(result < 0) throw CybMulticastException(2);
}


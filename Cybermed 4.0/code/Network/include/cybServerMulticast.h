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

/**
 * A classe CybServerMulticast implementa um servidor multicast para arquitetura cliente/servidor. Logo, o servidor
 * envia dados multicast, mas recebe dados de cada cliente individualmente. Se for desejado criar uma aplicação em
 * rede com multicast baseada na arquitetura peer-to-peer, então não se faz necessário implementar um servidor, todos
 * os nós podem ser implementados usando a classe CybClientMulticast.
 *
 **/

#ifndef _CYBSERVERMULTICAST_H
#define	_CYBSERVERMULTICAST_H
#include "cybUDPServer.h"
#include "cybMulticastException.h"

class CybServerMulticast: public CybUDPServer
{
private:
    CybDatagramSock* multiSock;
    CybNodeAddress* multiAddr;
    
public:
    /** Constructor
     *  @param const short
     *  @param const short
     *  @param const char*
     */
    CybServerMulticast(const short uniPort, const short multiPort, const char* group);
    
    /**
     *
     * @param void*
     * @param int
     */
    void sendMulticastData(void* data, int size) throw (CybMulticastException);
    //virtual void startServer(void) = 0;
    
};
#endif	/* _CYBSERVERMULTICAST_H */




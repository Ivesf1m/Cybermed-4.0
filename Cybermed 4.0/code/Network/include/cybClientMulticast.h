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
 * A classe CybClientMulticast implementa um cliente multicast. Se for desejado construir uma aplicação em rede
 * usando a arquitetura cliente/servidor, o cliente recebe dados multicast e envia dados para o servidor por unicast.
 * Se for utilizar a arquitetura peer-to-peer, então não há necessidade de um servidor, basta implementar os nós como
 * clientes multicast, podendo ser utilizado o método para envio de dados multicast.
 *
 **/

#ifndef _CYBCLIENTMULTICAST_H
#define	_CYBCLIENTMULTICAST_H
#include "cybUDPClient.h"
#include "cybMulticastException.h"

class CybClientMulticast: public CybUDPClient
{
private:
    struct ip_mreq mreq;
    CybDatagramSock* multiSock;
    CybNodeAddress* multiAddr;
    CybNodeAddress* bufferAddr;
    bool participateMultiGroup;

public:

    /** Constructor
     *  @param const short
     *  @param const short
     *  @param const char*
     *  @param const short
     *  @param const char*
     */
    CybClientMulticast(const short client_port, const short server_port, const char* server_ip, const short multiPort, const char* group);
    
    /** Constructor
     *  @param const short
     *  @param const char*
     *  @param const short
     *  @param const char*
     */
    CybClientMulticast(const short server_port, const char* server_ip, const short multiPort, const char* group);

    /**
     *
     */
    void joinGroup(void) throw (CybMulticastException);

    /**
     *
     *
     */
    void leavGroup(void);

    /**
     *
     * @param void*
     * @param int
     */
    void receiveMulticastData(void* data, int size) throw (CybMulticastException);

    /**
     *
     * @param void*
     * @param int
     */
    void sendMulticastData(void* data, int size) throw (CybMulticastException);
};
#endif	/* _CYBCLIENTMULTICAST_H */

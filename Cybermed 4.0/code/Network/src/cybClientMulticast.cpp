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

#include "cybClientMulticast.h"

CybClientMulticast::CybClientMulticast(const short client_port, const short server_port, const char* server_ip, const short multiPort, const char* group):
        CybUDPClient(client_port, server_port, server_ip)
    {
        /* multicast */
        mreq.imr_multiaddr.s_addr = inet_addr(group); /* endereço IP de grupo de multicast */
        mreq.imr_interface.s_addr = htonl(INADDR_ANY); /* endereço IP da interface local */
        this->multiSock = new CybDatagramSock();
        this->multiAddr = new CybNodeAddress(multiPort, group, AF_INET);
        this->bufferAddr = new CybNodeAddress();
        this->multiSock->connectToPort(this->multiSock->getSock(), this->multiAddr);
        participateMultiGroup = false;
    }
    
CybClientMulticast::CybClientMulticast(const short server_port, const char* server_ip, const short multiPort, const char* group):
        CybUDPClient(server_port, server_ip)
    {   
        /* multicast */        
        mreq.imr_multiaddr.s_addr = inet_addr(group); /* endereço IP de grupo de multicast */
        mreq.imr_interface.s_addr = htonl(INADDR_ANY); /* endereço IP da interface local */
        this->multiSock = new CybDatagramSock();
        this->multiAddr = new CybNodeAddress(multiPort, group, AF_INET);
        this->bufferAddr = new CybNodeAddress();        
        this->multiSock->connectToPort(this->multiSock->getSock(), this->multiAddr);
        participateMultiGroup = false;
    }

void CybClientMulticast::joinGroup() throw (CybMulticastException)
{
    int result;
    result = setsockopt(this->multiSock->getSock(), IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq));
    this->participateMultiGroup = true;
    if(result<0) throw CybMulticastException(3);
}

void CybClientMulticast::leavGroup()
{
    setsockopt(this->multiSock->getSock(), IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));
    this->participateMultiGroup = false;
}

void CybClientMulticast::receiveMulticastData(void* data, int size) throw (CybMulticastException)
{
    if(participateMultiGroup == false) throw CybMulticastException(4);
    int result = 0;
    result = recvfrom(this->multiSock->getSock(), data, size, 0, (struct sockaddr *)bufferAddr->getAddr(), bufferAddr->getAddrSize());
    if(result < 0) throw CybMulticastException(1);
}

/**
 * Método para caso queira se fazer uma aplicação em rede baseada na arquitetura peer-to-peer.
 * @param void*
 * @param int
 */
void CybClientMulticast::sendMulticastData(void* data, int size) throw (CybMulticastException)
{
    int result = 0;
    result = sendto(this->multiSock->getSock(), data, size, 0, (struct sockaddr *)multiAddr->getAddr(), multiAddr->getAddrSizeValue());
    if(result < 0) throw CybMulticastException(2);
}

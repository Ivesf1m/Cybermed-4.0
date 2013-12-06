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

/**
 * The cybMulticastPeer class was designed to support peer-to-peer multicast communication architecture.
 * For this purpose, the multicast peer have to join a Group and then send its multicast data.
 * Every CybMulticastPeer object has two addressess: multiAddr, which represents the group IP:port; 
 * and the udp address that binds the multicast port for receiveing data;
 *
 **/

#ifndef _CYBMULTICASTPEER_H
#define	_CYBMULTICASTPEER_H

#include "cybMulticastException.h"
#include "cybUDPServer.h"

#define MAX 10

class CybMulticastPeer : public CybUDPServer {

private:
    CybDatagramSock* multiSock;
    CybNodeAddress* multiAddr;
    CybNodeAddress* clientAddr[MAX];	
    struct ip_mreq multiReq;		
    
public:
    /** Constructor
     *  @param const short  
     *  @param const char*
     */
    CybMulticastPeer(const short multiPort, const char* group);
    
    /* Join into a multicast group
     * @param void
     */	
    void joinGroup(void) throw (CybMulticastException);

    /* Set the multicast loopback option in cases where the peer wants to receive the messages that himself send to the group
     * @param int
     */
    void setLoopbackOption(int flag);	


   /**
    * Set the Time To Live (TTL) multicast parameter
    * @param void*
    * @param int
    */	
    void setTTL(int ttl);
    
    /**
     * Sends multicast packets to a group
     * @param void*
     * @param int
     */
    void sendMulticastData(void* data, int size) throw (CybMulticastException);  
};
#endif	/* _CYBSERVERMULTICAST_H */

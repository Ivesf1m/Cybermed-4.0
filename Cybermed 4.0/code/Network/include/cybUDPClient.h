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
 * clientes UDP iterativos
 **/

#ifndef _CYBUDPCLIENT_H
#define	_CYBUDPCLIENT_H

#include "cybDatagramSock.h"
#include "cybCommunicationException.h"
#include "cybNode.h"

class CybUDPClient: public CybNode
{
protected:
    CybDatagramSock* dataSock;
    CybNodeAddress* serverAddr;
    CybNodeAddress* clientAddr;
           
public:

    /** Constructor */
    CybUDPClient(void);
        
    /** Constructor
     * @dataSock
     * @serverAddr
     * @clientAddr
     */
    CybUDPClient(CybDatagramSock* dataSock, CybNodeAddress* serverAddr, CybNodeAddress* clientAddr);
        
    /** Constructor
     * @client_port is the sender port from the client
     * @server_port is the listener port from the server
     * @server_ip
     */
    CybUDPClient(const short client_port, const short server_port, const char* server_ip);
        
    /** Constructor
	 * @client_port is the sender port from the client
	 * @server_port is the listener port from the server
	 * @server_ip
	 * @family
	 */
    CybUDPClient(const short client_port, const short server_port, const char* server_ip, const short family);
    
    /** Constructor
	 * @server_port is the listener port from the server
	 * @server_ip
	 */
    CybUDPClient(const short server_port, const char* server_ip);

    /** Constructor
	 * @server_port is the listener port from the server
	 * @server_ip
	 * @family
	 */
    CybUDPClient(const short server_port, const char* server_ip, const short family);
   
    virtual ~CybUDPClient();
    
public: 
    int getSock(void);
    CybDatagramSock* getDatagramSock(void);
    char* getIP(void);
    short getPort(void);
    short getFamily(void); 
    CybNodeAddress* getNodeAddr(void);
    struct sockaddr_in* getAddr(void);
    CybNodeAddress* getServerAddr(void);          
    
    /** */
    void makeConnection(void) throw (CybCommunicationException);
    
    /** */
    void receiveData(void* data, int size) throw (CybCommunicationException);

    /** */
    void sendData(void* data, int size) throw (CybCommunicationException);
    
    /** */
    void sendData(int sock, void* data, int size) throw (CybCommunicationException);

    /** */
    void receiveData(int sock, void* data, int size) throw (CybCommunicationException);
    
};

#endif	/* _CYBUDPCLIENT_H */


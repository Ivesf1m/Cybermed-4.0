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
 * servidores TCP iterativos
 **/

#ifndef _CYBTCPSERVER_H
#define	_CYBTCPSERVER_H

#include "cybStreamSock.h"
#include "cybTCPException.h"
#include "cybCommunicationException.h"
#include "cybTCPClient.h"
#include "cybNode.h"

#define MAX 10

class CybTCPServer: public CybNode
{

protected:
    int nclients;
    CybStreamSock* streamSock;
    CybNodeAddress* serverAddr;
    CybTCPClient* clients[MAX];
    
public:
    /** Constructor */
    CybTCPServer(void);

    /** Constructor
     *@server_port server port number
     */
    CybTCPServer(const short server_port);

    /** Constructor
     * @server_port
     * @family
     */
    CybTCPServer(const short server_port, const short family);
	
    /** Destructor */
	~CybTCPServer();
    

	/**
	 *
	 */
    int getSock(void);

    /** */
    char* getIP(void);

    /** */
    short getPort(void);

    /** */
    short getFamily(void); 

    /** */
    CybNodeAddress* getNodeAddr(void);

    /** */
    struct sockaddr_in* getAddr(void);

    /** */
    CybTCPClient* getClient(int i);

    /** */
    int getClientsNumber(void);
   
    /** */
    void receiveData(int sock, void* data, int size) throw (CybCommunicationException);

    /** */
    void sendData(int sock, void* data, int size) throw (CybCommunicationException);
    
    /** */
    void acceptConnection(CybTCPClient* client) throw (CybTCPException);

    /** */
    virtual void startServer(void) throw (CybTCPException);

    /** */
    virtual void communicate(int i) = 0; // o cara é obrigado a dizer como se dará a comunicação. i é o índice do cliente
};
#endif	/* _CYBTCPSERVER_H */




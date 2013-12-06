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
 * servidores UDP iterativos
 **/

#ifndef _CYBUDPSERVER_H
#define	_CYBUDPSERVER_H
                              
#include "cybDatagramSock.h"
#include "cybCommunicationException.h"
#include "cybNode.h"
#define MAX 10

class CybUDPServer: public CybNode
{
protected:
    CybDatagramSock* dataSock;
    CybNodeAddress* serverAddr;
    CybNodeAddress* clientAddr[MAX];
    
 public:
     
    /** Constructor */
    CybUDPServer(void);
    
    /** Constructor
     * @server_port
     */
    CybUDPServer(const short server_port);
    
    /** Constructor
	 * @server_port
	 * @family
	 */
    CybUDPServer(const short server_port, const short family);
    
    /** Destructor */
    virtual ~CybUDPServer();

    /** */
    int getSock(void);

    /** */
    CybDatagramSock* getDatagramSock(void);

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
    CybNodeAddress* getClientAddr(int i);
    
    /** */
    void sendData(int sock, void* data, int size) throw (CybCommunicationException);

    /** */
    void receiveData(int sock, void* data, int size) throw (CybCommunicationException);
    
    /** */
    void sendData(void* data, int size) throw (CybCommunicationException);

    /** */
    int receiveData(void* data, int size) throw (CybCommunicationException);
    
    /** */
    void sendData(void* data, int size, CybNodeAddress* address) throw (CybCommunicationException); 

    /** */
    int receiveDataFrom(void* data, int size, CybNodeAddress* address) throw (CybCommunicationException);

    //virtual void startServer(void) = 0;
};

#endif	/* _CYBUDPSERVER_H */


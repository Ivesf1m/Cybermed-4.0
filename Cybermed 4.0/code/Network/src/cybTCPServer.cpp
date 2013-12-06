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

#include "cybTCPServer.h"

    CybTCPServer::CybTCPServer(void)
    {

    }

    CybTCPServer::CybTCPServer(const short server_port)
	{  
            this->streamSock = new CybStreamSock();
            this->serverAddr = new CybNodeAddress(server_port, NULL, AF_INET);
            this->streamSock->connectToPort(this->streamSock->getSock(), this->serverAddr);
            
            cout << "The server is on." << endl;
	}
        
    CybTCPServer::CybTCPServer(const short server_port, const short family)
	{  
            this->streamSock = new CybStreamSock();
            this->serverAddr = new CybNodeAddress(server_port, NULL, family);
            this->streamSock->connectToPort(this->streamSock->getSock(), this->serverAddr);
            
            cout << "The server is on." << endl;
	}
	
    CybTCPServer::~CybTCPServer()
    {
            close(this->streamSock->getSock());
            cout << "The server is off." << endl;
	}
    
	int CybTCPServer::getSock(void)
	{
		return this->streamSock->getSock();
	}

	char* CybTCPServer::getIP(void)
	{
		return this->serverAddr->getIP();
	}

	short CybTCPServer::getPort(void)
	{
		return this->serverAddr->getPort();
	}

	short CybTCPServer::getFamily(void)
	{
		return this->serverAddr->getFamily();
	}

	CybNodeAddress* CybTCPServer::getNodeAddr(void)
	{
		return this->serverAddr;
	}

	struct sockaddr_in* CybTCPServer::getAddr(void)
	{
		return this->serverAddr->getAddr();
	}

	CybTCPClient* CybTCPServer::getClient(int i)
	{
		if(i>=MAX) return NULL;
		else return this->clients[i];
	}

	int CybTCPServer::getClientsNumber(void)
	{
		return nclients;
	}

	void CybTCPServer::receiveData(int sock, void* data, int size) throw (CybCommunicationException)
	{
		int result = 0;
		result = read(sock, data, size);
		if(result < 0) throw CybCommunicationException(1);
	}

	void CybTCPServer::sendData(int sock, void* data, int size) throw (CybCommunicationException)
	{
		int result = 0;
		result = write(sock, data, size);
		if(result < 0) throw CybCommunicationException(2);
	}

	void CybTCPServer::acceptConnection(CybTCPClient* client) throw (CybTCPException)
	{
		int result = 0;
		result  = accept(this->streamSock->getSock(), (struct sockaddr*)(client->getAddr()), this->serverAddr->getAddrSize());
		if(result < 0) throw CybTCPException(4);
		else client->getStreamSock()->setSock(result);
	}

	void CybTCPServer::startServer(void) throw (CybTCPException)
	{
		int result;
		int i = 0;

		while(true)
		{
			result = listen(this->getSock(), MAX); // fica esperando uma nova conexão
			if( result<0 ) throw CybTCPException(5);

			// aceita a conexão
			this->clients[i] = new CybTCPClient();

			try
			{
				acceptConnection(this->clients[i]);
			}
			catch(CybCommunicationException e)
			{
				e.showErrorMessage();
			}

			// faz a comunicação
			communicate(i);

			//fecha o socket
			close(this->clients[i]->getSock());
		}

	}

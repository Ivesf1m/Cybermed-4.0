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

#include "cybTCPClient.h"


    CybTCPClient::CybTCPClient(void)
    {
        this->streamSock = new CybStreamSock(0);
        this->clientAddr = new CybNodeAddress();
        this->serverAddr = new CybNodeAddress();
    }

    CybTCPClient::CybTCPClient(CybStreamSock* streamSock, CybNodeAddress* serverAddr, CybNodeAddress* clientAddr)
    {
        this->streamSock = streamSock;
        this->serverAddr = serverAddr;
        this->clientAddr = clientAddr;
    }
    
    CybTCPClient::CybTCPClient(const short client_port, const short server_port, const char* server_ip)
    {
        this->streamSock = new CybStreamSock();
        this->clientAddr = new CybNodeAddress(client_port, NULL, AF_INET);
        this->serverAddr = new CybNodeAddress(server_port, server_ip, AF_INET);
        this->streamSock->connectToPort(this->streamSock->getSock(), this->clientAddr);

        try
        {
            this->makeConnection();
        }
        catch(CybCommunicationException e)
        {
            e.showErrorMessage();
        }

        cout << "The client is on." << endl;
    }
    
    CybTCPClient::CybTCPClient(const short client_port, const short server_port, const char* server_ip, const short family)
    {
        this->streamSock = new CybStreamSock();
        this->clientAddr = new CybNodeAddress(client_port, NULL, family);
        this->serverAddr = new CybNodeAddress(server_port, server_ip, family);
        this->streamSock->connectToPort(this->streamSock->getSock(), this->clientAddr);

        try
        {
            this->makeConnection();
        }
        catch(CybCommunicationException e)
        {
            e.showErrorMessage();
        }

        cout << "The client is on." << endl;
    }
    
    CybTCPClient::CybTCPClient(const short server_port, const char* server_ip)
    {
        this->streamSock = new CybStreamSock();
        this->clientAddr = new CybNodeAddress(0, NULL, AF_INET);
        this->serverAddr = new CybNodeAddress(server_port, server_ip, AF_INET);

        try
        {
            this->makeConnection();
        }
        catch(CybCommunicationException e)
        {
            e.showErrorMessage();
        }

        cout << "The client is on." << endl;
    }
    
    CybTCPClient::CybTCPClient(const short server_port, const char* server_ip, const short family)
    {
        this->streamSock = new CybStreamSock();
        this->clientAddr = new CybNodeAddress(0, NULL, family);
        this->serverAddr = new CybNodeAddress(server_port, server_ip, family);

        try
        {
            this->makeConnection();
        }
        catch(CybCommunicationException e)
        {
            e.showErrorMessage();
        }

        cout << "The client is on." << endl;
    }

    CybTCPClient::~CybTCPClient()
    {
        close(this->streamSock->getSock());
        cout << "The client is off." << endl;
    }
	
	int CybTCPClient::getSock(void)
	{
		return this->streamSock->getSock();
	}

	CybStreamSock* CybTCPClient::getStreamSock(void)
	{
		return this->streamSock;
	}

	char* CybTCPClient::getIP(void)
	{
		return this->clientAddr->getIP();
	}

	short CybTCPClient::getPort(void)
	{
		return this->clientAddr->getPort();
	}

	short CybTCPClient::getFamily(void)
	{
		return this->clientAddr->getFamily();
	}

	CybNodeAddress* CybTCPClient::getNodeAddr(void)
	{
		return this->clientAddr;
	}

	struct sockaddr_in* CybTCPClient::getAddr(void)
	{
		return this->clientAddr->getAddr();
	}

	CybNodeAddress* CybTCPClient::getServerAddr(void)
	{
		return this->serverAddr;
	}

	void CybTCPClient::makeConnection(void) throw (CybCommunicationException)
	{
		int result = 0;
		/* start the connection between the client socket and the server socket */
		result = connect(this->streamSock->getSock(), (struct sockaddr *)this->serverAddr->getAddr(), this->serverAddr->getAddrSizeValue());
		if(result) throw CybCommunicationException(3);
	}

	void CybTCPClient::receiveData(void* data, int size) throw (CybCommunicationException)
	{
		int result = 0;
		result = read(this->streamSock->getSock(), data, size);
		if(result < 0) throw CybCommunicationException(1);
	}

	void CybTCPClient::sendData(void* data, int size) throw (CybCommunicationException)
	{
		int result = 0;
		result = write(this->streamSock->getSock(), data, size);
		if(result < 0) throw CybCommunicationException(2);
	}

	void CybTCPClient::receiveData(int sock, void* data, int size) throw (CybCommunicationException)
	{
		this->receiveData(data, size);
	}

	void CybTCPClient::sendData(int sock, void* data, int size) throw (CybCommunicationException)
	{
		this->sendData(data, size);
	}



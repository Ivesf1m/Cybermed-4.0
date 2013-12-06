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

#include "cybUDPClient.h"


	CybUDPClient::CybUDPClient(void) { }

	CybUDPClient::CybUDPClient(CybDatagramSock* dataSock, CybNodeAddress* serverAddr, CybNodeAddress* clientAddr)
	{
		this->dataSock = dataSock;
		this->serverAddr = serverAddr;
		this->clientAddr = clientAddr;
	}

	/* client_port is the sender port from the client and server_port is the listener port from de server */
	CybUDPClient::CybUDPClient(const short client_port, const short server_port, const char* server_ip)
	{
		this->dataSock = new CybDatagramSock();
		this->clientAddr = new CybNodeAddress(client_port, NULL, AF_INET);
		this->serverAddr = new CybNodeAddress(server_port, server_ip, AF_INET);

		this->dataSock->connectToPort(this->dataSock->getSock(), this->clientAddr);

		cout << "The client is on." << endl;
	}

	CybUDPClient::CybUDPClient(const short client_port, const short server_port, const char* server_ip, const short family)
	{
		this->dataSock = new CybDatagramSock();
		this->clientAddr = new CybNodeAddress(client_port, NULL, family);
		this->serverAddr = new CybNodeAddress(server_port, server_ip, family);

		this->dataSock->connectToPort(this->dataSock->getSock(), this->clientAddr);

		cout << "The client is on." << endl;
	}

	CybUDPClient::CybUDPClient(const short server_port, const char* server_ip)
	{
		this->dataSock = new CybDatagramSock();
		this->clientAddr = new CybNodeAddress(0, NULL, AF_INET);
		this->serverAddr = new CybNodeAddress(server_port, server_ip, AF_INET);

		this->dataSock->connectToPort(this->dataSock->getSock(), this->clientAddr);

		cout << "The client is on." << endl;
	}

	CybUDPClient::CybUDPClient(const short server_port, const char* server_ip, const short family)
	{
		this->dataSock = new CybDatagramSock();
		this->clientAddr = new CybNodeAddress(0, NULL, family);
		this->serverAddr = new CybNodeAddress(server_port, server_ip, family);

		this->dataSock->connectToPort(this->dataSock->getSock(), this->clientAddr);

		cout << "The client is on." << endl;
	}

	CybUDPClient::~CybUDPClient()
	{
		close(this->dataSock->getSock());
		cout << "The client is off." << endl;
	}


	int CybUDPClient::getSock(void)
	{
		return this->dataSock->getSock();
	}

	CybDatagramSock* CybUDPClient::getDatagramSock(void)
	{
		return this->dataSock;
	}

	char* CybUDPClient::getIP(void)
	{
		return this->clientAddr->getIP();
	}

	short CybUDPClient::getPort(void)
	{
		return this->clientAddr->getPort();
	}

	short CybUDPClient::getFamily(void)
	{
		return this->clientAddr->getFamily();
	}

	CybNodeAddress* CybUDPClient::getServerAddr(void)
	{
		return this->serverAddr;
	}

	CybNodeAddress* CybUDPClient::getNodeAddr(void)
	{
		return this->clientAddr;
	}

	struct sockaddr_in* CybUDPClient::getAddr(void)
	{
		return this->clientAddr->getAddr();
	}

	void CybUDPClient::makeConnection(void) throw (CybCommunicationException)
	{
		int result = 0;
		/* start the connection between the client socket and the server socket */
		result = connect(this->dataSock->getSock(), (struct sockaddr *)this->serverAddr->getAddr(), this->serverAddr->getAddrSizeValue());
		if(result) throw CybCommunicationException(3);
	}

	void CybUDPClient::receiveData(void* data, int size) throw (CybCommunicationException)
	{
		int result = 0;
		result = recvfrom(this->dataSock->getSock(), data, size, 0, (struct sockaddr *)this->serverAddr->getAddr(), this->serverAddr->getAddrSize());
		if(result < 0) throw CybCommunicationException(1);
	}

	void CybUDPClient::sendData(void* data, int size) throw (CybCommunicationException)
	{
		int result = 0;
		result = sendto(this->dataSock->getSock(), data, size, 0, (struct sockaddr *)(this->serverAddr->getAddr()), this->serverAddr->getAddrSizeValue());
		if(result < 0) throw CybCommunicationException(2);
	}

	void CybUDPClient::receiveData(int sock, void* data, int size) throw (CybCommunicationException)
	{
		receiveData(data, size);
	}
	
	void CybUDPClient::sendData(int sock, void* data, int size) throw (CybCommunicationException)
	{
		sendData(data, size);
	}

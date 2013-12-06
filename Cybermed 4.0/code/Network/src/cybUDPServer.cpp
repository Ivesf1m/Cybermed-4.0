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

#include "cybUDPServer.h"

	CybUDPServer::CybUDPServer(void) { }

	CybUDPServer::CybUDPServer(const short server_port)
	{
		int i;
		this->dataSock = new CybDatagramSock();
		this->serverAddr = new CybNodeAddress(server_port, NULL, AF_INET);

		for(i=0; i<MAX; i++)
		{
			this->clientAddr[i] = new CybNodeAddress();
		}

		this->dataSock->connectToPort(this->dataSock->getSock(), this->serverAddr);

		cout << "The server is on." << endl;
	}

	CybUDPServer::CybUDPServer(const short server_port, const short family)
	{
		int i;
		this->dataSock = new CybDatagramSock();
		this->serverAddr = new CybNodeAddress(server_port, NULL, family);

		for(i=0; i<MAX; i++)
		{
			this->clientAddr[i] = new CybNodeAddress();
		}

		this->dataSock->connectToPort(this->dataSock->getSock(), this->serverAddr);

		cout << "The server is on." << endl;
	}

	CybUDPServer::~CybUDPServer()
	{
		close(this->dataSock->getSock());
		cout << "The server is off." << endl;
	}


	int CybUDPServer::getSock(void)
	{
		return this->dataSock->getSock();
	}

	CybDatagramSock* CybUDPServer::getDatagramSock(void)
	{
		return this->dataSock;
	}

	char* CybUDPServer::getIP(void)
	{
		return this->serverAddr->getIP();
	}

	short CybUDPServer::getPort(void)
	{
		return this->serverAddr->getPort();
	}

	short CybUDPServer::getFamily(void)
	{
		return this->serverAddr->getFamily();
	}

	CybNodeAddress* CybUDPServer::getNodeAddr(void)
	{
		return this->serverAddr;
	}

	struct sockaddr_in* CybUDPServer::getAddr(void)
	{
		return this->serverAddr->getAddr();
	}

	CybNodeAddress* CybUDPServer::getClientAddr(int i)
	{
		return this->clientAddr[i];
	}

	void CybUDPServer::sendData(int sock, void* data, int size) throw (CybCommunicationException)
	{
		sendData(data, size);
	}

	void CybUDPServer::receiveData(int sock, void* data, int size) throw (CybCommunicationException)
	{
		receiveData(data, size);
	}

	void CybUDPServer::sendData(void* data, int size) throw (CybCommunicationException)
	{
		int result = 0;
		result = sendto(this->dataSock->getSock(), data, size, 0, (struct sockaddr *)this->clientAddr[0]->getAddr(), this->serverAddr->getAddrSizeValue());
		if(result < 0) throw CybCommunicationException(2);
	}

	int CybUDPServer::receiveData(void* data, int size) throw (CybCommunicationException)
	{
		struct sockaddr_in auxAddr;
		int result = 0;
		result = recvfrom(this->dataSock->getSock(), data, size, 0, (struct sockaddr *)this->clientAddr[0]->getAddr(), this->serverAddr->getAddrSize());
		if(result < 0) throw CybCommunicationException(1);
		return result;
	}

	void CybUDPServer::sendData(void* data, int size, CybNodeAddress* address) throw (CybCommunicationException)
	{
		int result = 0;
		result = sendto(this->dataSock->getSock(), data, size, 0, (struct sockaddr *)address->getAddr(), address->getAddrSizeValue());
		if(result < 0) { 
				throw CybCommunicationException(2);
				cout << "erro ao enviar...\n" << endl; 	
		} 
		//else cout << result << " bytes enviados: " << data << "para o host: "<< inet_ntoa(address->getAddr()->sin_addr) << endl;
	}

	int CybUDPServer::receiveDataFrom(void* data, int size, CybNodeAddress* address) throw (CybCommunicationException)
	{
		struct sockaddr_in auxAddr;
		int result = 0;
		result = recvfrom(this->dataSock->getSock(), data, size, 0, (struct sockaddr *)&auxAddr, this->serverAddr->getAddrSize());
		
		//cout << "Data: " << (char*) data << " received from host --> " << inet_ntoa(auxAddr.sin_addr) << ":" << htons(auxAddr.sin_port) << endl;

		address->setAddr(&auxAddr);
		if(result < 0) throw CybCommunicationException(1);
		return result;
	}

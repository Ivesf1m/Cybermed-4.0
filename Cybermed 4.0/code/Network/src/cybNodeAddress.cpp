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

#include "cybNodeAddress.h"


	CybNodeAddress::CybNodeAddress()
	{
		this->addr = new struct sockaddr_in;
		this->addrSize = sizeof(struct sockaddr_in);
	}

	CybNodeAddress::CybNodeAddress(const short port, const char* ip, const short family)
	{
		mountAddr(port, ip, family);
	}


	struct sockaddr_in* CybNodeAddress::getAddr(void)
	{
		return this->addr;
	}

	void CybNodeAddress::setAddr(struct sockaddr_in* addr)
	{
		this->addr = addr;
	}

	socklen_t CybNodeAddress::getAddrSizeValue(void)
	{
		return this->addrSize;
	}

	socklen_t* CybNodeAddress::getAddrSize(void)
	{
		return &(this->addrSize);
	}

	short CybNodeAddress::getPort(void)
	{
		  return (ntohs(this->addr->sin_port));
	}

	char* CybNodeAddress::getIP(void)
	{
		  return inet_ntoa(this->addr->sin_addr);
	}

	short CybNodeAddress::getFamily(void)
	{
		  return this->addr->sin_family;
	}

	void CybNodeAddress::setPort(const short port)
	{
		 this->addr->sin_port = htons(port);
	}

	void CybNodeAddress::setIP(const char* ip)
	{
		 inet_aton(ip, &this->addr->sin_addr);
	}

	void CybNodeAddress::setFamily(const short family)
	{
		 this->addr->sin_family = family;
	}

	void CybNodeAddress:: mountAddr(const short port, const char* ip, const short family)
	{
		this->addr = new struct sockaddr_in;
		this->addrSize = sizeof(struct sockaddr_in);
		this->addr->sin_family = AF_INET;
		this->addr->sin_port = htons(port);
		memset(this->addr->sin_zero, 0, 8); //checar
		int result;

		if(ip != NULL)
		{
		result = inet_aton(ip, &this->addr->sin_addr);
		if(result < 0)
		{
			cout << "<ERROR: problem in inet_aton() call.>" << endl;
			exit(1);
		}
		}
		else this->addr->sin_addr.s_addr = htonl(INADDR_ANY);

	}


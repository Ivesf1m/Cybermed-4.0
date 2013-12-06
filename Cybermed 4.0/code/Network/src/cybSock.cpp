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


#include "cybSock.h"

	/* O método connectToPort() faz a ligação do socket com uma porta local para tro-
	 * ca de dados. O primeiro argumento é o socket e o segundo, a estrutura de ende-
	 reço. */
	void CybSock::connectToPort(int s, CybNodeAddress* addr)
	{
		int result;
		short new_port;
		result = bind(s, (struct sockaddr *)addr->getAddr(), addr->getAddrSizeValue());

		while( result == -1 )
		{
			cout << "<WARNING: Problem to connect to the port " << ntohs(addr->getAddr()->sin_port) << ". Try another port.>" << endl;
			cout << "Port: " ;
			cin >> new_port;
			addr->getAddr()->sin_port = htons(new_port);
			result = bind(s, (struct sockaddr *)addr->getAddr(), addr->getAddrSizeValue());
		}
	}

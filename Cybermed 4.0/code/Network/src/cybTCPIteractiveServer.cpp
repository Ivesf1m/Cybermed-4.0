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

#include "cybTCPIteractiveServer.h"

    CybTCPIteractiveServer::CybTCPIteractiveServer(const short server_port): CybTCPServer(server_port)
    {
        
    }

	void CybTCPIteractiveServer::communicate(int i)
	{
		char* msg = "the server is on";
		int size = 30;
		char buffer[30];

		CybTCPClient* client = this->getClient(i);

		if(client)
		{
			try
			{// o problema esta aki
				this->receiveData(client->getSock(), buffer, size);
				cout << buffer << endl;

				this->sendData(client->getSock(), msg, size);
			}
			catch(CybCommunicationException e)
			{
				e.showErrorMessage();
			}
		}
	}



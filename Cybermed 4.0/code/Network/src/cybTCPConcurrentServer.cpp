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

#include "cybTCPConcurrentServer.h"

    CybTCPConcurrentServer::CybTCPConcurrentServer(const short server_port, int bufferSize): CybTCPServer(server_port)
    {
        this->bufferSize = bufferSize;
    }

	void CybTCPConcurrentServer::startServer(void) throw (CybTCPException)
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
			communicate(this->clients[i]->getSock());
			i++;
		}

	}

	void CybTCPConcurrentServer::communicate(int i)
	{
		// cria uma nova thread
		thread = new CybTCPServerThread(this, i); //cria nova thread
		thread->init();
		thread->start();
	}

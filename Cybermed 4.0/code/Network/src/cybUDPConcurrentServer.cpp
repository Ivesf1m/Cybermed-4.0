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
 *
 * A classe CybUDPConcurrentServer oferece suporte para servidores UDP concorrentes. Ela contém
 * uma instância de CybServerUDP e de CybServerThread, para obter tal comportamento. O servidor
 * concorrente simplesmente fica em escuta e a cada requisição que recebe cria uma thread para
 * atendê-la. Assim, não deve ser usado por muitos clientes de maneira simultânea, para evitar
 * esgotamento de recursos.
 *
 **/

#include "cybUDPConcurrentServer.h"

    CybUDPConcurrentServer::CybUDPConcurrentServer(const short server_port, int bufferSize)
    {
        server = new CybUDPIteractiveServer(server_port);
        this->bufferSize = bufferSize;
    }

	void CybUDPConcurrentServer::startServer(void)
	{
		int count = 0;
		char buffer[bufferSize];
		while(true)
		{
			try
			{
				server->receiveData(server->getSock(), buffer, bufferSize); // recebe dados
				cout << buffer << endl;

				thread = new CybUDPServerThread(server); //cria nova thread

				thread->init();
				thread->start();
			}

			catch(CybCommunicationException e)
			{
				e.showErrorMessage();
			}
		}
	}

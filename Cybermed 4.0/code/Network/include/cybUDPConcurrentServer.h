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

#ifndef _CYBUDPCONCURRENTSERVER_H
#define	_CYBUDPCONCURRENTSERVER_H
#include "cybUDPIteractiveServer.h"
#include "cybUDPServerThread.h"

class CybUDPConcurrentServer
{
private:
    int bufferSize;
    
public:
    CybUDPIteractiveServer* server;
    CybUDPServerThread* thread;
    
    /** Constructor */
    CybUDPConcurrentServer(const short server_port, int bufferSize);
    
    /** */
    void startServer();
    
};
#endif	/* _CYBUDPCONCURRENTSERVER_H */


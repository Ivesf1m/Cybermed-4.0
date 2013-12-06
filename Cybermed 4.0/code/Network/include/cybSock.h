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
 * A interface CybSock define os métodos necessários para a construção de um
 * socket em linguagem C. Veja que aqui ainda não há métodos para envio e recep-
 * ção de dados. Isto irá acontecer a partir da utilização do socket criado, na
 * definição de um servidor ou de um cliente.
 *
 **/

#ifndef _CYBSOCK_H
#define	_CYBSOCK_H

#include "cybNetwork.h"
#include "cybNodeAddress.h"

class CybSock
{
public:
    /** */
	void connectToPort(int s, CybNodeAddress* addr);

	/** */
	virtual void createSock(void) = 0;

	/** */
	virtual int getSock(void) = 0;
};

#endif	/* _CYBSOCK_H */



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

#ifndef _CYBNODEADDRESS_H
#define	_CYBNODEADDRESS_H

#include "cybNetwork.h"
#include <iostream>
#include <cstring>


using namespace std;

class CybNodeAddress
{
 
public:

	/** Constructor */
    CybNodeAddress();

    /** Constructor
     *@port
     *@ip
     *@family
     */
	CybNodeAddress(const short port, const char* ip, const short family);

	/** */
    struct sockaddr_in* getAddr(void);

    /** */
    void setAddr(struct sockaddr_in* addr);

    /** */
    socklen_t getAddrSizeValue(void);

    /** */
    socklen_t* getAddrSize(void);

    /** */
    short getPort(void);

    /** */
    char* getIP(void);

    /** */
    short getFamily(void);

    /** */
    void setPort(const short port);

    /** */
    void setIP(const char* ip);

    /** */
    void setFamily(const short family);

private:
    /** */
    void mountAddr(const short port, const char* ip, const short family);
	
	struct sockaddr_in* addr;
    socklen_t addrSize;
};
#endif	/* _CYBNODEADDRESS_H */



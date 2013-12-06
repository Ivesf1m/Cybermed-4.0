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

#ifndef CYBREMOTEINTERATOR_H_
#define CYBREMOTEINTERATOR_H_

#include "cybParameters.h"
#include "cybInterator.h"

class CybRemoteInterator : public CybInterator {
public:
	/** Consutructor */
	CybRemoteInterator();

	/** Gets the interator device. */
	CybDevice* getDevice();

	/** Creates the remote interator. */
	virtual void create(int id);

	void destroy();

	void setInteratorChange(char* buffer);

	void setInteratorPosition(int x, int y, int z);

    static CybRemoteInterator* getInterator();

	virtual ~CybRemoteInterator();
};

#endif /* CYBREMOTEINTERATOR_H_ */

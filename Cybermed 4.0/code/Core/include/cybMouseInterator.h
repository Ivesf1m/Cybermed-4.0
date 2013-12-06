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

#ifndef CYBMOUSEINTERATOR_H_
#define CYBMOUSEINTERATOR_H_

#include "cybInterator.h"
#include "cybParameters.h"
//class CybMouseInteraction;

class CybMouseInterator : public CybInterator {
public:
	/** Constructor
	 *
	 */
	CybMouseInterator();

	CybDevice* getDevice();
	void create(int id);
	void destroy();

	bool isMeshGrasped();
	CybVector3D<float> getFocus();

	void setMeshGrasped(bool meshGrasped);
	void setFocus(float x, float y, float z);
	void setMousePosition(float x, float y, float z);
	
	static CybInterator* getInterator();

	/** Destructor
	 *
	 */
	virtual ~CybMouseInterator();

private:
	CybDevice* mouse;
	CybVector3D<float> objectFocus;
	bool meshGrasped;

};

#endif /* CYBMOUSEINTERATOR_H_ */

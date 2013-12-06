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

#ifndef _CYB_FFD_NODE_H_
#define _CYB_FFD_NODE_H_

#include "cybVector3D.h"
#include "cybParameters.h"

class CybFFDNode
{
public:
	
	CybVector3D<float> point;
	//cybSurfaceTriTraits::sVertex* vertex;
	sVertex* vertex;
	mfList<int> neighbors;
	CybVector3D<float> min,max;
	CybVector3D<float> S, U, T;
	bool back;
	
	CybFFDNode();
	
	~CybFFDNode();
};

#endif /*_CYB_FFD_NODE_H_*/

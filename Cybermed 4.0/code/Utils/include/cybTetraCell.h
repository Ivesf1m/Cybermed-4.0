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

#ifndef CYBTETRACELL_H
#define CYBTETRACELL_H

#include "mf/mfMacros.h"
#include "mf/mfTetraCell.h"
#include "cybTraits.h"
#include "mf/mfMesh.h"

namespace mf
{

#define SPACE typename cybTetraCell<_Traits>::space
#define SVERTEX typename cybMesh<_Traits>::sVertex
#define IDS typename cybMesh<_Traits>::ids


/**
@class		cybTetraCell 
@file		cybTetraCell.h 
@short
	CyberMed Vertex Class

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.0
@date		2007, July
*/
template <class _Traits> class cybTetraCell: public mfTetraCell<_Traits>
{
public:
	typedef typename _Traits::space space;
	typedef typename _Traits::ids ids;
	typedef typename _Traits::sMesh sMesh;
	typedef typename _Traits::sVertex sVertex;

	/** Constructor */
	cybTetraCell()
	{	}

	/** Destructor */
	virtual ~cybTetraCell()
	{	}

	void getFaceVerticesIndex(int faceId, int *Vertices)
	{
		if(faceId == 0)
		{
			Vertices[0] = 1;
			Vertices[1] = 2;
			Vertices[2] = 3;
			return;
		}
		if(faceId == 1)
		{
			Vertices[0] = 0;
			Vertices[1] = 3;
			Vertices[2] = 2;
			return;
		}
		if(faceId == 2)
		{
			Vertices[0] = 0;
			Vertices[1] = 1;
			Vertices[2] = 3;
			return;
		}
		if(faceId == 3)
		{
			Vertices[0] = 0;
			Vertices[1] = 2;
			Vertices[2] = 1;
			return;
		}
	}

	void getFaceVerticesId(int faceId, int *Vertices)
	{
		if(faceId == 0)
		{
			Vertices[0] = this->getVertexId(1);
			Vertices[1] = this->getVertexId(2);
			Vertices[2] = this->getVertexId(3);
			return;
		}
		if(faceId == 1)
		{
			Vertices[0] = this->getVertexId(0);
			Vertices[1] = this->getVertexId(3);
			Vertices[2] = this->getVertexId(2);
			return;
		}
		if(faceId == 2)
		{
			Vertices[0] = this->getVertexId(0);
			Vertices[1] = this->getVertexId(1);
			Vertices[2] = this->getVertexId(3);
			return;
		}
		if(faceId == 3)
		{
			Vertices[0] = this->getVertexId(0);
			Vertices[1] = this->getVertexId(2);
			Vertices[2] = this->getVertexId(1);
			return;
		}
	}

private:
	

};


#undef SPACE
#undef IDS
#undef SVERTEX

}

#endif

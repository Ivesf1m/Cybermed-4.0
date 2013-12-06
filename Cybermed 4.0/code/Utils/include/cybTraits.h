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

#ifndef CYBTRAITS_H
#define CYBTRAITS_H

#include "cybVertex.h"
#include "mf/mfEdge.h"
#include "cybTriCell.h"
#include "cybTetraCell.h"
#include "cybMesh.h"
#include "cybMeshTetra.h"
#include "mf/mfMeshTriSurface.h"

#include "mf/mfTopology.h"
#include "mf/mfGeometric.h"

namespace mf
{

/**
* @file cybTraits.h 
* @short 
* 		This Trait Characterizes the object supported by the CyberMed System.
*
* @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
* @version	1.0
* @date		2007, July
* 
*/	
	
struct cybSurfaceTriTraits
{
	typedef double						space;
	typedef int						ids;

	typedef cybVertex<cybSurfaceTriTraits>			sVertex; 	// CyberMed Vertex Type
	typedef mfEdge<cybSurfaceTriTraits>			sEdge;		/**< Edge definition */
	typedef cybTriCell<cybSurfaceTriTraits>			sCell; 		// CyberMed Cell Type

	typedef mfMesh<cybSurfaceTriTraits>			sMesh;
	typedef mfMeshTriSurface<cybSurfaceTriTraits>		sOper;

	typedef mfGeometric<cybSurfaceTriTraits>		sGeometric;
	typedef mfTopology<cybSurfaceTriTraits>			sTopology;
};


struct cybTetraTraits
{
	typedef double					space;
	typedef int					ids;

	typedef cybVertex<cybTetraTraits>		sVertex; 	// CyberMed Vertex Type
	typedef mfEdge<cybTetraTraits>			sEdge;		// Edge definition 
	typedef cybTetraCell<cybTetraTraits>		sCell; 		// CyberMed Cell Type

	typedef mfMesh<cybTetraTraits>			sMesh;
	typedef cybMeshTetra<cybTetraTraits>		sOper;

	typedef mfGeometric<cybTetraTraits>		sGeometric;
	typedef mfTopology<cybTetraTraits>		sTopology;
};

}

#endif

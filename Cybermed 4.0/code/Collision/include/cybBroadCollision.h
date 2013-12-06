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

#include "cybCollision.h"
#include "cybTriCell.h"

#define SCELL typename cybMesh<cybTraits>::sCell 

#ifndef _CYB_BROADCOLLISION_H_
#define _CYB_BROADCOLLISION_H_

/**
 * @class CybBroadCollision 
 * @file cybBroadCollision.h 
 * @short Collision Broad Phase SUPER class
 *
 * This class specifies the parameters of a collision broad phase. 
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 */

class CybBroadCollision : public CybCollision
{		
protected:
	mfList<cybMesh<cybSurfaceTriTraits>::sCell *> listOfTriangles; 	/** < List Of triangles selected by the narrow collision detection. */ 
	
public:

	/** Constructor 
	 * 
	 * @param int layer The number layer of layer that the object will be detect collision.
	 * @param int interatorId The interator id of interator that will be detect collision with the object.
	 */
	CybBroadCollision(int layer, int interatorId);

	/** Constructor
	 *
	 * @param int layer The number layer of layer that the object will be detect collision.
	 * @param int idInterator The interator id of interator that will be detect collision with the object.
	 */
	CybBroadCollision(int layer, CybInterator* interator);


	/** Destructor */
	~CybBroadCollision();
	
	/**
	 * This method returns a reference to the list of triangles. 
	 * 
	 * @param void
	 * @return mfList<cybCell*>* A reference to the list of this object.
	 * 
	 */
	mfList<cybMesh<cybSurfaceTriTraits>::sCell *>* getListOfTrianglesReference();
};	


#endif /*_CYB_BROADCOLLISION_H_*/

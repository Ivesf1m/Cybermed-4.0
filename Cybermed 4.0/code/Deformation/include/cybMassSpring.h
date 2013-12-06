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

#ifndef _CYB_MASS_SPRING_H_
#define _CYB_MASS_SPRING_H_

#include "cybMassSpringNode.h"
#include "cybDeformation.h"

/**
 * @class CybMassSpring
 * @file cybMassSpring.h 
 * @short implements the mass-spring deformation method.
 * 
 * This class implements the mass-spring deformation method, it uses the euler method to solving it.
 * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @author ICMC-USP (http://www.icmc.usp.br), University of São Paulo
 * @version 1.0
 * @date 2007, July
 * 
 */

class CybMassSpring : public CybDeformation
{

private:
	CybMassSpringNode* nodes;		/**< Reference to an array of CybNodes, that stores the information of all points*/
	int vertex_number;	/**< Stores the number of vertex of this respective layer. */
	float intensity;
	
public:
 
	typedef mfVerticesIterator<cybSurfaceTriTraits> vIterator;
	typedef mfVertexStarIteratorTriSurf<cybSurfaceTriTraits> vStarIterator;

  	/** Constructor 
	 * 
	 * @param CybNarrowCollision *collision The object that will detect collision.
	 * @param int defMode The deformation mode.
	 *  
	 */
	CybMassSpring(CybNarrowCollision *collision, EnumDefMode defMode /*= DEF_GO_AND_BACK*/);

	/** Destructor. */
	~CybMassSpring();

	/**
	* This method apply force in an specific point and its neigbors.
	*
	* @param CybVector3D<float> force The force aplied.
	* @param int vertexId The vertex id.
	*
	*/	
	void applyForce(CybVector3D<float> force, int vertexId);

	/**
	* This method apply force in all the point in the mesh except the points presents in list.
	*
	* @param void.
	* @return void.
	*
	*/
	void applyForceAllPoints();

	/**
	* This method loads the ED of deformation.
	* 
	* @param void.
	* @return void.
	*
	*/
	void initED();

	/**
   	 * Thread method, called when thread is running.
	* 
	* @param void
	* @return void
	* 
	*/
	virtual void run();

	void setIntensity(float intensity);

	float getIntensity();
};

#endif /*_CYB_MASS_SPRING_H_*/

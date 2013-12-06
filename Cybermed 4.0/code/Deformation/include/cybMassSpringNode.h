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

#ifndef _CYB_MASS_SPRING_NODE_H_
#define _CYB_MASS_SPRING_NODE_H_

#include "cybVector3D.h"
#include "cybTraits.h"

using namespace mf;

/**
 * @class CybMassSpringNode
 * @file cybMassSpringNode.h 
 * @short Element used in ED of deformation.
 * 
 * Stores all informations about the shift of the points.
 * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */
class CybMassSpringNode
{
public:
	typedef cybVertex<cybSurfaceTriTraits> sVertex;
  
	CybVector3D<float> acceleration;	/**< It stores the point's acceleration. */
	CybVector3D<float> velocity; 		/**< It stores the point's velocity. */	
	CybVector3D<float> point;		/**< It stores the point's coordenate. */
	
	sVertex* vertex;			/**< It stores the points's reference. */
	mfList<int> neighbors;   		/**< It stores the neighbors list. */

	/** Constructor. */
	CybMassSpringNode();

	/** Destructor. */
	~CybMassSpringNode();
	/**
	* This method calculates the acceleration and the velocity of this point.
	*
	* @param CybVector3D<float> The force applied in this point.
	* @param float mass The mass of this point.
	* @param float step The step used in calculus.
	* @param float stiffness The stiffness of shift.
	* @return void	
	*
	*/
	void update_acceleration_velocity(CybVector3D<float> force, float mass, float step, float stiffness);

};

#endif /*_CYB_MASS_SPRING_NODE_H_*/

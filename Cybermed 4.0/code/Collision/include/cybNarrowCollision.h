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
#include "cybBroadCollision.h"
#include "cybTraits.h"

#define SCELL typename cybMesh<cybTraits>::sCell 

#ifndef _CYB_NARROWCOLLISION_H_
#define _CYB_NARROWCOLLISION_H_

/**
 * @class CybNarrowCollision 
 * @file cybNarrowCollision.h 
 * @short Collision Narrow Phase SUPER class.
 *
 * This class specifies the parameters of a collision narrow phase.  
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */

class CybNarrowCollision : public CybCollision
{
private:
	
	CybVector3D<float> triangleNormal;			/**< Indicates the normal of triangle of collision. */
	CybVector3D<float> vectorCollision;			/**< Stores the direction defined by (interatorPositionInObjectCoordenates - pointOfCollision). */

protected:	
	
	CybVector3D<float> pointOfCollision; 		/**< Stores the point of collision. */
	int triangleOfCollision;			/**< Stores the index of the triangle where the collision occured. */
	int vertexOfCollision;				/**< Indicates the vertex of triangle that there was collision. */	
	CybBroadCollision* broadObject;			/** < A reference to broad collision Object. */
	
public:
	
	/** Constructor 
	 * 
	 * @param int layer The number layer of layer that the object will be detect collision.
	 * @param int interatorId The interator id of interator that will be detect collision with the object.
	 */
	CybNarrowCollision(int layer, int interatorId);

	/** Constructor
	 *
	 * @param int layer The number layer of layer that the object will be detect collision.
	 * @param CybInterator* interator Pointer to interator that will be detect collision with the object.
	 */	
	CybNarrowCollision(int layer, CybInterator* interator);

	
	/** Constructor 
	 * 
	 * @param CybBroadCollision* broadObject The broad collision object associaded.
	 *  
	 */		
	CybNarrowCollision(CybBroadCollision* broadObject);
			
	/** Destructor */	
	~CybNarrowCollision();
	
	/**
	 * This method is abstract and can be implemented in derived class.
	 * It implements the collision detection method with an especific primitives list.
	 *
	 * @param mfList<cybMesh<cybTraits>::sCell *>* list Represents a list selected by 
	 * the broad phase and repassed to this.
	 * @return void
	 * 
	 */
	virtual void collision(mfList<cybMesh<cybSurfaceTriTraits>::sCell *>* list) = 0;
	
	/**
	 * This method destroys the this thread executation.
	 * and the thread of CybBroadCollision object associated.
	 * 
	 * @param void
	 * @return void
	 * 
	 */  	
  	void destroy(); 
	
	/**
	 *  This method returns a reference to the broad collision object
	 * associaded with this narrow collision.
	 * 
	 * @param void
	 * @return CybNarrowCollision* a reference to the narrow collision object associate.
	 * 
	 */	
	inline CybBroadCollision* getBroadCollisionObject();	

	/**
	* This method returns the coordenates of the collision point.
	*
	* @param void
	* @return CybVector3D<float> the collision point coordenates (in object coordenates).
	* 
	*/	
	inline CybVector3D<float> getPointOfCollision();

	/**
	* This method returns The number of the triangle of collision in layer interacted.
	*
	* @param void
	* @return int The number of triangle collided in list.
	*/		
	int getTriangleOfCollision();

	/**
	* This method returns the vertex of collision 0,1 or 2.
	*
	* @param void
	* @return int The vertex of triangle that was collided.
	*
	*/
	int getVertexOfCollision();

	/**
	 * This method creates this object thread
	 * and criates the thread of the broad collision object associated.
	 * 
	 * @param void
	 * @return void
	 * 
	 */
	 virtual void init();
	 
	 /**
	  * This method impements the routines to verifies if the interator is
	  * inside or outside the object. This method will must be called in the 
	  * son's run method, to verifies this (after the collision verification).
	  * 
	  * @param void.
	  * @return void.
	  * 
	  */ 
	 void verifiesInteratorSide();	 

	 /**
	 * This method verifies if is possible to use the method broad of the broad object
	 * in this collision detection.
	 * 
	 * @param void
	 * @return void
	 * 
	 */
	virtual void update();
};

#endif /*_CYB_NARROWCOLLISION_H_*/

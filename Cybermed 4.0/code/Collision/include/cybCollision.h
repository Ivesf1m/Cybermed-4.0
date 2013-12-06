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



#ifndef _CYB_COLLISION_H_
#define _CYB_COLLISION_H_

#include "cybThread.h"
#include "cybParameters.h"
#include "cybVector3D.h"
#include "cybTraits.h"
#include "cybCollisionData.h"
#include <cybermed/cybInterator.h>

/**
 * @class CybCollision 
 * @file cybCollision.h 
 * @short Collision detection SUPER class
 *
 * This class declarates and directs the processes of collision detection between 
 * an object in the ghaphics scene and an interactor. Your subclasses are implemented
 * visualizing the two phases in collision detection: the broad phase and the narrow phase.
 * An object only call ower method collision and all the parameters will be provided by
 * CybCollision class. 
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */

typedef cybSurfaceTriTraits::sVertex sVertex; //define a type to represent a vertex

class CybCollision : public CybThread
{	
private:
   bool is_equal_last_collision;								/**< Indicates if the atual collision is equal to last collision. */
   CybInterator* interator;

protected:
   bool  collisionStatus;									/**< Indicates if there was (true) or there wasn't (false) collision. */
   int layerOfCollision;									/**< Stores the layer ID in which collision was detected. */  
   int objectIndex;
 
public:

	/** Constructor 
	 * 
	 * @param int layer The number layer of layer that the object will be detect collision.
	 * @param int interatorId The interator id of interator that will be detect collision with the object.
	 *  
	 */
	CybCollision(int layer, int interatorId);
   
	/** Constructor
   	 *
   	 * @param int layer The number layer of layer that the object will be detect collision.
   	 * @param CybInterator* interator Pointer to the interator that will be detect collision with the object.
   	 *
   	 */
	CybCollision(int layer, CybInterator* interator);

	/** Destructor */ 
	~CybCollision();  	
   
	/**
	* This method returns the value of the collisionStatus atribute, indicating if there was
	* or there wasn't collision.
	*
	* @param void
	* @return bool True if there was collision and false if there wasn't.
	* 
	*/  
	bool getCollisionStatus();	// the son must update the collisionStatus attribute

	/**
	 * This method returns the value of layer where there was collision.
	 *
	 * @param void
	 * @return int the number that indicates the layer interacted.
	 * 
	 */
  	int getLayerOfCollision();

  	/**
  	 * This method returns a pointer to the interator that participates of the collision detection.
  	 * @param void
  	 * @return CybInterator* pointer to the interator.
  	 */
  	CybInterator* getInterator();
	int getObjectIndex();
	/**
	* This method returns if the atual collision
	* is equal to last collision.
	*
	* @param void.
	* @return bool If this collision is equal last collision.
	*
	*/   
	bool isEqualLastCollision();

	/**
	* This method modifies the interator of the collision.
	* @param CybInterator* interator Pointer to the interator.
	* @return void.
	*/
	void setInterator(CybInterator* interator);
	void setObjectIndex(int id);
	/**
	* This method habiitates the collision detection if the interator
	* is in a diferent position of the last position.
	*
	* @param void.
	* @return void.
	*
	*/   
	void update();

};
  		
#endif /*_CYB_COLLISION_H_*/

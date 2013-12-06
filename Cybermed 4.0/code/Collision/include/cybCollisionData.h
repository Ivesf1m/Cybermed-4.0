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

#include "cybInterator.h"
#include "cybPointOperator.h"

#ifndef _CYB_COLLISIONDATA_H_
#define _CYB_COLLISIONDATA_H_

/**
 * @class CybCollisionData
 * @file cybCollisionData.h 
 * @short Stores the interator information to the collision class. 
 * 
 * This class updates the interator position to the collisions objects.
 *  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */

class CybCollisionData
{	
	private:
	
	/** Constructor. */
	CybCollisionData();
	
	bool is_equal_last_position;								/**< Indicates if the atual position is equal to last position. */ 
	CybVector3D<float> interatorPositionInObjectCoordenates;			/**< Stores the interator's position in mouse coordenates. */
	CybVector3D<float> interatorPositionInGraphicsCoordenates;		/**< Stores the interator's position in graphics scene coordenates. */
	CybVector3D<float> lastInteratorPositionInObjectCoordenates;		/**< Stores the last interator's position in mouse coordenates. */
	CybVector3D<float> lastInteratorPositionInGraphicsCoordenates;	/**< Stores the last interator's position in graphics scene coordenates. */   
	CybVector3D<float> directionInObjectCoordenates;					/**< Stores the object direction in object coordenates. */
	CybVector3D<float> directionInGraphicsCoordenates;				/**< Stores the object direction in graphics coordenates. */
	CybParameters *cybCore;									/** A refernce to CybParameters. */
	static CybCollisionData* singletonInstance;				/**< The singleton instance of this class. */
	
	public:	
	
	/** Destructor. */
	~CybCollisionData();
	
	/**
  	 * This method returns the interator direction in object coordenates.
  	 * 
  	 * @param void
  	 * @return CybVector3D<float> The shift direction in object coordenates.
  	 * 
  	 */  	
  	CybVector3D<float> getDirectionInObjectCoordenates();
  	
  	/**
  	 * This method returns the interator direction in graphics coordenates.
  	 * 
  	 * @param void
  	 * @return CybVector3D<float> The shift direction in graphics coordenates.
  	 * 
  	 */   	
  	CybVector3D<float> getDirectionInGraphicsCoordenates();
  	
  	/**
  	 * This method returns the instance of this class.
  	 * 
  	 * @param void
  	 * @return CybCollisionData* A pointer to singleton object of this class.
  	 * 
  	 */  	
  	static CybCollisionData* getInstance();
  	
  	/**
	 * This method gets the values of the position ocupped by the interator in object's coordenates
	 * (without OpenGL's transforms).
	 *
	 * @param void.
	 * @return CybVector3D<float> The interator position in object coordenates.
	 * 
	 */
  	CybVector3D<float> getInteratorPositionInObjectCoordenates();
  	
  	/**
	 * This method gets the values of the position ocupped by the interator in graphics scene.
	 * (with OpenGL's transforms).
	 * 
	 * @param void.
	 * @return CybVector3D<float> The interator position in graphics coordenates.
	 * 
	 */
  	CybVector3D<float> getInteratorPositionInGraphicsCoordenates();
  	
  	/**
	 * This method gets the values of the last position ocupped by the interator in object's coordenates
	 * (without OpenGL's transforms).
	 * 
	 * @param void.
	 * @return CybVector3D<float> The interator position in object coordenates.
	 * 
	 */
  	CybVector3D<float> getLastInteratorPositionInObjectCoordenates();
  	
  	/**
	 * This method gets the values of the last position ocupped by the interator in graphics scene,
	 * (with OpenGL's transforms).
	 *
	 * @param void.
	 * @return CybVector3D<float> The interator position in graphics coordenates.
	 * 
	 */
  	CybVector3D<float> getLastInteratorPositionInGraphicsCoordenates();
  	
  	/**
  	 * This method indicates if the atual point is equal the last point.
  	 * 
  	 * @param void
  	 * @return bool If the atual point is equal last point.
  	 * 
  	 */  	
  	bool isEqualLastPosition();
	
	/**
	 * This method sets the position ocupped by the interator in object's coordenates.
	 *
	 * @param float x the coordenate in axis x of new position.
	 * @param float y the coordenate in axis y of new position.
	 * @param float z the coordenate in axis z of new position.
	 * @return void.
	 * 
	 */
  	void setInteratorPositionInObjectCoordenates(float x, float y, float z);
  	
  	/**
	 * This method sets the values of the position ocupped by the interator in graphics coordenates.
	 *
	 * @param float x the coordenate in axis x of graphics scene.
	 * @param float y the coordenate in axis y of graphics scene.
	 * @param float z the coordenate in axis z of graphics scene.
	 * @return void.
	 */
 	void setInteratorPositionInGraphicsCoordenates(float x, float y, float z);	
};

#endif /*_CYB_COLLISIONDATA_H_*/

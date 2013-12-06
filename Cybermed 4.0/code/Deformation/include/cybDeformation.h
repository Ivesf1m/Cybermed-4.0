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

#ifndef _CYB_DEFORMATION_H_
#define _CYB_DEFORMATION_H_

#include "cybThread.h"
#include "cybNarrowCollision.h"

	enum EnumDefMode		//define if the deformation only goes or back to the initial point
	{
		DEF_GO_AND_BACK,	/**> Define if the deformation backs to his initial state. */		
		DEF_ONLY_GO			/**> Define if the deformation only goes to final state and stop there. */
	};

/**
 * @class CybDeformation 
 * @file cybDeformation.h 
 * @short Deformation SUPER class
 *
 * This class do the deformation in an object in graphics scene.
 * It specifies how the deformation must to occur.
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */
 
class CybDeformation : public CybThread
{
	
protected:
	CybNarrowCollision *collisionObject;	/**< A reference to collision object associaded with this object. */
	float damping;							/**< The damping mesh defined in CybParameters. */
	float stiffness;						/**< The stifness mesh in CybParameters. */
	float mass;							/**< The mass correspondent to points of object associated. */
	float error;							/**< It indicates the error aceptable. */
	float step;								/**< It stores the step of dicrete calculus. */
	CybParameters *cybCore;					/**< Data reference. */
	
private:
	EnumDefMode deformationMode;	/**< Indicates the modo in operation in deformation routines (DEF_GO_AND_BACK or DEF_ONLY_GO). */
		
public:

	/**
	 * Construcutor
	 * 
	 * @param CybNarrowCollision *collisionObject A reference to a collision object.
	 * @param int defMode The mode that the collision will be worked (By default, it's initialized like DEF_GO_AND_BACK). 
	 * 
	 */
	CybDeformation(CybNarrowCollision *collisionObject, EnumDefMode deformationMode = DEF_GO_AND_BACK);
	
	/**
	 * This method returns a reference to the collision object associaded.
	 * 
	 * @param void.
	 * @return CybNarrowCollision* A reference to the collision object associaded.
	 * 
	 */
	CybNarrowCollision* getCollisionObject();
	
	/**
	 * This method returns the damping associated with the deformable layer.
	 * 
	 * @param void.
	 * @return float The damping associated.
	 * 
	 */
	inline float getDamping();
	
	/**
	 * This method returns the mode of deformation (DEF_GO_AND_BACK or DEF_ONLY_GO).
	 * 
	 * @param void.
	 * @return int The mode of deformation.
	 * 
	 */	
	EnumDefMode getDeformationMode();
	
	/**
	* This method returns the aceptable error. 
	* 
	* @param void
	* @return float The error.
	*
	*/
	inline float getError();
	
	/**
	* This method returns the step used in discrete calculus. 
	*
	* @param void
	* @return float The step.
	*
	*/
	inline float getStep();
	
	/**
	 * This method returns the stiffness associated with the deformable layer.
	 * 
	 * @param void.
	 * @return float The stiffness associated.
	 * 
	 */	
	inline float getStiffness();
	
	/**
	 * This method creates this object thread. 
	 * It habilitates the thread to the call the run() method declarated in any son of this class.
	 * The template indicates the Son that implements the run() method.
	 * 
	 * @param void
	 * @return void
	 * 
	 */
	 virtual void init();
	 
	 /**
	 * This method sets the error for aproximation in calculus in this object.
	 *
	 * @param float error The atual error associated.
	 * @return void
	 *
	 */
	 void setError(float error);
	 
	 /**
	 * This method sets the step for aproximation in calculus in this object.
	 *
	 * @param float step The atual error associated.
	 * @return void
	 *
	 */
	 void setStep(float step);
	 
	 /**
	  * This method updates the damping	and the stiffness of mesh
	  * before the deformation method to be called.
	  * 
	  * @param void.
	  * @param void.
	  * 
	  */
	 virtual void update();
};

#endif /*_CYB_DEFORMATION_H_*/

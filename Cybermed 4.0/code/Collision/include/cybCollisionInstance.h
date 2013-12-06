// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2011 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba.
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

#ifndef _CYB_COLLISIONINSTANCE_H_
#define _CYB_COLLISIONINSTANCE_H_

#include "cybCollision.h"
#include <string>
#include <cybermed/cybInterator.h>

/**
 * @class CybCollisionInstance
 * @file cybCollisionInstance.h 
 * @short Class for instantiating collision test objects.
 *
 * This class relates to collision objects in order to know the result of the collision test between them.
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 2.2
 * @date 2011, November
 * 
 */

class CybCollisionInstance
{
	public:
		/** Constructor 
		* 
	 	* @param CybCollision* obj1: the first collision object.
		* @param CybCollision* obj2: the second collision object.
	 	* @param string type: the type of collision (broad or narrow)
	 	*/
		CybCollisionInstance(CybCollision *, CybCollision *,  string);
		/*
		* Getter for the first object's pointer.
		*
		* @param void
		* @return CybCollision*: the first object's pointer.
		*/
		CybCollision* getFirstCollisionObject();
		/*
		* Getter for the second object's pointer.
		*
		* @param void
		* @return CybCollision*: the second object's pointer.
		*/
		CybCollision* getSecondCollisionObject();
		/*
		* Getter for the type of collision.
		*
		* @param void
		* @return string: type of collision.
		*/
		string getTypeOfCollision();
		/*
		* Getter for the status of collision.
		*
		* @param void
		* @return bool: status of collision between the two objects.
		*/
		bool getStatus();
		/*
		* Setter for the status of collision.
		*
		* @param bool status: the new status
		* @return void
		*/
		void setStatus(bool);
		/*
		* Prints a description for this instance.
		*
		* @param void
		* @return void
		*/
		void toString();
	private:
		CybCollision* firstObject;		//pointer to the first object.
		CybCollision* secondObject;		//pointer to the second object.
		string typeOfCollision;			//the type of collision in this instance (broad or narrow)
		bool status;				//the collision status between these two objects.
};

#endif //_CYB_COLLISIONINSTANCE_H_

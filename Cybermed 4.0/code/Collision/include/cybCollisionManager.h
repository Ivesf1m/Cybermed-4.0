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

#ifndef _CYB_COLLISIONMANAGER_H_
#define _CYB_COLLISIONMANAGER_H_

#include "cybThread.h"
#include "cybParameters.h"
#include "cybCollisionObserver.h"
#include "cybCollisionListener.h"
#include "cybCollisionInstance.h"
#include "cybCollision.h"
#include "cybSphereTriangle.h"

/**
 * @class CybCollisionManager
 * @file cybCollisionManager.h 
 * @short Collision Listener concrete class.
 *
 *  This class manages a specific collision object, notifying instances when necessary.
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 2.2
 * @date 2011, November
 */

class CybCollisionManager : public CybThread, CybCollisionListener
{
	public:
		/*
		* Constructor 1.
		*
		* @param CybCollision* obj: a pointer to the collision object that will be managed by this object.
		* @param bool interator: true if the collision object is related to an interator, false otherwise.
		* @param bool activateNarrow: true if narrow collision shall be used with this object, false otherwise.
		*/
		CybCollisionManager(CybCollision*, bool, bool);
		/*
		* Constructor 2.
		*
		* @param CybCollision* obj: a pointer to the collision object that will be managed by this object.
		* @param bool interator: true if the collision object is related to an interator, false otherwise.
		*/
		CybCollisionManager(CybCollision*, bool);
		/*
		* Destructor.
		*
		* @param void
		*/
		~CybCollisionManager();
		/*
		* Getter for the collision status.
		*
		* @param void
		* @return bool: the collision status.
		*/
		bool getCollisionStatus();
		/*
		* This method informs if narrow collision is activated within this object.
		*
		* @param void
		* @return bool: true if narrow is activated, false otherwise.
		*/
		bool isNarrowActivated();
		/*
		* This method notifies a collision instance about the collision object's status.
		*
		* @param CybCollisionInstance* instance: a pointer to the instance that will be notified.
		* @return void
		*/
		void notification(CybCollisionInstance*);
		/*
		* This method executes the tasks assigned to this object.
		*
		* @param void
		* @return void
		*/
		void run();
	private:
		CybCollision* collisionObject;		//A pointer to the collision object.
		CybParameters* cybcore;			//A pointer to the parameters object.
		bool collisionStatus;			//The collision status of this object.
		bool interatorManager;			//Tells if the collision object is related to an interator.
		CybSphereTriangle* narrowObject;	//Narrow collision object.	
};

#endif //_CYB_COLLISIONMANAGER_H_

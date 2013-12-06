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

#ifndef _CYB_COLLISIONOBSERVER_H_
#define _CYB_COLLISIONOBSERVER_H_

#include "cybCollision.h"
#include "cybCollisionInstance.h"
#include "cybCollisionListener.h"
#include <list>
#include <string>

/**
 * @class CybCollisionObserver 
 * @file cybCollisionObserver.h 
 * @short Observer object for collision.
 *
 * This class observes the state of collision of all the existent objects and notifies
 * their respective listeners. 
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 2.2
 * @date 2011, November
 */

class CybCollisionObserver
{
	public:
		/*
		* This method adds a listener (a pointer) to the list of listeners.
		*
		* @param CybCollisionListener* listener: the listener to be added.
		* @return void
		*/
		void addListener(CybCollisionListener*);
		/* The method adds a collision object (a pointer) to the list of objects.
		*
		* @param CybCollision* obj: the object to be added.
		* @param string type: the collision type of the added object.
		* @return void
		*/
		void addCollisionObject(CybCollision*, string);
		/*
		* This method updates the state of collision of the instance that contains the 
		* two collision objects passed as parameters.
		*
		* @param CybCollision* obj1: the first collision object.
		* @param CybCollision* obj2: the second collision object.
		* @param bool state: the new state of collision.
		* @return void
		*/
		void changeState(CybCollision*, CybCollision*, bool);
		/*
		* This method creates new collision instances associated to the last collision
		* object added.
		*
		* @param string type: the type of collision instance that must be created.
		* @return void
		*/		
		void createInstances(string);
		/*
		* This method is used to access the only instance of this class (Singleton Pattern)
		*
		* @param void
		* @return CybCollisionObserver*: an instance of this class.
		*/
		static CybCollisionObserver* getInstance();
		/*
		* This method notifies the other instances about the changes in the instance passed as parameter.
		* 
		* @param CybCollisionInstance* instance: the changed instance.
		* @return void
		*/
		void notifyListeners(CybCollisionInstance*);
		/*
		* This method removes a listener from the list.
		*
		* @param CybCollisionListener* listener: the listener to be removed.
		* @return void
		*/
		void removeListener(CybCollisionListener*);
	private:
		/*
		* Private constructor.
		*
		* @param void
		*/	
		CybCollisionObserver();	

					
		static CybCollisionObserver* instance;			//the only instance of this class.
		list<CybCollision*> collisionObjects;			//the list of collision objects.
		list<CybCollisionInstance*> collisionInstances;		//the list of collision instances.
		list<CybCollisionListener*> collisionListeners;		//the list of collision listeners.
		int numListeners;					//the number of listeners.
		int numObjects;						//the number of collision objects.
		int numInstances;					//the number of collision instances.
		static int currentIndex;				//the current collision object index.

};


#endif //_CYB_COLLISIONOBSERVER_H_

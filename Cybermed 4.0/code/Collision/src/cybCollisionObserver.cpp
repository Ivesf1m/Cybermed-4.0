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

#include "cybCollisionObserver.h"
#include "cybThread.h"

CybCollisionObserver* CybCollisionObserver::instance = NULL;
int CybCollisionObserver::currentIndex = 0;

CybCollisionObserver::CybCollisionObserver()
{
	numListeners = 0;
	numObjects = 0;
	numInstances = 0;
}

void CybCollisionObserver::addListener(CybCollisionListener* listener)
{
	collisionListeners.push_back(listener);
	++numListeners;
}

void CybCollisionObserver::addCollisionObject(CybCollision* object, string type)
{
	object->setObjectIndex(currentIndex++);
	collisionObjects.push_back(object);
	++numObjects;	
	if(numObjects > 1) createInstances(type);
}

void CybCollisionObserver::changeState(CybCollision* obj1, CybCollision* obj2, bool state)
{
	CybCollisionInstance* aux;	
	list<CybCollisionInstance*>::iterator it;
	for(it = collisionInstances.begin(); it != collisionInstances.end(); ++it)
	{	
		CybCollision* colOb1 = (*it)->getFirstCollisionObject();
		CybCollision* colOb2 = (*it)->getSecondCollisionObject();
		if(colOb1->getObjectIndex() == obj1->getObjectIndex() &&
		   colOb2->getObjectIndex() == obj2->getObjectIndex()){
			aux = (*it);
			break;
		}else if(colOb1->getObjectIndex() == obj2->getObjectIndex() &&
			 colOb2->getObjectIndex() == obj1->getObjectIndex()){
			aux = (*it);
			break;
		}else aux = NULL;
	}
	if(!aux) return;	
	if(aux->getStatus() != state)
	{
		aux->setStatus(state);
		notifyListeners(aux);
	}
}

void CybCollisionObserver::createInstances(string type)
{
	list<CybCollision*>::iterator it;
	CybCollision* novo = *(--collisionObjects.end());	
	for(it = --collisionObjects.end(); it != collisionObjects.begin(); --it)
	{
		if(*(it) == novo) continue;
		CybCollisionInstance* newInstance = new CybCollisionInstance(novo, *it, type);
		collisionInstances.push_back(newInstance);
	}
	CybCollisionInstance* beginInstance = new CybCollisionInstance(novo, *collisionObjects.begin(), type);
	collisionInstances.push_back(beginInstance);
}

CybCollisionObserver* CybCollisionObserver::getInstance()
{
	if(!instance) instance = new CybCollisionObserver();
	return instance;
}

void CybCollisionObserver::notifyListeners(CybCollisionInstance* instance)
{
	list<CybCollisionListener*>::iterator it;
	for(it = collisionListeners.begin(); it != collisionListeners.end(); ++it)
	{
		(*it)->notification(instance);
	}
}


void CybCollisionObserver::removeListener(CybCollisionListener* observer)
{
	collisionListeners.remove(observer);
	--numListeners;
}


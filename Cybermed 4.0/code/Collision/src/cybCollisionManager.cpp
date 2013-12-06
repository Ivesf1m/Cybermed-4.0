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

#include "cybCollisionManager.h"
#include <iostream>

using namespace std;

CybCollisionManager::CybCollisionManager(CybCollision* obj, bool interator, bool activateNarrow)
{
	collisionObject = obj;
	interatorManager = interator;
	if(activateNarrow) narrowObject = new CybSphereTriangle(obj->getLayerOfCollision(), obj->getInterator());
	else narrowObject = NULL;
	cybcore = CybParameters::getInstance();
	this->setTime(50);
	CybCollisionObserver::getInstance()->addListener(this);
	narrowObject->init();
}

CybCollisionManager::CybCollisionManager(CybCollision* obj, bool interator)
{
	collisionObject = obj;
	interatorManager = interator;
	narrowObject = NULL;
	cybcore = CybParameters::getInstance();
	this->setTime(50);
	CybCollisionObserver::getInstance()->addListener(this);
}

CybCollisionManager::~CybCollisionManager()
{
	cout << "Gerenciador de colisoes destruido" << endl;
}

bool CybCollisionManager::getCollisionStatus()
{
	return collisionStatus;
}

bool CybCollisionManager::isNarrowActivated()
{
	return (narrowObject ?  true : false);
}

void CybCollisionManager::notification(CybCollisionInstance* inst)
{
	if(inst->getFirstCollisionObject() == collisionObject ||
	   inst->getSecondCollisionObject() == collisionObject)
	{
		collisionStatus = inst->getStatus();
	}
}

void CybCollisionManager::run()
{
	CybThread::lock();
	if(collisionStatus){
		if(interatorManager) collisionObject->getInterator()->setColor(1,0,0,1);
		else cybcore->setColor(collisionObject->getLayerOfCollision(),1,0,0,1);
		if(narrowObject)
		{
			if(narrowObject->isHabilitated()); //vazio intencional
			else narrowObject->start();
			if(narrowObject->getCollisionStatus())
			{
				cybcore->setColor(narrowObject->getLayerOfCollision(), 0,0,1,1);
				narrowObject->getInterator()->setColor(0,0,1,1);
			}else; //vazio intencional
		}		
	}else{
		if(interatorManager) collisionObject->getInterator()->setColor(0,1,0,1);
		else cybcore->setColor(collisionObject->getLayerOfCollision(),0,1,0,1);
		if(narrowObject && narrowObject->isHabilitated()) narrowObject->stop();
	}
	CybThread::unlock();
}

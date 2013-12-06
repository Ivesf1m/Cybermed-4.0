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

CybCollision::CybCollision(int layer, int interatorId) : CybThread()
{
	this->collisionStatus  = false;			// Collision is not habilitated
	this->layerOfCollision = layer;  		// layer that the collision method verifies the collision (default)

	CybParameters* cybCore = CybParameters::getInstance();
	this->interator 	   = cybCore->getInterator(interatorId);
}

CybCollision::CybCollision(int layer, CybInterator* interator) : CybThread()
{
	this->collisionStatus  = false;			// Collision is not habilitated
	this->layerOfCollision = layer;  		// layer that the collision method verifies the collision (default)

	this->interator 	   = interator;
}

	
	/** Destructor */ 
	CybCollision::~CybCollision()
	{
	
	}    	
	
	bool CybCollision::getCollisionStatus()
	{
		return this->collisionStatus;
	}	
	
	int CybCollision::getLayerOfCollision()
	{
		return this->layerOfCollision;
	} 
	
	CybInterator* CybCollision::getInterator() {
		return this->interator;
	}

	int CybCollision::getObjectIndex()
	{
		return objectIndex;
	}

	bool CybCollision::isEqualLastCollision()
	{
		return this->is_equal_last_collision;
	} 
	
	void CybCollision::setInterator(CybInterator* interator) {
		this->interator = interator;
	}

	void CybCollision::setObjectIndex(int id)
	{
		objectIndex = id;
	}

	void CybCollision::update()
	{
		CybThread::lock();
		
			CybVector3D<float> position = interator->getPosition();
			CybCollisionData::getInstance()->setInteratorPositionInGraphicsCoordenates(position[0], position[1], position[2]);   		// The interator coordenates are in graphics scene.
		
		CybThread::unlock();

		this->is_equal_last_collision = (CybCollisionData::getInstance())->isEqualLastPosition(); 
	}

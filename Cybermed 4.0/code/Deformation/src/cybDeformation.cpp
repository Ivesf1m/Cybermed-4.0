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

#include "cybDeformation.h"

	CybDeformation::CybDeformation(CybNarrowCollision *collisionObject, EnumDefMode deformationMode) : CybThread()
	{
		this->deformationMode = deformationMode;
		this->collisionObject = collisionObject;
		this->error = 0.0001f;
		this->step = 0.08f;
		cybCore = CybParameters::getInstance();		
	}
 
	CybNarrowCollision* CybDeformation::getCollisionObject()
	{
		return this->collisionObject;		
	}
	
	float CybDeformation::getDamping()
	{
		return this->damping;
	}

	EnumDefMode CybDeformation::getDeformationMode()
	{
		return this->deformationMode;
	}		
	   
	float CybDeformation::getError()
	{
		return this->error;
	}
	
	float CybDeformation::getStep()
	{
		return this->step;
	}
		
	float CybDeformation::getStiffness()
	{
		return this->stiffness;
	}
		
	void CybDeformation::init()
	{
		CybThread::init();
		collisionObject->init();	//creates the thread of collision object associated	
	}
	
	void CybDeformation::setError(float error)
	{
		this->error = error;
	}
	
	void CybDeformation::setStep(float step)
	{
		this->step = step;
	}
	
	void CybDeformation::update()
	{
		this->damping = cybCore->getMaterialPropertyValue(this->collisionObject->getLayerOfCollision(),DAMPING);
		this->stiffness = cybCore->getMaterialPropertyValue(this->collisionObject->getLayerOfCollision(),STIFFNESS);
		this->mass = cybCore->getMaterialPropertyValue(this->collisionObject->getLayerOfCollision(),MASS);
	}

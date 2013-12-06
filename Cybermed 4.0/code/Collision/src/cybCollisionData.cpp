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

#include "cybCollisionData.h"

CybCollisionData* CybCollisionData::singletonInstance = NULL;

	/** Constructor. */
	CybCollisionData::CybCollisionData() 
	{ 
		cybCore = CybParameters::getInstance();	
		this->is_equal_last_position = false;
	}	
	
	
	/** Destructor. */
	CybCollisionData::~CybCollisionData()	
	{ 
		delete CybCollisionData::singletonInstance;		
	}

	CybVector3D<float> CybCollisionData::getDirectionInObjectCoordenates()
	{
		return this->directionInObjectCoordenates;	
	}
  	
  	CybVector3D<float> CybCollisionData::getDirectionInGraphicsCoordenates()
  	{
  		return this->directionInGraphicsCoordenates;  		
  	}
  	
  	CybCollisionData* CybCollisionData::getInstance()
  	{
		if(CybCollisionData::singletonInstance == NULL)
			CybCollisionData::singletonInstance = new CybCollisionData();

  		return CybCollisionData::singletonInstance;	
  	}

	CybVector3D<float> CybCollisionData::getInteratorPositionInObjectCoordenates()
  	{
  		return this->interatorPositionInObjectCoordenates;
  	}  	
  	
  	CybVector3D<float> CybCollisionData::getInteratorPositionInGraphicsCoordenates()
  	{
  		return this->interatorPositionInGraphicsCoordenates;
  	}  	
  	
  	CybVector3D<float> CybCollisionData::getLastInteratorPositionInObjectCoordenates()
  	{
  		return this->lastInteratorPositionInObjectCoordenates;
  	}  	
  	
  	CybVector3D<float> CybCollisionData::getLastInteratorPositionInGraphicsCoordenates()
  	{
  		return this->lastInteratorPositionInGraphicsCoordenates;
  	}  	
  	
  	bool CybCollisionData::isEqualLastPosition()
  	{	
  		return this->is_equal_last_position;
  	}
  	
  	void CybCollisionData::setInteratorPositionInObjectCoordenates(float x, float y, float z)
  	{
		CybVector3D<float> p(x,y,z);

		this->lastInteratorPositionInObjectCoordenates = this->interatorPositionInObjectCoordenates;  		//the last is the atual
		this->lastInteratorPositionInGraphicsCoordenates = this->interatorPositionInGraphicsCoordenates;

		this->interatorPositionInObjectCoordenates(x,y,z);	// Stores the atual state	

		// calculate the coordenates in graphics scene
		this->interatorPositionInGraphicsCoordenates = CybPointOperator::executTransformation(this->interatorPositionInObjectCoordenates, 0);

		//claculates the direction
		this->directionInObjectCoordenates = this->interatorPositionInObjectCoordenates - this->lastInteratorPositionInObjectCoordenates;
		this->directionInGraphicsCoordenates = this->interatorPositionInGraphicsCoordenates -      this->lastInteratorPositionInGraphicsCoordenates;

		if(this->directionInObjectCoordenates == CybVector3D<float>(0,0,0))
			this->is_equal_last_position = true;
		else 
			this->is_equal_last_position = false;
  	}
  	
 	void CybCollisionData::setInteratorPositionInGraphicsCoordenates(float x, float y, float z)
 	{
 		CybVector3D<float> p(x,y,z);
		
		this->lastInteratorPositionInObjectCoordenates = this->interatorPositionInObjectCoordenates;
		this->lastInteratorPositionInGraphicsCoordenates = this->interatorPositionInGraphicsCoordenates;

		this->interatorPositionInGraphicsCoordenates(x,y,z);

		if(cybCore->transforChange)
		{
			CybPointOperator::calculateInverseMatrix(0);	// calculate the inverse matrix	
			cybCore->transforChange = false;
		}

		this->interatorPositionInObjectCoordenates = CybPointOperator::executInverseTransformation(this->interatorPositionInGraphicsCoordenates, 0);

		this->directionInObjectCoordenates = this->interatorPositionInObjectCoordenates - this->lastInteratorPositionInObjectCoordenates;
		this->directionInGraphicsCoordenates = this->interatorPositionInGraphicsCoordenates - this->lastInteratorPositionInGraphicsCoordenates;
		    
		if(this->directionInObjectCoordenates == CybVector3D<float>(0,0,0))
			this->is_equal_last_position = true;
		else 
			this->is_equal_last_position = false;
 	}   	


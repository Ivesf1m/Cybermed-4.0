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
 
#include "cybNarrowCollision.h"

	CybNarrowCollision::CybNarrowCollision(int layer, int interatorId) : CybCollision(layer, interatorId)
	{
		this->triangleOfCollision = -1;	
		this->vertexOfCollision = -1;	
		this->broadObject = NULL;
	}
	
	CybNarrowCollision::CybNarrowCollision(int layer, CybInterator* interator) : CybCollision(layer, interator)
	{
		this->triangleOfCollision = -1;
		this->vertexOfCollision   = -1;
		this->broadObject 		  = NULL;
	}

	CybNarrowCollision::CybNarrowCollision(CybBroadCollision* broadObject) : CybCollision(broadObject->getLayerOfCollision(), broadObject->getInterator())
	{
		this->triangleOfCollision = -1;
		this->vertexOfCollision = -1;
		this->broadObject = broadObject;
	}

	CybNarrowCollision::~CybNarrowCollision()
	{
		this->destroy();
	}

	void CybNarrowCollision::destroy()
	{
		CybThread::destroy();
		if(this->broadObject != NULL) this->broadObject->destroy();
	}
	
	CybBroadCollision* CybNarrowCollision::getBroadCollisionObject()
	{
		return this->broadObject;
	}
	
	CybVector3D<float> CybNarrowCollision::getPointOfCollision()
	{
		return this->pointOfCollision;
	}
	
	int CybNarrowCollision::getTriangleOfCollision()
	{
		return this->triangleOfCollision;
	}
	
	int CybNarrowCollision::getVertexOfCollision()
	{
		return this->vertexOfCollision;
	}
	
	void CybNarrowCollision::init()
	{
		CybThread::init();
		//criates the broad object thread
		if(this->broadObject != NULL) this->broadObject->init();	
	}
	
	void CybNarrowCollision::verifiesInteratorSide()
	{	
		cybTriCell<cybSurfaceTriTraits> *cell;
		cybMesh<cybSurfaceTriTraits> *mesh;
		int vId;	
		CybVector3D<float> normal;
		static int propertyFace;
	
		if(this->collisionStatus == true)	//if there was collision
		{		
			CybParameters* cybCore = CybParameters::getInstance();	
			//gets the face propriety
			propertyFace = cybCore->getLayerFace(this->layerOfCollision);	
	
			mesh = cybCore->mesh[this->layerOfCollision];
			cell = mesh->getCell(triangleOfCollision);
			mesh->updateCellNormalVector(triangleOfCollision);
			normal = cell->getNormal();		// and get the triangle of collision normal
	
			this->triangleNormal[0] = normal[0];
			this->triangleNormal[1] = normal[1];
			this->triangleNormal[2] = normal[2];
	
			this->vectorCollision = (CybCollisionData::getInstance())->getInteratorPositionInObjectCoordenates() - this->pointOfCollision; 	
	
			//if the dirction and the shift direction are in same direction
			if(((100*this->triangleNormal)^(100*CybCollisionData::getInstance()->getDirectionInObjectCoordenates())) >= 0.0f)	
			{		
				if(propertyFace == FRONT)	//sets the collision as false because the interator is inside the object
				{
					this->collisionStatus = false;
					this->triangleOfCollision = -1;
				}
			}
			else
				if(propertyFace == BACK) //sets the collision as false because the interator is outside the object
				{
					this->collisionStatus = false;
					this->triangleOfCollision = -1;
				}
		}		
	}
	
	void CybNarrowCollision::update()
	{
		CybCollision::update();
	
		if(this->broadObject != NULL)	//if exists an broad object
		{
			if(this->broadObject->getListOfTrianglesReference()->size() != 0) //and the list is full
			{
				this->collision(this->broadObject->getListOfTrianglesReference());	//collision wirh some triangles
				CybNarrowCollision::verifiesInteratorSide(); // verifies the collision with the face proprietities
				this->setIsHablitated(false);	// don't call the collision method
			}  
		}
	}

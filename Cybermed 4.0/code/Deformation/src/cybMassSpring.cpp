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
	
#include "cybMassSpring.h"

	CybMassSpring::CybMassSpring(CybNarrowCollision *collision, EnumDefMode defMode) : CybDeformation(collision, defMode)
	{
		this->vertex_number = CybParameters::getInstance()->nv[this->collisionObject->getLayerOfCollision()];
		this->nodes = new CybMassSpringNode[this->vertex_number];
		this->intensity = 1.0;
		this->initED();	
	}
	
	
	CybMassSpring::~CybMassSpring()
	{
		delete[] this->nodes;
	}
	
	void CybMassSpring::applyForce(CybVector3D<float> force, int vertexId)
	{
		CybThread::lock();
		
		CybVector3D<float> shift, p,f;	
		sMesh* mesh = CybParameters::getInstance()->mesh[collisionObject->getLayerOfCollision()];
	
		// calculate the acceleration and velocity of the point
		this->nodes[vertexId].update_acceleration_velocity(force, this->mass,this->step,this->stiffness);	
	
		//calculate the shift
		shift = this->step*(this->nodes[vertexId].velocity);
		
		this->nodes[vertexId].vertex->setCoord(0,this->nodes[vertexId].vertex->getCoord(0) + shift[0]);
		this->nodes[vertexId].vertex->setCoord(1,this->nodes[vertexId].vertex->getCoord(1) + shift[1]);
		this->nodes[vertexId].vertex->setCoord(2,this->nodes[vertexId].vertex->getCoord(2) + shift[2]);	
	
		CybThread::unlock();
	
		for(int i=0; i < nodes[vertexId].neighbors.size(); i++)
		{
			CybThread::lock();
			//  force applied in each neighbor point
			f = this->damping*shift; 
	
			this->nodes[this->nodes[vertexId].neighbors.pos(i)].update_acceleration_velocity(force, this->mass,this->step,this->stiffness);
	
			shift = this->step*(this->nodes[this->nodes[vertexId].neighbors.pos(i)].velocity);
		
			//Set the new point
			this->nodes[this->nodes[vertexId].neighbors.pos(i)].vertex->setCoord(0,this->nodes[this->nodes[vertexId].neighbors.pos(i)].vertex->getCoord(0) + shift[0]);
			this->nodes[this->nodes[vertexId].neighbors.pos(i)].vertex->setCoord(1,this->nodes[this->nodes[vertexId].neighbors.pos(i)].vertex->getCoord(1) + shift[1]);
			this->nodes[this->nodes[vertexId].neighbors.pos(i)].vertex->setCoord(2,this->nodes[this->nodes[vertexId].neighbors.pos(i)].vertex->getCoord(2) + shift[2]);	
	
			CybThread::unlock();
		}		
	}
	
	void CybMassSpring::applyForceAllPoints()
	{
		CybThread::lock();
		CybVector3D<float> shift, force, f;
		float d;
		sMesh* mesh = CybParameters::getInstance()->mesh[collisionObject->getLayerOfCollision()];
	
		for(int i=0; i < this->vertex_number; i++)
		{
			if(((this->nodes[i].velocity)^(this->nodes[i].velocity)) > this->error || ((this->nodes[i].acceleration)^(this->nodes[i].acceleration)) > this->error)
			{
				force[0] = this->nodes[i].vertex->getCoord(0);
				force[1] = this->nodes[i].vertex->getCoord(1);
				force[2] = this->nodes[i].vertex->getCoord(2);
	
				force = this->damping*(this->nodes[i].point - force);
				this->nodes[i].update_acceleration_velocity(force, this->mass,this->step,this->stiffness);
	
				shift = this->step*(this->nodes[i].velocity);
				
				this->nodes[i].vertex->setCoord(0,this->nodes[i].vertex->getCoord(0) + shift[0]);
				this->nodes[i].vertex->setCoord(1,this->nodes[i].vertex->getCoord(1) + shift[1]);
				this->nodes[i].vertex->setCoord(2,this->nodes[i].vertex->getCoord(2) + shift[2]);
					
			}else
			{				
				this->nodes[i].vertex->setCoord(0,this->nodes[i].point[0]);
				this->nodes[i].vertex->setCoord(1,this->nodes[i].point[1]);
				this->nodes[i].vertex->setCoord(2,this->nodes[i].point[2]);
			}
		}
		
		CybThread::unlock();
	
	}
	
	void CybMassSpring::initED()
	{
		vIterator vIterator(CybParameters::getInstance()->mesh[this->collisionObject->getLayerOfCollision()]);
		vStarIterator itvs(CybParameters::getInstance()->mesh[this->collisionObject->getLayerOfCollision()]);
		CybMassSpringNode *node = NULL;
		int nvertex = 0;
	
		for(vIterator.initialize(),nvertex=0; vIterator.notFinish(); ++vIterator,nvertex++)
		{	
			node = &this->nodes[nvertex];
	
			node->vertex = *vIterator;
	
			node->point[0] = node->vertex->getCoord(0);
			node->point[1] = node->vertex->getCoord(1);
			node->point[2] = node->vertex->getCoord(2);
	
			// get the neighbors
			for( itvs.initialize( nvertex ); itvs.notFinish(); ++itvs) 	
				node->neighbors.insertOnlyOne(itvs->getVertexId( (itvs->getVertexIndex(nvertex)+1)%3));

			for( itvs.initialize( nvertex ); itvs.notFinish(); ++itvs) 	
				node->neighbors.insertOnlyOne(itvs->getVertexId( (itvs->getVertexIndex(nvertex)+2)%3));

			node->neighbors.erase(node->neighbors.search(nvertex));	//remove the index of original point
		}	
	}

	void CybMassSpring::run()
	{		
		if(collisionObject->getCollisionStatus() && collisionObject->getTriangleOfCollision() >= 0)
		{
			//if(!collisionObject->isEqualLastCollision())
			//{							
				this->applyForce(this->intensity*CybCollisionData::getInstance()->getDirectionInObjectCoordenates(), CybParameters::getInstance()->mesh[this->collisionObject->getLayerOfCollision()]->getCell(this->collisionObject->getTriangleOfCollision())->getVertexId(this->collisionObject->getVertexOfCollision()));
			//}		
		}		
		else
		{
			if(this->getDeformationMode() == DEF_GO_AND_BACK)
				this->applyForceAllPoints();
		}
	}
	
	void CybMassSpring::setIntensity(float intensity)
	{
	    this->intensity = intensity;
	}
	
	float CybMassSpring::getIntensity()
	{
	    return this->intensity;
	}
	

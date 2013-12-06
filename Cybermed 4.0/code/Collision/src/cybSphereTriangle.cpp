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

#include "cybSphereTriangle.h"
	
	CybSphereTriangle::CybSphereTriangle(int layer, int interatorId) : CybNarrowCollision(layer, interatorId)
	{
		this->radius = 1;

		this->ver0 = &vertex[0];
		this->ver1 = &vertex[1];
		this->ver2 = &vertex[2];
	}
	
	CybSphereTriangle::CybSphereTriangle(int layer, CybInterator* interator) : CybNarrowCollision(layer, interator)
	{
		this->radius = 1;

		this->ver0 = &vertex[0];
		this->ver1 = &vertex[1];
		this->ver2 = &vertex[2];
	}
	

	/**
	 * Constructor.
	 * 
	 * @param CybBroadCollision* broadObject The broad collision object associated.
	 * 
	 */
	CybSphereTriangle::CybSphereTriangle(CybBroadCollision* broadObject) : CybNarrowCollision(broadObject)
	{
		this->radius = 1;
	
		this->ver0 = &vertex[0];
		this->ver1 = &vertex[1];
		this->ver2 = &vertex[2];
	}
	
	void CybSphereTriangle::collision(mfList<sCell *>* list)
	{
		sphereCenter = CybCollisionData::getInstance()->getInteratorPositionInObjectCoordenates();	//copy the interator location
		CybParameters* cybCore = CybParameters::getInstance();	
		// if there wasn't collision then return false
		// it sweeps all the triangle's list
		CybThread::lock();
		this->collisionStatus = false; 
		this->triangleOfCollision = -1;
		CybThread::unlock();
		
		for(triangle = 0; triangle < list->size(); triangle++)	//verifies all the triangles of the list
		{
			CybThread::lock();
			pointerPointClosest = &pointClosest;
		
			// gets the reference by the layer
			this->vertex0 = cybCore->mesh[this->layerOfCollision]->getVertex(list->pos(triangle)->getVertexId(0));
			this->vertex1 = cybCore->mesh[this->layerOfCollision]->getVertex(list->pos(triangle)->getVertexId(1)); 
			this->vertex2 = cybCore->mesh[this->layerOfCollision]->getVertex(list->pos(triangle)->getVertexId(2)); 
		
			// it does reference to coordenates the triangles' vertex
			(*this->ver0)[0] = vertex0->getCoord(0);
			(*this->ver0)[1] = vertex0->getCoord(1);
			(*this->ver0)[2] = vertex0->getCoord(2);
	
			(*this->ver1)[0] = vertex1->getCoord(0);
			(*this->ver1)[1] = vertex1->getCoord(1);
			(*this->ver1)[2] = vertex1->getCoord(2);
	
			(*this->ver2)[0] = vertex2->getCoord(0);
			(*this->ver2)[1] = vertex2->getCoord(1);
			(*this->ver2)[2] = vertex2->getCoord(2);
	
			CybThread::unlock();
			
			this->P1_P0 = vertex[1] - vertex[0];
			this->P2_P0 = vertex[2] - vertex[0];
			this->P2_P1 = vertex[2] - vertex[1];
			this->P0_C = vertex[0] - sphereCenter;
			this->P1_C = vertex[1] - sphereCenter;
			this->P2_C = vertex[2] - sphereCenter;
	
			// it counts <p1-p0,p1-c>
			this->delta[0] = (P1_P0^P1_C);
			// it counts -<p1-p0,p0-c>
			this->delta[1] = -(P1_P0^P0_C);
			// it counts <p2-p0,p2-c>
			this->delta[2] = (P2_P0^P2_C);
			// it counts -<p2-p0,p0-c>
			this->delta[3] = -(P2_P0^P0_C);
			// it counts <p2-p1,p2-c>
			this->delta[4] = (P2_P1^P2_C);
			// it counts -<p2-p1,p1-c>
			this->delta[5] = -(P2_P1^P1_C);
	
			// it verifies if the nearest point is vertex of triangle
			if(delta[1]<=0 && delta[3]<=0)
				this->pointerPointClosest = ver0;
			else if(delta[0]<=0 && delta[5]<=0)
				this->pointerPointClosest = ver1;
			else if(delta[2]<=0 && delta[4]<=0)
				this->pointerPointClosest = ver2;
			else
			{
				// it counts the auxiliar determinative
				this->det[0] = delta[0]*delta[4] + delta[5]*(P1_P0^P2_C);
				this->det[1] = delta[1]*delta[2] - delta[3]*(P1_P0^P2_C);
				this->det[2] = delta[3]*delta[0] - delta[1]*(P2_P0^P1_C);
	
				// it verifies if the nearest point is on one of the sides
				if(det[0] <= 0)
				{
					if(det[1] <= 0)
						this->pointerPointClosest = ver2;
					else if(det[2] <= 0)
						this->pointerPointClosest = ver1;
					else
						this->pointClosest = (vertex[1]*delta[4] + vertex[2]*delta[5])/(delta[4]+delta[5]);
				}
				else if(det[1] <= 0)
				{
					if(det[2] <= 0)
						this->pointerPointClosest = ver0;
					else
						this->pointClosest = (vertex[0]*delta[2] + vertex[2]*delta[3])/(delta[2]+delta[3]);
				}
				else if(det[2] <= 0)
					this->pointClosest = (vertex[0]*delta[0] + vertex[1]*delta[1])/(delta[0]+delta[1]);
				else
					this->pointClosest = (vertex[0]*det[0] + vertex[1]*det[1] + vertex[2]*det[2])/(det[0]+det[1]+det[2]);
			}
	
			this->X_C = *(this->pointerPointClosest) - this->sphereCenter;
			// it verifies if the distance between the nearest point and the sphre's center is less that radius
			if((X_C^X_C) <= (radius*radius))
			{
	
				this->pointOfCollision = *(this->pointerPointClosest);
	
				this->vertexOfCollision = CybPointOperator::executVertexAproximation(vertex[0], vertex[1], vertex[2],pointOfCollision); //find the closest vertex
				CybThread::lock();
				this->triangleOfCollision = this->triangle;	// triangle of collision (index of the list in method parameter)
	
				this->collisionStatus = true; // if there was collision then return true and the point of collision	

				CybThread::unlock();
				break;
			}
		} //end of for
	}
	
	void CybSphereTriangle::collision()
	{
		//cout << "passo 1" << endl;
		CybParameters* cybCore = CybParameters::getInstance();	
		cybCellIterator cInterator(cybCore->mesh[this->layerOfCollision]);	// interactive list of triangles of layer referencied for mesh[layer]
		//cout << "passo 2" << endl;
		sphereCenter = (CybCollisionData::getInstance())->getInteratorPositionInObjectCoordenates();
	
		//cout << "passo 3" << endl;
		// if there wasn't collision then return false
		// it sweeps all the triangle's list
		CybThread::lock();
		this->collisionStatus = false; 
		this->triangleOfCollision = -1;
		CybThread::unlock();
		
		for(cInterator.initialize(), triangle = 0; cInterator.notFinish(); ++cInterator, triangle++)
		{
			pointerPointClosest = &pointClosest;
	
			CybThread::lock();
	
			// It obtaines reference to the vertex 0 of triangle instancied by itc
			this->vertex0 = cybCore->mesh[this->layerOfCollision]->getVertex(cInterator->getVertexId(0)); 
			this->vertex1 = cybCore->mesh[this->layerOfCollision]->getVertex(cInterator->getVertexId(1));
			this->vertex2 = cybCore->mesh[this->layerOfCollision]->getVertex(cInterator->getVertexId(2));
	
			//cout << "passo 4" << endl;
			// it does reference to coordenates the triangles' vertex
			(*this->ver0)[0] = vertex0->getCoord(0);
			(*this->ver0)[1] = vertex0->getCoord(1);
			(*this->ver0)[2] = vertex0->getCoord(2);
	
			//cout << "passo 5" << endl;

			(*this->ver1)[0] = vertex1->getCoord(0);
			(*this->ver1)[1] = vertex1->getCoord(1);
			(*this->ver1)[2] = vertex1->getCoord(2);
	
			//cout << "passo 6" << endl;

			(*this->ver2)[0] = vertex2->getCoord(0);
			(*this->ver2)[1] = vertex2->getCoord(1);
			(*this->ver2)[2] = vertex2->getCoord(2);
			CybThread::unlock();
			
			
			this->P1_P0 = vertex[1] - vertex[0];
			this->P2_P0 = vertex[2] - vertex[0];
			this->P2_P1 = vertex[2] - vertex[1];
			this->P0_C = vertex[0] - sphereCenter;
			this->P1_C = vertex[1] - sphereCenter;
			this->P2_C = vertex[2] - sphereCenter;
	
			//cout << "passo 7" << endl;

			// it counts <p1-p0,p1-c>
			this->delta[0] = (P1_P0^P1_C);
			// it counts -<p1-p0,p0-c>
			this->delta[1] = -(P1_P0^P0_C);
			// it counts <p2-p0,p2-c>
			this->delta[2] = (P2_P0^P2_C);
			// it counts -<p2-p0,p0-c>
			this->delta[3] = -(P2_P0^P0_C);
			// it counts <p2-p1,p2-c>
			this->delta[4] = (P2_P1^P2_C);
			// it counts -<p2-p1,p1-c>
			this->delta[5] = -(P2_P1^P1_C);
	
			// it verifies if the nearest point is vertex of triangle
			if(delta[1]<=0 && delta[3]<=0)
				this->pointerPointClosest = ver0;
			else if(delta[0]<=0 && delta[5]<=0)
				this->pointerPointClosest = ver1;
			else if(delta[2]<=0 && delta[4]<=0)
				this->pointerPointClosest = ver2;
			else
			{
				// it counts the auxiliar determinative
				this->det[0] = delta[0]*delta[4] + delta[5]*(P1_P0^P2_C);
				this->det[1] = delta[1]*delta[2] - delta[3]*(P1_P0^P2_C);
				this->det[2] = delta[3]*delta[0] - delta[1]*(P2_P0^P1_C);
	
				// it verifies if the nearest point is on one of the sides
				if(det[0] <= 0)
				{
					if(det[1] <= 0)
						this->pointerPointClosest = ver2;
					else if(det[2] <= 0)
						this->pointerPointClosest = ver1;
					else
						this->pointClosest = (vertex[1]*delta[4] + vertex[2]*delta[5])/(delta[4]+delta[5]);
				}
				else if(det[1] <= 0)
				{
					if(det[2] <= 0)
						this->pointerPointClosest = ver0;
					else
						this->pointClosest = (vertex[0]*delta[2] + vertex[2]*delta[3])/(delta[2]+delta[3]);
				}
				else if(det[2] <= 0)
					this->pointClosest = (vertex[0]*delta[0] + vertex[1]*delta[1])/(delta[0]+delta[1]);
				else
					this->pointClosest = (vertex[0]*det[0] + vertex[1]*det[1] + vertex[2]*det[2])/(det[0]+det[1]+det[2]);
			}
	
			this->X_C = *(this->pointerPointClosest) - this->sphereCenter;
			// it verifies if the distance between the nearest point and the sphre's center is less that radius
			if((X_C^X_C) <= (radius*radius))
			{
				this->pointOfCollision = *(this->pointerPointClosest);			
	
				this->vertexOfCollision = CybPointOperator::executVertexAproximation(vertex[0], vertex[1], vertex[2],pointOfCollision); //find the closest vertex
				CybThread::lock();
				this->triangleOfCollision = this->triangle;	// triangle of collision
	
				this->collisionStatus = true; // if there was collision then return true and the point of collision	

				CybThread::unlock();
				break;
			}
		} //end of for 
	
	} // end of method
	
	float CybSphereTriangle::getRadius()
	{
		return this->radius;
	}
	
	void CybSphereTriangle::setRadius(float radius) {
		this->radius = radius;
	}

	void CybSphereTriangle::run()
	{
		this->collision();
		this->verifiesInteratorSide();	// verifies the collision with the face proprietities
	}

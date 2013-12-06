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

#include "cybFFD.h"

CybFFD::CybFFD(CybNarrowCollision *collision, EnumDefMode defMode): CybDeformation(collision, defMode)
{
	this->parameters = new CybFFDParameters(this->collisionObject->getLayerOfCollision());	
	mesh = CybParameters::getInstance()->mesh[this->collisionObject->getLayerOfCollision()];		
}	


void CybFFD::deformation(CybFFDNode* element)
{
	CybVector3D<float> newPoint;
	CybVector3D<float> coordenate;
	
	coordenate = this->parameters->calculateCoordenate(element);
	
	for(int j=0; j<element->neighbors.size(); j++)
	{
		cout << "entrou" << endl;
		newPoint = this->parameters->calculateNewPoint(&(this->parameters->listPoints[element->neighbors.pos(j)]), coordenate);	
		cout << "passou" << endl;
		//	newPoint.toString();

		CybThread::lock();

		this->parameters->listPoints[element->neighbors.pos(j)].vertex->setCoord(0,newPoint[0]);
		this->parameters->listPoints[element->neighbors.pos(j)].vertex->setCoord(1,newPoint[1]);
		this->parameters->listPoints[element->neighbors.pos(j)].vertex->setCoord(2,newPoint[2]);

		CybThread::unlock();
		//mesh->updateVertexNormalVector(element->neighbors.pos(j));															
	}
}

void CybFFD::run()
{
	if(this->collisionObject->getCollisionStatus() == true)
	{
		CybVector3D<float> interatorPosition = CybCollisionData::getInstance()->getInteratorPositionInObjectCoordenates();
		CybVector3D<float> direction = CybCollisionData::getInstance()->getDirectionInObjectCoordenates();				
		CybVector3D<float> point;
		CybFFDNode *element = NULL;
		int vertexOfCollision = CybParameters::getInstance()->mesh[this->collisionObject->getLayerOfCollision()]->getCell(this->collisionObject->getTriangleOfCollision())->getVertexId(this->collisionObject->getVertexOfCollision());
		//cout << "dir: ";
		//direction.toString();

		point = interatorPosition + direction;

		//def->collisionObject.lock();
		CybThread::lock();
	
		this->parameters->listPoints[vertexOfCollision].vertex->setCoord(0, point[0]);
		this->parameters->listPoints[vertexOfCollision].vertex->setCoord(1, point[1]);
		this->parameters->listPoints[vertexOfCollision].vertex->setCoord(2, point[2]);
	
		CybThread::unlock();
		//def->collisionObject.unlock();

		for(int i=0; i<CybParameters::getInstance()->nv[this->collisionObject->getLayerOfCollision()]; i++)
		{
			if(this->parameters->listPoints[i].vertex == this->parameters->listPoints[vertexOfCollision].vertex) 
			{
				element = &this->parameters->listPoints[i];
				cout << "entrou" << endl;
				cout << element->neighbors.size() << endl;
				this->deformation(element);

				i = CybParameters::getInstance()->nv[this->collisionObject->getLayerOfCollision()];		
			}
		}
		/*
		if((back == true) && (lastVertexCollision != vertexOfCollision))
		{
			cout << "Tah voltando!" << endl;

			point.x = vertexOfCollision->getCoord(0);
			point.y = vertexOfCollision->getCoord(1);
			point.z = vertexOfCollision->getCoord(2);
			
			vertexOfCollision->setCoord(0,element->point.x);
			vertexOfCollision->setCoord(1,element->point.y);
			vertexOfCollision->setCoord(2,element->point.z);
			
			//direction = element->point - point;
			
			//norm = CybPoint3D::norm(&direction);
			
			//direction = direction/norm;

			//	def->collisionObject.lock();

			def->deformation(element);

			//	def->collisionObject.unlock();

			back = false;
			cout << flush;
			
			lastVertexCollision = vertexOfCollision;
		}*/
	}
}

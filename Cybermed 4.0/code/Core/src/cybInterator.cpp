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


#include "cybInterator.h"

	/** Constructor */
	CybInterator::CybInterator()
	{
		id = 0;
		activeMesh = 0;
		graphicObjectId = -1;
		enabled = false;
		activeMeshChange = true;

		for (int i = 0; i < 3; i++) {
			interatorRot[i] = 0;
			interatorTrans[i] = 0;
			interatorSca[i] = 1;
			interatorStartPosition[i] = 0;

			position[i] = 0;
			lastPosition[i] = 0;
			lastRotation[i] = 0;

			interatorColor[i] = 1;
		}
		interatorColor[3] = 1;

		this->interatorType = MOUSE_INTERATOR;

		interatorMesh = new cybMesh<cybSurfaceTriTraits>[10];
		//this->interatorMesh = new cybMesh<cybTraits>;
	}

	void CybInterator::addListener(CybInteratorListener* listener) {
		listenersList.push_back(listener);
	}

	CybVector3D<float> CybInterator::getRotation() {
		return this->interatorRot;
	}

	CybVector3D<float> CybInterator::getScale() {
		return this->interatorSca;
	}

	CybVector3D<float> CybInterator::getTranslation() {
		return this->interatorTrans;
	}

	int CybInterator::getId() {
		return this->id;
	}
	
	int CybInterator::getGraphicObjectId() {
		return this->graphicObjectId;
	}
	
	CybVector3D<float> CybInterator::getPosition() {
		return this->position;
	}

	CybVector3D<float> CybInterator::getStartPosition() {
		return this->interatorStartPosition;
	}
	
	CybVector3D<float> CybInterator::getOrientation() {
		return this->orientation;
	}
	
	CybVector4D<float> CybInterator::getColor() {
		return this->interatorColor;
	}

	cybMesh<cybSurfaceTriTraits>* CybInterator::getMesh(int idMesh) {
		return &(interatorMesh[idMesh]);
	}
	
	CybModel *CybInterator::getCybModel() {
		return models;
	}

	int CybInterator::getInteratorType() {
		return this->interatorType;
	}

	int CybInterator::getActiveMesh() {
		return this->activeMesh;
	}

	bool CybInterator::isEnabled() {
		return this->enabled;
	}
	
	bool CybInterator::isActiveMeshChange() {
		return this->activeMeshChange;
	}

	void CybInterator::setId(int id) {
		this->id = id;
	}
	
	void CybInterator::setInteratorType(int type) {
		this->interatorType = type;
	}

	void CybInterator::setGraphicObjectId(int graphicObjectId) {
		if (graphicObjectId >= 0) {
			this->graphicObjectId = graphicObjectId;
		}
	}
	
	void CybInterator::setEnabled(bool enabled) {
		this->enabled = enabled;
	}
	
	void CybInterator::setAttribute(float x, float y, float z) {

	}
	
	void CybInterator::setMesh(int idMesh, cybMesh<cybSurfaceTriTraits>* interatorMesh) {
		this->interatorMesh[idMesh] = *interatorMesh;
	}

	void CybInterator::setPosition(float x, float y, float z) {
		bool update = false;

		this->position[0] = x;
		this->position[1] = y;
		this->position[2] = z;

		for(int i=0; i<3; i++) {
			if (this->position[i] != this->lastPosition[i]) {
				update = true;
				this->lastPosition[i] = this->position[i];
				break;
			}
		}
		
		if (models != 0) {		
			update = true;
		}

		if (isEnabled() && update) {
			for(it = listenersList.begin(); it != listenersList.end(); it++) {
				(*it)->interatorPositionEventPerformed(x, y, z);
			}
		}
	}

	void CybInterator::setRotation(float x, float y, float z) {
		bool updateRot = false;

		//cout << x << " " << y << " " << z << endl;

		this->interatorRot[0] = x;
		this->interatorRot[1] = y;
		this->interatorRot[2] = z;

		for(int i=0; i<3; i++) {
			if (this->interatorRot[i] != this->lastRotation[i]) {
				updateRot = true;
				this->lastRotation[i] = this->interatorRot[i];
				break;
			}
		}

		if (isEnabled() && updateRot) {
			for(it = listenersList.begin(); it != listenersList.end(); it++) {
				(*it)->interatorRotationEventPerformed(x, y, z);
			}
		}
	}

	void CybInterator::setScale(float x, float y, float z) {
		this->interatorSca[0] = x;
		this->interatorSca[1] = y;
		this->interatorSca[2] = z;
	}

	void CybInterator::setTranslation(float x, float y, float z) {
		this->interatorTrans[0] = x;
		this->interatorTrans[1] = y;
		this->interatorTrans[2] = z;
	}

	void CybInterator::setColor(float r, float g, float b, float alfa) {
		this->interatorColor[0] = r;
		this->interatorColor[1] = g;
		this->interatorColor[2] = b;
		this->interatorColor[3] = alfa;
	}

	void CybInterator::setActiveMesh(int idMesh) {
		this->activeMesh = idMesh;
		activeMeshChange = true;
		setPosition(0, 0, 0);
	}

	void CybInterator::setActiveMeshChange(bool change) {
		this->activeMeshChange = change;
	}
	
	void CybInterator::setCybModel(CybModel *m) {
		models = m;
	}

	void CybInterator::drawInterator() {
		if (this->isEnabled()) {

			//cout << "drawInterator() CybInterator" << endl;

			sVertex *v0, *v1, *v2;
			int l;

			mfCellsIterator<cybSurfaceTriTraits> cellsIterator(&interatorMesh[activeMesh]);

			glColor4f(interatorColor[0], interatorColor[1], interatorColor[2], interatorColor[3]);

			// transformations

			//cout << "CybInterator "<< position[0] << " " <<  position[1] << " " << position[2] << endl;
			glTranslated(position[0] + interatorTrans[0], position[1] + interatorTrans[1], position[2] + interatorTrans[2]);

			glTranslated(-interatorStartPosition[0], -interatorStartPosition[1], -interatorStartPosition[2]);
			glRotated(interatorRot[0],1,0,0);
			glRotated(interatorRot[1],0,1,0);
			glRotated(interatorRot[2],0,0,1);
			glTranslated(interatorStartPosition[0], interatorStartPosition[1], interatorStartPosition[2]);

			for(cellsIterator.initialize(), l = 0; cellsIterator.notFinish(); ++cellsIterator, l++)
			{
				v0 = interatorMesh[activeMesh].getVertex(cellsIterator->getVertexId(0));
				v1 = interatorMesh[activeMesh].getVertex(cellsIterator->getVertexId(1));
				v2 = interatorMesh[activeMesh].getVertex(cellsIterator->getVertexId(2));

				glBegin(GL_TRIANGLES);
				glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
				glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));

				glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
				glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));

				glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
				glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
				glEnd();
			}
			glLoadIdentity();
		}
	}


	void CybInterator::restartMesh() {
		//delete this->interatorMesh;
		//this->interatorMesh = new cybMesh<cybTraits>;
		//cout << "mesh Deleted" << endl;
	}

	/** Destructor */
	CybInterator::~CybInterator()
	{
	

	}
	
	

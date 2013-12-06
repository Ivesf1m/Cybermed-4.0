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
#include "cybHapticInterator.h"

	CybHapticInterator::CybHapticInterator() {
		this->hapticDevice = new CybOpenHPhantom();
		//this->hapticDevice->createHapticLayers(1, true);
		//this->hapticMatrix = new double[16];
		setInteratorType(HAPTIC_INTERATOR);
	}

	void CybHapticInterator::create(int id) {
		this->setId(id);

		//hapticDevice->createHapticLayers(1, true);

		if (!hapticDevice->deviceIsEnable()) {
			cout << "deviceInit" << endl;
			hapticDevice->initDevice();

		}

		setEnabled(true);
	}

	CybDevice* CybHapticInterator::getDevice() {
		return this->hapticDevice ;
	}

	void CybHapticInterator::destroy() {
		hapticDevice->stopDevice();
	}

	double* CybHapticInterator::getHapticMatrix() {
		return this->hapticMatrix;
	}

	void CybHapticInterator::setHapticMatrix(double* matrix) {
		//this->hapticMatrix = matrix;
	}

	void CybHapticInterator::drawInterator() {
		if (this->isEnabled()) {

			hapticDevice->updateWorkspace();

			hapticDevice->drawHaptics();

			drawHapticsCursor();
		}
	}

	/**	Function responsible for drawing interator object when haptics is habilitated.
	@param void
	@return void
	*/
	void CybHapticInterator::drawHapticsCursor()
	{
		//cout << "drawHapticsCursor()" << endl;

	 	CybParameters *cybCore = CybParameters::getInstance();

		static const double kCursorRadius = 0.5;
		static const double kCursorHeight = 1.5;
		static const int kCursorTess = 15;
		double currentPosition[3], lastPosition[3];
		HLdouble proxyxform[16];
		static bool calcIsNeed = true;
		static GLuint gCursorDisplayList = 0;
		int index = cybCore->activeInterator;	// Interator object actived
		int l;
		sVertex *v0, *v1, *v2;

		GLUquadricObj *qobj = 0;

		glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
		glPushMatrix();

		// interator object from file
		if (!gCursorDisplayList || isActiveMeshChange())
		{
			gCursorDisplayList = glGenLists(1);
			glNewList(gCursorDisplayList, GL_COMPILE);
			qobj = gluNewQuadric();

			CybVector4D<float> color 	   	 = getColor();
			CybVector3D<float> startPosition = getStartPosition();
			CybVector3D<float> translation 	 = getTranslation();
			CybVector3D<float> rotation    	 = getRotation();
			CybVector3D<float> scale	   	 = getScale();

			sMesh* mesh = getMesh(getActiveMesh());

			sCellIterator cellsIterator(mesh);
			glColor4f(color[0], color[1], color[2], color[3]);

			CybVector3D<float> position = getPosition();

			// transformations
			glScaled(scale[0], scale[1], scale[2]);

			//cout << position[0] << " " << position[1] << " " << position[2] << endl;
			glTranslated(position[0] + translation[0], position[1] + translation[1], position[2] + translation[2]);

			glTranslated(-startPosition[0], -startPosition[1], -startPosition[3]);

			glRotated(rotation[0],1,0,0);
			glRotated(rotation[1],0,1,0);
			glRotated(rotation[2],0,0,1);
			glTranslated(startPosition[0], startPosition[1], startPosition[3]);

			for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator)
			{
				v0 = mesh->getVertex(cellsIterator->getVertexId(0));
				v1 = mesh->getVertex(cellsIterator->getVertexId(1));
				v2 = mesh->getVertex(cellsIterator->getVertexId(2));

				glBegin(GL_TRIANGLES);
				glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
				glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));

				glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
				glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));

				glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
				glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
				glEnd();
			}

			gluDeleteQuadric(qobj);
			glEndList();
			setActiveMeshChange(false);
		}

		double rotation[3];
		// Get the proxy transform in world coordinates.
		//hapticDevice->getProxyTransformationMatrix(proxyxform);
		hapticDevice->getProxyTransformationMatrix(this->hapticMatrix);

		hapticDevice->getCurrentProxyPosition(currentPosition);
		//hapticDevice->getDevicePosition(currentPosition);
		hapticDevice->getDeviceRotation(rotation);

		hapticDevice->getLastProxyPosition(lastPosition);

		glMultMatrixd(this->hapticMatrix);

		//cout << "scale " << hapticDevice->getHapticScaleFactor() << endl;

		// Apply the local cursor scale factor.
		glScaled(hapticDevice->getHapticScaleFactor(), hapticDevice->getHapticScaleFactor(), hapticDevice->getHapticScaleFactor());

		if(calcIsNeed )
		{
			//cout << currentPosition[0] << " " << currentPosition[1] << " " << currentPosition[2] << endl;
 			setPosition(currentPosition[0], currentPosition[1], currentPosition[2]);
 			setRotation(rotation[0], rotation[1], rotation[2]);
			//setPosition(0, 0, 0);

			glGetFloatv(GL_MODELVIEW_MATRIX, cybCore->transforMatrix[0]);
 			calcIsNeed = false;
		}
		else
			calcIsNeed = true;

		glEnable(GL_COLOR_MATERIAL);
		glColor3f(0.0, 0.5, 1.0);

		glCallList(gCursorDisplayList);

		glPopMatrix();
		glPopAttrib();

	}

	CybHapticInterator::~CybHapticInterator() {
		hapticDevice->stopDevice();
	}
	
	CybInterator* CybHapticInterator::getInterator(){
	
	    //To be tested
	
	    CybParameters* cybCore = CybParameters::getInstance();
	
		CybInterator* interator = new CybHapticInterator();
			
		cybCore->addInterator(interator);

		cybCore->hapticsPlugged[0] = true;

		cybCore->hapticsPlugged[1] = true;

		cybCore->phantomOn = true;
		
		return interator;
			
	}

	//#endif /*End phantom code */

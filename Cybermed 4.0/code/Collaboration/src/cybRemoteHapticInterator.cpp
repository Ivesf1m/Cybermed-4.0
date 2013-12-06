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

#include "cybRemoteHapticInterator.h"

CybRemoteHapticInterator::CybRemoteHapticInterator() {
	setInteratorType(REMOTE_HAPTIC_INTERATOR);

#ifdef CYBHAPTICS_H
	cout << "CYBHAPTICS_H" << endl;
	this->hapticMatrix = new HLdouble[16];
	memset(this->hapticMatrix, 0, sizeof(HLdouble)*16);
#else
	this->hapticMatrix = new double[16];
	memset(this->hapticMatrix, 0, sizeof(double)*16);
#endif


}

void CybRemoteHapticInterator::drawInterator() {
	//cout << "drawRemoteHapticInterator() in" << endl;
	if (isEnabled()) {

		//cout << "desenhando cursor remoto..." << endl;

		CybParameters *cybCore = CybParameters::getInstance();

		static const double kCursorRadius = 0.5;
		static const double kCursorHeight = 1.5;
		static const int kCursorTess = 15;
		double currentPosition[3], lastPosition[3];
		static bool calcIsNeed = true;
		static GLuint gCursorDisplayList = 0;
		//int index = cybCore->activeInterator;	// Interator object actived
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

		// Get the proxy transform in world coordinates.
		glMultMatrixd(hapticMatrix);

		// Apply the local cursor scale factor.
		CybVector3D<float> scale = getScale();

		glScaled(1.76573, 1.76573, 1.76573);

		if(calcIsNeed )
		{
			setPosition(hapticMatrix[12], hapticMatrix[13], hapticMatrix[14]);

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

		//cout << "drawRemoteHapticInterator() out" << endl;
	}

}

CybRemoteInterator* CybRemoteHapticInterator::getInterator() {
    
    CybParameters *cybCore = CybParameters::getInstance();
    CybInterator *interator = new CybRemoteHapticInterator();
	cybCore->addInterator(interator);
	return dynamic_cast<CybRemoteInterator *>(interator);
}

#ifdef CYBHAPTICS_H
void CybRemoteHapticInterator::setHapticMatrix(HLdouble* matrix) {
	//delete[] hapticMatrix;
	this->hapticMatrix = matrix;
}
#else

void CybRemoteHapticInterator::setHapticMatrix(double* matrix) {
	//delete[] hapticMatrix;
	this->hapticMatrix = matrix;
}

#endif


CybRemoteHapticInterator::~CybRemoteHapticInterator() {
	delete this->hapticMatrix;
}


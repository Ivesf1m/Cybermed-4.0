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

#include "cybMouseInteraction.h"
#include "cybMouseInterator.h"

	CybMouseInteraction CybMouseInteraction::singletonInstance;
	
	CybMouseInteraction::CybMouseInteraction()
	{
		mouseRightClicked = false;
		mouseMiddleClicked = false;
		mouseLeftClicked = false;
		yAnt = 300;
		previousX = -1;
		previousY = -1;
		xP = 0;
		yP = 0;
		xi = 0;
		yi = 0;
		initzi = 24;
		zi = initzi;	// 75
		zP = zi;	// 7.45
		firstTime = true;
		layerInteracted = -1;
		cybCore = CybParameters::getInstance();

		mouseInterator = NULL;
		//mouseInterator = new CybMouseInterator();

		//mouseInterator->setEnabled(true);
		//cybCore->addInterator(mouseInterator);
	}
	
	
	CybMouseInteraction *CybMouseInteraction::getInstance() { return &singletonInstance; }
	
	
	void CybMouseInteraction::getEnvironmentData()
	{
		glGetDoublev(GL_PROJECTION_MATRIX, cybCore->projectionMatrix);
		glGetDoublev(GL_MODELVIEW_MATRIX, cybCore->modelviewMatrix);
		glGetIntegerv(GL_VIEWPORT, cybCore->viewportMatrix);
	
		windowHeight = cybCore->Resy;
	
		proportionX = 1/cybCore->dfNearClipDistance;
		proportionY = 1/cybCore->dfNearClipDistance;
	
		if(firstTime)
		{
			firstTime = false;
			if(cybCore->layerInteractionChoosen)
				layerInteracted = cybCore->layerInteracted;
		}
	}
	
	
	void CybMouseInteraction::mouseInteraction(int button, int state, int x, int y)
	{
		
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // grasp
			if (mouseInterator != NULL)
				mouseInterator->setMeshGrasped(true);
		else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
			if (mouseInterator != NULL)
				mouseInterator->setMeshGrasped(false);
	
		if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) // enabling xz plane
			mouseRightClicked = true;
		if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
			mouseRightClicked = false;
	
		glutPostRedisplay();
	}
	
	
	void CybMouseInteraction::mouseMoveInteraction(int x, int y)
	{

		double xint, yint, zint;
	
		if(mouseRightClicked)	// Plane xz actived
		{
			xi = x;
			zi += (float)(y-yAnt)/10;
	
			if(cybCore->modified || firstTime)
				getEnvironmentData();
	
			gluUnProject((double) xi, (double) yi, 0, cybCore->modelviewMatrix, cybCore->projectionMatrix, cybCore->viewportMatrix, &xint, &yint, &zint);
	
			xP = xint*proportionX*((-zi)+cybCore->dfNearClipDistance+initzi);
			yP = yint*proportionY*((-zi)+cybCore->dfNearClipDistance+initzi);
			zP = zi;

			if (mouseInterator != NULL) {
				mouseInterator->setMousePosition(xP, yP, zP);
				mouseInterator->setFocus(xP - previousXCoord, yP - previousYCoord, zP - previousZCoord);
			}
			yAnt = y;
	
			if((previousX - x) || (previousY - y))
			{
				cybCore->interatorPosChange = true;
			}
			else
			{
				cybCore->interatorPosChange = false;
			}
	
			previousXCoord = xP;
			previousYCoord = yP;
			previousZCoord = zP;
			previousY = y;
			previousX = x;
		}
	
		glutPostRedisplay();
	}
	
	
	void CybMouseInteraction::mousePassiveMoveInteraction(int x, int y)
	{
		
		double xint, yint, zint;
	
		xi = x;
		yi = windowHeight - y;
	
		if(cybCore->modified | firstTime)
			getEnvironmentData();
	
		gluUnProject((double) xi, (double) yi, 0, cybCore->modelviewMatrix, cybCore->projectionMatrix, cybCore->viewportMatrix, &xint, &yint, &zint);
	
		xP = xint*proportionX*((-zi)+cybCore->dfNearClipDistance+initzi);
		yP = yint*proportionY*((-zi)+cybCore->dfNearClipDistance+initzi);

		if (mouseInterator != NULL) {
			mouseInterator->setMousePosition(xP, yP, zP);
			mouseInterator->setFocus(xP - previousXCoord, yP - previousYCoord, zP - previousZCoord);
		}
		yAnt = y;
	
		if((previousX - x) || (previousY - y)) 
		{
			cybCore->interatorPosChange = true;
		}
		else
		{
			cybCore->interatorPosChange = false;
		}
	
		previousXCoord = xP;
		previousYCoord = yP;
		previousZCoord = zP;
		previousY = y;
		previousX = x;
	
		glutPostRedisplay();
	}

	void CybMouseInteraction::setMouseInterator(CybMouseInterator* mouseInterator) {
		this->mouseInterator = mouseInterator;
	}

	CybMouseInterator* CybMouseInteraction::getMouseInterator() {
		return this->mouseInterator;
	}

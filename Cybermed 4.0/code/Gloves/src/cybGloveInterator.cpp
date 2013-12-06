// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#include <iostream>
#include "cybGloveInterator.h"


using namespace std;

CybGloveInterator::CybGloveInterator(string type) {

	if (type.compare("5DTGlove") == 0)
		gloveDevice = new Cyb5DTGlove();
	else 
		cout << "Glove type don't found!" << endl;	
		
	
	firstTime = true;
	setInteratorType(GLOVE_5DT_INTERATOR);
}

//Este segundo construtor recebe um parametro string a mais (port), este parametro especifica em que porta a luva deve
//ser aberta, já que a 5DT dá esse suporte. Se não for especificado a 5DT por padrá abre a /dev/usb/hiddev0
CybGloveInterator::CybGloveInterator(string type, string port) {
	if (type.compare("5DTGlove") == 0)
		gloveDevice = new Cyb5DTGlove(port);
	else 
		cout << "Glove type don't found!" << endl;	
		
	
		
	firstTime = true;
	setInteratorType(GLOVE_5DT_INTERATOR);
}

CybGloveInterator::~CybGloveInterator() {

}

void CybGloveInterator::create(int id) {
	setId(id);	
	gloveDevice->initDevice();		
	setEnabled(true);	
	
		
}

void CybGloveInterator::destroy() {
	gloveDevice->stopDevice();
}

void CybGloveInterator::drawInterator() {
	if (firstTime) {
		if (getCybModel() == 0)
			cout << "cybmodel nulo" << endl;
		getCybModel()->setUpdateModel(gloveDevice->getGloveName());
		getCybModel()->setDevice(getDevice());	
		firstTime = false;
	}	
	CybVector4D<float> color 	   	 = getColor();
	CybVector3D<float> startPosition  = getStartPosition();
	CybVector3D<float> translation 	 = getTranslation();
	CybVector3D<float> rotation    	 = getRotation();
	CybVector3D<float> scale	   	 = getScale();
	
	glPushMatrix();
	
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
	
	drawGloveInterator();
	setPosition(0, 0, 0);
	glPopMatrix();
	
}

void CybGloveInterator::drawGloveInterator() {
	getCybModel()->update();
	getCybModel()->draw();
}	

CybDevice *CybGloveInterator::getDevice() {
	return gloveDevice;
}

CybInterator* CybGloveInterator(){

    //a ser testado

    CybParameters *cybCore = CybParameters::getInstance();

    CybInterator* interator = new CybGloveInterator("5DTGlove");		
	cybCore->addInterator(interator);
		
	cybCore->gloveOn = true;
	
	return interator;

}

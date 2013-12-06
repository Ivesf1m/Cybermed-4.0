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

#include "cybMouseInterator.h"
//#include "cybMouseInteraction.h"

CybMouseInterator::CybMouseInterator() {
	meshGrasped = false;
	objectFocus[0] = 1.0;
	objectFocus[1] = 0.0;
	objectFocus[2] = 0.0;

	setInteratorType(MOUSE_INTERATOR);
}

CybDevice* CybMouseInterator::getDevice() {
	return NULL;
}

void CybMouseInterator::create(int id) {
	setId(id);
}

void CybMouseInterator::destroy() {

}

bool CybMouseInterator::isMeshGrasped() {
	return this->meshGrasped;
}

CybVector3D<float> CybMouseInterator::getFocus() {
	return this->objectFocus;
}

void CybMouseInterator::setMeshGrasped(bool meshGrasped) {
	this->meshGrasped = meshGrasped;
}

void CybMouseInterator::setMousePosition(float x, float y, float z) {
	this->setPosition(x, y, z);
}

void CybMouseInterator::setFocus(float x, float y, float z) {
	this->objectFocus[0] = x;
	this->objectFocus[1] = y;
	this->objectFocus[2] = z;
}

CybInterator* CybMouseInterator::getInterator(){

	CybParameters* cybCore = CybParameters::getInstance();
	//CybMouseInteraction* mouseInteraction = CybMouseInteraction::getInstance();
	CybInterator* interator = new CybMouseInterator();
	//mouseInteraction->setMouseInterator((CybMouseInterator*)interator);
	cybCore->addInterator(interator);
	cybCore->mouseOn = true;
	
	return interator;

}

CybMouseInterator::~CybMouseInterator() {
	// TODO Auto-generated destructor stub
}

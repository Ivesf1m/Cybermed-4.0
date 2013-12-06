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

#include "cybGloveCollaboration.h"

CybGloveCollaboration::CybGloveCollaboration(int port, int communicationType, const char *multicastGroupIP) : CybCollaboration(port, communicationType, multicastGroupIP) {
	//vazio	
}

    CybInterator* CybGloveCollaboration::getMainInterator() {
	CybInterator* interator = CybGloveInterator::getInterator();
	CybGlove *cybglove = dynamic_cast<CybGlove *>(interator->getDevice());
	cybglove->setPort(port);
	interator->create(cybCore->getNumInterators() - 1);
	
	return interator;
}

void CybGloveCollaboration::interatorPositionEventPerformed(float x, float y, float z) {
	
	char buffer[250];
	int	arraySize = 50;

	memset(buffer, 0, 250);
	
	CybModelCollaboration* modelcollaboration = dynamic_cast<CybModelCollaboration *> (mainInterator->getCybModel());
	float *matrix = modelcollaboration->getMatrix();	
	int pos = 0;

	buffer[pos++] = INTERATOR_POSITION_CHANGE;

	memcpy(buffer + pos, matrix, sizeof(float)*arraySize);
	pos += sizeof(float)*arraySize;

	sendDataToAll(buffer, pos, properties->getCommunicationType());
}

void CybGloveCollaboration::interatorRotationEventPerformed(float x, float y, float z) {
	
}

void CybGloveCollaboration::processInteratorRotationChangeMsg(char* buffer, string ipStr, short int port) {

}

void CybGloveCollaboration::setPortName(string portName) {
	this->port = portName;
}

CybGloveCollaboration::~CybGloveCollaboration() {
	glove->stopDevice();
}


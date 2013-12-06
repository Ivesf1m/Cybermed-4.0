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

#include "cybCollaborationPerformance.h"

CybCollaborationPerformance::CybCollaborationPerformance() {

	 numBytesSent = 0;
	 numBytesReceived = 0;

	 numPktsReceived = 0;
	 numPktsSent = 0;

	 layerRotationPktS = 0;
	 layerRotationPktR = 0;
		
         interatorPositionPktS = 0;
	 interatorPositionPktR = 0;

	 interatorRotationPktS = 0;
	 interatorRotationPktR = 0;

	 layerColorPktS = 0;
	 layerColorPktR = 0;

	 cout << "Performance CREATED!!" << endl;
}

int CybCollaborationPerformance::getNumBytesSent(void) {
	return this->numBytesSent;
} 
int CybCollaborationPerformance::getNumBytesReceived(void) {
	return this->numBytesReceived;
}

int CybCollaborationPerformance::getNumPktsReceived(void) {
	return this->numPktsReceived;
}

int CybCollaborationPerformance::getNumPktsSent(void) {
	return this->numPktsSent;
}

int CybCollaborationPerformance::getLayerRotationPktS(void) {
	return this->layerRotationPktS;
}

int CybCollaborationPerformance::getLayerRotationPktR(void) {
	return this->layerRotationPktR;
}

int CybCollaborationPerformance::getInteratorPositionPktS(void) {
	return this->interatorPositionPktS;
}

int CybCollaborationPerformance::getInteratorPositionPktR(void) {
	return this->interatorPositionPktR;
}

int CybCollaborationPerformance::getInteratorRotationPktS(void) {
	return this->interatorRotationPktS;
}

int CybCollaborationPerformance::getIteratorRotationPktR(void) {
	return this->interatorRotationPktR;
}

int CybCollaborationPerformance::getLayerColorPktS(void) {
	return this->layerColorPktS;
}
	
int CybCollaborationPerformance::getLayerColorPktR(void) {
	return this->layerColorPktR;
}

// ------------- Sets

void CybCollaborationPerformance::setNumBytesSent(int bytes) {
	this->numBytesSent += bytes;
} 

void CybCollaborationPerformance::setNumBytesReceived(int bytes) {
	this->numBytesReceived += bytes;
}

void CybCollaborationPerformance::setNumPktsReceived() {
	this->numPktsReceived++;
}

void CybCollaborationPerformance::setNumPktsSent() {
	this->numPktsSent++;
}


void CybCollaborationPerformance::setLayerPositionPktS() {
	this->layerPositionPktS++;
}

void CybCollaborationPerformance::setLayerPositionPktR() {
	this->layerPositionPktR++;
}


void CybCollaborationPerformance::setLayerRotationPktS() {
	this->layerRotationPktS++;
}

void CybCollaborationPerformance::setLayerRotationPktR() {
	this->layerRotationPktR++;	
}


void CybCollaborationPerformance::setInteratorPositionPktS() {
	this->interatorPositionPktS++;
}

void CybCollaborationPerformance::setInteratorPositionPktR() {
	this->interatorPositionPktR++;
}

void CybCollaborationPerformance::setInteratorRotationPktS() {
	this->interatorRotationPktS++;
}

void CybCollaborationPerformance::setInteratorRotationPktR() {
	this->interatorRotationPktR++;
}

void CybCollaborationPerformance::setLayerColorPktS() {
	this->layerColorPktS++; 
}
	
void CybCollaborationPerformance::setLayerColorPktR() {
	this->layerColorPktR++;
}

void CybCollaborationPerformance::countTrafficSent(char pktType, int bytes) {

	switch(pktType) {

		case 2: //Receive collaboration configuration data

		break;

		case 3: //Interator position change message Type
			setInteratorPositionPktS();
		break;

		case 4: //Interator rotation change message Type
			setInteratorRotationPktS();
		break;

		case 5: //Layer position change message Type
			setLayerPositionPktS();
		break;

		case 6: //Layer rotation change message Type
			setLayerRotationPktS();
		break;

		case 7: //Layer color change message Type
			setLayerColorPktS();
		break;
	}
	this->setNumPktsSent();
	this->setNumBytesSent(bytes);
}

/*typedef enum tMessageType {
	JOIN_REQUEST 		  = 0,
	LEAVE_REQUEST 		  = 1,
	SCENE_CONFIGURATION 	  = 2,
	INTERATOR_POSITION_CHANGE = 3,
	INTERATOR_ROTATION_CHANGE = 4,
	LAYER_POSITION_CHANGE 	  = 5,
	LAYER_ROTATION_CHANGE 	  = 6,
	LAYER_COLOR_CHANGE	  = 7,
	ACCEPT			  = 8,
} tMessageType;*/


void CybCollaborationPerformance::countTrafficReceived(char pktType, int bytes) {

	switch(pktType) {

		case 2: //Receive collaboration configuration data

		break;

		case 3: //Interator position change message Type
			setInteratorPositionPktR();			
		break;

		case 4: //Interator rotation change message Type
			setInteratorRotationPktR();
		break;

		case 5: //Layer position change message Type
			setLayerPositionPktR();
		break;

		case 6: //Layer rotation change message Type
			setLayerRotationPktR();
		break;

		case 7: //Layer color change message Type
			setLayerColorPktR();
		break;
	}
	this->setNumPktsReceived();
	this->setNumBytesReceived(bytes);
}


void CybCollaborationPerformance::reportPerformance() { 
	
	cout << "============ Collaboration Report ===========" << endl;
	cout << "bytes sent: " << numBytesSent << endl;
        cout << "bytes received: " << numBytesReceived << endl;
 	cout << "packets received: " << numPktsReceived << endl;
 	cout << "packets sent: " << numPktsSent << endl;
 	cout << "LAYER_RORATION_CHANGE packets sent: " << layerRotationPktS << endl;
 	cout << "LAYER_RORATION_CHANGE packets received: " << layerRotationPktR << endl;
 	cout << "LAYER_POSITION_CHANGE packets sent: " << layerPositionPktS << endl;
 	cout << "LAYER_POSITION_CHANGE packets received: " << layerPositionPktR << endl;
 	cout << "INTERATOR_POSITION_CHANGE packets sent: " << interatorPositionPktS << endl;
 	cout << "INTERATOR_POSITION_CHANGE packets received: " << interatorPositionPktR << endl;
 	cout << "INTERATOR_ROTATION_CHANGE packets sent: " << interatorRotationPktS << endl;
 	cout << "INTERATOR_ROTATION_CHANGE packets received: " << interatorRotationPktR << endl;
        cout << "LAYER_COLOR_CHANGE packets sent: " << layerColorPktS << endl;
	cout << "LAYER_COLOR_CHANGE packets received: " << layerColorPktR << endl;
}



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

#include "cybCollaborationIntegrant.h"

CybCollaborationIntegrant::CybCollaborationIntegrant() {
	this->address = new CybNodeAddress();
}

CybCollaborationIntegrant::CybCollaborationIntegrant(CybNodeAddress* address) {
	this->address = address;
}

CybCollaborationIntegrant::CybCollaborationIntegrant(string ipAddress, const short port) {
	this->address = new CybNodeAddress(port, ipAddress.c_str(), AF_INET);
}

CybCollaborationIntegrant::CybCollaborationIntegrant(string name, string ipAddress, const short port) {
	this->name = name;
	cout << "ipAddress " << ipAddress << " port " << port << endl;
	this->address = new CybNodeAddress(port, ipAddress.c_str(), AF_INET);
}

CybCollaborationIntegrant::CybCollaborationIntegrant(string name, CybNodeAddress* address) {
	this->name = name;
	this->address = address;
}

string CybCollaborationIntegrant::getName() {
	return this->name;
}

CybNodeAddress* CybCollaborationIntegrant::getAddress() {
	return this->address;
}

CybRemoteInterator* CybCollaborationIntegrant::getInterator() {
	return this->interator;
}

char* CybCollaborationIntegrant::getInteratorModel() {
	return this->interatorModel;
}

int CybCollaborationIntegrant::getIdInteratorModel() {
	return this->idInteratorModel;
}

void CybCollaborationIntegrant::setName(string name) {
	this->name = name;
}

void CybCollaborationIntegrant::setAddress(CybNodeAddress* address) {
	if (address != NULL) {
		this->address = address;
	}
}

void CybCollaborationIntegrant::setInterator(CybRemoteInterator* interator) {
	this->interator = interator;
}

void CybCollaborationIntegrant::setInteratorModel(int idInteratorModel) {
	this->idInteratorModel = idInteratorModel;
}

CybCollaborationIntegrant::~CybCollaborationIntegrant() {
	delete this->interator;
	delete this->address;
}

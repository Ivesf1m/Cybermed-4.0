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

#include "cybRemoteGloveInterator.h"


CybRemoteGloveInterator::CybRemoteGloveInterator() {
	setInteratorType(REMOTE_GLOVE_INTERATOR);
	
}

void CybRemoteGloveInterator::setMatrix(float matrix[]) {	
	remoteModel = dynamic_cast<CybModelCollaboration *>(getCybModel());		
	remoteModel->setMatrix(matrix);	
}

void CybRemoteGloveInterator::drawInterator() {
	if (getCybModel() == 0) {
		return;
	}
    remoteModel = dynamic_cast<CybModelCollaboration *>(getCybModel());		
	remoteModel->draw();
}

CybRemoteInterator* CybRemoteGloveInterator::getInterator() {

        CybParameters *cybCore = CybParameters::getInstance();
        CybInterator *interator = new CybRemoteGloveInterator();
		cybCore->addInterator(interator);
		return dynamic_cast<CybRemoteInterator *>(interator);
}

CybRemoteGloveInterator::~CybRemoteGloveInterator() {

} 


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

#include "cybAssessLinker.h"

CybAssessLinker::CybAssessLinker(CybAssess* assess, 
				 CybAssessDataProvider* dataProvider,
				 CybAssessIO* io)
{
	this->assess = assess;
	this->dataProvider = dataProvider;
	this->io = io;
	this->resultSet = new mfList<double>;
}
 
CybAssessLinker::~CybAssessLinker()
{
	this->resultSet->clear();
	
	delete this->resultSet;
}

CybAssess* CybAssessLinker::getAssess()
{
	return this->assess;
}

mfList<double>* CybAssessLinker::getResultSet()
{
	return this->resultSet;
}

CybAssessIO* CybAssessLinker::getIO()
{
	return this->io;
}

CybAssessDataProvider* CybAssessLinker::getDataProvider()
{
	return this->dataProvider;
}

void CybAssessLinker::init()
{
	this->dataProvider->init();
	CybThread::init();
}

CYB_ASSESS_MODE CybAssessLinker::getCurrentMode()
{
	return this->current_mode;
}

void CybAssessLinker::setCurrentMode(CYB_ASSESS_MODE mode)
{
	this->current_mode = mode;
}

void CybAssessLinker::run()
{
	CybVectorND<float>* aux = NULL;
	
	switch(this->current_mode)
	{
		case DO_NOTHING: break;
		
		case OBTAIN_DATA: this->assess->addData(dataProvider->getData());
		dataProvider->getData()->show();
		cout << endl;
						break;
						
		case OBTAIN_DATA_AND_DO_ASSESSMENT:
						aux = dataProvider->getData();
						this->assess->addData(aux);
						this->resultSet->insert(this->assess->assessment(aux));
						break;
						
		case TRAINING : this->assess->training();
						break;
						
		case DO_ASSESSMENT:
						this->resultSet->clear();
						for(int i=0; i < this->assess->getData()->size(); i++)
							this->resultSet->insert(this->assess->assessment(this->assess->getData()->pos(i)));
						break;
						
		case SAVE_ASSESS:
						this->io->write(this->assess);
						break;
						
		case SAVE_DATA: this->io->writeData(this->assess);
						break;
	}
}

void CybAssessLinker::update()
{
	
}


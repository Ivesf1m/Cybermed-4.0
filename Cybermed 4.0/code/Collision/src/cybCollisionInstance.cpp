// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2011 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba.
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

#include "cybCollisionInstance.h"

CybCollisionInstance::CybCollisionInstance(CybCollision * obj1, CybCollision *obj2,  string type)
{
	firstObject = obj1;
	secondObject = obj2;
	typeOfCollision = type;
	status = 0;
}

CybCollision* CybCollisionInstance::getFirstCollisionObject()
{
	return firstObject;
}

CybCollision* CybCollisionInstance::getSecondCollisionObject()
{
	return secondObject;
}

string CybCollisionInstance::getTypeOfCollision()
{
	return typeOfCollision;
}

bool CybCollisionInstance::getStatus()
{
	return status;
}

void CybCollisionInstance::setStatus(bool state)
{
	status = state;
}
void CybCollisionInstance::toString(){
	cout << firstObject <<  " " << secondObject << " " << typeOfCollision << " " << status << endl;
}

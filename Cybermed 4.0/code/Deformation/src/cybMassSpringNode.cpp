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

#include "cybMassSpringNode.h"

	CybMassSpringNode::CybMassSpringNode()
	{
		vertex = NULL;
	}
	
	CybMassSpringNode::~CybMassSpringNode()
	{
		this->neighbors.clear();
	}
	
	void CybMassSpringNode::update_acceleration_velocity(CybVector3D<float> force, float mass, float step, float stiffness)
	{
		CybVector3D<float> p(vertex->getCoord(0), vertex->getCoord(1), vertex->getCoord(2));	// get point
	
		this->acceleration =  (force - stiffness* this->velocity)/mass;	// calculate accelaration
		this->velocity += this->acceleration*step;	//calculate velocity
	}

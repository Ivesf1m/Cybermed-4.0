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

#include "cybBayesianNetwork.h"

#ifndef _CYB_INFO_NODE_H_
#define _CYB_INFO_NODE_H_

class CybInfoNode
{
private:
	int parent;
	int son;
	double score;

public:
	
	CybInfoNode(CybBayesianNetwork* net, int parent, int son)
	{
		this->parent = parent;
		this->son = son;
		net->addArc(parent,son);
		net->initModel();
		this->score = net->score();			
		net->removeArc(parent,son);
		net->initModel();
	}		
	
	double getScore()
	{
		return this->score;
	}
	
	int getParent()
	{
		return this->parent;
	}
	
	int getSon()
	{
		return this->son;
	}
	
};

#endif /*_CYB_INFO_NODE_H_*/

// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#ifndef _CYBBOXHOLDER_H_
#define _CYBBOXHOLDER_H_

#include "cybBoxDrawer.h"
#include <list>
#include <iostream>

using namespace std;

/**
 * @class CybBoxHolder
 * @file cybBoxHolder.h 
 * @short This class is a bundle for box drawers.
 *
 * This class holds references to all existent box drawers and calls their draw method. 
 * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 3.0
 * @date 2012, March
 * 
 */

class CybBoxHolder
{
	public:
		/*
		* This method adds a box drawer pointer to the list.
		*
		* @param CybBoxDrawer* drawer: a pointer to the drawer to be added.
		* @return void
		*/
		void addBox(CybBoxDrawer*);
		/* 
		* This method iterated through the list of drawers and calls their draw method.
		* 
		* @param void
		* @return void
		*/
		void drawBoxes();
		/*
		* This method is used to access the single instance of this class (Singleton Pattern)
		*
		* @param void
		* @return CybBoxHolder*: the single instance of this class.
		*/
		static CybBoxHolder* getInstance();
		/*
		* This method removes a box drawer pointer to the list.
		*
		* @param CybBoxDrawer* drawer: a pointer to the drawer to be removed.
		* @return void
		*/		
		void removeBox(CybBoxDrawer*);
	private:
		CybBoxHolder();					//This class' private constructor
		list<CybBoxDrawer*> boxList;			//The list of box drawers.		
		static CybBoxHolder* instance;			//The single instance of this class.
};

#endif //_CYBBOXHOLDER_H_

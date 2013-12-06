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

#include <iostream>
#include <GL/glut.h>

#ifndef _CYB_MENU_NODE_H_
#define _CYB_MENU_NODE_H_

/**
	@class CybMenuNode 
	@file cybMenuNode.h 
	@short
		Stores all the menu atributtes.
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2007, July
*/

class CybMenuNode
{
public:
	char* name;		/**< The name showed by the menu. */
	int event;		/**< Indicates the event associaded with this element. */

	/** Contructor.
	*
	* @param char* name The name associated with this element.
	* @param int event The event associated with this element.
	*
	*/
	CybMenuNode(char* name, int event);

	/** Destructor. */
	~CybMenuNode();
	
};

#endif /*_CYB_MENU_NODE_H_*/

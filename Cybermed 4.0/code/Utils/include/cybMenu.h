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

#ifndef _CYB_MENU_H_
#define _CYB_MENU_H_

#include <cstring>
#include "cybMenuNode.h"
#include "mf/mfList.h"

using namespace mf;

/**
	@class CybMenu 
	@file cybMenu.h 
	@short
		This class implements methods for construct menus and integrate its in CyberMed System.
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2007, July
*/
class CybMenu
{	
private:
	mfList<CybMenuNode*> elements;		/**< Indicates an array of elements (names and events). */	
	mfList<CybMenu*> submenu;		/**< Stores the references to the submenus of this. */
	int id;				/**< Stores the id of this menu. */
	void (*mainFunction)(int);	/**< Stores a pointer to the main function associated with this menu. */
	int size;			/**< Stores the size of this menu. */
	int bottom;  			/**< Indicates the bottom of maouse associated with the menu. */
	
protected:

	/**
	* Constructor.
	*
	* @param (void (*mainFunction)(int)) The function associated with this menu.
	*
	*/ 
	CybMenu(void (*mainFunction)(int));

public:

	/**
	* Destructor
	*/	
	~CybMenu();
	
	/**	
	* This method add an option to this menu.
	*
	* @param char* name The name associated to the option.
	* @param int event The event associated.
	* @return void
	*
	*/
	void add(char* name, int event);
	
	/**
	* This method add a submenu to this menu.
	*
	* @param char* name The name associated to submenu.
	* @param CybMenu* submenu The submenu associated.
	* @return void
	*
	*/
	void add(char* name, CybMenu* submenu = NULL);

	/**
	* This method calls the menu initialization of menu structure.
	*
	* @param void.
	* @return void.
	*
	*/
	void createMenu();
	
	/**
	*
	* This method creates a menu structure.
	*
	* @param CybMenu* submenu The super menu of struct.
	*
	*/
	static void createSubMenu(CybMenu* submenu);

	/**
	* This method returns the number associated with the event of menu.
	* If the name is not found returns -1 or the index of array (the index is associated with this event).
	*
	* @param char* name The name associated with a item of menu.
	* @return int The number associated with this event.
	*
	*/
	int getEvent(char* name);

	/**
	* This method returns a name associated with this menu that is in index position.
	*
	* @param int index The position of the name.
	* @param char* The name associated.
	*
	*/
	char* getName(int index);

	/**
	* This method returns a new instance of CybMenu class
	*
	* @param (void (*mainFunction)(int)) The function associated with the menu criated.
	* @return CybMenu* the CybMenu Reference.
	*
	*/
	static CybMenu* getNewMenu(void (*mainFunction)(int));

	/**
	* This method sets the bottom of mouse associated with this menu.
	*
	* @param char bottom The first caracter of bottom ('r' or 'R' if the bottom is right bottom, 
	* 'l' or 'L' if is the left bottom and 'm' or 'M' if is the middle bottom).
	*
	*/
	void setButtom(char bottom);

	
};

#endif /*_CYB_MENU_H_*/

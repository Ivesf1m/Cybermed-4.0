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

#ifndef CYBMOUSE_H
#define CYBMOUSE_H

#include <GL/glew.h>
#include <GL/glut.h>

#include "cybParameters.h"
#include "cybMenu.h"
#include "cybMouseListener.h"
#include <list>

typedef list<CybMouseListener*> tMouseListeners;

/**
@class		CybMouse 
@file		cybMouse.h 
@short
	Mouse interaction class

@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.0
@date		2007, July
*/

class CybMouse
{

	private:

	static tMouseListeners listenersList;
	static tMouseListeners::iterator it;
	//static list<int*> intList;

	protected:
		static CybMouse* singletonInstance;		/**< The unique instance*/

	/** Constructor*/
	CybMouse();
	
	public:
	
	void addMouseListener(CybMouseListener* listener);

	/** Get the singleton instance of CybMouse*/
	static CybMouse *getInstance();
	
	/**	Mouse interaction function
	@param int button
	@param int state
	@param int x
	@param int y
	@return void
	*/
	void mouse(int button, int state, int x, int y);

	/**	Mouse motion interaction function.
	*	Used in rotation interaction.
	@param int x
	@param int y
	@return void
	*/
	void mouseMove(int x, int y);

	/**	Creates the interactive menu.
	@param void
	@return void
	*/
	
	virtual void createMenu();
	/**	Haptics interaction menu function.
	@param int menu_option
	@return void
	*/
	static void HapticsMenu(int op);

	/**	Main intercative menu function.
	@param int menu_option
	@return void
	*/
	static void MainMenu(int op);

	/**	Layer intercative submenu function.
	@param int option
	@return void
	*/
	static void LayerMenu(int op);
};

#endif /*CYBMOUSE_H*/

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

#include "cybMenu.h"

	CybMenu::CybMenu(void (*mainFunction)(int))
	{
		this->mainFunction = mainFunction;
		this->setButtom('r');
		this->size = 0;
	}


	CybMenu::~CybMenu()
	{
		for(int i = 0; i < this->elements.size(); i++)
		{
			delete elements.pos(i);
			delete submenu.pos(i);
		}
		
		 elements.clear();
		 submenu.clear();
	}
	

	void CybMenu::add(char* name, int event)
	{
		this->elements.insert(new CybMenuNode(name,event));	
		this->submenu.insert(NULL);		
		size++;
	}
	

	void CybMenu::add(char* name, CybMenu* submenu)
	{
		this->elements.insert(new CybMenuNode(name,size));	
		this->submenu.insert(submenu);	
		size++;
	}


	void CybMenu::createMenu()
	{
		CybMenu::createSubMenu(this);	
		glutAttachMenu(this->bottom);
	}


	void CybMenu::createSubMenu(CybMenu* submenu)
	{
		if(submenu == NULL) return;
		else
		{
			for(int i = 0; i < submenu->size; i++)
				createSubMenu(submenu->submenu.pos(i));	// creates the sons
		}

		submenu->id = glutCreateMenu(submenu->mainFunction);	//create the menu

		for(int i = 0; i < submenu->elements.size(); i++)
		{
			if(submenu->submenu.pos(i) && submenu->elements.pos(i))
			{
				glutAddSubMenu(submenu->elements.pos(i)->name, submenu->submenu.pos(i)->id);	
				
			}
			else if(submenu->elements.pos(i))
			{		
				glutAddMenuEntry(submenu->elements.pos(i)->name,submenu->elements.pos(i)->event);
				
			}
		}
	}


	int CybMenu::getEvent(char* name)
	{
		for(int i = 0; i < this->elements.size(); i++)		
			if(!strcmp(name,elements.pos(i)->name))  return elements.pos(i)->event;	
		
		return -1;
	}


	char* CybMenu::getName(int index)
	{
		if(index > size || index < 0) return NULL;

		return this->elements.pos(index)->name;
	}


	CybMenu* CybMenu::getNewMenu(void (*mainFunction)(int))
	{
		return new CybMenu(mainFunction);
	}


	void CybMenu::setButtom(char bottom)
	{
		if(bottom == 'r' || bottom == 'R') this->bottom = GLUT_RIGHT_BUTTON;
		else 
		if(bottom == 'l' || bottom == 'L') this->bottom = GLUT_LEFT_BUTTON;
		else 
		if(bottom == 'm' || bottom == 'M') this->bottom = GLUT_MIDDLE_BUTTON;
	}



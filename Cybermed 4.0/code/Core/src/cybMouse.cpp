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

#include "cybMouse.h"

	CybMouse*  CybMouse::singletonInstance;
	tMouseListeners CybMouse::listenersList;
	tMouseListeners::iterator CybMouse::it;

	/** Constructor*/
	CybMouse::CybMouse()
	{ 
		//this->listenersList = new list<tMouseListeners>();
	}
	
	CybMouse *CybMouse::getInstance() { return singletonInstance; }


	void CybMouse::addMouseListener(CybMouseListener* listener) {
		listenersList.push_back(listener);
	}

	void CybMouse::mouse(int button, int state, int x, int y)
	{
		CybParameters *cybCore = CybParameters::getInstance();
	
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			cybCore->moving = 1;
			cybCore->initialX = x;
			cybCore->initialY = y;
			glutSetCursor(GLUT_CURSOR_CYCLE);
		}
		else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			cybCore->moving = 0;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	
		if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		  //cout << "RIGHT AND UP" << endl;
		  //if(cybCore->isMenuOn()) cout << "isMenuOn = TRUE" << endl; else cout << "isMenuOn = FALSE" << endl;
		  //if(cybCore->mouseOn) cout << "mouseOn = TRUE" << endl; else cout << "mouseOn = FALSE" << endl;
			if(cybCore->isMenuOn() && cybCore->mouseOn){
				//cout << "Entrei nas duas condições" << endl;
				this->createMenu();
			}
		}
		
		glutPostRedisplay();
	}
	
	
	void CybMouse::mouseMove(int x, int y)
	{
		CybParameters *cybCore = CybParameters::getInstance();
	
		float xSpeed = 0.4166; 
		float ySpeed = 0.4166; 
	
		if(cybCore->moving)
		{


			cybCore->setAngle(cybCore->getXAngle() + ((double)(y - cybCore->initialY)*ySpeed), cybCore->getYAngle() + ((double)(x - cybCore->initialX)*xSpeed), 0);
			//cybCore->yAngle = cybCore->yAngle + ((double)(x - cybCore->initialX)*xSpeed);
			//cybCore->xAngle = cybCore->xAngle + ((double)(y - cybCore->initialY)*ySpeed);
			cybCore->initialX = x;
			cybCore->initialY = y;
			cybCore->transforChange = true;

			for(it = listenersList.begin(); it != listenersList.end(); it++) {
				(*it)->mouseEventPerformed(x, y);
			}
		}
	
		glutPostRedisplay();
	}
	
	
	void CybMouse::createMenu()
	{		
		
		CybParameters *cybCore= CybParameters::getInstance();	
	
		static CybMenu *submenu1 = CybMenu::getNewMenu(LayerMenu);
		static CybMenu *submenu3 = CybMenu::getNewMenu(HapticsMenu);
		static CybMenu *menu  = CybMenu::getNewMenu(MainMenu);
		static bool wasCreated = false;	
		int i;
		
		if(!wasCreated)
		{
			for (i=0; i < cybCore->numLayer; i++)
				submenu1->add(cybCore->getLayerName(i), i);	
	
			if(cybCore->hapticsPlugged[0]) // haptics device is on
			{		
				submenu3->add("Activate", 0);
				submenu3->add("Deactivate", 1);
			}
	
			if(cybCore->numLayer) menu->add("Layer",submenu1);
		
			if(cybCore->hapticsPlugged[0]) // haptics device is on
				menu->add("Haptic Interaction",submenu3);					
	
			menu->add("Help",0);
			menu->add("Exit",1);
	
			menu->setButtom('r');
			wasCreated = true;
		}
		menu->createMenu();
	}
	
	
	void CybMouse::HapticsMenu(int op)
	{	
		CybParameters *cybCore = CybParameters::getInstance();
	
		switch (op)
		{
		case 0:
			if(!cybCore->mouseOn){
				cybCore->phantomOn = true;
				CybParameters::setCollisionStatus(true);
			}
			else
				cout << "Error! Phantom interaction cannot be started at the " 
				<< "same time that the mouse is activated. \n"
				<< "Deactivate the mouse interaction first.\n";
			break;
		case 1:
			//cybCore->phantomOn = false;
			//CybParameters::setCollisionStatus(false);
			break;
		}
	}
	
	void CybMouse::MainMenu(int op)
	{
		switch (op)
		{
		case 0:
	
			break;
		case 1: 	exit(0);
		break;
		}
	}
	
	void CybMouse::LayerMenu(int op)
	{
		CybParameters *cybCore = CybParameters::getInstance();
	
		if(cybCore->habLayer[op] == 1)
			cybCore->habLayer[op] = 0;
		else
			cybCore->habLayer[op] = 1;
	
		glutPostRedisplay();
	}

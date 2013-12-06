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

#ifndef CYBMOUSEINTERACTION_H
#define CYBMOUSEINTERACTION_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "cybParameters.h"
#include "cybInterator.h"
#include "cybMouseInterator.h"
//class CybMouseInterator;

/**
@class		CybMouseInteraction 
@file		cybMouseInteraction.h 
@short
	Mouse interaction class

@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.0
@date		2007, July
*/
class CybMouseInteraction {
	
public:
	bool mouseRightClicked;		/**< Flag that indicates if the right mouse button was clicked. */
	bool mouseMiddleClicked;	/**< Flag that indicates if the middle mouse button was clicked. */
	bool mouseLeftClicked;		/**< Flag that indicates if the left mouse button was clicked. */

private:
	int yAnt;			/**< Previous y coordinate state. */
	int previousX;			/**< Previous x coordinate state. */
	int previousY;			/**< Previous y coordinate state (differnt kind of use from yAnt). */
	int previousZ;			/**< Previous z coordinate state. */
	int windowHeight;		/**< Viewing window height. */
	float previousXCoord;		/**< Previous x coordinate state for focus calculations. */
	float previousYCoord;		/**< Previous y coordinate state for focus calculations (differnt kind of use from yAnt). */
	float previousZCoord;		/**< Previous z coordinate state for focus calculations. */
	float xP;			/**< Projection coordinate */
	float yP;			/**< Projection coordinate */
	float zP;			/**< Projection coordinate */
	float xi;			/**< Coordinate obtained by mouse interaction */
	float yi;			/**< Coordinate obtained by mouse interaction */
	float zi;			/**< Coordinate obtained by mouse interaction */
	float initzi;			/**< Initial value of zi Coordinate */
	float proportionX;		/**< Proportion calculated on the x axis for the coordinates of the interator */
	float proportionY;		/**< Proportion calculated on the y axis for the coordinates of the interator */

	int layerInteracted;		/**< Layer to be interacted */

	bool firstTime;			/**< Variable used to check if the function getEnvironmentData() is being used for the fisrt time. */
	CybParameters *cybCore;
	static CybMouseInteraction singletonInstance;		/**< The unique instance*/
		
	
private:

	CybMouseInterator* mouseInterator;

	/** Constructor */
	CybMouseInteraction();

public:
	/** Get the singleton instance of CybMouseInteraction */
	static CybMouseInteraction *getInstance();

	/**	Function that obtains data from the virtual environment.
	The data obtained are the projection, modelview and viewport matrix.
	@param void
	@return void
	*/
	void getEnvironmentData();

	/**	Mouse interaction function
		Sets the states of the mouse buttons.
	@param int button
	@param int state
	@param int x
	@param int y
	@return void
	*/
	void mouseInteraction(int button, int state, int x, int y);

	/**	Mouse motion interaction function.
		The interaction on the xz plane occurs here when the right mouse button is clicked.
	@param int x
	@param int y
	@return void
	*/
	void mouseMoveInteraction(int x, int y);

	/**	Mouse motion interaction function.
		The interaction on the xy plane occurs here.
	@param int x
	@param int y
	@return void
	*/
	void mousePassiveMoveInteraction(int x, int y);

	void setMouseInterator(CybMouseInterator* mouseInterator);

	CybMouseInterator* getMouseInterator();
};

#endif /*CYBMOUSEINTERACTION_H*/

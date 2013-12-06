// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#ifndef CYBGLOVEINTERATOR_H_
#define CYBGLOVEINTERATOR_H_

/**
	@class CybGloveInterator
	@file cybGloveInterator.h 
	@short
			
		This class is a interator for data gloves.
	
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2011, October
*/


#include <string>

#include "cybInterator.h"
#include "cyb5DTGlove.h"

using namespace std;

class CybGloveInterator : public CybInterator {
public:
	/** Constructor 
	receive a string that idicates the glove type
	*/
	CybGloveInterator(string type);
	/** Constructor
	receive two strings that indicates the glove type and the port where the glove is connected
	*/
	CybGloveInterator(string type, string port);
	/** Destrucotor */
	~CybGloveInterator();
	
	/** Return the gloveDevice
	@param void
	@return CybDevice *
	*/
	virtual CybDevice *getDevice();
	
	/** Create a id for this interator
	@param int
	@return void
	*/
	virtual void create(int id);
	/** Stop this interator
	@param void
	@return void
	*/
	virtual void destroy();
	
	/** Draw the interator
	@param coid
	@return void
	*/
	virtual void drawInterator();
	
	static CybInterator* getInterator();

private:
	CybGlove *gloveDevice;
	bool firstTime;
	
	/** Function called by Draw to draw the glove interator
	@param void
	@return void
	*/
	void drawGloveInterator();
};


#endif //CYBGLOVEINTERATOR_H_

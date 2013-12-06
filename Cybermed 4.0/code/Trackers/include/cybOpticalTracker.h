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

#ifndef CYBOPTICALTRACKER_H_
#define CYBOPTICALTRACKER_H_

#ifdef CYBOPTICALTRACKER_H

#include "cybTracker.h"

/**
 * @class CybOpticalTracker
 * @file CybOpticalTracker.h 
 * @short This class defines a Optical tracker.
 * 
 *
 *  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2008, July
 * 
 */

class CybOpticalTracker : public CybTracker
{
public:

	/** Constructor */
	CybOpticalTracker();

	/** Destructor */
	virtual ~CybOpticalTracker();
	
protected:
	
	 /**
  	 * Return the 3D position tracked
  	 * 
  	 * @param double *position
  	 * @return void
  	 * 
  	 */ 
	virtual void getPosition(double *position){};

	 /**
  	 * Create and configure an instance of a Optical tracker
  	 * 
  	 * @param void *userdate
  	 * @return void
  	 * 
  	 */ 
	virtual void createTracker(void *userData){};
	
};

#endif //CYBOPTICALTRACKER_H

#endif //CYBOPTICALTRACKER_H_

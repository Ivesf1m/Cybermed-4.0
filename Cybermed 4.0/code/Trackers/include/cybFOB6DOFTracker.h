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

#ifndef CYBFOB6DOFTRACKER_H_
#define CYBFOB6DOFTRACKER_H_

#include "cybMagneticTracker.h"

#include "fob/fob.h"
#include "fob/mathematics.h"
#include <GL/glut.h>



/**
 	@class	CybFOB6DOFTracker
 	@file	cybFOB6DOFTracker.h 
 	@short
		This class defines a magnetic tracker based on Flocks of Birds (FOB).
		This class uses libfob library to communicate with FOB.
		***** use one sensor (until now) *****
		
 
	@author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 	@version 1.0
 	@date 2009, July
  
 */

class CybFOB6DOFTracker : public CybMagneticTracker
{
	private:	

	fob::fob flockGlobal;			// Global FOB
	char *port;				// Default Port
	fob::hemisphere hemisphere;		// Default Hemisphere
	fob::port_speed speed;			// Default Port speed
	int birdsOn;				// Number of FOB Birds


	GLfloat posx;				// Initial X position
	GLfloat posy;				// Initial Y position
	GLfloat posz;				// Initial Z position
	GLfloat scale;				// Scale of position values


	GLfloat matrixIn[16];			// Matrix with informations
						// about initial position and
						// orientation of the fob
						// sensor
	
	public:
	/** Constructor*/
	CybFOB6DOFTracker();

	/** Destructor */
	~CybFOB6DOFTracker();
	
	bool flockON;			// Indicate if FOB is on


	/**
  	 * This method is used to set the port where the Tracker device is conected
  	 * 
  	 * @param char *device_port
  	 * @return void
  	 * 
  	 */ 
	void setTrackerPort(char *device_port);


	/**
  	 * This method is used to set the hemisphere where the Tracker will work
  	 * 
  	 * @param fob::hemisphere hemisphere
  	 * @return void
  	 * 
  	 */ 
	void setTrackerHemisphere(fob::hemisphere hemisphere);

	/**
  	 * This method is used to set the scale factor of tracker position
  	 * 
  	 * @param float newScale
  	 * @return void
  	 * 
  	 */ 
	void setScale(float newScale);



	/**
  	 * This method is used to init the FOB, get birds list and initial matrix
  	 * 
  	 * @param void
  	 * @return void
  	 * 
  	 */ 
	void initDevice(void);

	virtual void createTracker(void *userData);

	/**
  	 * This method is used to create and config an instance of tracker
  	 * 
  	 * @param void
  	 * @return void
  	 * 
  	 */ 
	void createTracker(void);

	/**
  	 * This method is used to check if tracker is enable
  	 * 
  	 * @param void
  	 * @return bool
  	 * 
  	 */ 
	bool isTrackerEnable(void);


	/**
  	 * This method is used to stop the FOB
  	 * 
  	 * @param void
  	 * @return void
  	 * 
  	 */ 
	void stopDevice(void);


	/**
  	 * This method return the 3D position of the tracked object
  	 * 
  	 * @param float *position (posx, posy, posz)
  	 * @return void
  	 * 
  	 */ 
	void getInitialPosition(float *position);


	/**
  	 * This method return the 3D position of the tracked object
  	 * 
  	 * @param float *position
  	 * @return void
  	 * 
  	 */ 
	void getPosition(float *position);


	/**
  	 * This method reset the initial position of the tracked object
  	 * 
  	 * @param void
  	 * @return void
  	 * 
  	 */ 
	void resetInitialPosition(void);


	 /**
  	 * This method should set a orientation matrix in 4x4 matrix
  	 * 
  	 * @param float *matrix
  	 * @return void
  	 * 
  	 */ 
	void getMatrix(float *matrix);


	/**
	 * This method is used to set a matrix from the row major format for
	 * collumn major format
	 *
	 * @param float *matrix
	 * @return void
	 *
	 */
	void transposeMatrix(float *matrix);

};

#endif //CYBFOB6DOFTRACKER_H_

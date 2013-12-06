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

#ifndef CYBGLOVE_H_
#define CYBGLOVE_H_

/**
	@class CybGlove
	@file cybGlove.h 
	@short
			
		This class to provide an abstract implementation with the necessary	
		methods for the inclusion of data glove devices to the applications that use the Cybermed
	
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2011, October
*/

#include "cybDevice.h"
#include <string> 
using namespace std;

class CybGlove : public CybDevice {
	public: 
	enum CybGloveHand {CYB_HAND_LEFT, CYB_RIGHT_HAND}; //return enum of getGloveHand function
	
	/** Destructor */
	virtual ~CybGlove();
	
	CybGlove();
	
	/** Initialize glove device
	@param void 
	@return void 
	*/
	virtual void initDevice() = 0;
	
	/** Stop glove device
	@param void 
	@return void
	*/	
	virtual void stopDevice() = 0;
	
	/** Obtains the most recent scaled (between 0 and 1) sensor values from the
	currently connected glove.
	@param float *
	@return void
	*/
	virtual void getSensorScaledAll(float *data) = 0;
	
	/** Obtains the most recent scaled (between 0 and 1) value for a specific sensor
	from the currently connected glove.
	@param int
	@return float
	*/	
	virtual float getSensorScaled(int sensor) = 0;
	
	/** Obtains the number of available sensors.
	@param void
	@return int
	*/
	virtual int getNumSensors() = 0;
	
	/** Get the glove hand, left or right {CYB_HAND_LEFT, CYB_RIGHT_HAND}
	@param void
	@return int
	*/
	virtual int getGloveHand() = 0;
	
	/** Return glove's name 
	@param void
	@return string
	*/
	virtual string getGloveName() = 0;
	
	bool deviceIsEnable();
	
	void setEnable(bool flag);
	
	void setPort(string portName) {
	port = portName;
	}

	string getPort() {
	return port;
	}
	
	protected:
		bool enable;
		string port;
	
};

#endif //CYBGLOVE_H_

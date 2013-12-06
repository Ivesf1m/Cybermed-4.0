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

#ifndef CYB5DTGLOVE_H_
#define CYB5DTGLOVE_H_

#include "fglove.h" // 5DT SDK
#include "cybGlove.h"
using namespace std;

/**
	@class Cyb5DTGlove 
	@file cyb5DTGlove.h 
	@short
		This class provide a higher level manipulation of the glove device.
		This class can be used for any data glove 5DT 	

	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2011, October
*/

class Cyb5DTGlove : public CybGlove {
	public:
	/**Constructor**/
	Cyb5DTGlove();
	/** Constructor
	@param string 
	This constructor receive a string that indicates a port where the glove is connected, 
	In the default constructor is /dev/usb/hiddev0	
	*/
	Cyb5DTGlove(string port);
	/**Destructor**/
	virtual ~Cyb5DTGlove();
	
	/** Initialize glove device
	@param void 
	@return void 
	*/
	virtual void initDevice();
	/** Stop glove device
	@param void 
	@return void 
	*/
	virtual void stopDevice();
	
	
	/** Get the glove hand, left or right {CYB_HAND_LEFT, CYB_RIGHT_HAND}
	@param void
	@return int
	*/
	virtual int getGloveHand();
	
	/** Obtains the type of the currently connected glove
	Returns one of FD_GLOVENONE, FD_GLOVE7, FD_GLOVE7W, FD_GLOVE16
	FD_GLOVE16W, FD_GLOVE14U, FD_GLOVE14UW, or FD_GLOVE14U_USB, as
	defined by the enumerated type EfdGloveTypes.
	@param void
	@return int
	*/
	int getGloveType();
	
	/** Obtains the number of available sensors values the driver can make available.
	Returns the number of sensors. Currently it is fixed at 18, but future 5DT driver
	releases may differ.
	@param void
	@return int
	*/
	virtual int getNumSensors();
	
	/** Return glove's name 
	@param void
	@return string	
	The string returned can be:
	None
	Data Glove 5 Ultra
	Data Glove 5 Ultra W
	Data Glove 5 Ultra USB
	Data Glove 5
	Data Glove 5W
	Data Glove 16
	Data Glove 16W
	DG14 Ultra serial
	DG14 Ultra W
	DG14 Ultra USB
	*/
	virtual string getGloveName();
	
	/** Obtains the most recent raw sensor values (array data) from the currently connected glove.
	@param int *
	@return unigned short
	*/
	void getSensorRawAll(unsigned short *data);
	
	/** Obtains the most recent raw sensor value for a specific sensor from the
	currently connected glove.
	@param int
	@return unsigned short	
	*/
	unsigned short getSensorRaw(int sensor);
	
	/** Forces the raw value for all the sensors. The values for each sensor are in data param)
	@param unsigned short *
	@return void
	*/
	void setSensorRawAll(unsigned short *data);
	
	/** Forces the raw value for a specific sensor.
	@param int, unsigned short
	@return void
	*/	
	void setSensorRaw(int sensor, unsigned short raw);
	
	/** Obtains the most recent scaled (auto-calibrated) sensor values from the
	currently connected glove.
	@param float *
	@return void
	*/
	virtual void getSensorScaledAll(float *data);
	
	/** Obtains the most recent scaled (auto-calibrated) value for a specific sensor
	from the currently connected glove.
	@param int
	@return float
	*/	
	virtual float getSensorScaled(int sensor);
	
	
	/** Obtains the number of available gestures that can be recognized by the glove driver.
	@param void
	@return int
	*/
	int getNumGestures();
	
	/** Obtains the current gesture being performed.
	@param void
	@return int
	*/
	int getGesture();
	
	/** Obtains the current auto-calibration settings of the driver. 
	@param unsigned short * 
	@param unsigned short *
	@return void	
	*/
	void getCalibrationAll(unsigned short *pUpper, unsigned short *pLower);
	
	/** Obtains the current auto-calibration settings of the driver for a specific sensor.
	@param int, unsigned short *
	@param unsigned short *
	@return void
	*/
	void getCalibration(int sensor, unsigned short *pUpper, unsigned short *pLower);
	
	/** Resets the current auto-calibration settings of the driver to user defined values.
	@param unsigned short *
	@param unisgned short *
	@return void
	*/
	void setCalibrationAll(unsigned short *pUpper, unsigned short *pLower);
	
	/** Resets the current auto-calibration settings of the driver for a specific sensor to
	user defined values
	@param int
	@param usigned short
	@param unsigned short
	@return void
	*/
	void setCalibration(int sensor, unsigned short nUpper, unsigned short nLower);
	
	/** Resets the internal auto-calibration settings of the driver to appropriate default
	values (for all the sensors).
	@param int
	@return void
	*/
	void resetCalibration(int sensor);
	
	/** Resets the internal auto-calibration settings of the driver to appropriate default
	values (for a specific sensor).
	@param void
	@return void
	*/
	void resetCalibration();
	
	/** Obtains the maximum scaled value for each sensor. 
	@param float *
	@return void
	*/
	void getSensorMaxAll(float *pMax);
	
	/** Obtains the maximum scaled value for a specific sensor.
	@param int
	@return void
	*/
	float getSensorMax(int sensor);
	
	/** Sets the maximum scaled value for each sensor.
	@param float *
	@return void
	*/
	void setSensorMaxAll(float *pMax);
	
	/** Sets the maximum scaled value for a specific sensor.
	@param int
	@param float
	@return void
	*/
	void setSensorMax(int sensor, float fMax);
	
	/** Obtains the current gesture recognition threshold settings of the driver.
	@param float *
	@param float *
	@return void
	*/
	void getThresholdAll(float *pUpper, float *pLower);
	
	/** Obtains the current gesture recognition threshold settings of the driver for a
	specific sensor.
	@param float *
	@param float *
	@return void
	*/
	void getThreshold(int sensor, float *pUpper, float *pLower);
	
	/** Sets the current gesture recognition threshold settings of the driver.
	@param float *
	@param float *
	@return void
	*/
	void setThresholdAll(float *pUpper, float *pLower);
	
	/** Sets the current gesture recognition threshold settings of the driver for a specific
	sensor.	
	@param int
	@param float
	@param float
	@return void
	*/
	void setThreshold(int sensor, float pUpper, float pLower);
	
	/** Obtains the information data block of the currently connected glove.
	@param unsigned char * (Array of 32 bytes that will contain the information data)
	@return void
	*/
	void getGloveInfo(unsigned char *data);
	/** Obtains the information data block of the driver.
	@param void
	@return string
	*/
	string getDriverInfo();
	
	/** Sets the Callback function
	@param void (*)()
	@return void
	*/
	void setCallback(void (*func)());
	
	/** Obtains the latest packet rate.
	@param void
	@return int
	*/
	int getPacketRate();
	
	/** Indicates if the driver has received new data since this function was last called.
	@param void
	@return bool
	*/
	bool newData();
	
	/** Obtains the major version of the glove‟s firmware.
	@param void
	@return int
	*/
	int getFWVersionMajor();
	/** Obtains the minor version of the glove‟s firmware.
	@param void
	@return int
	*/
	int getFWVersionMinor();
	
	/** Indicates if the driver is currently auto calibrating. 
	@param void
	@return bool
	*/
	bool getAutoCalibrate();
	
	/** Turns auto calibration on or off.
	@param bool
	@return bool
	*/
	bool setAutoCalibrate(bool bAutoCalibrate);
	
	/** Saves the current calibration values to file.
	@param string
	@return bool
	*/
	bool saveCalibration(string fileName);
	
	/** Loads calibration values from file. Current calibration values are discarded.
	@param string
	@return bool
	*/ 
	bool loadCalibration(string fileName);
	
	/** Scans the USB for available gloves.
	@param unsigned short *
	@param int &
	@return int 
	*/
	int scanUSB(unsigned short *aPID, int &NumMax);
	
	private:
	fdGlove *glove; //5DT glove type, defined in fglove.h
};
#endif//CYB5DTGLOVE_H_


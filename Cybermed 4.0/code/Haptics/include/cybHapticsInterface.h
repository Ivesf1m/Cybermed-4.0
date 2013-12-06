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

#ifndef CYBHAPTICSINTERFACE_H
#define CYBHAPTICSINTERFACE_H

/**
	@class CybHapticsInterface 
	@file cybHapticsinterface.h 
	@short
			
		This class to provide an abstract implementation with the necessary	
		methods for the inclusion of haptic devices to the applications that use the Cybermed
	
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2007, July
*/
#include "cybDevice.h"

class CybHapticsInterface : public CybDevice {

public:

  /** Constructors*/
	CybHapticsInterface()
	{
	}


  	/** Get current device position
	@param double* position
	@return void
	*/		
  virtual void getCurrentProxyPosition(double * position){}
    
  
	/** Indicates if haptic device is enable
	@param void 
	@return bool
	*/
  virtual bool  deviceIsEnable() = 0;
    
  
	/** Initialize haptic device
	@param void 
	@return void 
	*/
  virtual void initDevice() = 0;
    
  
 	/** Stop haptic device
	@param void 
	@return void
	*/	
  virtual void stopDevice() = 0;
    
  
	/** Update haptic workspace
	@param void 
	@return void
	*/	
  virtual void updateWorkspace() = 0;
    
  
	/** Get haptic scale factor
	@param void 
	@return double
	*/
  virtual double  getHapticScaleFactor(){}
    
  
	/** Get proxy transformation matrix
	@param double 
	@return void
	*/
  virtual void getProxyTransformationMatrix(double * transMatrix) = 0;
    
	/** Get current force intensity applied for haptic device
	@param double force[]
	@return void
	*/
  virtual void getCurrentForceIntensity(double * force){}
    
  
	/** Get haptic device torque
	@param double torque[]
	@return void
	*/	
  virtual void getTorque(double *torque){}

	/** Get proxy rotation
	@param double rotation[]
	@return void
	*/	

  virtual void getProxyRotation(double *rotation){}
    
  
	/** Draw haptic scene
	@param void
	@return void 
	*/  
  virtual void drawHaptics() = 0;
    
  
	/** This method can be used for to verify haptic rendering erros and/or calibration status
	@param void
	@return void 
	*/
  virtual void  IdleHaptics(){}
    
};
#endif //CYBHAPTICSINTERFACE_H

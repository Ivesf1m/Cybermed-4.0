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

#ifndef _CYBOPENHPHANTOM_H
#define _CYBOPENHPHANTOM_H

#include "cybHapticsInterface.h"
#include "cybPhantom.h"

/**
	@class CybOpenHPhantom 
	@file cybOpenHPhantom.h 
	@short
		This class provide a higher level manipulation of the haptic device and haptic rendering

	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2007, July
*/

class CybOpenHPhantom : public CybHapticsInterface
{
	
	private:
	CybPhantom hapticHandle;/**< CybHaptic instace*/	
	CybParameters *cybCore;/**< CybParameters instace*/
	bool guided;
	double position[3];
	
	public:
	   
	/** Constructor*/
	CybOpenHPhantom();
	
	/** Destructor*/
	~CybOpenHPhantom();
		
	/** Get the current device position
	@param int coord
	@return double
	*/		
	double getCurrentProxyPosition(int coord);
	
	/** Get the current device position
		@param double position
		@return void
	 */
	void getCurrentProxyPosition(double *position);
	
	/** Get the last proxy position
	@param double position
	@return void
	*/
	void getLastProxyPosition(double *lastPosition);
		
	/** Get the last proxy position
		@param int position
		@return void
	 */	
	double getLastProxyPosition(int coord);
	
	/** Indicates if haptic device is enable
	@param void 
	@return bool
	*/
	bool deviceIsEnable();
	
	/** Initialize haptic device
	@param void 
	@return void 
	*/	
	void initDevice();
	
	/** Stop haptic device
	@param void 
	@return void
	*/	
	void stopDevice();
	
	/** Update haptic workspace
	@param void 
	@return void
	*/	
	void updateWorkspace();
	
	/** Get haptic scale factor
	@param void 
	@return double
	*/
	double getHapticScaleFactor();
		
	/** Get proxy transformation matrix - ALPHA VERSION
	@param double 
	@return void
	*/
	void getProxyTransformationMatrix(double transMatrix[]);
	
	/** Get current force intensity applied for haptic device
	@param double force[]
	@return void
	*/
	void getCurrentForceIntensity(double *_force);
		
	/** Get last force intensity applied for haptic device
		@param double force[]
		@return void
	 */
	void getLastForceIntensity(double *_lastForce);
	
	/** Get haptic device torque
	@param double torque[]
	@return void
	*/	
	void getTorque(double *_torque);
		
	/** Get device gimbal angle
	@param double gimbalAngle[]
	@return void
	*/
	void getDeviceGimbalAngle(double *_gimbalAngle);
	
	/** Get device joint angle
	@param double jointAngle[]
	@return void 
	*/
	void getDeviceJointAngle(double *_jointAngle);
	
	/** Get proxy rotation - Don't use
	@param double rotation[]
	@return void 
	*/
	void getProxyRotation(double _rotation[]);
	
	/** Get current force intensity applied for haptic device
	@param int coord
	@return double
	*/
	double getCurrentForceIntensity(int coord);
	
	/** Get last force intensity applied for haptic device
	@param int coord
	@return double
		*/
	double getLastForceIntensity(int coord);
	
	/** Get haptic device torque
	@param int coord
	@return double
	*/
	double getTorque(int coord);
	
	/** Get device gimbal angle
	@param int coord
	@return double
	*/		
	double getDeviceGimbalAngle(int coord);
		
	/** Get device joint angle
	@param int coord
	@return double 
	*/
	double getDeviceJointAngle(int coord);

	  
	/** Draw haptic scene
	@param void
	@return void 
	*/  
	void drawHaptics();
		
	/** This method verifies haptic rendering erros and calibration status
	@param void
	@return void 
	*/
	void IdleHaptics();

		
	void getDevicePosition(double position[]);


	void getDeviceRotation(double rotation[]);

	/** Set cursor size pixel
	@param int size
	@return void 
	*/
	void setCursorSizePixels(int size);

	void setGuided(bool guided);

	bool isGuided();

	void setAnchorPosition(float x, float y, float z);

	void setCurrentForceIntensity(const HDfloat* _force);

	void setTorque(const HDfloat* _torque);

	/** Create haptics Layers for haptic rendering
	@param void 
	@return void 
	*/
	void createHapticLayers(int numLayers, bool defaultInitialization);

	/** Enable layer for haptic rendering
	@param void 
	@return void 
	*/
	void enableHapticLayer(int layerId);
	
	/** Disable for haptic rendering
	@param void 
	@return void 
	*/
	void disableHapticLayer(int layerId);
	
		
	/** Enable material properties of all haptics layers
	@param void 
	@return void 
	*/
	void enableHapticMaterialProperty();
		
	/** Disable material properties of all haptics layers
	@param void 
	@return void 
	*/
	void disableHapticMaterialProperty();
	
	
	/** Disable a haptic layer material property
	@param int layerId 
	@return void 
	*/
	void disableHapticLayerMaterial(int layerId);
	
	/** Enable a haptic layer material property
	@param int layerId 
	@return void 
	*/
	void enableHapticLayerMaterial(int layerId);


	/** Create an ambient property
	@param void 
	@return void 
	*/		
	void createAmbientProperty();
	
	/** Enable the ambient property rendering
	@param void 
	@return void 
	*/
	void enableAmbientProperty();
	/** Disable the ambient property rendering
	@param void 
	@return void 
	*/	
	void disableAmbientProperty();

	/** Destroy the ambient properties attributes
	@param void 
	@return void 
	  */
	void destroyAmbientProperty();

};
#endif

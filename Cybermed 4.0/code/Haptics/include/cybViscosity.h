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

#ifndef __CYBVISCOSITY_H_
#define __CYBVISCOSITY_H_

#include <iostream>

#include <HD/hd.h>
#include <HDU/hdu.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>
#include <HL/hl.h>
#include <HLU/hlu.h>

#include "cybMaterialPropertyDefinitions.h"
/**
	@class CybViscosity 
	@file cybViscosity.h 
	@short
		This class is responsible for the inclusion of the viscosity to the applications that use Phantom family haptic device
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2007, July
*/

using namespace std;
class CybViscosity
{
	public:
	typedef struct ViscosityProperties
		{
			HLenum currentFace;
			float gain;
			double forceMag;
			EnumFace faceID;
			int id;
			ViscosityProperties()
			{
				currentFace = HL_FRONT;
				gain = 0.0;
				forceMag = 0.0;
				faceID = FRONT;
				id = 0;
			}
		}ViscosityShape; /**< Structure that contain the viscosity shape properties*/

	private:

	int stackControl;/**< control the property stack*/
	int numViscosityLayers;/**< Number of viscosity shapes*/	

	float viscosityCons;/**< Current viscosity constant*/
	
	bool viscousHandleIsEnable; /**< Boolean variable that indicate if the viscosity thread is enable*/
	bool handleIsEnable; /** Boolean variable that indicate if the viscosity system handler is enable*/

	static int ID; /** Identity of the currently touched layer*/
	static bool untouchOn; /** Indicate when the proxy untouch a haptic layer*/
	static bool solPerfurOn;/** Indicates when the magnitude of a force was exceeded requesting the popthrough*/
	static ViscosityShape **stackViscousAtribbute;/** Stack of viscous attributes*/
	static ViscosityShape *currentViscousProperty;/** Current viscous attribute*/
	
	static CybViscosity *singletonInstance;		/**< The singleton instance*/

	HDSchedulerHandle handle; /**< viscosity thread reference*/
	HDSchedulerHandle viscousHandle;/**< viscosity system handler reference*/

	public:
	
	static ViscosityShape *ViscosityShapeAttribute;	/**< List of viscosity shapes attributes*/
	
	private:
	
	/** Constructor*/
	CybViscosity();
	
	/** Constructor
	@param int numLayer
	*/	
	CybViscosity(int numLayers);

	public:

	/** Destructor*/
	~CybViscosity();

	public:
	
	/** Get the CybViscosity instance
	@param void
	@return CybViscosity *
	*/
	static CybViscosity *getInstance();
	
	/** Get the CybViscosity instance
	@param int numLayers
	@return CybViscosity *
	*/
	static CybViscosity *getInstance(int numLayers);
	

	/** Initialize the visocity shape attributes
	@param EnumFace face
	@param float gain
	@param double forceMag
	@param int layerID
	*/
	void initStatus(EnumFace face,	
			float gain,	
			double forceMag, 
			int layerID);
	
	/** Start the ambient property
	@param void
	@return void
	*/
	void startAmbientProperty();

	/** Stop the ambient property
	@param void
	@return void
	*/
	void stopAmbientProperty();

	/** Unscheduler the viscosity thread and viscosity handler
	@param void
	@return void
	*/

	void destroyAmbientProperty();
	
	/**Callback function that is called when an object was touched, preparing the viscosity property for a possible layer transaction
	@param HLenum event
	@param HLuint object
	@param HLenum thread
	@param HLcache* cache
	@param void* userdata
	@return void		
	*/

	static void HLCALLBACK touchShapeCallback(HLenum event,
						HLuint object, HLenum thread,
						HLcache *cache, void *userdata);

	/**Callback function that is called when an object was untouched
	@param HLenum event
	@param HLuint object
	@param HLenum thread
	@param HLcache* cache
	@param void* userdata
	@return void		
	*/
	static void HLCALLBACK untouchShapeCallback(HLenum event,
						HLuint object,
						HLenum thread,
						HLcache *cache,
						void *userdata);

	/**Callback function that is called when the interator is moving on object, preparing the viscosity property for a possible layer transaction
	@param HLenum event
	@param HLuint object
	@param HLenum thread
	@param HLcache* cache
	@param void* userdata
	@return void		
	*/
	static void HLCALLBACK movingObjectCallback(HLenum event,
						HLuint object,
						HLenum thread,
						HLcache *cache,
						void *userdata);

		
	private:
	
	/**Push a viscosity attribute on top of stack
	@param ViscosityShape* shapeVis
	@return int		
	*/	
	int pushAttribute(ViscosityShape *shapeVis);

	/**Pop a viscosity attribute of top of stack
	@param void
	@return ViscosityShape*
	*/
	ViscosityShape *popAttribute();

	/**Indicate if the attributes stack is empty
	@param void
	@return bool
	*/
	bool isStackEmpty();

	/**Update the attribute stack for each ambient and your viscosity constant
	@param float gGain
	@param EnumFace faceID
	@param int objectID
	@param HLenum currentFace
	*/
	void updateEffect(float gGain,
			EnumFace faceID,
			int objectID,
			HLenum currentFace);
	
	static HDCallbackCode HDCALLBACK ViscousForceCallback(void *pUserData);
	
	static HDCallbackCode HDCALLBACK handleAmbientCB(void *pUserData);

};

#endif /* __CYBVISCOSITY_H_ */

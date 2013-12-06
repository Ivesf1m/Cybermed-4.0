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


#ifndef __CYBHAPTICS_H_
#define __CYBHAPTICS_H_

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <assert.h>


#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <HD/hd.h>
#include <HDU/hdu.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>
#include <HL/hl.h>
#include <HLU/hlu.h>

#ifndef MF_H
#include "mf/mf.h"
#endif

#ifndef CYBPARAMETERS_H
#include "cybParameters.h"
#endif

#ifndef __CYBVISCOSITY_H_
#include "cybViscosity.h"
#endif

/**
	@class CybHaptics 
	@file cybHaptics.h 
	@short
		This class is responsible for the inclusion of the haptic context to the applications, well as the management of the 
		haptic devices. 

	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2007, July
*/

class CybPhantom
{
	
	typedef struct
	{
		hduVector3Dd force;
		hduVector3Dd lastForce;
		hduVector3Dd torque;
		hduVector3Dd gimbalAngle;
		hduVector3Dd jointAngle;
		hduVector3Dd pos;
		hduVector3Dd lastPos;
		HDdouble rotation[4];
		int flagState;
	}HapticState;/**< Structure that contains information about haptic device's states*/
	
	typedef struct
	{
		bool calibrationOk;
		HDenum calibrationType;
		HLenum hlCalibrationType;
		HDenum calibrationStatus;
	}CalibrationState;/**< Structure that contains information about haptic device's calibration states*/

	typedef struct Property
	{
		HDfloat stiffness;
		HDfloat damping;
		HDfloat static_friction;
		HDfloat dynamic_friction;
		HDfloat popthrough;
		HLenum propertyFace[5];
		Property()
		{
			stiffness = 1.0f;
			damping = 0.0f;
			static_friction = 0.0f;
			dynamic_friction = 0.0f;
			popthrough = 1.0f;
		}
	}MaterialProperties; /**< Structures that contains the haptic property representation*/

	private:
		HHD hapticDevice;/**< Haptic device instance*/
		HHLRC hapticContext;/**< Haptic Context instace*/
		HDdouble workspacemodel[16];/**< Transformation matrix for the mapping of the graphical scene*/
		bool flagWorkspaceUpdate; /**< Workspace update flag*/
		bool shapeIdListIscreated;/**< Shape ID list flag*/
		HLenum **propertyFace;
		CybParameters *cybCore;

		static HDdouble* anchor;
		HDdouble anchorPosition[3];
		bool guided;

		bool *habHapticLayersSave;/**< Indicate if the layers properties was saved*/
	public:
		HapticState states;/**< States of haptic devices*/
		bool isEnable;/**< This flag indicates when the haptic device was initialized*/
		double scaleFactor;/**< Scale factor for haptic workspace mapping...*/
		int numHapticLayers;/**< Number of haptic layers*/
		CalibrationState stateCalibration;/**< States of haptic device calibration...*/
		HLuint *shapeId;/**< Shape id for shape we will render haptically.*/
		double cursor_size_pixel;/**< Cursor size pixel*/
		bool *habHapticLayers;/**< Layers habilited for haptic rendering*/
		bool *habHapticLayersMaterial;/**< Pointer to list of flags that enable each haptic layer material property */
		MaterialProperties *properties;/**< Reference to material property data*/
		bool materialPropertiesIsEnable;/**< This flag indicates when the material property is enable*/

		bool ambientPropertyIsEnable; /**< Indicate if the ambient property is enable*/

	public:
		/** Constructor*/
		CybPhantom();

		/** Destructor*/
		~CybPhantom();

		static HDCallbackCode HDCALLBACK setForce(void *pUserData);

		void setGuided(bool guided);

		bool isGuided();

		void setAnchorPosition(double x, double y, double z);
		
		/**	Create haptic device instance and initializes haptic device states
		@param void 
		@return void
		*/
		int initHL();
			

		/**	Set flag that indicates when the haptic device was initialized
		@param void 
		@return void
		*/
		void hapticDeviceIsEnable();
			
		/**	Show haptic device information
		@param void 
		@return void
		*/
		void showDeviceInformation();

		/**	Provide a safe closing for haptic device
		@param void 
		@return void
		*/
		void exitHL();

					
		/**	This method mapping graphical workspace for the haptic workspace
		@param void 
		@return void
		*/
		void hapticWorkspaceCalibration();
		
		/** Callback function responsible for the request and acquisition of infomações of the háptico device
		@param void *pUserData
		@return HDCallbackCode
		*/
		static HDCallbackCode HDCALLBACK getStateCB(void *pUserData);
		
		/** Update a state's flag
		0 - Force
		1 - Torque
		2 - Gimbal Angle
		3 - Joint Angle	
		4 - Device Position
			
		@param int flag_id
		@return void
		*/
		void updateState(int _flag);

		/** Callback function resposible for checking the calibration states
		@param HLenum event
		@param HLuint object
		@param HLenum thread
		@param HLcache *cache
		@param void *pUserData
		@return void
		*/
		static void HLCALLBACK checkCalibrationCB(HLenum event, HLuint object, HLenum thread,
												  HLcache *cache, void *pUserData);
		/** Haptic rendering method
		@param void 
		@return void
		*/
		void hapticRendering();
			
		/** Return haptic device instance
		@param void 
		@return HHD
		*/
		HHD getDevice();
			
		
		/** Generete list of shapes
		@param int num
		@return void
		*/			
		void genShapeIdList(int num);
		
		/** Generete list of shapes
		@param int num
		@return void
		*/
		void genProperties();

		/** Verify haptic rendering errors
		@param void 
		@return void
		*/
		void HLIdleFunc();


		/******************************************************************************
				Functions responsible for haptic device calibration
		******************************************************************************/

		/** Check calibration type
		@param CalibrationState
		@return void
		*/
		void checkCalibrationStatus(CalibrationState *pUserData);

		/** Get Calibration status
		@param CalibrationState
		@return HDEnum
		*/
		HDenum GetCalibrationStatus(CalibrationState *pState);
		
		/** Check calibration status
		@param void 
		@return HDboolean
		*/
		HDboolean CheckCalibration();
		
		/** Callback function responsible for haptic device calibration
		@param void
		@return HDCallbackCode
		*/
		static HDCallbackCode HDCALLBACK UpdateCalibrationCallback(void *pUserData);
		
		/** Callback function responsible for get calibration status
		@param void
		@return HDCallbackCode
		*/
		static HDCallbackCode HDCALLBACK calibrationServoLoop(void *pUserData);

		/** Update the material faces of the layer
		@param void
		@return void
		*/		
		void updateHapticsFaces();


		/** Create and initialize every parameters needs for generate viscosity to the scene
		@param void
		@return void
		*/
		void createAmbientContext();

		/** Save the material properties attributes
		@param void
		@return void
		*/
		void saveAttributes();
		
		/** Recover the save attributes
		@param void
		@return void
		*/
		void recoverAttributes();
};

#endif

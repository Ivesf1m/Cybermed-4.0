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

#include "cybViscosity.h"

	CybViscosity *CybViscosity::singletonInstance = NULL;
	CybViscosity::ViscosityShape *CybViscosity::ViscosityShapeAttribute = NULL;
	CybViscosity::ViscosityShape **CybViscosity::stackViscousAtribbute = NULL;
	CybViscosity::ViscosityShape *CybViscosity::currentViscousProperty = NULL;

	int CybViscosity::ID = false;
	bool CybViscosity::untouchOn = false;
	bool CybViscosity::solPerfurOn = false;

	CybViscosity::CybViscosity()
	{
		cout << " CybViscosity Error: Unknown number of layers!"<< endl;
	}
	
	CybViscosity::CybViscosity(int numLayers)
	{
		handle = HD_INVALID_HANDLE;
		viscousHandle = HD_INVALID_HANDLE;
		untouchOn = false;
		solPerfurOn = false;
		stackControl = 0;
		numViscosityLayers = numLayers + 1;
		viscousHandleIsEnable = false;
		handleIsEnable = false;
	
		stackViscousAtribbute = new ViscosityShape*[10];
		ViscosityShapeAttribute = new ViscosityShape[numViscosityLayers];
		currentViscousProperty = &ViscosityShapeAttribute[numViscosityLayers - 1];
	
		viscosityCons = ViscosityShapeAttribute[numViscosityLayers - 1].gain;
	}
	
	CybViscosity::~CybViscosity()
	{
	
		if(viscousHandleIsEnable)
		{
			hdUnschedule(handle);
			viscousHandleIsEnable = false;	
		}
	
		if(handleIsEnable){
			hdUnschedule(viscousHandle);
			handleIsEnable = false;
		}
	}
	
	CybViscosity *CybViscosity::getInstance()
	{
		if(!singletonInstance)
			singletonInstance = new CybViscosity();
		return singletonInstance;
	}
	
	CybViscosity *CybViscosity::getInstance(int numLayers)
	{
		if(!singletonInstance){
			singletonInstance = new CybViscosity(numLayers);
			return singletonInstance;
		}
		else return singletonInstance;
	}
	
	void CybViscosity::initStatus(EnumFace face,	
			float gain,	
			double forceMag, 
			int layerID)
	{
		if(face == FRONT)
			ViscosityShapeAttribute[layerID].currentFace = HL_FRONT;
		else ViscosityShapeAttribute[layerID].currentFace = HL_BACK;
	
		ViscosityShapeAttribute[layerID].gain = gain;
		ViscosityShapeAttribute[layerID].forceMag = forceMag;
		ViscosityShapeAttribute[layerID].faceID = face;
		ViscosityShapeAttribute[layerID].id = layerID;
	}
	
	void CybViscosity::startAmbientProperty()
	{			
		viscosityCons = currentViscousProperty->gain;
	
		if(!viscousHandleIsEnable){
			handle = hdScheduleAsynchronous(handleAmbientCB, this, HD_MAX_SCHEDULER_PRIORITY);
			viscousHandleIsEnable = true;
		}
	
		if(!handleIsEnable){
			viscousHandle = hdScheduleAsynchronous(ViscousForceCallback, &viscosityCons, HD_DEFAULT_SCHEDULER_PRIORITY);
			handleIsEnable = true;
		}
	}
	
	void CybViscosity::stopAmbientProperty()
	{
		if(handleIsEnable){
			hdUnschedule(viscousHandle);
			handleIsEnable = false;
		}
	}
	
	void CybViscosity::destroyAmbientProperty()
	{
		if(viscousHandleIsEnable)
		{
			hdUnschedule(handle);
			viscousHandleIsEnable = false;	
		}
	
		if(handleIsEnable){
			hdUnschedule(viscousHandle);
			handleIsEnable = false;
		}
	}
	
	void HLCALLBACK CybViscosity::touchShapeCallback(HLenum event,
			HLuint object, HLenum thread,
			HLcache *cache, void *userdata)
	{
		hduVector3Dd forceTest;
		double magnitude;
	
		int *id =  (int *) userdata;
	
		hlCacheGetDoublev(cache, HL_DEVICE_FORCE, forceTest);

		//Calculate the applied magnitude of force
		magnitude = hduVecMagnitude(forceTest);
	
		if(magnitude >= ViscosityShapeAttribute[*id].forceMag)
		{
			ID = *id;
			solPerfurOn = true;
	
			if(ViscosityShapeAttribute[*id].faceID == FRONT){
	
				ViscosityShapeAttribute[*id].currentFace = HL_BACK;
			}
			else {
	
				ViscosityShapeAttribute[*id].currentFace = HL_FRONT;	
			}
		}
		else 
		{
			solPerfurOn = false;
		}
	}
	
	void HLCALLBACK CybViscosity::untouchShapeCallback(HLenum event,
			HLuint object,
			HLenum thread,
			HLcache *cache,
			void *userdata)
	{
		untouchOn = true;
	}
	
	
	void HLCALLBACK CybViscosity::movingObjectCallback(HLenum event,
			HLuint object,
			HLenum thread,
			HLcache *cache,
			void *userdata)
	{
		hduVector3Dd forceTest;
		double magnitude;
		int *id = (int *) userdata;
	
		hlCacheGetDoublev(cache, HL_DEVICE_FORCE, forceTest);
	
		//Calculate the applied magnitude of force
		magnitude = hduVecMagnitude(forceTest);
	
		if(magnitude > ViscosityShapeAttribute[*id].forceMag)
		{		
			ID = *id;
			solPerfurOn = true;
	
			if(ViscosityShapeAttribute[*id].faceID == FRONT){
	
				ViscosityShapeAttribute[*id].currentFace = HL_BACK;
			}
			else {
	
				ViscosityShapeAttribute[*id].currentFace = HL_FRONT;	
			}
		}
		else 
		{
			solPerfurOn = false;
		}
	
	}
	
	int CybViscosity::pushAttribute(ViscosityShape *shapeVis)
	{
		if(stackControl >= 9)
		{
			fprintf(stderr, "Viscosity Error: Stack Full!");
			return 0;
		}
		else{
	
			stackViscousAtribbute[stackControl] = shapeVis;
			stackControl++;
	
		}
		return 1;
	}
	
	CybViscosity::ViscosityShape *CybViscosity::popAttribute()
	{
		if(stackControl <= 0)
		{
			fprintf(stderr, "Viscosity Error: Stack Empty!");
			return 0;
		}
		else{
	
			stackControl--;
			return stackViscousAtribbute[stackControl];
		}
	}
	
	bool CybViscosity::isStackEmpty()
	{
	
		if(stackControl == 0)
			return true;
		else return false;
	}
	
	
	void CybViscosity::updateEffect(float gGain,
			EnumFace faceID,
			int objectID,
			HLenum currentFace)
	{
		/*Update the gain and magnitude of the current effect. The effect must be active. 
			Note that not all effects will use all of these properties.*/
		if(ViscosityShapeAttribute[objectID].faceID == FRONT){
	
			pushAttribute(currentViscousProperty);
			currentViscousProperty = &ViscosityShapeAttribute[objectID];
			currentViscousProperty->faceID = faceID;
			viscosityCons = currentViscousProperty->gain;
		}
		else
		{
			currentViscousProperty->faceID = faceID;
			currentViscousProperty = popAttribute();
			viscosityCons = currentViscousProperty->gain;
		}
	}
	
	HDCallbackCode HDCALLBACK CybViscosity::ViscousForceCallback(void *pUserData)
	
	{
		HDErrorInfo error;
		hduVector3Dd velocity;
		hduVector3Dd force;
		HDfloat *Damping = (HDfloat *) pUserData;
		HDdouble kDamping;
		hdBeginFrame(hdGetCurrentDevice());
	
		hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
		hdGetDoublev(HD_NOMINAL_MAX_DAMPING, &kDamping);
	
		kDamping = kDamping*(*Damping);
	
		/* Apply a force that opposes the velocity vector. */
	
		hduVecScale(force, velocity, -kDamping);
	
		hdSetDoublev(HD_CURRENT_FORCE, force);
	
		hdEndFrame(hdGetCurrentDevice());
	
		/* Check if an error occurred while attempting to render the force */
		if (HD_DEVICE_ERROR(error = hdGetError()))
		{
			hduPrintError(stderr, &error,
					"Viscosity Erro: Detected error during scheduler callback.\n");
	
			if (hduIsSchedulerError(&error))
			{
				return HD_CALLBACK_DONE;
			}
		}
	
		return HD_CALLBACK_CONTINUE;
	}
	
	
	HDCallbackCode HDCALLBACK CybViscosity::handleAmbientCB(void *pUserData)
	{	
		CybViscosity *obj = (CybViscosity *) pUserData;		
	
		hlBeginFrame();
	
		if(untouchOn && solPerfurOn){
	
			if(ViscosityShapeAttribute[ID].faceID == FRONT){
				obj->updateEffect(currentViscousProperty->gain, BACK, ID, HL_BACK);	
			}
			else {
	
				bool teste = obj->isStackEmpty();
				if(teste == true)
				{
					obj->updateEffect(currentViscousProperty->gain, FRONT, ID, HL_FRONT);
				}
				else {
					obj->updateEffect(currentViscousProperty->gain, FRONT, ID, HL_FRONT);
				}
			}
		}
		untouchOn = false;
	
		hlEndFrame();
	
		return HD_CALLBACK_CONTINUE;
	}

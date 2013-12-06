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

#include "cybOpenHPhantom.h"

	CybOpenHPhantom::CybOpenHPhantom()
	{
		cybCore = CybParameters::getInstance();
		guided = false;
	}

	CybOpenHPhantom::~CybOpenHPhantom()
	{
	}

	double CybOpenHPhantom::getCurrentProxyPosition(int coord)
	{
		hapticHandle.updateState(4);
		return hapticHandle.states.pos[coord];
	}

	void CybOpenHPhantom::getCurrentProxyPosition(double *position)
	{
		hapticHandle.updateState(4);
		
		position[0] = hapticHandle.states.pos[0];
		position[1] = hapticHandle.states.pos[1];
		position[2] = hapticHandle.states.pos[2];
	}
	
	
	void CybOpenHPhantom::getLastProxyPosition(double *lastPosition)
	{
		 hapticHandle.updateState(5);

		 lastPosition[0] = hapticHandle.states.lastPos[0];
		 lastPosition[1] = hapticHandle.states.lastPos[1];
		 lastPosition[2] = hapticHandle.states.lastPos[2];
	}
		
	
	double CybOpenHPhantom::getLastProxyPosition(int coord)
	{
			hapticHandle.updateState(5);
			return hapticHandle.states.lastPos[coord];
	}
	
	
	bool CybOpenHPhantom::deviceIsEnable()
	{
		hapticHandle.hapticDeviceIsEnable();
		return hapticHandle.isEnable;
	}
	
	
	void CybOpenHPhantom::initDevice()
	{
		hapticHandle.initHL();
	}
	
	
	void CybOpenHPhantom::stopDevice()
	{
		hapticHandle.exitHL();
	}
	
	
	void CybOpenHPhantom::updateWorkspace()
	{
		hapticHandle.hapticWorkspaceCalibration();
	}
	
	
	double CybOpenHPhantom::getHapticScaleFactor()
	{
		return hapticHandle.scaleFactor;
	}
		
	
	void CybOpenHPhantom::getProxyTransformationMatrix(double transMatrix[])
	{
		hlGetDoublev(HL_PROXY_TRANSFORM, transMatrix);
	}
	
	void CybOpenHPhantom::getDevicePosition(double position[]) {
		hlGetDoublev(HL_DEVICE_POSITION, position);
	}

	void CybOpenHPhantom::getDeviceRotation(double rotation[]) {
		hlGetDoublev(HL_DEVICE_ROTATION, rotation);
	}
	
	void CybOpenHPhantom::getCurrentForceIntensity(double *_force)
	{
		hapticHandle.updateState(0);
		
		_force[0] = hapticHandle.states.force[0];
		_force[1] = hapticHandle.states.force[1];
		_force[2] = hapticHandle.states.force[2];
		
	}

	void CybOpenHPhantom::setGuided(bool guided) {
		hapticHandle.setGuided(guided);
	}
		
	bool CybOpenHPhantom::isGuided() {
		return hapticHandle.isGuided();
	}

	void CybOpenHPhantom::setCurrentForceIntensity(const HDfloat* _force) {
		hdSetFloatv(HD_CURRENT_FORCE, _force);
	}
	
	void CybOpenHPhantom::setAnchorPosition(float x, float y, float z) {
		hapticHandle.setAnchorPosition(x, y, z);
	}

	void CybOpenHPhantom::getLastForceIntensity(double *_lastForce)
	{
		hapticHandle.updateState(6);
	
		_lastForce[0] = hapticHandle.states.lastForce[0];
		_lastForce[1] = hapticHandle.states.lastForce[1];
		_lastForce[2] = hapticHandle.states.lastForce[2];
	
	}
	
	
	void CybOpenHPhantom::getTorque(double *_torque)
	{
		hapticHandle.updateState(1);
		
		_torque[0] = hapticHandle.states.torque[0];
		_torque[1] = hapticHandle.states.torque[1];
		_torque[2] = hapticHandle.states.torque[2];
		
	}

	void CybOpenHPhantom::setTorque(const HDfloat* _torque) {

		hdSetFloatv(HD_CURRENT_TORQUE, _torque);
	}
		
	
	void CybOpenHPhantom::getDeviceGimbalAngle(double *_gimbalAngle)
	{
		hapticHandle.updateState(2);
		
		_gimbalAngle[0] = hapticHandle.states.gimbalAngle[0];
		_gimbalAngle[1] = hapticHandle.states.gimbalAngle[1];
		_gimbalAngle[2] = hapticHandle.states.gimbalAngle[2];
	}
	
	
	void CybOpenHPhantom::getDeviceJointAngle(double *_jointAngle)
	{
		hapticHandle.updateState(3);
		
		_jointAngle[0] = hapticHandle.states.jointAngle[0];
		_jointAngle[1] = hapticHandle.states.jointAngle[1];
		_jointAngle[2] = hapticHandle.states.jointAngle[2];
		
	}
	
	
	void CybOpenHPhantom::getProxyRotation(double _rotation[])
	{
		/*
		_rotation[0] = hapticHandle.states.rotation[0];
		_rotation[1] = hapticHandle.states.rotation[1];
		_rotation[2] = hapticHandle.states.rotation[2];
		_rotation[3] = hapticHandle.states.rotation[3];
		*/
	}
	
	
	double CybOpenHPhantom::getCurrentForceIntensity(int coord)
	{
		hapticHandle.updateState(0);
		return hapticHandle.states.force[coord];
	}
	
	
	double CybOpenHPhantom::getLastForceIntensity(int coord)
	{
		hapticHandle.updateState(6);
		return hapticHandle.states.lastForce[coord];
	}
	
	
	double CybOpenHPhantom::getTorque(int coord)
	{
		hapticHandle.updateState(1);
		return hapticHandle.states.torque[coord];
	}
	
			
	double CybOpenHPhantom::getDeviceGimbalAngle(int coord)
	{
		hapticHandle.updateState(2);
		return hapticHandle.states.gimbalAngle[coord];
	}
		
	
	double CybOpenHPhantom::getDeviceJointAngle(int coord)
	{
		hapticHandle.updateState(3);
		return hapticHandle.states.jointAngle[coord];
	}

	  
	 
	void CybOpenHPhantom::drawHaptics()
	{
		//cout << "drawHaptics()" << endl;
		hapticHandle.hapticRendering();
		
	}
		
	
	void CybOpenHPhantom::IdleHaptics()
	{
		hapticHandle.HLIdleFunc();
		if(cybCore->phantomOn)
			hapticHandle.CheckCalibration();
	}

		
	
	void CybOpenHPhantom::setCursorSizePixels(int size)
	{
		hapticHandle.cursor_size_pixel = size;
	}

	
	void CybOpenHPhantom::createHapticLayers(int numLayers, bool defaultInitialization)
	{
		if(hapticHandle.habHapticLayers == NULL){

			hapticHandle.habHapticLayers = new bool[numLayers];
			for(int i = 0; i < numLayers; i++)
				hapticHandle.habHapticLayers[i] = defaultInitialization;
	
			hapticHandle.numHapticLayers = numLayers;
		}
		else {	cout<<"Message Error: Haptic layers already had been created!"<<endl;}
	}

	
	void CybOpenHPhantom::enableHapticLayer(int layerId)
	{
		if(hapticHandle.habHapticLayers != NULL){
			
			if (layerId >= hapticHandle.numHapticLayers)
			 	cout<<"Message Error: Impossible to enable layer, invalid Layer ID!"<<endl;
	
			else hapticHandle.habHapticLayers[layerId] = true;
		
		}
		else cout<<"Message Error: Haptic Layer don't exist!"<<endl;
	}
	
	
	void CybOpenHPhantom::disableHapticLayer(int layerId)
	{
		if(hapticHandle.habHapticLayers != NULL){
			
			if (layerId >= hapticHandle.numHapticLayers){
			 		cout<<"Message Error: Impossible to disable layer, invalid Layer ID!"<<endl;
				}	
			else hapticHandle.habHapticLayers[layerId] = false;
		
		}
		else cout<<"Message Error: Haptic Layer don't exist!"<<endl;
	}
	
		
	
	void CybOpenHPhantom::enableHapticMaterialProperty()
	{
		if(cybCore->materialPropertyContextCreated())
		{
			hapticHandle.genProperties();
			hapticHandle.materialPropertiesIsEnable = true;
		 }
		 else {cout<<"Message Error: Material context don't exist!"<<endl;}
	}
		
	
	void CybOpenHPhantom::disableHapticMaterialProperty()
	{
		hapticHandle.materialPropertiesIsEnable = false;
		}
	
	
	
	void CybOpenHPhantom::disableHapticLayerMaterial(int layerId)
	{		
		if(hapticHandle.habHapticLayers != NULL){
			if(hapticHandle.habHapticLayersMaterial != NULL){

				if (layerId >= hapticHandle.numHapticLayers){
						cout<<"Message Error: Impossible to disable layer material property, invalid Layer ID!"<<endl;
					}
				else hapticHandle.habHapticLayersMaterial[layerId] = false;
			}
			else cout<<"Message Error: Haptic material context don't exist!"<<endl;
		}
		else cout<<"Message Error: Haptic Layer don't exist!"<<endl;
		
	}
	
	
	void CybOpenHPhantom::enableHapticLayerMaterial(int layerId)
	{
		if(hapticHandle.habHapticLayers != NULL){
				if(hapticHandle.habHapticLayersMaterial != NULL){
					
					if (layerId >= hapticHandle.numHapticLayers)
						cout<<"Message Error: Impossible to enable layer material property, invalid Layer ID!"<<endl;
			
					else hapticHandle.habHapticLayersMaterial[layerId] = true;
				
				}
				else cout<<"Message Error: Haptic material context don't exist!"<<endl;
			}
		else cout<<"Message Error: Haptic Layer don't exist!"<<endl;
		
		}
				
		void CybOpenHPhantom::createAmbientProperty()
		{	
			hapticHandle.createAmbientContext();
			
		}
				
		void CybOpenHPhantom::enableAmbientProperty()
		{
		
			CybViscosity *viscosity = CybViscosity::getInstance();
			viscosity->startAmbientProperty();
			hapticHandle.ambientPropertyIsEnable = true;
		}
			
		void CybOpenHPhantom::disableAmbientProperty()
		{
			CybViscosity *viscosity = CybViscosity::getInstance();
			viscosity->stopAmbientProperty();
		}

		void CybOpenHPhantom::destroyAmbientProperty()
		{
			CybViscosity *viscosity = CybViscosity::getInstance();
			viscosity->destroyAmbientProperty();
			
			hapticHandle.ambientPropertyIsEnable = false;
			
			hapticHandle.recoverAttributes();
		}

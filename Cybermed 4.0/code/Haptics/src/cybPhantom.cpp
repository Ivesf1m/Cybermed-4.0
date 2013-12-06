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


#include "cybPhantom.h"

	HDdouble* CybPhantom::anchor= new HDdouble[3];

	
	CybPhantom::CybPhantom()
	{
		//cout << "CybPhantom() in" << endl;
		hapticDevice = HD_INVALID_HANDLE;
		hapticContext = 0;
		isEnable = false;
		states.flagState = -1;
		stateCalibration.calibrationOk = true;
		cursor_size_pixel = 20;
		shapeIdListIscreated = false;
		materialPropertiesIsEnable = false;
		habHapticLayers  = NULL;
		habHapticLayersMaterial = NULL;
		properties = NULL;
		ambientPropertyIsEnable = false;
	
		guided = false;

		anchorPosition[0] = 0;
		anchorPosition[1] = 0;
		anchorPosition[2] = 0;

		cybCore = CybParameters::getInstance();
	
		//cout << "CybPhantom() out" << endl;
	}
	
	
	CybPhantom::~CybPhantom()
	{
	}
	
	void CybPhantom::setAnchorPosition(double x, double y, double z) {
		/*this->anchorPosition[0] = x;
		this->anchorPosition[1] = y;
		this->anchorPosition[2] = z;*/

		this->anchor[0] = x;
		this->anchor[1] = y;
		this->anchor[2] = z;
	}
	
	
	int CybPhantom::initHL()
	{
		//TODO HABILITAR O OUTPUT FORCE NA HD.

		HDErrorInfo error;
	
		hapticDevice = hdInitDevice(HD_DEFAULT_DEVICE);
		if(HD_DEVICE_ERROR(error = hdGetError()))
		{
			//Falta tratar o erro!
			hduPrintError(stderr, &error, "Failed to initialize haptic device");
			return -1;
		}

		checkCalibrationStatus(&stateCalibration);	
	
		hapticContext = hlCreateContext(hapticDevice);
		hlMakeCurrent(hapticContext);
	
		hlTouchableFace(HL_FRONT_AND_BACK);
	
		hlEnable(HL_HAPTIC_CAMERA_VIEW);

		//hlEnable(HL_ADAPTIVE_VIEWPORT);
	
		//hdEnable(HD_FORCE_OUTPUT);

		return 0;
	}
	
	
	
	void CybPhantom::hapticDeviceIsEnable()
	{
		if(hapticDevice != HD_INVALID_HANDLE)
			isEnable = true;
	
		else isEnable =  false;
	}
	
	
	void CybPhantom::showDeviceInformation()
	{
		cout<<"Used Device: "<<hdGetString(HD_DEVICE_MODEL_TYPE)<<endl;
		cout<<"Version Driver: "<<hdGetString(HD_DEVICE_DRIVER_VERSION)<<endl;
		cout<<"Device Vendor: "<<hdGetString(HD_DEVICE_VENDOR)<<endl;
		cout<<"Serial Number: "<<hdGetString(HD_DEVICE_SERIAL_NUMBER)<<endl;
	}
	
	
	void CybPhantom::exitHL()
	{
		if(shapeIdListIscreated){
			for(int i = 0; i < numHapticLayers; i++)
				hlDeleteShapes(shapeId[i], 1);
			delete [] properties;
		}
	
	
		hlMakeCurrent(NULL);
		if(hapticContext != NULL)
		{
			hlDeleteContext(hapticContext);
		}
	
		if(hapticDevice != HD_INVALID_HANDLE)
		{
			hdDisableDevice(hapticDevice);
			hapticDevice = HD_INVALID_HANDLE;
		}
	
		if(ambientPropertyIsEnable){
			CybViscosity *viscosity = CybViscosity::getInstance();
			viscosity->stopAmbientProperty();
			delete viscosity;
		}
	
	}
	
	
	
	void CybPhantom::hapticWorkspaceCalibration()
	{
		GLdouble projection[16];
		GLdouble modelview[16];
		GLint	viewport[4];

		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetIntegerv(GL_VIEWPORT, viewport);
	
		hlWorkspace(-90,-60,-50,90,60,50);
	
		hlMatrixMode(HL_TOUCHWORKSPACE);
	
		hduMapWorkspaceModel(modelview, projection, workspacemodel);
	
		/* Compute the scale needed to display the cursor of a particular size in screen coordinates. */
		scaleFactor = hduScreenToWorkspaceScale(modelview, projection, viewport, workspacemodel);
		scaleFactor *= cursor_size_pixel; 
	
	}
	
	HDCallbackCode HDCALLBACK CybPhantom::getStateCB(void *pUserData)
	{
		HapticState  *copyState;
		copyState = (HapticState *) pUserData;
		if(copyState->flagState == 0)
		{
			hdGetDoublev(HD_CURRENT_FORCE, copyState->force);
		}
		else if(copyState->flagState == 1)
		{
			hdGetDoublev(HD_CURRENT_TORQUE, copyState->torque);
		}
		else if(copyState->flagState == 2)
		{
			hdGetDoublev(HD_CURRENT_GIMBAL_ANGLES, copyState->gimbalAngle);
		}
		else if(copyState->flagState == 3)
		{
			hdGetDoublev(HD_CURRENT_JOINT_ANGLES, copyState->jointAngle);
		}
		else if(copyState->flagState == 4)
		{
			hdGetDoublev(HD_CURRENT_POSITION, copyState->pos);	
		}
		else
		{
			//cout<<"FlagState error: Invalid flag!"<<endl;
			return HD_CALLBACK_DONE;
		}
		return HD_CALLBACK_DONE;
	}
	
	
	void CybPhantom::updateState(int _flag)
	{
		states.flagState = _flag;
	
		hdScheduleSynchronous(getStateCB, &states, HD_MIN_SCHEDULER_PRIORITY);
	
	}
	
	
	void HLCALLBACK CybPhantom::checkCalibrationCB(HLenum event, HLuint object, HLenum thread,
			HLcache *cache, void *pUserData)
	{
		CalibrationState *state = static_cast <CalibrationState *> (pUserData);
	
		if(event == HL_EVENT_CALIBRATION_UPDATE)
		{
			cout<<"Warning: Device Require calibration update!"<<endl;
			state->calibrationOk = false;
			state->hlCalibrationType = HL_EVENT_CALIBRATION_UPDATE;
			hlUpdateCalibration();
		}
		else if(event == HL_EVENT_CALIBRATION_INPUT)
		{
			cout<<"Warning: Device requires calibration.input!"<<endl;
			state->hlCalibrationType = HL_EVENT_CALIBRATION_INPUT;
			state->calibrationOk = true;
		}
	}
	
	void CybPhantom::setGuided(bool guided) {
		this->guided = guided;
		hdScheduleAsynchronous(setForce, NULL, HD_DEFAULT_SCHEDULER_PRIORITY);
	}

	HDCallbackCode HDCALLBACK CybPhantom::setForce(void *pUserData) {
		//cout << "setForce()" << endl;

		hduVector3Dd position;//buffer para a recepção de dados do socket
		hduVector3Dd force;


		HDdouble forceClamp;
		static const HDdouble kAnchorStiffness = 0.1;

		hdBeginFrame(hdGetCurrentDevice()); /*Começa o frame.*/

		hdGetDoublev(HD_CURRENT_POSITION, position);

		//cout << anchorPosition[0] << " " << anchorPosition[1] <<  " " << anchorPosition[2] << endl;

		hduVecSubtract(force, anchor, position);
		hduVecScaleInPlace(force, kAnchorStiffness);
		//hdGetDoublev(HD_NOMINAL_MAX_CONTINUOUS_FORCE, &forceClamp);
		/*if (hduVecMagnitude(force) > forceClamp)
		{
			hduVecNormalizeInPlace(force);
			hduVecScaleInPlace(force, forceClamp);
		}*/
		//cout << force[0] << " " << force[1] <<  " " << force[2] << endl;
		hdSetDoublev(HD_CURRENT_FORCE, force);

		hdEndFrame(hdGetCurrentDevice());

		return HD_CALLBACK_CONTINUE;

	}

	bool CybPhantom::isGuided() {
		return this->guided;
	}
	
	void CybPhantom::hapticRendering()
	{
		if(!shapeIdListIscreated)
		{
			genShapeIdList(cybCore->numLayer);
			shapeIdListIscreated = true;
		}
	
		if(habHapticLayers == NULL)
		{
			cout<<"Message Error: Haptic Layer don't exist!"<<endl;
		}
		else{
			hlBeginFrame();
	
			glPushMatrix();
	
			//cout << "Haptic layers " << numHapticLayers << endl;
			for(int j = 0; j < numHapticLayers; j++){

				if(habHapticLayers[j] == true){
	

					glTranslated(cybCore->xTrans + cybCore->layerTrans[j][0], cybCore->yTrans + cybCore->layerTrans[j][1], cybCore->zTrans + cybCore->layerTrans[j][2]);
					glScaled(cybCore->xScale * cybCore->layerSca[j][0], cybCore->yScale * cybCore->layerSca[j][1], cybCore->zScale * cybCore->layerSca[j][2]);

					glTranslated(cybCore->cX, cybCore->cY, cybCore->cZ);
					glRotated(cybCore->getXAngle() + cybCore->layerRot[j][0],1,0,0);
					glRotated(cybCore->getYAngle() + cybCore->layerRot[j][1],0,1,0);
					glRotated(cybCore->getZAngle() + cybCore->layerRot[j][2],0,0,1);
					glTranslated(-cybCore->cX, -cybCore->cY, -cybCore->cZ);


					if(materialPropertiesIsEnable){
	
						if(cybCore->materialPropertyContextCreated() && cybCore->propertyFaceModified())
							updateHapticsFaces();
	
						if(habHapticLayersMaterial == NULL)
						{
							cout<<"Message Error: Material context don't exist!"<<endl;
						}
						else{
							if(habHapticLayersMaterial[j] == true){		
								hlMaterialf(propertyFace[j][0], HL_STIFFNESS, cybCore->getMaterialPropertyValue(j, STIFFNESS));
	
								hlMaterialf(propertyFace[j][1], HL_DAMPING, cybCore->getMaterialPropertyValue(j, DAMPING));
	
								hlMaterialf(propertyFace[j][2], HL_STATIC_FRICTION, cybCore->getMaterialPropertyValue(j, STATIC_FRICTION));
	
								hlMaterialf(propertyFace[j][3], HL_DYNAMIC_FRICTION, cybCore->getMaterialPropertyValue(j, DYNAMIC_FRICTION));
	
								if(ambientPropertyIsEnable){
									hlMaterialf(HL_FRONT_AND_BACK, HL_POPTHROUGH,1);
								}
								else{
									hlMaterialf(propertyFace[j][4], HL_POPTHROUGH,cybCore->getMaterialPropertyValue(j, POPTHROUGH));
								}
							}
						}
					}
	
	
					hlHinti(HL_SHAPE_FEEDBACK_BUFFER_VERTICES, cybCore->nv[j]);				  
					hlBeginShape(HL_SHAPE_FEEDBACK_BUFFER, shapeId[j]);
	
					if(ambientPropertyIsEnable)
						hlTouchableFace(CybViscosity::ViscosityShapeAttribute[j].currentFace);
					else hlTouchableFace(HL_FRONT_AND_BACK);
	
					CybVector3D<float> v1;
	
	
					for(int i = 0; i < cybCore->nt[j]; i++){
	
						glBegin(GL_TRIANGLES);
	
						v1 = cybCore->vNormalCell[j][i];
						glNormal3f(v1[0], v1[1], v1[2]);
	
						v1 = cybCore->coordList[j][cybCore->v[j][i][0]];
						glVertex3f(v1[0], v1[1], v1[2]);
	
						v1 = cybCore->coordList[j][cybCore->v[j][i][1]];
						glVertex3f(v1[0], v1[1], v1[2]);
	
						v1 = cybCore->coordList[j][cybCore->v[j][i][2]];
						glVertex3f(v1[0], v1[1],v1[2]);		  
	
						glEnd();
						glFlush();
					}
	
					hlEndShape();
	

				}
	
				glLoadIdentity();
			}
	
			glPopMatrix();
			hlEndFrame();
		}
		hlCheckEvents();
	}
	
	
	HHD CybPhantom::getDevice()
	{
		return hapticDevice;
	}
	
	void CybPhantom::genShapeIdList(int num)
	{
		shapeId = new HLuint[num];
		for(int i = 0; i < num; i++){
			shapeId[i] = hlGenShapes(1);
		}
	}
	
	void CybPhantom::genProperties()
	{	 	
		if(habHapticLayersMaterial == NULL){
	
			habHapticLayersMaterial = new bool[numHapticLayers];
			propertyFace = new HLenum*[numHapticLayers];
	
			for(int i = 0; i < numHapticLayers; i++)
				propertyFace[i] = new HLenum[5];
	
			for(int i = 0; i < numHapticLayers; i++){
				habHapticLayersMaterial[i] = false;
				propertyFace[i][0] = HL_FRONT;
				propertyFace[i][1] = HL_FRONT;
				propertyFace[i][2] = HL_FRONT;
				propertyFace[i][3] = HL_FRONT;
				propertyFace[i][4] = HL_FRONT;
			}
		}
	
	}
	
	void CybPhantom::HLIdleFunc()
	{
		HLerror error;
		while (HL_ERROR(error = hlGetError()))
		{
			fprintf(stderr, "Error: %s\n", error.errorCode);
	
			if (error.errorCode == HL_DEVICE_ERROR)
			{
				hduPrintError(stderr, &error.errorInfo,
						"Error during haptic rendering\n");
			}
		}
	
		if(cybCore->phantomOn && !flagWorkspaceUpdate){
	
			hapticWorkspaceCalibration();
			flagWorkspaceUpdate = true;
		}
		else if(!cybCore->phantomOn)
		{
			flagWorkspaceUpdate = false;
		}		
	
	}
	
	
	/******************************************************************************
					Functions responsible for haptic device calibration
	 ******************************************************************************/
	
	void CybPhantom::checkCalibrationStatus(CalibrationState *pUserData)
	{
		int supportedCalibrationStyles;
		hdGetIntegerv(HD_CALIBRATION_STYLE, &supportedCalibrationStyles);
		if(supportedCalibrationStyles & HD_CALIBRATION_ENCODER_RESET)
		{
			pUserData->calibrationType = HD_CALIBRATION_ENCODER_RESET;
		}
		if(supportedCalibrationStyles & HD_CALIBRATION_INKWELL)
		{
			pUserData->calibrationType = HD_CALIBRATION_INKWELL;
		}
		if(supportedCalibrationStyles & HD_CALIBRATION_AUTO)
		{
			pUserData->calibrationType = HD_CALIBRATION_AUTO;
		}
	
		if(pUserData->calibrationStatus == HD_CALIBRATION_ENCODER_RESET){
			printf("Calibration' type not implemented!");
			exit(-1);
		}
	}
	
	HDenum CybPhantom::GetCalibrationStatus(CalibrationState *pState)
	{
		hdScheduleSynchronous(calibrationServoLoop, pState, HD_MIN_SCHEDULER_PRIORITY);
	
		return pState->calibrationStatus;
	}
	
	HDboolean CybPhantom::CheckCalibration()
	{
		HDErrorInfo error;
		HDenum status = GetCalibrationStatus(&stateCalibration);
	
		if(status == HD_CALIBRATION_OK)
		{
			return HD_TRUE;
		}
		else if (status == HD_CALIBRATION_NEEDS_MANUAL_INPUT)
		{
			printf("Calibration requires manual input...\n");
			return HD_FALSE;
		}
		else if (status == HD_CALIBRATION_NEEDS_UPDATE)
		{
			hdScheduleSynchronous(UpdateCalibrationCallback, &stateCalibration,HD_DEFAULT_SCHEDULER_PRIORITY);
			if(HD_DEVICE_ERROR(error = hdGetError()))
			{
				printf("\nFailed to update Calibration!\n");
				return HD_FALSE;
			}
			else
				cout<<"Calibration sucessfully"<<endl;					  
		}
		else
		{
			assert(!"Unknow Calibration status");
			return HD_FALSE;
		}
	
	}
	
	HDCallbackCode HDCALLBACK CybPhantom::UpdateCalibrationCallback(void *pUserData)
	{
		CalibrationState *pState = (CalibrationState *) pUserData;
		if( hdCheckCalibration() == HD_CALIBRATION_NEEDS_UPDATE)
		{
			hdUpdateCalibration(pState->calibrationType);
		}
		return HD_CALLBACK_DONE;
	}
	
	HDCallbackCode HDCALLBACK CybPhantom::calibrationServoLoop(void *pUserData)
	{
		CalibrationState *state = (CalibrationState *) pUserData;
	
		hlBeginFrame();
		state->calibrationStatus = hdCheckCalibration();
		hlEndFrame();
	
		return HD_CALLBACK_DONE;
	}
	
	void CybPhantom::updateHapticsFaces()
	{
		HLenum HLface;
		for(int i = 0; i < cybCore->numLayer; i++)
		{
			if(cybCore->getMaterialFace(i, STIFFNESS) == FRONT)
				propertyFace[i][0] = HL_FRONT;
			else if(cybCore->getMaterialFace(i, STIFFNESS) == BACK)
				propertyFace[i][0] = HL_BACK;
			else propertyFace[i][0] = HL_FRONT_AND_BACK;
	
			if(cybCore->getMaterialFace(i, DAMPING) == FRONT)
				propertyFace[i][1] = HL_FRONT;
			else if(cybCore->getMaterialFace(i, DAMPING) == BACK)
				propertyFace[i][1] = HL_BACK;
			else propertyFace[i][1] = HL_FRONT_AND_BACK;
	
			if(cybCore->getMaterialFace(i, STATIC_FRICTION) == FRONT)
				propertyFace[i][2] = HL_FRONT;
			else if(cybCore->getMaterialFace(i, STATIC_FRICTION) == BACK)
				propertyFace[i][2] = HL_BACK;
			else propertyFace[i][2] = HL_FRONT_AND_BACK;
	
			if(cybCore->getMaterialFace(i, DYNAMIC_FRICTION) == FRONT)
				propertyFace[i][3] = HL_FRONT;
			else if(cybCore->getMaterialFace(i, DYNAMIC_FRICTION) == BACK)
				propertyFace[i][3] = HL_BACK;
			else propertyFace[i][3] = HL_FRONT_AND_BACK;
	
			if(cybCore->getMaterialFace(i, POPTHROUGH) == FRONT)
				propertyFace[i][4] = HL_FRONT;
			else if(cybCore->getMaterialFace(i, POPTHROUGH) == BACK)
				propertyFace[i][4] = HL_BACK;
			else propertyFace[i][4] = HL_FRONT_AND_BACK;
	
		}
	
		cybCore->materialFaceModified = false;
	
	}
	
	void CybPhantom::createAmbientContext()
	{
		CybViscosity *viscosity = CybViscosity::getInstance(cybCore->numLayer);
	
		if(!shapeIdListIscreated)
		{
			genShapeIdList(cybCore->numLayer);
			shapeIdListIscreated = true;
		}		
	
		if(!materialPropertiesIsEnable)
			genProperties();
	
		hlAddEventCallback(HL_EVENT_UNTOUCH, HL_OBJECT_ANY, HL_CLIENT_THREAD, 
				&CybViscosity::untouchShapeCallback, NULL);
	
		for(int i = 0; i < cybCore->numLayer; i++){
	
			hlAddEventCallback(HL_EVENT_TOUCH, shapeId[i], HL_CLIENT_THREAD, 
					&CybViscosity::touchShapeCallback, &CybViscosity::ViscosityShapeAttribute[i].id);
			hlAddEventCallback(HL_EVENT_MOTION, shapeId[i], HL_CLIENT_THREAD, 
					&CybViscosity::movingObjectCallback, &CybViscosity::ViscosityShapeAttribute[i].id);
		}
	
		habHapticLayersSave = new bool[cybCore->numLayer];
	
		saveAttributes();
	}
	
	
	void CybPhantom::saveAttributes()
	{
		for(int i = 0; i < cybCore->numLayer; i++)
		{
			habHapticLayersSave[i] = habHapticLayers[i];
			habHapticLayers[i] = true;
		}
	}
	
	void CybPhantom::recoverAttributes()
	{
		for(int i = 0; i < cybCore->numLayer; i++){
			habHapticLayers[i] = habHapticLayersSave[i];
		}	
	}

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

#include "cybParameters.h"

	bool CybParameters::collisionStatus = false;
	CybParameters CybParameters::singletonInstance;
	
	CybParameters::CybParameters()
	{
		nTextures = 0; //Default -> No textures		
		viewType = 1; // Default -> Normal visualization
		trackerOn = false;
		phantomOn = true; // Default -> no device is activated
		mouseOn = true;
		gloveOn = false;
		hapticsPlugged[0] = false; // If haptics is not pluged, haptics menu is deactivated
		hapticsPlugged[1] = false; //Dual haptics use. To next version
		trackersPlugged[0] = false; // Now we have just one tracker to test
		keyboardOn = true;
		menuHabiltated = false;
		interactionHabilitated = true;
		transforChange = true;
		interatorPosChange = true;
		numInteractionObj = 0;
		activeInterator = -1;
		collisionHabilitated = 1;
		layerInteractionChoosen = false;
		layerInteracted = -1;
		numInterators = 0;
		xSum = 0;
		ySum = 0;
		zSum = 0;
		properties = NULL;
		materialFaceModified = false;
		materialContexIsEnable = false;
		sceneEditable = true;
	}
	
	CybParameters::~CybParameters()
	{
		for(int i=0; i < numLayer; i++)
			daloc(i);
		delete [] properties;
	}
	
	CybParameters *CybParameters::getInstance() { return &singletonInstance; }
	
	void CybParameters::addTriangle(int idLayer, int p1, int p2, int p3)
	{
		float aux1x, aux1y, aux1z, aux2x, aux2y, aux2z;
		float x1, y1, z1, x2, y2, z2, x3, y3, z3;
		float vNormal[3];
		float norma;
	
		v[idLayer][nt[idLayer]][0] = p1;
		v[idLayer][nt[idLayer]][1] = p2;
		v[idLayer][nt[idLayer]][2] = p3;
		//CybViewCore.numLayer = idLayer + 1;
	
		x1 = coordList[idLayer][p1][0];
		y1 = coordList[idLayer][p1][1];
		z1 = coordList[idLayer][p1][2];
		x2 = coordList[idLayer][p2][0];
		y2 = coordList[idLayer][p2][1];
		z2 = coordList[idLayer][p2][2];
		x3 = coordList[idLayer][p3][0];
		y3 = coordList[idLayer][p3][1];
		z3 = coordList[idLayer][p3][2];
	
		// Calculo de normais do triangulo
		aux1x = x2 - x1;
		aux1y = y2 - y1;
		aux1z = z2 - z1;
		aux2x = x3 - x1;
		aux2y = y3 - y1;
		aux2z = z3 - z1;
	
		vNormal[0] = (aux1y*aux2z) - (aux2y*aux1z);
		vNormal[1] = (aux1z*aux2x) - (aux2z*aux1x);
		vNormal[2] = (aux1x*aux2y) - (aux2x*aux1y);
	
		norma = sqrt(vNormal[0]*vNormal[0] + vNormal[1]*vNormal[1] + vNormal[2]*vNormal[2]);
	
		if(norma != 0)
		{
			vNormalCell[idLayer][nt[idLayer]][0] = vNormal[0]/norma;
			vNormalCell[idLayer][nt[idLayer]][1] = vNormal[1]/norma;
			vNormalCell[idLayer][nt[idLayer]++][2] = vNormal[2]/norma;
		}
		else
		{
			vNormalCell[idLayer][nt[idLayer]][0] = 1;
			vNormalCell[idLayer][nt[idLayer]][1] = 1;
			vNormalCell[idLayer][nt[idLayer]++][2] = 1;
		}
	
		xSum += (x1 + x2 + x3);
		ySum += (y1 + y2 + y3);
		zSum += (z1 + z2 + z3);
	}
	
	
	void CybParameters::addVertex(int idLayer, float x, float y, float z)
	{
		coordList[idLayer][nv[idLayer]][0] = x;
		coordList[idLayer][nv[idLayer]][1] = y;
		coordList[idLayer][nv[idLayer]++][2] = z;
	}
	
	
	void CybParameters::initParameters()
	{
		if(viewType == 1)
		{
			paralaxe=0;
			stereoMagnitude=0;
		}
		else
		{
			paralaxe=0.3;
			stereoMagnitude=0;
		}
	
		objChosen = 0;
	
		modified = 1;
	
		xAngle = 0;
		yAngle = 0;
		zAngle = 0;
	
		xTrans = 0;
		yTrans = 0;
		zTrans = 0;
	
		xScale = 1;
		yScale = 1;
		zScale = 1;
	
		camPosZ = 75;	//50
	
		widthProportion = 1;
		heightProportion = 1;
	
		for(int i=0; i<numLayer; i++)
			habLayer[i] = 1;
	}
	
	bool CybParameters::isSceneEditable() {
		return this->sceneEditable;
	}

	void CybParameters::setSceneEditable(bool editable) {
		this->sceneEditable = editable;
	}

	void CybParameters::setCollisionHabilitated(int collisionType)
	{
		collisionHabilitated = collisionType;
	}
	
	void CybParameters::setColor(CybVector4D<float> *colors)
	{
		for(int i=0; i < numLayer; i++)
		{
			color[i][0] = colors[i][0];
			color[i][1] = colors[i][1];
			color[i][2] = colors[i][2];
			color[i][3] = colors[i][3];
		}
	}
	
	void CybParameters::setColor(int layerID, float r, float g, float b, float a)
	{
		if (isSceneEditable()) {
			color[layerID][0] = r;
			color[layerID][1] = g;
			color[layerID][2] = b;
			color[layerID][3] = a;
		}
	}
	
	void CybParameters::setColor(int layer, CybVector4D<float> color) {

		if (isSceneEditable()) {
			this->color[layer] = color;

			for(itLayer = layerListenersList.begin(); itLayer != layerListenersList.end(); itLayer++) {
				(*itLayer)->layerColorEventPerformed(layer, color[0], color[1], color[2], color[3]);
			}
		}
	}

	void CybParameters::setInteractionOff()
	{
		interactionHabilitated = false;
	}
	
	void CybParameters::setInteractionOn()
	{
		interactionHabilitated = true;
	}
	
	bool CybParameters::isInteractionEnable()
	{
		return interactionHabilitated;
	}
	
	void CybParameters::setKeyboardOff()
	{
		keyboardOn = false;
	}
	
	void CybParameters::setKeyboardOn()
	{
		keyboardOn = true;
	}
	
	
	bool CybParameters::isKeyboardEnable()
	{
		return keyboardOn;
	}
	
	void CybParameters::setAngle(float xAngle, float yAngle, float zAngle) {
		if (isSceneEditable()) {
			this->xAngle = xAngle;
			this->yAngle = yAngle;
			this->zAngle = zAngle;
		}
	}

	CybVector4D<float> CybParameters::getColor(int layer) {
		CybVector4D<float> colorAux;
		colorAux[0] = color[layer][0];
		colorAux[1] = color[layer][1];
		colorAux[2] = color[layer][2];
		colorAux[3] = color[layer][3];

		return colorAux;
	}

	float CybParameters::getXAngle() {
		return this->xAngle;
	}

	float CybParameters::getYAngle() {
			return this->yAngle;
		}

	float CybParameters::getZAngle() {
		return this->zAngle;
	}

	void CybParameters::setLayerRotation(int layerId, float x, float y, float z)
	{
		if (isSceneEditable()) {
			layerRot[layerId][0] = x; //[layer][axis]
			layerRot[layerId][1] = y;
			layerRot[layerId][2] = z;
		}
	}
	
	void CybParameters::setLayerScale(int layerId, float x, float y, float z)
	{
		if (isSceneEditable()) {
			layerSca[layerId][0] = x; //[layer][axis]
			layerSca[layerId][1] = y;
			layerSca[layerId][2] = z;
		}
	}
	
	void CybParameters::setLayerTranslation(int layerId, float x, float y, float z)
	{
		if (isSceneEditable()) {
			layerTrans[layerId][0] = x; //[layer][axis]
			layerTrans[layerId][1] = y;
			layerTrans[layerId][2] = z;
		}
	}
	
	/*void CybParameters::setInteratorRotation(int interatorId, float x, float y, float z)
	{
		interatorRot[interatorId][0] = x; //[layer][axis]
		interatorRot[interatorId][1] = y;
		interatorRot[interatorId][2] = z;
	}
	
	void CybParameters::setInteratorScale(int interatorId, float x, float y, float z)
	{
		interatorSca[interatorId][0] = x; //[layer][axis]
		interatorSca[interatorId][1] = y;
		interatorSca[interatorId][2] = z;
	}
	
	
	void CybParameters::setInteratorTranslation(int interatorId, float x, float y, float z)
	{
		interatorTrans[interatorId][0] = x; //[layer][axis]
		interatorTrans[interatorId][1] = y;
		interatorTrans[interatorId][2] = z;
	}
	*/
	
	void CybParameters::setMenuOff() {	menuHabiltated = false;	}
	
	void CybParameters::setMenuOn() {	menuHabiltated = true;	}
	
	bool CybParameters::isMenuOn()	{	return menuHabiltated;	}
	
	void CybParameters::setParalaxe(double paralaxe) {	this->paralaxe = paralaxe;	}
	
	void CybParameters::setStereoMagnitude(double stereoMagnitude){	this->stereoMagnitude = stereoMagnitude;	}
	
	double CybParameters::getParalaxe()	{	return paralaxe;	}
	
	double CybParameters::getStereoMagnitude()	{	return stereoMagnitude;	}
	
	void CybParameters::setLayerName(char *stringName, int numLayer) {	layerName[numLayer] = stringName;	}
	
	char *CybParameters::getLayerName(int numLayer) {	return layerName[numLayer];	}
	
	void CybParameters::setSizeOfData(int triangles, int vertex, int idLayer)
	{
		nt[idLayer] = 0;
		nv[idLayer] = 0;
		aloc(triangles, vertex, idLayer);
	}
	
	void CybParameters::setVertexNormalVector(sMesh *_mesh, int idLayer)
	{
		int counter;
		float normalX, normalY, normalZ;
		mfVertexStarIteratorTriSurf<cybSurfaceTriTraits> itvs(_mesh);
	
		for(int i = 0; i < nv[idLayer]; i++)
		{
			normalX = 0;
			normalY = 0;
			normalZ = 0;
			counter = 0;
			
			for(itvs.initialize(i); itvs.notFinish(); ++itvs) 
			{
				normalX += vNormalCell[idLayer][&itvs][0];
				normalY += vNormalCell[idLayer][&itvs][1];
				normalZ += vNormalCell[idLayer][&itvs][2];
			
				counter++;
			}

			if(counter == 0)
				counter = 1;   
		
			vNormal[idLayer][i][0] = (float)(normalX/counter); //v[idLayer][i][ ] the vertice id
			vNormal[idLayer][i][1] = (float)(normalY/counter);
			vNormal[idLayer][i][2] = (float)(normalZ/counter);
		} // for 'i'
	}
	
	void CybParameters::setWindowSize(int windowX, int windowY)
	{
		Resx = windowX;
		Resy = windowY;
	}
	
	void CybParameters::startParameters()
	{
		alocParameters();
		initParameters();
	}
	
	double CybParameters::StereoProjection(double dfLeftBorder, double dfRightBorder, double dfBottomBorder,
			double dfTopBorder, double dfNearBorder, double dfFarBorder,
			double dfTargetPlane, double dfCameraToTargetDistance,
			double dfStereoMagnitudeAdj, double dfParallaxBalanceAdj)
	{
		double constMagnitudeStero = 0.07;
		// the X & Y axis ranges, in the target Z plane
		dfXRange = dfRightBorder - dfLeftBorder;
		double dfYRange = dfTopBorder - dfBottomBorder;
	
		// midpoints of the X & Y axis ranges
		dfXMidpoint = (dfRightBorder + dfLeftBorder) / 2.0;
		double dfYMidpoint = (dfTopBorder + dfBottomBorder) / 2.0;
	
		// convert clipping plane positions to distances in front of camera
		double dfCameraPlane = dfTargetPlane + dfCameraToTargetDistance;
	
		dfNearClipDistance = 50; // dfCameraPlane - dfNearBorder;	//3
		dfFarClipDistance = dfCameraPlane - dfFarBorder;
	
		dfStereoCameraOffset = dfXRange * constMagnitudeStero * dfStereoMagnitudeAdj;
		dfStereoCameraOffset /= 2.0;  // offset each camera by half the overall sep
	
		double dfFrustumAsymmetry = -dfStereoCameraOffset * dfParallaxBalanceAdj;
	
		double n_over_d = dfNearClipDistance / dfCameraToTargetDistance;
		dfXRange *= n_over_d;
		dfYRange *= n_over_d;
		dfFrustumAsymmetry *= n_over_d;
	
		FrustumTop = dfYRange / 2.0; 
		FrustumBase = -dfYRange / 2.0; 
	
		return dfFrustumAsymmetry;
	}
	
	void CybParameters::createMaterialPropertyContext(int _numlayer)
	{
	
		if(!materialContexIsEnable){
			genMaterialProperties(_numlayer);
			materialContexIsEnable = true;
		}
		else {	cout<<"Message Error: Material property context already had been created!"<<endl;}
	}
	
	void CybParameters::genMaterialProperties(int _numlayer)
	{
	
		properties = new MaterialProperties[_numlayer];
		activeFaces = new EnumFace[_numlayer];
		for(int i = 0; i < _numlayer; i++){
			activeFaces[i] = FRONT_AND_BACK;
			for(int j = 0; j < 6; j++)
				properties[i].propertyFace[j] = FRONT_AND_BACK;
		}
	
		materialFaceModified = true;
	
	}
	
	bool CybParameters::materialPropertyContextCreated()
	{
		return materialContexIsEnable;
	}
	
	bool CybParameters::propertyFaceModified()
	{
		return materialFaceModified;
	}
	
	void CybParameters::setMaterialPropertyValue(int layer, EnumProperty property, float value)
	{
		if(!materialContexIsEnable)
			cout << " Message Error: Materiel property context not created!" << endl;
		else{
			if(layer > numLayer || layer < 0)
				cout << "Invalid Layer Id!" << endl;
			else if(property == STIFFNESS)
				properties[layer].stiffness = value;
			else if(property == DAMPING)
				properties[layer].damping = value;
			else if(property == STATIC_FRICTION)
				properties[layer].static_friction = value;
			else if(property == DYNAMIC_FRICTION)
				properties[layer].dynamic_friction = value;
			else if(property == POPTHROUGH)
				properties[layer].popthrough = value;
			else if(property == MASS)
				properties[layer].mass = value;
			else
				cout<<"Message Error: Invalid Property"<<endl;
		}
	}
	
	float CybParameters::getMaterialPropertyValue(int layer, EnumProperty property)
	{
		if(!materialContexIsEnable)
		{
			cout << " Message Error: Materiel property context not created!" << endl;
			return 0.0f;
		}
		else
		{
			if(layer > numLayer || layer < 0)
				cout << "Invalid Layer Id!" << endl;
			else if(property == STIFFNESS)
				return properties[layer].stiffness;
			else if(property == DAMPING)
				return properties[layer].damping;
			else if(property == STATIC_FRICTION)
				return properties[layer].static_friction;
			else if(property == DYNAMIC_FRICTION)
				return properties[layer].dynamic_friction;
			else if(property == POPTHROUGH)
				return properties[layer].popthrough;
			else if(property == MASS)
				return properties[layer].mass;
			else
				cout<<"Message Error: Invalid Property"<<endl;
			return 0.0f;
		}
	}
	
	void CybParameters::setLayerFace(int layer, EnumFace face)
	{
		activeFaces[layer] = face;
	}
	
	EnumFace CybParameters::getLayerFace(int layer)
	{	
		//cout << "layer " << layer << endl;
		return activeFaces[layer]; 
	}
	
	void CybParameters::setMaterialFace(int layer, EnumProperty property, EnumFace face)
	{
		if(!materialContexIsEnable)
			cout << " Message Error: Materiel property context not created!" << endl;
		else
		{
			if(layer > numLayer || layer < 0)
				cout << "Invalid Layer Id!" << endl;
			else if(property == STIFFNESS)
				properties[layer].propertyFace[0] = face;
			else if(property == DAMPING)
				properties[layer].propertyFace[1] = face;
			else if(property == STATIC_FRICTION)
				properties[layer].propertyFace[2] = face;
			else if(property == DYNAMIC_FRICTION)
				properties[layer].propertyFace[3] = face;
			else if(property == POPTHROUGH){
				properties[layer].propertyFace[4] = face;
			}
			else if(property == MASS){
				properties[layer].propertyFace[5] = face;
			}
			else
				cout<<"Message Error: Invalid Property"<<endl;
	
			materialFaceModified = true;
		}
	}
	
	EnumFace CybParameters::getMaterialFace(int layer, EnumProperty property)
	{
		if(!materialContexIsEnable){
			cout << " Message Error: Materiel property context not created!" << endl;
			return FRONT_AND_BACK;
		}
		else{
	
			if(layer > numLayer || layer < 0){
				cout << "Invalid Layer Id, default face was returned!" << endl;
				return FRONT_AND_BACK;
			}
			else if(property == STIFFNESS)
				return properties[layer].propertyFace[0];
			else if(property == DAMPING)
				return properties[layer].propertyFace[1];
			else if(property == STATIC_FRICTION)
				return properties[layer].propertyFace[2];
			else if(property == DYNAMIC_FRICTION)
				return properties[layer].propertyFace[3];
			else if(property == POPTHROUGH)
				return properties[layer].propertyFace[4];
			else if(property == MASS)
				return properties[layer].propertyFace[5];
			else{
				cout<<"Message Error: Invalid Property, default property was returned"<<endl;
				return FRONT_AND_BACK;
			}
		}
	}
	
	void CybParameters::aloc(int triangles, int vertex, int idLayer)
	{
		daloc(idLayer);
	
		if(!isaloc[0])
		{
			isaloc[idLayer] = true;
	
			// Triangles
			v = new CybVector3D<int>*[numLayer];
	
			// Coordenates
			coordList = new CybVector3D<float>*[numLayer];
	
			// Normal cells
			vNormalCell = new CybVector3D<float>*[numLayer];
	
			// Normal vertexes
			vNormal = new CybVector3D<float>*[numLayer];
		}
	
		coordList[idLayer] = new CybVector3D<float> [vertex];
	
		v[idLayer] = new CybVector3D<int>[triangles];
	
		vNormalCell[idLayer] = new CybVector3D<float>[triangles];
	
		vNormal[idLayer] = new CybVector3D<float>[triangles];
	}
	
	void CybParameters::alocParameters()
	{
		char c, *a;
		habLayer = new int[numLayer];
		nt = new int[numLayer];
		nv = new int[numLayer];
		isaloc = new bool[numLayer];
		layerName = new char*[numLayer];
	
		transforMatrix = new GLfloat*[numLayer];
		for(int i=0; i<numLayer; i++)
			transforMatrix[i] = new GLfloat[16];
	
		color = new CybVector4D<float>[numLayer];
	
		layerRot = new CybVector3D<float>[numLayer];
		layerTrans = new CybVector3D<float>[numLayer];
		layerSca = new CybVector3D<float>[numLayer];
	
		layerGeometricCenter = new CybVector3D<float>[numLayer];
	
		for(int i = 0; i < numLayer; i++)
		{
			isaloc[i] = false;
	
			for(int j = 0; j<3; j++)
			{
				layerRot[i][j] = 0;
				layerTrans[i][j] = 0;
				layerSca[i][j] = 1;
				color[i][j] = 1;
			}
			color[i][3] = 1 ;
	
			layerName[i] = "Layer ";
		}
	}
	
	void CybParameters::daloc(int idLayer)
	{
		if(isaloc[idLayer])
		{
			delete []v[idLayer];
			delete []coordList[idLayer];
			delete []vNormal[idLayer];
		}
	}
	
	bool CybParameters::getCollisionStatus()
	{
		return CybParameters::collisionStatus;
	}
	
	void CybParameters::setCollisionStatus(bool status)
	{
		CybParameters::collisionStatus = status;
	}

	void CybParameters::createTextures(int numTextures) {
		CybParameters::nTextures = numTextures;
		CybParameters::texName = (char **)malloc(numTextures*sizeof(char*));
		CybParameters::texture = (GLuint*)malloc(numTextures*sizeof(GLuint));
	}


	tInteratorsList CybParameters::getInteratorList() {
		return this->interators;
	}

	CybInterator* CybParameters::getInterator(int idInterator) {
		if (idInterator < numInterators)
			return this->interators[idInterator];

		return NULL;
	}

	int CybParameters::getNumInterators() {
		return this->numInterators;
	}

	void CybParameters::addInterator(CybInterator* interator) {
		interators.push_back(interator);
		numInterators++;
	}

	void CybParameters::removeInterator(CybInterator* interator) {

	}

	void CybParameters::addLayerListener(CybLayerListener* listener) {
		layerListenersList.push_back(listener);
	}

	void CybParameters::addDeformableLayer(int numLayer) {
		deformableLayers.push_back(numLayer);
	}

	void CybParameters::removeDeformableLayer(int numLayer) {
		for(int i = 0; i < deformableLayers.size(); i++)
			if(deformableLayers[i] == numLayer) 
				deformableLayers.erase(deformableLayers.begin() + i);
	}

	bool CybParameters::isDeformableLayer(int numLayer) {
		for(int i = 0; i < deformableLayers.size(); i++)
			if(deformableLayers[i] == numLayer) 
				return true;
		return false;
	}
	
		void CybParameters::changeDualWindowState(bool state){
		dualWindowActive = state;
	}

	bool CybParameters::isDualWindowContextActive(){
		return dualWindowActive;
	}

	int CybParameters::getRightWindow(){
		return rightWindow;
	}

	int CybParameters::getLeftWindow(){
		return leftWindow;
	}

	void CybParameters::setRightWindow(int identifier){
		rightWindow = identifier;
	}

	void CybParameters::setLeftWindow(int identifier){
		leftWindow = identifier;
	}

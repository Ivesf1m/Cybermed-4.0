// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2011 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba.
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


#include "cybAABB.h"


CybAABB::CybAABB(int layer, CybInterator* interator, bool iib, bool draw)
	: CybBroadCollision(layer, interator)
{
	isInteratorBox = iib;
	calculateCenterAndSizes();
	realCenter = center;
	realSizes = sizes;
	initialSizes = sizes;
	if(iib)getInteratorTransformations(lastTransf);
	else getMeshTransformations(lastTransf);
	if(!draw) drawer = NULL;
	else{
		CybVector3D<float> scale, translation;
		translation[0] = lastTransf[0]; translation[1] = lastTransf[1]; translation[2] = lastTransf[2];
		scale[0] = lastTransf[3]; scale[1] = lastTransf[4]; scale[2] = lastTransf[5];
		drawer = new CybAABBDrawer(center, sizes, scale, translation);
	}
	calculateRealCenter();
	calculateRealSizes();
	CybCollisionObserver::getInstance()->addCollisionObject(this, "broad");
}

CybAABB::CybAABB(int layer, int interatorId, bool iib, bool draw)
	: CybBroadCollision(layer, interatorId)
{
	isInteratorBox = iib;
	calculateCenterAndSizes();
	realCenter = center;
	realSizes = sizes;
	initialSizes = sizes;
	if(iib)getInteratorTransformations(lastTransf);
	else getMeshTransformations(lastTransf);
	if(!draw) drawer = NULL;
	else{
		CybVector3D<float> scale, translation;
		translation[0] = lastTransf[0]; translation[1] = lastTransf[1]; translation[2] = lastTransf[2];
		scale[0] = lastTransf[3]; scale[1] = lastTransf[4]; scale[2] = lastTransf[5];
		drawer = new CybAABBDrawer(center, sizes, scale, translation);
	}
	calculateRealCenter();
	calculateRealSizes();
	CybCollisionObserver::getInstance()->addCollisionObject(this, "broad");
}

CybAABB::CybAABB(const CybAABB& caixa)
	: CybBroadCollision(caixa.layerOfCollision, getInterator())
{
	center = caixa.center;
	sizes = caixa.sizes;
	listOfTriangles = caixa.listOfTriangles;
	collisionStatus = false;
	isInteratorBox = caixa.isInteratorBox;
	realCenter = caixa.realCenter;
	realSizes = caixa.realSizes;
	initialSizes = caixa.initialSizes;
	drawer = caixa.drawer;
	for(int i = 0; i < 9; ++ i) lastTransf[i] = caixa.lastTransf[i];
	CybCollisionObserver::getInstance()->addCollisionObject(this, "broad");
}

CybAABB::CybAABB(CybNarrowCollision *narrow, bool iib, bool draw)
	: CybBroadCollision(narrow->getLayerOfCollision(), narrow->getInterator())
{
	isInteratorBox = iib;
	calculateCenterAndSizes();
	realCenter = center;
	realSizes = sizes;
	initialSizes = sizes;
	if(iib)getInteratorTransformations(lastTransf);
	else getMeshTransformations(lastTransf);
	if(!draw) drawer = NULL;
	else{
		CybVector3D<float> scale, translation;
		translation[0] = lastTransf[0]; translation[1] = lastTransf[1]; translation[2] = lastTransf[2];
		scale[0] = lastTransf[3]; scale[1] = lastTransf[4]; scale[2] = lastTransf[5];
		drawer = new CybAABBDrawer(center, sizes, scale, translation);
	}
	calculateRealCenter();
	calculateRealSizes();
	CybCollisionObserver::getInstance()->addCollisionObject(this, "broad");
}

CybAABB& CybAABB::operator=(const CybAABB& caixa)
{
	if(this == &caixa) return *this; //self-assignment

	listOfTriangles.clear(); //emptying list

	center = caixa.center;
	sizes = caixa.sizes;
	setInterator(getInterator());
	layerOfCollision = caixa.layerOfCollision;
	listOfTriangles = caixa.listOfTriangles;
	realCenter = caixa.realCenter;
	realSizes = caixa.realSizes;
	isInteratorBox = caixa.isInteratorBox;
	initialSizes = caixa.initialSizes;
	drawer = caixa.drawer;
	for(int i = 0; i < 9; ++ i) lastTransf[i] = caixa.lastTransf[i];
	objectIndex = caixa.objectIndex;
}

void CybAABB::addTest(CybAABB* c)
{
	testList.push_back(c);
}

void CybAABB::calculateCenterAndSizes()
{
	float maxX = 0, maxY = 0, maxZ = 0;
	float minX = 0, minY = 0, minZ = 0;
	cybMesh<cybSurfaceTriTraits>* mesh;
	if(isInteratorBox) mesh = getInterator()->getMesh(getInterator()->getActiveMesh());
	else mesh = CybParameters::getInstance()->mesh[layerOfCollision];
	int numVertex = mesh->getNumberOfVertices();
	for(int i = 0; i != numVertex; i++)
	{
		if(maxX < mesh->getVertex(i)->getCoord(0)) maxX = mesh->getVertex(i)->getCoord(0);
		if(minX > mesh->getVertex(i)->getCoord(0)) minX = mesh->getVertex(i)->getCoord(0);
		if(maxY < mesh->getVertex(i)->getCoord(1)) maxY = mesh->getVertex(i)->getCoord(1);
		if(minY > mesh->getVertex(i)->getCoord(1)) minY = mesh->getVertex(i)->getCoord(1);
		if(maxZ < mesh->getVertex(i)->getCoord(2)) maxZ = mesh->getVertex(i)->getCoord(2);
		if(minZ > mesh->getVertex(i)->getCoord(2)) minZ = mesh->getVertex(i)->getCoord(2);
	}

	center[0] = (fabs(maxX) - fabs(minX))/2;
	center[1] = (fabs(maxY) - fabs(minY))/2;
	center[2] = (fabs(maxZ) - fabs(minZ))/2;

	sizes[0] = (fabs(maxX) + fabs(minX))/2;
	sizes[1] = (fabs(maxY) + fabs(minY))/2;
	sizes[2] = (fabs(maxZ) + fabs(minZ))/2;

}

void CybAABB::calculateRealCenter()
{
	realCenter[0] = (center[0] + lastTransf[0]) * lastTransf[3];
	realCenter[1] = (center[1] + lastTransf[1]) * lastTransf[4];
	realCenter[2] = (center[2] + lastTransf[2]) * lastTransf[5];
}

void CybAABB::calculateRealSizes()
{
	realSizes[0] = sizes[0] * lastTransf[3];
    	realSizes[1] = sizes[1] * lastTransf[4];
    	realSizes[2] = sizes[2] * lastTransf[5];
}

void  CybAABB::calculateRotatedSizes(int axis, float angle, float* values)
{
	int rot1, rot2;
	if(axis == 0){ rot1 = 1; rot2 = 2; }
	else if(axis == 1){ rot1 = 0; rot2 = 2; }
	else if(axis == 2){ rot1 = 0; rot2 = 1; }
	else return;
	float aux = angle/180;
	if(aux == (int) aux) return; //If the angle is an exact multiple of 180, the sizes remain the same.
	aux = angle/90;
	if(aux == (int) aux){
		float swap = values[rot1];
		values[rot1] = values[rot2];
		values[rot2] = swap;
		return;
	}//If the angle is an exact odd multiple of 90 (90 * {1,3,5,...}), we exchange the values of the sizes.
	float hyp = sqrt(pow(values[rot1], 2) + pow(values[rot2], 2)); //we might need this from now on.
	aux = angle/45;
	if(aux = (int) aux){
		values[rot1] = hyp;
		values[rot2] = hyp;
		return;
	}//If the angle is an exact odd multiple of 45 (45 * {1,3,5,...}), the box becomes the maximum area square
	 //because the sizes are now equal to the hypotenuse of the triangle formed by them.

	/*From this point on we separate the treatment of the rotation in intervals, according to the angle.*/
	float size1, size2;
	if((angle > 0.0 && angle < 45.0) || (angle > 180.0 && angle < 225.0)){
		size1 = values[rot1] + values[rot2]*tan(degToRad(angle));
		size2 = values[rot2] + values[rot1]*tan(degToRad(angle));

	}
	else if((angle > 135.0 && angle < 180.0) || (angle > 315.0 && angle < 360.0)){
		size1 = values[rot1] - values[rot2]*tan(degToRad(angle));
		size2 = values[rot2] - values[rot1]*tan(degToRad(angle));
	}
	else if((angle > 90.0 && angle < 135.0) || (angle > 270.0 && angle < 315.0)){
		size1 = values[rot2] + values[rot1]*tan(degToRad(angle - 90.0));
		size2 = values[rot1] + values[rot2]*tan(degToRad(angle - 90.0));
	}
	else if((angle > 45.0 && angle < 90.0) || (angle > 225.0 && angle < 270.0)){
		size1 = values[rot2] - values[rot1]*tan(degToRad(angle - 90.0));
		size2 = values[rot1] - values[rot2]*tan(degToRad(angle - 90.0));
	}
	if(size1 > hyp) values[rot1] = hyp;
	else values[rot1] = size1;
	if(size2 > hyp) values[rot2] = hyp;
	else values[rot2] = size2;
	return;
}

bool CybAABB::collision(CybAABB& c)
{
	if(fabs(realCenter[0] - c.getRealCenter()[0]) > (realSizes[0] + c.getRealSizes()[0])){ return false;}
	if(fabs(realCenter[1] - c.getRealCenter()[1]) > (realSizes[1] + c.getRealSizes()[1])){ return false; }
	if(fabs(realCenter[2] - c.getRealCenter()[2]) > (realSizes[2] + c.getRealSizes()[2])){ return false; }
	return true;
}

float CybAABB::degToRad(float angle)
{
	return angle*PI/180;
}

void CybAABB::describeBox()
{
	cout << "A coordenada x do centro da caixa e: " << center[0] << endl;
	cout << "A coordenada y do centro da caixa e: " << center[1] << endl;
	cout << "A coordenada z do centro da caixa e: " << center[2] << endl;
	cout << "O semi-comprimento x da caixa e: " << sizes[0] << endl;
	cout << "O semi-comprimento y da caixa e: " << sizes[1] << endl;
	cout << "O semi-comprimento z da caixa e: " << sizes[2] << endl;
}

void CybAABB::destroy()
{
	CybThread::destroy();
}

CybVector3D<float>& CybAABB::getCenter()
{
	return center;
}

CybAABBDrawer* CybAABB::getDrawer()
{
	return drawer;
}

void CybAABB::getInteratorTransformations(float *t){
	CybThread::lock();
	for(int i = 0; i < 9; ++i){
		if(i < 3){
			t[i] = getInterator()->getTranslation()[i];
		}else if(i >= 3 && i < 6){
			t[i] = getInterator()->getScale()[i-3];
		}else t[i] = getInterator()->getRotation()[i-6];
	}
	CybThread::unlock();
}

void CybAABB::getMeshTransformations(float *t){
	CybThread::lock();
	CybParameters* cybcore = CybParameters::getInstance();
	t[0] = cybcore->xTrans + cybcore->layerTrans[layerOfCollision][0];
	t[1] = cybcore->yTrans + cybcore->layerTrans[layerOfCollision][1];
	t[2] = cybcore->zTrans + cybcore->layerTrans[layerOfCollision][2];
	t[3] = cybcore->xScale * cybcore->layerSca[layerOfCollision][0];
	t[4] = cybcore->yScale * cybcore->layerSca[layerOfCollision][1];
	t[5] = cybcore->zScale * cybcore->layerSca[layerOfCollision][2];
	t[6] = cybcore->getXAngle() + cybcore->layerRot[layerOfCollision][0];
	t[7] = cybcore->getYAngle() + cybcore->layerRot[layerOfCollision][1];
	t[8] = cybcore->getZAngle() + cybcore->layerRot[layerOfCollision][2];
	CybThread::unlock();
}

int CybAABB::getObjectIndex()
{
	return objectIndex;
}

CybVector3D<float>& CybAABB::getRealCenter()
{
	return realCenter;
}

CybVector3D<float>& CybAABB::getRealSizes()
{
	return realSizes;
}

CybVector3D<float>& CybAABB::getSizes()
{
	return sizes;
}

list<CybAABB*> CybAABB::getTestList()
{
	return testList;
}

void CybAABB::init()
{
	CybThread::init();
}

void CybAABB::removeTest(CybAABB* c)
{
	list<CybAABB*>::iterator it;
	for(it = testList.begin(); it != testList.end(); ++it)
	{
		CybThread::lock();
		if((*it) == c) testList.remove(c);
		CybThread::unlock();
	}
}

void CybAABB::run()
{
	list<CybAABB*>::iterator it;
	CybThread::lock();
	CybCollisionObserver* observer = CybCollisionObserver::getInstance();
	bool teste;
	for(it = testList.begin(); it != testList.end(); ++it)
	{	
		teste = collision(*(*it));	
		observer->changeState(this, (*it), teste);
	}
	CybThread::unlock();
	update();	
}

void CybAABB::setCenter(CybVector3D<float>& center)
{
	this->center = center;
}

void CybAABB::setCenter(float cx, float cy, float cz)
{
	center[0] = cx;
	center[1] = cy;
	center[2] = cz;
}

void CybAABB::setSizes(CybVector3D<float>& sizes)
{
	this->sizes = sizes;
}

void CybAABB::setSizes(float sx, float sy, float sz)
{
	sizes[0] = sx;
	sizes[1] = sy;
	sizes[2] = sz;
}

void CybAABB::treatRotation(float* transf, bool* axis)
{
	float rotX[3] = {initialSizes[0], initialSizes[1], initialSizes[2]};
	float rotY[3] = {initialSizes[0], initialSizes[1], initialSizes[2]};
	float rotZ[3] = {initialSizes[0], initialSizes[1], initialSizes[2]};;
	float *auxRot[3] = {rotX, rotY, rotZ};
	for(int i = 0; i < 3; ++i){
	    if(axis[i]){
            calculateRotatedSizes(i, transf[i + 6], auxRot[i]);
	    }
    	}
    	sizes[0] = max(max(rotX[0], rotY[0]), rotZ[0]);
   	sizes[1] = max(max(rotX[1], rotY[1]), rotZ[1]);
    	sizes[2] = max(max(rotX[2], rotY[2]), rotZ[2]);
	drawer->setSizes(sizes);
    	calculateRealCenter();
    	calculateRealSizes();
	describeBox();
}

void CybAABB::update()
{
	CybCollision::update();
	if(isInteratorBox){
		CybThread::lock();
		CybVector3D<float> aux = CybCollisionData::getInstance()->getInteratorPositionInGraphicsCoordenates();
		setCenter(aux);
		drawer->setCenter(aux);
		CybThread::unlock();
		calculateRealCenter();
    }
	float transf[9];
	if(isInteratorBox) getInteratorTransformations(transf);
	else getMeshTransformations(transf);
	//treating rotation
	bool mudancaR = false;
	bool eixos[3] = {false, false, false};
	for(int k = 6; k < 9; ++k){
		if(lastTransf[k] != transf[k]){
			lastTransf[k] = transf[k];
			mudancaR = true;
			eixos[k-6] = true;
		}
	}
	if(mudancaR) treatRotation(lastTransf, eixos);
	//treating scale and translation
	bool mudanca = false;
	for(int j = 0; j < 6; ++j){
		if(lastTransf[j] != transf[j]){
			lastTransf[j] = transf[j];
			mudanca = true;
		}
	}
	if(mudanca){
		calculateRealCenter();
		calculateRealSizes();
		CybVector3D<float> scale, translation;
		translation[0] = lastTransf[0]; translation[1] = lastTransf[1]; translation[2] = lastTransf[2];
		scale[0] = lastTransf[3]; scale[1] = lastTransf[4]; scale[2] = lastTransf[5];
		drawer->setTranslation(translation);
		drawer->setScale(scale);
	}
}


void CybAABB::updateBox(float cx, float cy, float cz)
{
	setCenter(cx,cy,cz);
}

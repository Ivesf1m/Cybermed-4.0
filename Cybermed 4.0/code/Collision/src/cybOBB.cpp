// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#include "cybOBB.h"


CybOBB::CybOBB(int layerID, CybInterator* interator, bool interatorBox, bool draw)
       :CybBroadCollision(layerID, interator)
{
	this->interatorBox = interatorBox;
	buildFromTriangles();
	initialSizes = sizes;
	if(interatorBox)getInteratorGlobalTransformations(lastGlobalTransf);
	else{ getMeshGlobalTransformations(lastGlobalTransf); getMeshLayerTransformations(lastLayerTransf); }
	if(!draw) drawer = NULL;
	else drawer = new CybOBBDrawer(orientation, center, sizes);
	CybCollisionObserver::getInstance()->addCollisionObject(this, "obb");
	update();
}

CybOBB::CybOBB(int layerID, int interatorID, bool interatorBox, bool draw)
       :CybBroadCollision(layerID, interatorID)
{
	this->interatorBox = interatorBox;
	buildFromTriangles();
	initialSizes = sizes;
	if(interatorBox)getInteratorGlobalTransformations(lastGlobalTransf);
	else{ getMeshGlobalTransformations(lastGlobalTransf); getMeshLayerTransformations(lastLayerTransf); }
	if(!draw) drawer = NULL;
	else drawer = new CybOBBDrawer(orientation, center, sizes);
	CybCollisionObserver::getInstance()->addCollisionObject(this, "obb");
	update();
}

CybOBB::CybOBB(const CybOBB& box)
       :CybBroadCollision(box.layerOfCollision, getInterator())
{
	delete this->drawer;	
	
	this->center = box.center;
	this->sizes = box.sizes;
	this->initialSizes = box.initialSizes;
	for(int i = 0; i < 3; ++i){
 		this->orientation[i] = box.orientation[i];
		this->lastGlobalTransf[i] = box.lastGlobalTransf[i];
		this->lastLayerTransf[i] = box.lastLayerTransf[i];
	}
	this->interatorBox = box.interatorBox;
	this->drawer = box.drawer;	
	CybCollisionObserver::getInstance()->addCollisionObject(this, "obb");
}

CybOBB::CybOBB(CybNarrowCollision* narrowObj, bool interatorBox, bool draw)
       :CybBroadCollision(narrowObj->getLayerOfCollision(), narrowObj->getInterator())
{
	this->interatorBox = interatorBox;
	buildFromTriangles();
	initialSizes = sizes;
	if(interatorBox)getInteratorGlobalTransformations(lastGlobalTransf);
	else{ getMeshGlobalTransformations(lastGlobalTransf); getMeshLayerTransformations(lastLayerTransf); }
	if(!draw) drawer = NULL;
	else drawer = new CybOBBDrawer(orientation, center, sizes);
	CybCollisionObserver::getInstance()->addCollisionObject(this, "obb");
}

CybOBB::~CybOBB()
{
	cout << "OBB destruida" << endl;
}

CybOBB& CybOBB::operator=(const CybOBB& box)
{
	delete this->drawer;

	this->layerOfCollision = box.layerOfCollision;
	this->setInterator(getInterator());
	this->center = box.center;
	this->sizes = box.sizes;
	for(int i = 0; i < 3; ++i){
		this->orientation[i] = box.orientation[i];
		this->lastGlobalTransf[i] = box.lastGlobalTransf[i];
		this->lastLayerTransf[i] = box.lastLayerTransf[i];
	}
	this->interatorBox = box.interatorBox;
	this->drawer = box.drawer;
}

void CybOBB::addTest(CybOBB* box)
{
	testList.push_back(box);
}

void CybOBB::buildFromTriangles()
{
	//Defining which mesh will be used.
	cybMesh<cybSurfaceTriTraits>* mesh;
	if(interatorBox) mesh = getInterator()->getMesh(getInterator()->getActiveMesh());
	else mesh = CybParameters::getInstance()->mesh[layerOfCollision];

	//Variable declarations.
	cybSurfaceTriTraits::sCell* aux;
	sVertex *ponto1, *ponto2, *ponto3;
	CybVector3D<double> pt1, pt2, pt3;
	CybVector3D<double> mu, mui;
	CybVector3D<double> norm;
	CybVector3D<double> covMatrix[3];
	int qtdCells = mesh->getNumberOfCells();
	double Ai, Am = 0.0;
	double cxx = 0.0, cxy = 0.0, cxz = 0.0, cyy = 0.0, cyz = 0.0, czz = 0.0;

	//Calculating the covariance terms. 
	for(int i = 0; i < qtdCells; ++i)
	{
		aux = mesh->getCell(i);
		ponto1 = mesh->getVertex(aux->getVertexId(0));
		ponto2 = mesh->getVertex(aux->getVertexId(1));
		ponto3 = mesh->getVertex(aux->getVertexId(2));
		pt1(ponto1->getCoord(0), ponto1->getCoord(1), ponto1->getCoord(2));
		pt2(ponto2->getCoord(0), ponto2->getCoord(1), ponto2->getCoord(2));
		pt3(ponto3->getCoord(0), ponto3->getCoord(1), ponto3->getCoord(2));
		
		mui = (pt1 + pt2 + pt3)/3.0;
		norm = (pt2 - pt1) * (pt3 - pt1);
		Ai = norm.getNorm()/2.0;
		mu = mu + (mui * Ai);
		Am += Ai;

		cxx += ( 9.0 * mui[0] * mui[0] + pt1[0] * pt1[0] + pt2[0] * pt2[0] + pt3[0] * pt3[0] ) * (Ai/12.0);
		cxy += ( 9.0 * mui[0] * mui[1] + pt1[0] * pt1[1] + pt2[0] * pt2[1] + pt3[0] * pt3[1] ) * (Ai/12.0);
		cxz += ( 9.0 * mui[0] * mui[2] + pt1[0] * pt1[2] + pt2[0] * pt2[2] + pt3[0] * pt3[2] ) * (Ai/12.0);
		cyy += ( 9.0 * mui[1] * mui[1] + pt1[1] * pt1[1] + pt2[1] * pt2[1] + pt3[1] * pt3[1] ) * (Ai/12.0);
		cyz += ( 9.0 * mui[1] * mui[2] + pt1[1] * pt1[2] + pt2[1] * pt2[2] + pt3[1] * pt3[2] ) * (Ai/12.0);
		czz += ( 9.0 * mui[2] * mui[2] + pt1[2] * pt1[2] + pt2[2] * pt2[2] + pt3[2] * pt3[2] ) * (Ai/12.0);
	}
	
	//Dividing Am from mu and the covariance terms.
	mu = mu / Am;
	cxx /= Am; cxy /= Am; cxz /= Am; cyy /= Am; cyz /= Am; czz /= Am; 

	//Subtracting the E[X]*E[Y] terms.
	cxx -= mu[0] * mu[0]; cxy -= mu[0] * mu[1]; cxz -= mu[0] * mu[2];
	cyy -= mu[1] * mu[1]; cyz -= mu[1] * mu[2]; czz -= mu[2] * mu[2];
	
	//Building the covariance matrix.
	covMatrix[0](cxx, cxy, cxz);
	covMatrix[1](cxy, cyy, cyz);
	covMatrix[2](cxz, cyz, czz);

	//Building OBB from the covariance matrix.
	buildOBB(covMatrix, mesh);
}

void CybOBB::buildOBB(CybVector3D<double>* covMatrix, cybMesh<cybSurfaceTriTraits>* mesh)
{
	//Calculating the eigen vectors and the eigen values of the covariance matrix.
	//The eigen vectors will be the OBB's orienting vectors.
	CybVector3D<double> eigenVectors[3];
	double eigenValues[3];
	calculateEigenSystem(covMatrix, eigenValues, eigenVectors);
	
	//Organizing the orientation matrix
	for(int j = 0; j < 3; ++j)
	{
		for(int i = 0; i < 3; ++i)
		{
			orientation[j][i] = covMatrix[i][j];
		}
		orientation[j].normalize();
	}

	//Calculating the maximum and minimum values on each axis, projecting onto the orientation vectors.
	CybVector3D<double> minim(1e10, 1e10, 1e10), maxim(-1e10, -1e10, -1e10);
	CybVector3D<double> p_prime(0,0,0);
	CybVector3D<double> aux(0,0,0);
	int qttPoints = mesh->getNumberOfVertices();
	sVertex* cPoint; //current point
	for(int i = 0; i < qttPoints; ++i)
	{
		cPoint = mesh->getVertex(i);
		aux(cPoint->getCoord(0), cPoint->getCoord(1), cPoint->getCoord(2));
		p_prime(orientation[0] ^ aux, orientation[1] ^ aux, orientation[2] ^ aux);
		minim = minim.min(p_prime);
		maxim = maxim.max(p_prime);
	}
	
	//Cálculo do centro (ponto médio dos eixos) e dos semi-eixos.
	CybVector3D<double> cAux = (maxim + minim) * 0.5;
	center(orientation[0] ^ cAux, orientation[1] ^ cAux, orientation[2] ^ cAux);
	sizes = (maxim - minim) * 0.5;
}

void CybOBB::calculateEigenSystem(CybVector3D<double>* covMatrix, double* eigVal, CybVector3D<double>* eigVec)
{
	const double epsilon = 1e-10;
	const int maxSweeps = 32;
	double m11 = covMatrix[0][0];
	double m12 = covMatrix[0][1];
	double m13 = covMatrix[0][2];
	double m22 = covMatrix[1][1];
	double m23 = covMatrix[1][2];
	double m33 = covMatrix[2][2];
	setIdentity(eigVec, 3);
	for(int i = 0; i < maxSweeps; ++i)
	{
		//Leaves for loop if values are less than epsilon.
		if(fabs(m12) < epsilon && fabs(m13) < epsilon && fabs(m23) < epsilon) break;

		//Treating position [1][2]
		if(m12 != 0.0)
		{
			double u = (m22 - m11) * 0.5/m12;
			double u2 = u * u;
			double u2p1 = u2 + 1.0;
			double t = (u2p1 != u2) ? ((u < 0.0) ? -1.0 : 1.0) * (sqrt(u2p1) - fabs(u)) : 0.5/u;
			double c = 1.0/sqrt(t*t + 1.0);
			double s = c * t;
			
			m11 -= t * m12;
			m22 += t * m12;
			m12 = 0.0;

			double temp = c * m13 - s * m23;
			m23 = s * m13 + c * m23;
			m13 = temp;

			for(int j = 0; j < 3; ++j)
			{
				double temp2 = c * eigVec[j][0] - s * eigVec[j][1];
				eigVec[j][1] = s * eigVec[j][0] + c * eigVec[j][1];
				eigVec[j][0] = temp2;
			}
		}

		//Treating position [1][3]
		if(m13 != 0.0)
		{
			double u = (m33 - m11) * 0.5/m13;
			double u2 = u * u;
			double u2p1 = u2 + 1.0;
			double t = (u2p1 != u2) ? ((u < 0.0) ? -1.0 : 1.0) * (sqrt(u2p1) - fabs(u)) : 0.5/u;
			double c = 1.0 / sqrt(t*t + 1.0);
			double s = c * t;
			
			m11 -= t * m13;
			m33 += t * m13;
			m13 = 0.0;

			double temp = c * m12 - s * m23;
			m23 = s * m12 + c * m23;
			m12 = temp;
			
			for(int j = 0; j < 3; ++j)
			{
				double temp2 = c * eigVec[j][0] - s * eigVec[j][2];
				eigVec[j][2] = s * eigVec[j][0] + c * eigVec[j][2];
				eigVec[j][0] = temp2;
			}
		}
		
		//Treating position [2][3]
		if(m23 != 0.0)
		{
			double u = (m33 - m22) * 0.5/m23;
			double u2 = u * u;
			double u2p1 = u2 + 1.0;
			double t = (u2p1 != u2) ? ((u < 0.0) ? -1.0 : 1.0) * (sqrt(u2p1) - fabs(u)) : 0.5/u;
			double c = 1.0 / sqrt(t*t + 1.0);
			double s = c * t;

			m22 -= t * m23;
			m33 += t * m23;
			m23 = 0.0;

			double temp = c * m12 - s * m13;
			m13 = s * m12 + c * m13;
			m12 = temp;

			for(int j = 0; j < 3; ++j)
			{
				double temp2 = c * eigVec[j][1] - s * eigVec[j][2];
				eigVec[j][2] = s * eigVec[j][1] + c * eigVec[j][2];
				eigVec[j][1] = temp2;
			}
		}
	}
	eigVal[0] = m11;
	eigVal[1] = m22;
	eigVal[2] = m33;
}

bool CybOBB::collision(CybOBB& box)
{
	//Convention used in the comments: A is this box and B is the parameter box.
	double ra, rb;
	double R[3][3], AbsR[3][3];

	//Computing the rotation matrix that expresses "box" in this OBB's vector space.
	for(int i = 0; i < 3; ++i){
		CybVector3D<double> vetor1(this->orientation[i][0], this->orientation[i][1], this->orientation[i][2]);
		for(int j = 0; j < 3; ++j){
			CybVector3D<double> vetor2(box.orientation[0][j], box.orientation[1][j], box.orientation[2][j]); 
			R[i][j] = vetor1 ^ vetor2;
		}
	}

	//Computing the translation t
	CybVector3D<double> t(box.center[0] - center[0], box.center[1] - center[1], box.center[2] - center[2]);

	//Porjecting translation to this box's vector space.
	CybVector3D<double> t2(t ^ orientation[0], t ^ orientation[1], t ^ orientation[2]);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			AbsR[i][j] = fabs(R[i][j]) + EPSILON;
		}
	}

	CybVector3D<double> boxSize = box.sizes;;

	//Testing axes L = A0, L = A1, L = A2
	for(int i = 0; i < 3; ++i){
		ra = sizes[i];		
		rb = boxSize[i] * AbsR[i][0] + boxSize[i] * AbsR[i][1] + boxSize[i] * AbsR[i][2];
		if(fabs(t[i]) > ra + rb) return false;
	}

	//Testing axes L = B0, L = B1, L = B2
	for(int i = 0; i < 3; ++i){
		ra = sizes[0] * AbsR[0][i] + sizes[1] * AbsR[1][i] + sizes[2] * AbsR[2][i];
		rb = boxSize[i];
		if(fabs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return false;
	}

	//Testing axis L = A0 X B0
	ra = sizes[1] * AbsR[2][0] + sizes[2] * AbsR[1][0];
	rb = boxSize[1] * AbsR[0][2] + boxSize[2] * AbsR[0][1];
	if(fabs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return false;

	//Testing axis L = A0 X B1
	ra = sizes[1] * AbsR[2][1] + sizes[2] * AbsR[1][1];
	rb = boxSize[0] * AbsR[0][2] + boxSize[2] * AbsR[0][0];
	if(fabs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return false;

	//Testing axis L = A0 X B2
	ra = sizes[1] * AbsR[2][2] + sizes[2] * AbsR[1][2];
	rb = boxSize[0] * AbsR[0][1] + boxSize[1] * AbsR[0][0];
	if(fabs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return false;

	//Testing axis L = A1 X B0
	ra = sizes[0] * AbsR[2][0] + sizes[2] * AbsR[0][0];
	rb = boxSize[1] * AbsR[1][2] + boxSize[2] * AbsR[1][1];
	if(fabs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return false;

	//Testing axis L = A1 X B1
	ra = sizes[0] * AbsR[2][1] + sizes[2] * AbsR[0][1];
	rb = boxSize[0] * AbsR[1][2] + boxSize[2] * AbsR[1][0];
	if(fabs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return false;

	//Testing axis L = A1 X B2
	ra = sizes[0] * AbsR[2][2] + sizes[2] * AbsR[0][2];
	rb = boxSize[0] * AbsR[1][1] + boxSize[1] * AbsR[1][0];
	if(fabs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return false;

	//Testing axis L = A2 X B0
	ra = sizes[0] * AbsR[1][0] + sizes[1] * AbsR[0][0];
	rb = boxSize[1] * AbsR[2][2] + boxSize[2] * AbsR[2][1];
	if(fabs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return false;

	//Testing axis L = A2 X B1
	ra = sizes[0] * AbsR[1][1] + sizes[1] * AbsR[0][1];
	rb = boxSize[0] * AbsR[2][2] + boxSize[2] * AbsR[2][0];
	if(fabs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return false;

	//Testing axis L = A2 X B2
	ra = sizes[0] * AbsR[1][2] + sizes[1] * AbsR[0][2];
	rb = boxSize[0] * AbsR[2][1] + boxSize[1] * AbsR[2][0];
	if(fabs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return false;

	//If it is here, no separating axis was found. The OBBs are colliding then.
	return true;
}

void CybOBB::describeBox()
{
	cout << "The box's orienting vector are: " << endl;
	for(int i = 0; i < 3; ++i)
	{
		cout << "Vector " << i << ":  ";
		cout << orientation[i][0] << "   " << orientation[i][2] << "   "  << orientation[i][1] << "   " << endl;
	}
	cout << "The box's center is: " << endl;
	cout << "Center:   " <<  center[0] << ",   " << center[1] << ",   " << center[2] << endl;
	cout << "The box's halfedge lengths are: " << endl;
	cout << "Halfedge lengths:  " << sizes[0] << ",   " << sizes[1] << ",   " << sizes[2] << endl;
}

void CybOBB::destroy()
{
	CybThread::destroy();
}

CybVector3D<double>& CybOBB::getCenter()
{
	return center;
}

void CybOBB::getInteratorGlobalTransformations(CybVector3D<double>* transf)
{
	CybThread::lock();
	for(int i = 0; i < 3; ++i){
		transf[0][i] = getInterator()->getTranslation()[i];
		transf[1][i] = getInterator()->getScale()[i];
		transf[2][i] = getInterator()->getRotation()[i];
	}
	CybThread::unlock();
}

void CybOBB::getMeshGlobalTransformations(CybVector3D<double>* transf)
{
	CybThread::lock();
	CybParameters* cybcore = CybParameters::getInstance();
	transf[0][0] = cybcore->xTrans;
	transf[0][1] = cybcore->yTrans;
	transf[0][2] = cybcore->zTrans;
	transf[1][0] = cybcore->xScale;
	transf[1][1] = cybcore->yScale;
	transf[1][2] = cybcore->zScale;
	transf[2][0] = cybcore->getXAngle();
	transf[2][1] = cybcore->getYAngle();
	transf[2][2] = cybcore->getZAngle();
	CybThread::unlock();
}

void CybOBB::getMeshLayerTransformations(CybVector3D<double>* transf)
{
	CybThread::lock();
	CybParameters* cybcore = CybParameters::getInstance();
	transf[0][0] = cybcore->layerTrans[layerOfCollision][0];
	transf[0][1] = cybcore->layerTrans[layerOfCollision][1];
	transf[0][2] = cybcore->layerTrans[layerOfCollision][2];
	transf[1][0] = cybcore->layerSca[layerOfCollision][0];
	transf[1][1] = cybcore->layerSca[layerOfCollision][1];
	transf[1][2] = cybcore->layerSca[layerOfCollision][2];
	transf[2][0] = cybcore->layerRot[layerOfCollision][0];
	transf[2][1] = cybcore->layerRot[layerOfCollision][1];
	transf[2][2] = cybcore->layerRot[layerOfCollision][2];
	CybThread::unlock();
}

int CybOBB::getObjectIndex()
{
	return objectIndex;
}

CybVector3D<double>* CybOBB::getOrientation()
{
	return orientation;
}

CybVector3D<double>& CybOBB::getSizes()
{
	return sizes;
}

vector<CybOBB*>& CybOBB::getTestList()
{
	return testList;
}

void CybOBB::init()
{
	CybThread::init();
}

void CybOBB::removeTest(CybOBB* box)
{
	vector<CybOBB*> aux;
	for(int i = 0; i < (int) testList.size(); ++i)
	{
		if(testList[i] != box) aux.push_back(testList[i]);
	}
	testList = aux;
}

void CybOBB::run()
{
	CybThread::lock();
	CybCollisionObserver* obs = CybCollisionObserver::getInstance();
	bool test;
	for(int i = 0; i < (int) testList.size(); ++i)
	{
		test = collision(*(testList[i]));
		obs->changeState(this, testList[i], test);
	}
	CybThread::unlock();
	update();
}

void CybOBB::setCenter(double x, double y, double z)
{
	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void CybOBB::setIdentity(CybVector3D<double>* matrix, int dimension)
{
	for(int i = 0; i < dimension; ++i)
	{
		for(int j = 0; j < dimension; ++j)
		{
			if(i == j) matrix[i][j] = 1;
			else matrix[i][j] = 0;
		}
	}
}

void CybOBB::treatRotation(int axis, double angle)
{
	double* mr;
	double radAng = PI * angle / 180.0;
	double seno = sin(radAng);
	double cosseno = cos(radAng);
	double mrx[9] = {1,0,0,0, cosseno, -seno, 0, seno, cosseno};
	double mry[9] = {cosseno, 0, seno, 0, 1, 0, -seno, 0, cosseno};
	double mrz[9] = {cosseno, -seno, 0, seno, cosseno, 0, 0, 0, 1};	
	if(axis == 0)mr = mrx;
	else if(axis = 1) mr = mry; 
	else mr = mrz;
	CybMatrix<double> rotMat(3,3,mr);
	CybVector3D<double> verts[2];
	verts[0](center[0] - sizes[0], center[1] - sizes[1], center[2] - sizes[2]);
	verts[1](center[0] + sizes[0], center[1] + sizes[1], center[2] + sizes[2]);
	for(int i = 0; i < 2; ++i){
		CybMatrix<double> aux(verts[i]);
		aux = aux * rotMat;
		verts[i](aux[0][0], aux[0][1], aux[0][2]);
	}
	center = (verts[0] + verts[1])/2.0;
	sizes = (verts[1] - verts[0])/2.0;

}

void CybOBB::update()
{
	CybCollision::update();
	if(interatorBox){
		CybThread::lock();
		CybVector3D<float> aux = CybCollisionData::getInstance()->getInteratorPositionInGraphicsCoordenates();
		double array[3] = {aux[0], aux[1], aux[2]};
		CybMatrix<double> aux2(1,3,array);
		setCenter(aux[0], aux[1], aux[2]);
		drawer->setCenter(&aux2);
		CybThread::unlock();
	}
	CybVector3D<double> localTransf[3], globalTransf[3];
	if(interatorBox) getInteratorGlobalTransformations(globalTransf);
	else{
		getMeshGlobalTransformations(globalTransf);
		getMeshLayerTransformations(localTransf);


		//Treating rotations
		for(int j = 0; j < 3; ++j){
			if(lastLayerTransf[2][j] != localTransf[2][j]){
				lastLayerTransf[2][j] = localTransf[2][j];
				treatRotation(j, localTransf[2][j]);
				drawer->updateLocalRotation(center, sizes);
			}
			if(lastGlobalTransf[2][j] != globalTransf[2][j]){
				lastGlobalTransf[2][j] = globalTransf[2][j];
				center = drawer->updateGlobalRotation(j, globalTransf[2][j]);
			}
		}


		//Treating translations and scales.
		bool mudancaG = false;
		bool mudancaL = false;
		for(int i = 0; i < 2; ++i){
			for(int j = 0; j < 3; ++j){
				if(lastLayerTransf[i][j] != localTransf[i][j]){
					lastLayerTransf[i][j] = localTransf[i][j];
					mudancaL = true;
				}
				if(lastGlobalTransf[i][j] != globalTransf[i][j]){
					lastGlobalTransf[i][j] = globalTransf[i][j];
					mudancaG = true;
				}
			}
		}
		if(mudancaG){
			drawer->updateGlobalTranslation(lastGlobalTransf[0]);			
			drawer->updateGlobalScale(lastGlobalTransf[1]);
			for(int i = 0; i < 3; ++i){
				center[i] = (center[i] + globalTransf[0][i]) * globalTransf[1][i];
				sizes[i] = initialSizes[i] * globalTransf[1][i];
			}
		}
		if(mudancaL){
			for(int i = 0; i < 3; ++i){
				center[i] = (center[i] + localTransf[0][i]) * localTransf[1][i];
				sizes[i] = initialSizes[i] * localTransf[1][i];
			}
			drawer->updateLocalTranslation(center);
			drawer->updateLocalScale(center, sizes);
		}

		
		
	}
}
			

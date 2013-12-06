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

#include "cybViewMono.h"
#include <iostream>

CybViewMono::CybViewMono(CybMouse* mouse, CybAbstractDisplay* d) : Cyb3DWorld(mouse, false, d) 
{		
	Cyb3DWorld : viewNumber = 1; //sets the visualization type
	frustum = new CybPerpectiveFrustum(PI / 3.0, aspect, 1, 100);
	this->d->init();
}

void CybViewMono::display()
{
	CybParameters *cybCore = CybParameters::getInstance();
	double frustumAssimetry;
	static bool k = false;
	sVertex *v0, *v1, *v2;
	int l, index;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Setting up the Projection matrix.

	if(cybcore->modified == 1){
		frustumAssimetry = cybCore->StereoProjection(-6.4, 6.4, -6.4, 6.4, 6.0, -6.0, 180, 14.5, -cybCore->getStereoMagnitude(), cybCore->getParalaxe());
		cybCore->rightFrustumLeftEye = cybCore->widthProportion*(cybCore->dfXRange/2 - frustumAssimetry);
		cybCore->leftFrustumLeftEye = cybCore->widthProportion*(-cybCore->dfXRange/2 - frustumAssimetry);
		cybCore->modified = 0;
	}

	pStack.loadIdentity();
	frustum->setPerspectiveProjection(cybCore->leftFrustumLeftEye, cybCore->rightFrustumLeftEye, cybCore->widthProportion*cybCore->FrustumBase, cybCore->heightProportion*cybCore->FrustumTop, cybCore->dfNearClipDistance, cybCore->dfFarClipDistance);
	pStack.loadMatrix(frustum.getProjectionMatrix());

	frame.setForward(0.0, 0.0, cybCore->camPosZ);

	//Setting up the ModelView matrix.
	mvStack.loadIdentity();

	if(cybcore->getNumInterators() > 0){
		mvStack.pushMatrix();
		int numInterators = cybcore->getNumInterators();
		for (int i = 0; i < numInterators; i++) {
				CybInterator* interator = cybCore->getInterator(i);
				interator->drawInterator();
		}
		mvStack.popMatrix();
		mvStack.loadIdentity();
	}

	//aqui ficava a função lights

	for(int j = 0; j < freePos; ++j){

		mvStack.pushMatrix();
		if(cybCore->habLayer[j]){
			mfCellsInterator<cybSurfaceTriTraits> cellsInterator(cybCore->mesh[j]);
			//glColor4f(cybCore->getColor(j)[0], cybCore->getColor(j)[1], cybCore->getColor(j)[2], cybCore->getColor(j)[3]);
			CybThread::lock();
			mat4 t1, s1, t2, r1, r2, r3, t3;
			CybLineMatrix::createTranslationMatrix4D(t1, cybCore->xTrans + cybCore->layerTrans[j][0], cybCore->yTrans + cybCore->layerTrans[j][1], cybCore->zTrans + cybCore->layerTrans[j][2]);
			CybLineMatrix::createScaleMatrix4D(s1, cybCore->xScale * cybCore->layerSca[j][0], cybCore->yScale * cybCore->layerSca[j][1], cybCore->zScale * cybCore->layerSca[j][2]);
			CybLineMatrix::createTranslationMatrix4D(t2, cybCore->cX, cybCore->cY, cybCore->cZ);
			CybLineMatrix::createRotationMatrix4D(r1, cybCore->getXAngle() + cybCore->layerRot[j][0],1,0,0);
			CybLineMatrix::createRotationMatrix4D(r2, cybCore->getYAngle() + cybCore->layerRot[j][1],0,1,0);
			CybLineMatrix::createRotationMatrix4D(r3, cybCore->getZAngle() + cybCore->layerRot[j][2],0,0,1);
			CybLineMatrix::createTranslationMatrix4D(t3, -cybCore->cX, -cybCore->cY, -cybCore->cZ);
			mvStack.multMatrix(t1);
			mvStack.multMatrix(s1);
			mvStack.multMatrix(t2);
			mvStack.multMatrix(r1);
			mvStack.multMatrix(r2);
			mvStack.multMatrix(r3);
			mvStack.multMatrix(t3);

			for(int l = 0; l < 16; ++l) cybCore->transforMatrix[l] = mvStack.getMatrix()[l];
			CybThread::unlock();

			/*Setting uniform values and using the Shader*/
			d->setMatrices(mvStack.getMatrix(), pStack.getMatrix());
			d->uniforms();
			d->use();		

			if(cybCore->isDeformableLayer(j)){
				CybVector3D<float> aux;
				CybTriangleBatch model;
				model.begin(mesh[j]->getNumberOfVertices());
				for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator){
					v0 = cybCore->mesh[j]->getVertex(cellsIterator->getVertexId(0));
					v1 = cybCore->mesh[j]->getVertex(cellsIterator->getVertexId(1));
					v2 = cybCore->mesh[j]->getVertex(cellsIterator->getVertexId(2));
					vec3 verts[3] = {v0, v1, v2}
					vec3 norms[3];
					vec2 tc[3];
					aux = v0->getNormal();
					norms[0][0] = aux[0]; norms[0][1] = aux[1]; norms[0][2] = aux[2];
					aux = v1->getNormal();
					norms[1][0] = aux[0]; norms[1][1] = aux[1]; norms[1][2] = aux[2];
					aux = v2->getNormal();
					norms[2][0] = aux[0]; norms[2][1] = aux[1]; norms[2][2] = aux[2];
					model.addTriangle(verts, norms, tc);
				}
				model.end();
				model.draw();
			}
			else objects[j].draw();
		}
		mvStack.popMatrix();
	}

		if(!k){
			cybCore->transforChange = true;
			k = true;
		}

		mvStack.loadIdentity();
		CybBoxHolder::getInstance()->drawBoxes();
		mvStack.loadIdentity();
		glutSwapBuffers();
}

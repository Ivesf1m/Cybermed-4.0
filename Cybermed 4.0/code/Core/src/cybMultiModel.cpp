#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "cybParameters.h"
#include "cybMultiModel.h"

using namespace std;

CybMultiModel::CybMultiModel() {		
	firstTimeRight = firstTimeLeft = true;
}

CybMultiModel::~CybMultiModel() {
	meshes.clear();
}

bool CybMultiModel::addModel(string model) {
	meshes.push_back(new cybMesh<cybSurfaceTriTraits>);		
	int size = meshes.size();		
	bool teste = loadModel(meshes[size - 1], model);	
	if(!teste) {
		cout << "Error loading model: " << model << endl;
		meshes.pop_back();
	}
}

bool CybMultiModel::loadModel( mfReader<cybSurfaceTriTraits>::sMesh *pMesh, string model) {
	
	bool teste = false;	
	mfReader<cybSurfaceTriTraits> *in = mfReaderFactory<cybSurfaceTriTraits>::getReader(model.c_str());
		
	teste = in->read(pMesh, model.c_str());
	
	delete in;

	if (!teste) {
		return teste;
		
	}
	
	mfCellsIterator<cybSurfaceTriTraits> cellsIterator(pMesh);
	
	
	//Calcula a normal 
	for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator)
	{
	
	cellsIterator->updateVertexesNormalVector(pMesh);
	
	}
	
	
	return teste;
}

bool CybMultiModel::loadModels(string models[], int numModels) {	
	int size;
	bool teste;
	//for
	for (int i = 0; i < numModels; ++i) {	
		
		meshes.push_back(new  cybMesh<cybSurfaceTriTraits>);	
	
		size = meshes.size();		
		
		teste = loadModel(meshes[size - 1], models[i]);
		
		//desaloca e apaga o vetor
		if (!teste) {
			cout << "Error loading model: " << models[i] << endl;
			while (meshes.size() != 1) {
				delete meshes[0];
			}
			meshes.clear();
			return false;
		}	
	
	}//for
	return true;
}



void CybMultiModel::drawModel(int meshID) {
	CybParameters *cybCore = CybParameters::getInstance();
	if (firstTimeRight || firstTimeLeft) {		
		
			
		for (size_t i = 0; i < meshes.size(); ++i ) {			
			mfReader<cybSurfaceTriTraits>::sMesh *pMesh = meshes.at(i);	
			mfCellsIterator<cybSurfaceTriTraits> cellsIterator(pMesh);	
			mfReader<cybSurfaceTriTraits>::sVertex *v0, *v1, *v2;
			GLuint temp;		
			/*Desenha o Modelo*/
			
			
			temp = glGenLists(1);
			if ( cybCore->isDualWindowContextActive()) {
				if (glutGetWindow() == cybCore->getRightWindow()) { 
					list.push_back(temp);	
					firstTimeRight = false;						
				} 
				else if (glutGetWindow() == cybCore->getLeftWindow()){
					list2.push_back(temp);	
					firstTimeLeft = false;				
				}
			}
			else {
				list.push_back(temp);
				firstTimeRight = firstTimeLeft = false;
			}
			
			glNewList(temp, GL_COMPILE);
			for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator) {			

				v0 = pMesh->getVertex(cellsIterator->getVertexId(0));
				v1 = pMesh->getVertex(cellsIterator->getVertexId(1));
				v2 = pMesh->getVertex(cellsIterator->getVertexId(2));		
	
				glBegin(GL_TRIANGLES);
				glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
				glVertex3f(v0->getCoord(0) , v0->getCoord(1) , v0->getCoord(2));
	
				glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
				glVertex3f(v1->getCoord(0) , v1->getCoord(1) , v1->getCoord(2));

				glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
				glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
				glEnd();
			} //for cellsIterator
			glEndList();
		} //for i			
	} //if
	
	if (!(cybCore->isDualWindowContextActive())) {
		glCallList(list[meshID]);		
	}
	else {
		if (glutGetWindow() == cybCore->getRightWindow()) {
			glCallList(list[meshID]);	
		}
		else if (glutGetWindow() == cybCore->getLeftWindow()) {
			glCallList(list2[meshID]);
		}	
	}
}

mfReader<cybSurfaceTriTraits>::sMesh *CybMultiModel::getMesh(int meshID) {
	return meshes.at(meshID);
}

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

#ifndef CYBDATAOBTAINER_H
#define CYBDATAOBTAINER_H

#include "cybParameters.h"
#include "mf/mfReaderModel.h"

/**
@class		CybDataObtainer 
@file		cybParameters.h 
@short
	Class that syncronizes the OF data structure with the visualization class. This 
	class requires a model that satisfy Topological Manifold definitions to work 
	efficiently and without problems. Topological Manifold definitions are:
	- No vertices or cells with the same definitions
	- No cells intersections
	- No hanging nodes
	- Cells with the same orientation

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.5
@date		2009, November
*/

template <class _Traits> class CybDataObtainer
{
public:
	typedef mfCellsIterator<cybSurfaceTriTraits> sCIterator;
	typedef mfVerticesIterator<cybSurfaceTriTraits> sVIterator;

	typedef mfCellsIterator<cybTetraTraits> sTetraCIterator;
	typedef mfVerticesIterator<cybTetraTraits> sTetraVIterator;

	CybDataObtainer(int layerNumber, int numInterators);

	/**	Reads the colors of the graphical objects from its source file.
	@param char *fileName
	@param int id
	@return void
	*/
	void readColor(char *fileName, int id);

	/**	Reads the colors of the interaction objects from its source file.
	@param char *fileName
	@param int id
	@return void
	*/
	void readInteratorColor(char *fileName, int id);

	/**	Sets the layer name for the interactive menu.
	@param char layer_name
	@param int layer_id
	@return void
	*/
	void setLayerName(char *layer, int layerId);

	/**	Starts  loading the interaction object represented by a mesh.
	@param int numInterators
	@param ofMesh<cybTraits> _interatorMesh[]
	@return void
	*/
	void startInteratorParameters(int numInterators = 1);

	/**	Starts loading the parameters
	@param int number_of_layers
	@param ofMesh<cybTraits> mesh[]
	@param cybData *_cybCore
	@return void
	*/

	/**	Starts  loading the interaction object represented by a mesh.
	@param int idInterator
	@param ofMesh<cybTraits> _interatorMesh[]
	@return void
	 */
	void startInterator(int idInterator, int idMesh);

	void startParameters(int numLayers = 1);
	
private:
	int winX;		/**< Visualization window width. */
	int winY;		/**< Visualization window height. */
	bool tetraLoaded;
	CybVector4D<float> *color;	/**< Objects' color vector. */
	//CybVector3D<float>  *interColor;	/**< Interaction objects' color vector. */
	CybParameters *cybCore;				/**< Acess the system setting and a copy of data structure*/

	sMesh *mesh;	/**< Reference the visualization meshes */
	sTetraMesh *tetraMesh;

	//cybMesh<cybTraits> *interatorMesh; /**Reference the interators meshes*/
	
	/**	Loads the interaction objects meshes and stores them for visualization.
	@param Interator_id
	@return void
	*/
	void loadInteratorMesh(int idInterator, int idMesh);

	/**	Loads the layers and stores them for visualization.
	@param ofMesh<ofDefaultSurface> mesh
	@param int Layer_id
	@return void
	*/
	void loadMesh(sMesh *_mesh, int idLayer);

	/**	Loads the vizualization model that is identified by idLayer.
	@param ofMesh<ofDefaultSurface> mesh
	@param int Layer_id
	@return void
	*/
	void loadLayer(sMesh *_mesh, int idLayer);
	
	void loadLayer(sMesh *_mesh, sTetraMesh *_tetraMesh, int idLayer);
	
	public:

	/**	Load the model defined by the triangular mesh files.
	@param sMesh *_mesh
	@return void
	*/
	void loadModel(sMesh *_mesh);

	/**	Load the model defined by the tetrahedral mesh files.
	@param sMesh *_mesh
	@return void
	*/
	void loadModel(sTetraMesh *_mesh);

	/**	Loads interators models from VRML files.
	@param int layerID
	@param char fileName
	@return void
	*/
	void loadInteratorModel(int layerID, int meshId, char *fileName);
	
	void loadInteratorModel(int layerID, CybModel *model);

	void generateSurfaceMesh(int layerID);
};

/** Constructor */
template <class _Traits> CybDataObtainer<_Traits>::CybDataObtainer(int numLayer, int numInterators)
{
	cybCore = CybParameters::getInstance();

	cybCore->numLayer = numLayer;

	winX = 600;
	winY = 600;

	tetraLoaded = false;

	color = new CybVector4D<float>[numLayer];

	//interColor = new CybVector3D<float>[numInterators];
	
	mesh = new sMesh[numLayer];
	tetraMesh = new sTetraMesh[numLayer];
	//interatorMesh = new sMesh[10];
}

template <class _Traits> void CybDataObtainer<_Traits>::loadLayer(sMesh *_mesh, int idLayer)
{
	MF_ASSERT(_mesh);

	cybCore->mesh[idLayer] = _mesh;

	loadMesh(_mesh, idLayer);
}

template <class _Traits> void CybDataObtainer<_Traits>::loadLayer(sMesh *_mesh, sTetraMesh *_tetraMesh, int idLayer)
{
	MF_ASSERT(_mesh);

	cybCore->mesh[idLayer] = _mesh;
	cybCore->tetraMesh[idLayer] = _tetraMesh;

	loadMesh(_mesh, idLayer);
}

template <class _Traits> void CybDataObtainer<_Traits>::loadMesh(sMesh *_mesh, int idLayer)
{
	int l;
	sCIterator itc(cybCore->mesh[idLayer]);
	sVIterator itv(cybCore->mesh[idLayer]);

	cybCore->layerGeometricCenter[idLayer][0] = 0;
	cybCore->layerGeometricCenter[idLayer][1] = 0;
	cybCore->layerGeometricCenter[idLayer][2] = 0;

	cybCore->setSizeOfData(cybCore->mesh[idLayer]->getNumberOfCells(), cybCore->mesh[idLayer]->getNumberOfVertices(), idLayer);

	for(itv.initialize(); itv.notFinish(); ++itv)
	{
		cybCore->addVertex(idLayer, itv->getCoord(0), itv->getCoord(1), itv->getCoord(2));
		cybCore->layerGeometricCenter[idLayer][0] += itv->getCoord(0);
		cybCore->layerGeometricCenter[idLayer][1] += itv->getCoord(1);
		cybCore->layerGeometricCenter[idLayer][2] += itv->getCoord(2);
	}
	
	cybCore->layerGeometricCenter[idLayer][0] /= cybCore->nv[idLayer];
	cybCore->layerGeometricCenter[idLayer][1] /= cybCore->nv[idLayer];
	cybCore->layerGeometricCenter[idLayer][2] /= cybCore->nv[idLayer];
	
	for(itc.initialize(); itc.notFinish(); ++itc)
	{
		cybCore->addTriangle(idLayer, itc->getVertexId(0), itc->getVertexId(1), itc->getVertexId(2));

		itc->updateVertexesNormalVector(cybCore->mesh[idLayer]);
	}

	cybCore->setVertexNormalVector(_mesh, idLayer);

	for(l = 0, itv.initialize(); itv.notFinish(); l++, ++itv)
	{
		itv->setVNormalCoord(0, cybCore->vNormal[idLayer][l][0]);
		itv->setVNormalCoord(1, cybCore->vNormal[idLayer][l][1]);
		itv->setVNormalCoord(2, cybCore->vNormal[idLayer][l][2]);

		//cout << " " << &itv << " " << itv->getVNormalCoord(0) << " " << itv->getVNormalCoord(1) << " " << itv->getVNormalCoord(2) << endl;
	}
}

template <class _Traits> void CybDataObtainer<_Traits>::loadInteratorMesh(int idInterator, int idMesh)
{
	CybInterator* interator = cybCore->getInterator(idInterator);

	sCIterator cellsIterator(interator->getMesh(idMesh));

	for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator)
	{
		cellsIterator->updateVertexesNormalVector(interator->getMesh(idMesh));
	}

	//interator->setMesh(intMesh);
}

template <class _Traits> void CybDataObtainer<_Traits>::readColor(char *fileName, int id)
{	
	float rgba[4];
	mfReaderModel<cybSurfaceTriTraits> in;		
	in.readColor(rgba, fileName);
	for (int i = 0; i < 4; ++i) {
		color[id][i] = rgba[i];
	}	
}


/*Lembrar de colocar o leitor de cor dentro do leitor de malha*/
template <class _Traits> void CybDataObtainer<_Traits>::readInteratorColor(char *fileName, int id)
{
	float rgba[4];
	mfReaderModel<cybSurfaceTriTraits> in;		
	in.readColor(rgba, fileName);
	
	CybInterator* interator = cybCore->getInterator(id);
	interator->setColor(rgba[0], rgba[1], rgba[2], 1);	
}

template <class _Traits> void CybDataObtainer<_Traits>::setLayerName(char *layer, int layerId)
{

	if(layerId < cybCore->numLayer)
		cybCore->layerName[layerId] = layer;
	else
		cout << "\n Layer doesn't exist. \n";
}

template <class _Traits> void CybDataObtainer<_Traits>::startParameters(int numLayers)
{
	cout << "startParameters" << endl;
	int numTriangle = 0;
	cybCore->numLayer = numLayers;

	cybCore->startParameters();
	
	MF_ASSERT(winX > 0);
	MF_ASSERT(winY > 0);

	cybCore->mesh = new cybMesh<_Traits>*[numLayers];
	cybCore->tetraMesh = new sTetraMesh*[numLayers];

	cybCore->Resx = winX;
	cybCore->Resy = winY;

	for(int i=0; i < numLayers; i++)
	{
        	if(tetraLoaded)
			loadLayer(&mesh[i], &tetraMesh[i], i);
		else
			loadLayer(&mesh[i], i);
		
		//view.loadMesh();
		numTriangle += cybCore->mesh[i]->getNumberOfCells();
	}
	cybCore->cX = cybCore->xSum/(3*numTriangle);
	cybCore->cY = cybCore->ySum/(3*numTriangle);
	cybCore->cZ = cybCore->zSum/(3*numTriangle);

	cybCore->setColor(color);	
}

template <class _Traits> void CybDataObtainer<_Traits>::startInterator(int idInterator, int idMesh)
{	
	CybInterator* interator = cybCore->getInterator(idInterator);
	if (interator->getCybModel() != 0) { //CybModel doesn't need execute this function
		return;
	}
	MF_ASSERT(*(interator->getMesh(idMesh)));
	loadInteratorMesh(idInterator, idMesh);	
}


template <class _Traits> void CybDataObtainer<_Traits>::startInteratorParameters(int numInterators)
{
	int i;	
	cybCore->numInteractionObj = numInterators;

	for(i=0; i < numInterators; i++)
	{
		CybInterator* interator = cybCore->getInterator(i);
		MF_ASSERT(*(interator->getMesh()));
		loadInteratorMesh(i);
	}	
}

template <class _Traits> void CybDataObtainer<_Traits>::loadModel(sMesh *_mesh)
{	
	for(int i = 0; i < cybCore->numLayer; i++)
	{
		mesh[i] = _mesh[i];
	}	
}

template <class _Traits> void CybDataObtainer<_Traits>::loadModel(sTetraMesh *_mesh)
{
	tetraLoaded = true;

	for(int i =0; i < cybCore->numLayer; i++)
	{
		tetraMesh[i] = _mesh[i];
		cout << "[LoadModel] Generating Surface" << endl;
		generateSurfaceMesh(i);
	}
}

template <class _Traits> void CybDataObtainer<_Traits>::loadInteratorModel(int layerID, int meshId, char *fileName)
{
	CybInterator* interator = cybCore->getInterator(layerID);
	
	mfReaderModel<cybSurfaceTriTraits> in;		
	in.read(interator->getMesh(meshId), fileName);

	readInteratorColor(fileName, layerID);
}

template <class _Traits> void CybDataObtainer<_Traits>::loadInteratorModel(int layerID, CybModel *model)
{			
	CybInterator* interator = cybCore->getInterator(layerID);
	interator->setCybModel(model);
}

template <class _Traits> void CybDataObtainer<_Traits>::generateSurfaceMesh(int layerID)
{
	//sTetraVIterator vIt(tetraMesh[layerID]);
	mfCellsIterator<cybTetraTraits> cIt(&tetraMesh[layerID]);
	cybTetraTraits::sVertex *v, *v0, *v1, *v2;
	int vId[tetraMesh[layerID].getNumberOfVertices()];
	int vIdOfFace[3];
	int indexVector[3];
	//int vCounter = 0;
	int auxVId = 0;
	double coords[3];

	for(int i = 0; i < tetraMesh[layerID].getNumberOfVertices(); i++)
	{
		vId[i] = -1;
	}

	cout << "[GenerateSurface] Starting Generation " << endl;
	for(cIt.initialize(); cIt.notFinish(); ++cIt)
	{
		for(int i = 0; i < 4; i++)
		{
			if(cIt->getMateId(i) < 0)
			{
				//cout << " In after getMateId " << endl;
				cIt->getFaceVerticesIndex(i, indexVector);
				vIdOfFace[0] = cIt->getVertexId(indexVector[0]);
				vIdOfFace[1] = cIt->getVertexId(indexVector[1]);
				vIdOfFace[2] = cIt->getVertexId(indexVector[2]);
				//cout << vIdOfFace[0] << " " << vIdOfFace[1] << " " << vIdOfFace[2] << " " << endl;

				for(int j = 0; j<3; j++)
				{
					if(vId[vIdOfFace[j]] < 0)
					{
						v = tetraMesh[layerID].getVertex(vIdOfFace[j]);

						coords[0] = v->getCoord(0);
						coords[1] = v->getCoord(1);
						coords[2] = v->getCoord(2);
						mesh[layerID].addVertex(coords);

						vId[vIdOfFace[j]] = auxVId;
						auxVId++;
					}
				}

				vIdOfFace[0] = vId[vIdOfFace[0]];
				vIdOfFace[1] = vId[vIdOfFace[1]];
				vIdOfFace[2] = vId[vIdOfFace[2]];

				//cout << "adding c " << vIdOfFace[0] << " " << vIdOfFace[1] << " " << vIdOfFace[2] << endl;
				mesh[layerID].addCell(vIdOfFace);
				//cerr << "c added " << endl;
			}
		}
	}
}

#endif

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

#ifndef CYBMESH_H
#define CYBMESH_H

#include "mf/mfMacros.h"
#include "mf/mfVector.h"
#include "mf/mf.h"
#include <math.h>
#include "cybVector3D.h"

namespace mf
{

#define IDS typename cybMesh<_Traits>::ids
#define SVERTEX typename cybMesh<_Traits>::sVertex
#define SCELL typename cybMesh<_Traits>::sCell
#define SPACE typename cybMesh<_Traits>::space

/**
@class		cybMesh 
@file	 	cybMesh.h 
@short
	Cyb Mesh Class
	This class must be initialized with elements types (vertices and cells) and the operation class.
	Operation class depends of the vertices and cells dimensions.
	_Traits must have: space, ids, sVertex, sCell, sOper

@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@author ICMC-USP (http://www.icmc.usp.br), University of São Paulo
@version	1.0
@date		2007, July
*/

template <class _Traits> class cybMesh : public mfMesh<_Traits>
{
public:

	typedef typename _Traits::space space;
	typedef typename _Traits::ids ids;
	typedef typename _Traits::sVertex sVertex;
	typedef typename _Traits::sCell sCell;
	typedef typename _Traits::sOper sOper;

	/**	Constructor */
	cybMesh()
	{	
		maxIncidEdges = 0;
	}
	
	/**	Destructor */
	~cybMesh()
	{	}

	/** 
	 * Add a cell in mesh.
	 * 
	 * @param ids idvertices vector with vertices ids of the cell
	 * @return ids the cell id in mesh
	 */
	ids addCell(ids *idvertices MF_DMUTEXVD);

	/** 
	 * Update the veritices normal vector of one cell
	 * 
	 * @param int idCell the cell id
	 * @return void
	 */
	void updateCellVerticesNormal(int idCell);
	
	/** 
	 * Update the cell normal vector
	 * 
	 * @param int idCell the cell id
	 * @return void
	 */
	void updateCellNormalVector(int idCell);

	/** 
	 * Update the normal vector of one vertice
	 * 
	 * @param ids idVertex the vertex id
	 * @return void
	 */
	void updateVertexNormalVector(ids idVertex);

	/**
	 * Return the maximum number of incident edges in one vertex
	 *
	 * @param void
	 * @return int the mesh maximum number of incident edges in one vertex
	 */
	int getMaxIncidEdges();

	/**
	 * Return the lenght of one edge
	 *
	 * @param sCell *cell the cell which contains the edge
	 * @param int coordinate (0 for x, 1 for y and 2 for z)
	 * @param int edge one of the three edges
	 * @return int the maximum number of incident edges in one vertex
	 */
	space getEdgeLenght(sCell *cell, int coordinate, int edge);

private:
	int maxIncidEdges;		/**< the mesh maximum number of incident edges in one vertex */
};

template <class _Traits> int cybMesh<_Traits>::getMaxIncidEdges()
{
	return maxIncidEdges;
}

template <class _Traits> IDS cybMesh<_Traits>::addCell(ids *idvertices MF_DMUTEXV)
{
	int idCell, i;
	space aux1x, aux1y, aux1z, aux2x, aux2y, aux2z;
	space x1, x2, x3, y1, y2, y3, z1, z2, z3;
	float vNormal[3];
	float norma;

	//vNormal = new float[3];

	idCell = mfMesh<_Traits>::addCell(idvertices);

	/*MF_ASSERT(idvertices);

	MF_LOCK(cells_mutex);

	int idcell = cells.getFree();

	MF_UNLOCK(cells_mutex);

	oper.addCell(idcell, idvertices MF_MUTEXV);*/

	//return idcell;

	x1 = this->getVertex(idvertices[0])->getCoord(0);
	y1 = this->getVertex(idvertices[0])->getCoord(1);
	z1 = this->getVertex(idvertices[0])->getCoord(2);
	x2 = this->getVertex(idvertices[1])->getCoord(0);
	y2 = this->getVertex(idvertices[1])->getCoord(1);
	z2 = this->getVertex(idvertices[1])->getCoord(2);
	x3 = this->getVertex(idvertices[2])->getCoord(0);
	y3 = this->getVertex(idvertices[2])->getCoord(1);
	z3 = this->getVertex(idvertices[2])->getCoord(2);

	//cout << " v1 " << x1 << " " << y1 << " " << z1 << endl;
	//cout << " v2 " << x2 << " " << y2 << " " << z2 << endl;
	//cout << " v3 " << x3 << " " << y3 << " " << z3 << endl;

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
		for(i=0;i<3;i++) 
			vNormal[i] /= norma;
	else 
		for(i=0;i<3;i++) 
			vNormal[i] = 1;

	//cout << "Passed idCell: " << idCell << endl;

	this->getCell(idCell)->setNormal(vNormal);

	//cout << " Normal was set... " << endl;

	//delete vNormal;

	return idCell;
}

template <class _Traits> void cybMesh<_Traits>::updateCellNormalVector(int idCell)
{
	sCell *cell;
	int count, i;
	float normal[3], nCell[3];
	float norma;
	space aux1x, aux1y, aux1z, aux2x, aux2y, aux2z;
	space x1, x2, x3, y1, y2, y3, z1, z2, z3;

	cell = this->getCell(idCell);

	// cell norm update
	x1 = this->getVertex(cell->getVertexId(0))->getCoord(0);
	y1 = this->getVertex(cell->getVertexId(0))->getCoord(1);
	z1 = this->getVertex(cell->getVertexId(0))->getCoord(2);
	x2 = this->getVertex(cell->getVertexId(1))->getCoord(0);
	y2 = this->getVertex(cell->getVertexId(1))->getCoord(1);
	z2 = this->getVertex(cell->getVertexId(1))->getCoord(2);
	x3 = this->getVertex(cell->getVertexId(2))->getCoord(0);
	y3 = this->getVertex(cell->getVertexId(2))->getCoord(1);
	z3 = this->getVertex(cell->getVertexId(2))->getCoord(2);

	aux1x = x2 - x1;
	aux1y = y2 - y1;
	aux1z = z2 - z1;
	aux2x = x3 - x1;
	aux2y = y3 - y1;
	aux2z = z3 - z1;

	nCell[0] = (aux1y*aux2z) - (aux2y*aux1z);
	nCell[1] = (aux1z*aux2x) - (aux2z*aux1x);
	nCell[2] = (aux1x*aux2y) - (aux2x*aux1y);

	norma = sqrt(nCell[0]*nCell[0] + nCell[1]*nCell[1] + nCell[2]*nCell[2]);

	if(norma != 0) 
		for(i=0;i<3;i++) nCell[i] /= norma;
	else 
		for(i=0;i<3;i++) nCell[i] = 1;

	this->getCell(idCell)->setNormal(nCell);
}

template <class _Traits> void cybMesh<_Traits>::updateCellVerticesNormal(int idCell)
{
	sCell *cell;
	mfVertexStarIteratorTriSurf<_Traits> its(this);
	int count, i; 
	ids idVertex;
	float normal[3], *nCell, norma;
	space aux1x, aux1y, aux1z, aux2x, aux2y, aux2z;
	space x1, x2, x3, y1, y2, y3, z1, z2, z3;

	nCell = new float[3];

	cell = this->getCell(idCell);

	// cell norm update
	x1 = this->getVertex(cell->getVertexId(0))->getCoord(0);
	y1 = this->getVertex(cell->getVertexId(0))->getCoord(1);
	z1 = this->getVertex(cell->getVertexId(0))->getCoord(2);
	x2 = this->getVertex(cell->getVertexId(1))->getCoord(0);
	y2 = this->getVertex(cell->getVertexId(1))->getCoord(1);
	z2 = this->getVertex(cell->getVertexId(1))->getCoord(2);
	x3 = this->getVertex(cell->getVertexId(2))->getCoord(0);
	y3 = this->getVertex(cell->getVertexId(2))->getCoord(1);
	z3 = this->getVertex(cell->getVertexId(2))->getCoord(2);

	aux1x = x2 - x1;
	aux1y = y2 - y1;
	aux1z = z2 - z1;
	aux2x = x3 - x1;
	aux2y = y3 - y1;
	aux2z = z3 - z1;

	nCell[0] = (aux1y*aux2z) - (aux2y*aux1z);
	nCell[1] = (aux1z*aux2x) - (aux2z*aux1x);
	nCell[2] = (aux1x*aux2y) - (aux2x*aux1y);

	norma = sqrt(nCell[0]*nCell[0] + nCell[1]*nCell[1] + nCell[2]*nCell[2]);

	if(norma != 0) 
		for(i=0;i<3;i++) nCell[i] /= norma;
	else 
		for(i=0;i<3;i++) nCell[i] = 1;

	this->getCell(idCell)->setNormal(nCell);
	
	// vertex norm update
	for(i = 0; i<3; i++)
	{
		for(int j = 0; j<3; j++)
			normal[j] = 0;
		count = 0;
		
		idVertex = cell->getVertexId(i);
		
		for(its.initialize(idVertex);its.notFinish();++its)
		{
			nCell = its->getNormal();
			for(int k=0;k<3;k++) 
			{
				normal[k] += nCell[k];
				//cout <<  "triangle i " << n_cell[0] << endl;
			}
			count++;
		}
		
		for(int l=0; l<3 ;l++) 
			normal[l] /= count;
		
		
		this->getVertex(cell->getVertexId(i))->setNormal(normal);
	}
}

template <class _Traits> void cybMesh<_Traits>::updateVertexNormalVector(ids idVertex)
{
	mfVertexStarIteratorTriSurf<_Traits> its(this), auxits(this);
	CybVector3D<float> nCell;
	CybVector3D<float> normalV;
	CybVector3D<float> cell;
	int count = 0;
	int vIndex;
	ids vId;

	for(its.initialize(idVertex);its.notFinish();++its)
	{
		its->updateNormalVector(this);
		cell = its->getNormal();

			nCell[0] = cell[0];
			nCell[1] = cell[1];
			nCell[2] = cell[2]; 
		
			normalV += nCell;
		
		count++;
	}
	
	normalV /= count;
	
	this->getVertex(idVertex)->setNormal(normalV.toArray());	//sets the normal of vertex
}

template <class _Traits> SPACE cybMesh<_Traits>::getEdgeLenght(sCell *cell, int coordinate, int edge)
{
	if(edge == 0) return (this->getVertex((cell)->getVertexId(0))->getCoord(coordinate) - this->getVertex((cell)->getVertexId(1))->getCoord(coordinate));
	if(edge == 1) return (this->getVertex((cell)->getVertexId(0))->getCoord(coordinate) - this->getVertex((cell)->getVertexId(2))->getCoord(coordinate));
	if(edge == 2) return (this->getVertex((cell)->getVertexId(1))->getCoord(coordinate) - this->getVertex((cell)->getVertexId(2))->getCoord(coordinate));
	else return 0;	
}

#undef IDS
#undef SVERTEX
#undef SCELL
#undef SPACE

}

#endif

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

#ifndef CYBTRICELL_H
#define CYBTRICELL_H

#include "mf/mfMacros.h"
#include "mf/mfTriCell.h"
#include "mf/mfVertexStarIteratorTriSurf.h"
#include "cybTraits.h"
#include "mf/mfMesh.h"

namespace mf
{

#define SPACE typename cybTriCell<_Traits>::space
#define SVERTEX typename cybMesh<_Traits>::sVertex
#define IDS typename cybMesh<_Traits>::ids


/**
@class		cybTriCell 
@file		cybTriCell.h 
@short
	CyberMed Vertex Class

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.0
@date		2007, July
*/
template <class _Traits> class cybTriCell: public mfTriCell<_Traits>
{
public:
	typedef typename _Traits::space space;
	typedef typename _Traits::ids ids;
	typedef typename _Traits::sMesh sMesh;
	typedef typename _Traits::sVertex sVertex;

	/** Constructor */
	cybTriCell()
	{	}

	/** Destructor */
	virtual ~cybTriCell()
	{	}

	/**
	* Sets the value of the normal vector for one of its axis.
	* @param float *v_normal An vector refernce with the new coordenates.
	* @return void
	*/
	void setNormal(float *v_normal);

	/**
	* Returns the normal vector's value
	* @param void
	* @return CybVector3D<float> The normal.
	*/	
	CybVector3D<float> getNormal();

	/**	
	* Returns the normal vector's value from on of the axis.
	* @param int pos The coordenate of normal.
	* @return float The coordenate.
	*/
	float getCNormalCoord(int pos);
	
	/**	
	* Sets the value of the normal vector for one of its axis.
	* @param int pos The coordenate of normal.
	* @param float value The new coordenate value.
	* @return void
	*/
	void setCNormalCoord(int pos, float value);
	
	/**	
	* Updates the cell and vertex normal vector.
	* @param sMesh *mesh The mesh associated.
	* @return void
	*/
	void updateVertexesNormalVector(sMesh *mesh);
	
	/**	
	* Updates the cell and vertex normal vector.
	* @param sMesh *mesh The mesh associated.
	* @return void
	*/
	void updateNormalVector(sMesh *mesh);

private:
	CybVector3D<float> cNormal;	/**< Cell's normal vector */
};


template <class _Traits> float cybTriCell<_Traits>::getCNormalCoord(int pos)
{
	return cNormal[pos];
}

template <class _Traits> void cybTriCell<_Traits>::setCNormalCoord(int pos, float value)
{
	cNormal[pos] = value;
}

template <class _Traits> void cybTriCell<_Traits>::updateNormalVector(sMesh *mesh)
{
	float *nCell;
	float norma;
	float aux1x, aux1y, aux1z, aux2x, aux2y, aux2z;
	float x[3], y[3], z[3];

	sVertex *v[3];

	nCell = new float[3];

	v[0] = mesh->getVertex(this->getVertexId(0));
	v[1] = mesh->getVertex(this->getVertexId(1));
	v[2] = mesh->getVertex(this->getVertexId(2));

	for(int j=0; j <3; j++)
	{
		x[j] = v[j]->getCoord(0); //data is obtained from here because it's the objects original data.
		y[j] = v[j]->getCoord(1);
		z[j] = v[j]->getCoord(2);
	}

	aux1x = x[1] - x[0];
	aux1y = y[1] - y[0];
	aux1z = z[1] - z[0];
	aux2x = x[2] - x[0];
	aux2y = y[2] - y[0];
	aux2z = z[2] - z[0];

	nCell[0] = (aux1y*aux2z) - (aux2y*aux1z);
	nCell[1] = (aux1z*aux2x) - (aux2z*aux1x);
	nCell[2] = (aux1x*aux2y) - (aux2x*aux1y);

	norma = sqrt(nCell[0]*nCell[0] + nCell[1]*nCell[1] + nCell[2]*nCell[2]);

	if(norma)
	{
		cNormal[0] = nCell[0]/norma;
		cNormal[1] = nCell[1]/norma;
		cNormal[2] = nCell[2]/norma;
	}
	else
	{
		cNormal[0] = 1;
		cNormal[1] = 1;
		cNormal[2] = 1;
	}
}

template <class _Traits> void cybTriCell<_Traits>::updateVertexesNormalVector(sMesh *mesh)
{
	mfVertexStarIteratorTriSurf<_Traits> its(mesh);
	CybVector3D<float> nCell;
	float norma;
	float aux1x, aux1y, aux1z, aux2x, aux2y, aux2z;
	float vNormal[3];
	float x[3], y[3], z[3];
	int count;
	ids idVertex;
	sVertex *v[3];

	v[0] = mesh->getVertex(this->getVertexId(0));
	v[1] = mesh->getVertex(this->getVertexId(1));
	v[2] = mesh->getVertex(this->getVertexId(2));

	for(int j=0; j <3; j++)
	{
		x[j] = v[j]->getCoord(0); //data is obtained from here because it's the objects original data.
		y[j] = v[j]->getCoord(1);
		z[j] = v[j]->getCoord(2);
	}

	aux1x = x[1] - x[0];
	aux1y = y[1] - y[0];
	aux1z = z[1] - z[0];
	aux2x = x[2] - x[0];
	aux2y = y[2] - y[0];
	aux2z = z[2] - z[0];

	nCell[0] = (aux1y*aux2z) - (aux2y*aux1z);
	nCell[1] = (aux1z*aux2x) - (aux2z*aux1x);
	nCell[2] = (aux1x*aux2y) - (aux2x*aux1y);

	norma = sqrt(nCell[0]*nCell[0] + nCell[1]*nCell[1] + nCell[2]*nCell[2]);

	if(norma)
	{
		cNormal[0] = nCell[0]/norma;
		cNormal[1] = nCell[1]/norma;
		cNormal[2] = nCell[2]/norma;
	}
	else
	{
		cNormal[0] = 1;
		cNormal[1] = 1;
		cNormal[2] = 1;
	}

	// vertex norm update
	for(int i = 0; i<3; i++)
	{
		vNormal[0] = 0;
		vNormal[1] = 0;
		vNormal[2] = 0;
		count = 0;

		idVertex = this->getVertexId(i);

		for(its.initialize(idVertex);its.notFinish();++its)
		{
			nCell = its->getNormal();
			//cout << &its << " ";
			for(int k=0;k<3;k++)
			{
				vNormal[k] += nCell[k];
			}
			count++;
		}
		//cout << count << endl;

		for(int l=0; l<3 ;l++)
			vNormal[l] /= count;

		mesh->getVertex(this->getVertexId(i))->setNormal(vNormal);
	}
}

template <class _Traits> void cybTriCell<_Traits>::setNormal(float *v_normal)
{
	for(int i=0; i<3;i++) cNormal[i] = v_normal[i];
}

template <class _Traits> CybVector3D<float> cybTriCell<_Traits>::getNormal()
{
	return cNormal;
}

#undef SPACE
#undef IDS
#undef SVERTEX

}

#endif

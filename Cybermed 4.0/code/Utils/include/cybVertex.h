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

#ifndef CYBVERTEX_H
#define CYBVERTEX_H

#include "mf/mfMacros.h"
#include "mf/mfVertex3D.h"
#include "cybTraits.h"
#include "cybVector3D.h"

namespace mf
{

#define SPACE typename cybVertex<_Traits>::space
#define IDS typename cybMesh<_Traits>::ids

/**
@class		CybVertex 
@file		cybVertex.h 
@short
	CyberMed Vertex Class

@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.0 
@date		2007, July
*/
template <class _Traits> class cybVertex: public mfVertex3D<_Traits>
{
private:
	typedef typename _Traits::sMesh sMesh;
	typedef typename _Traits::ids ids;
	typedef typename _Traits::space space;

	CybVector3D<float> vNormal;	/**< Vertex's normal vector */

public:
		
	/** Constructor	 */
	cybVertex()
	{	}
	
	/** Destructor	 */
	~cybVertex()
	{	}

	/**	
	* Returns the normal vector's value from on of the axis.
	* @param int pos The axis of normal.
	* @return float The coordeante.
	*/
	inline float getVNormalCoord(int pos);

	/**	
	* Sets the value of the normal vector for one of its axis.
	*	
	* @param int pos The axis of normal.
	* @param float value The value of coordenate.
	* @return void
	*
	*/
	inline void setVNormalCoord(int pos, float value);

	/**	
	* Sets the value of the normal vector for one of its axis.
	* @param float *v_normal An array with the coordenates of normal.
	* @return void
	*/
	inline void setNormal(float *v_normal);
		
	/**	
	* Returns the normal vector's value
	* @param void
	* @return CybVector3D<float> the normal.
	*/
	inline CybVector3D<float> getNormal();
};

template <class _Traits> float cybVertex<_Traits>::getVNormalCoord(int pos)
{
	return vNormal[pos];
}

template <class _Traits> void cybVertex<_Traits>::setVNormalCoord(int pos, float value)
{
	vNormal[pos] = value;
}

template <class _Traits> void cybVertex<_Traits>::setNormal(float *v_normal)
{
	for(int i=0; i<3 ;i++) vNormal[i] = v_normal[i];
}

template <class _Traits> CybVector3D<float> cybVertex<_Traits>::getNormal()
{
	return vNormal;
}

#undef SPACE
#undef IDS

}

#endif

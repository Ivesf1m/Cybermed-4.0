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

#include "cybVector3D.h"

#ifndef _CYB_VERTEX4DH_H_
#define _CYB_VERTEX4DH_H_

/**
 * @class CybVector4DH
 * @file cybVector4DH.h 
 * @short This class implements a homogenius coordenate of a point and its operations.
 *
 * This class defines a homogenius coordenate of a point and the operations can that realized about its. 
  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */

template <class _TYPE = float> class CybVector4DH : public CybVector<CybVector4DH<_TYPE>, _TYPE>
{
	
public:

	_TYPE elements[4];	/**> Stores the elements of this class. */
	 
	/** 
	* Constructor
	* 
	* @param float x The x coordenate of the point.
	* @param float y The y coordenate of the point.
	* @param float z The z coordenate of the point.
	* @param float w The homogenius coordenate point.
	* 
	*/
	CybVector4DH<_TYPE>(_TYPE x = 0, _TYPE y = 0, _TYPE z = 0, _TYPE w = 1)	//default of w is 1
	{
		this->elements[0] = x;
		this->elements[1] = y;
		this->elements[2] = z;
		this->elements[3] = w;

		this->ELEMENTS = this->elements;
	}

	/** Destructor */
	~CybVector4DH<_TYPE>(){}
	
	/**
	 * This method converts an 4D vector (homogenius coordenate) in an 3D vector.
	 * 
	 * @param void.
	 * @return CybVector3D The correspondent CybVector3D.
	 * 
	 */	
	CybVector3D<_TYPE> toVector3D()
	{	
		CybVector3D<_TYPE> temp(this->elements[0]/this->elements[3],this->elements[1]/this->elements[3],this->elements[2]/this->elements[3]);
		
		return temp;
	}

	/**
	 * This operator returns the dot product between this
	 * vector and an other (in parameter).
	 * 
	 * @param CybVector4DH<_TYPE> vector The vector operand in dot product operation.
	 * @return _TYPE The dot product.
	 * 
	 */	
	 _TYPE operator^(CybVector4DH<_TYPE> vector)
	 {
	 	CybVector3D<_TYPE> a = this->toVector3D();			// converts to 3D vector
	 	CybVector3D<_TYPE> b = vector.toVector3D();
	 	
	 	return a^b;
	 }
	
	/**
	 * This operator does this CybVector4DH<_TYPE> equal the other vector in parameter.
	 * 
	 * @param CybVector4DH<_TYPE> vector The vector operand in dot product operation.
	 * @return CybVector4DH<_TYPE> The associated object.
	 * 
	 */		
	CybVector4DH<_TYPE> operator=(CybVector4DH<_TYPE> vector)
	{
		this->elements[0] = vector[0];
		this->elements[1] = vector[1];
		this->elements[2] = vector[2];
		this->elements[3] = vector[3];
		
		return *this;
	}

	/**
	 * This operator returns if two CybVector4D<_TYPE>s are equals.
	 * 
	 * @param CybVector4D<_TYPE> vector A CybVector4D<_TYPE> compared with this.
	 * @return bool If the CybVector4D<_TYPE>s are equals.
	 * 
	 */	
	 bool operator==(CybVector4DH<_TYPE> vector)
	 {
	 	return ((this->elements[0] == vector[0]) && (this->elements[1] == vector[1]) && (this->elements[2] == vector[2]) && (this->elements[3] == vector[3]));
	 }
	 
	 /**
	 * This operator returns the sum of two CybVector4DH<_TYPE>s.
	 * 
	 * @param CybVector4DH<_TYPE> vector A CybVector4DH<_TYPE> that it wants the sum with this.
	 * @return CybVector4DH<_TYPE> A CybVector4DH<_TYPE> that will be the sum of parameter with this.
	 * 
	 */			
	 CybVector4DH<_TYPE> operator+(CybVector4DH<_TYPE> vector)
	 {
	 	CybVector3D<_TYPE> a = this->toVector3D();
	 	CybVector3D<_TYPE> b = vector.toVector3D();
	 	CybVector4DH<_TYPE> temp(this->elements[0]+vector[0], this->elements[1]+vector[1], this->elements[2]+vector[2], 1); 	
	 	return temp;	 	
	 }	
	 
	/**
	 * This operator returns the difference of two CybVector4DH<_TYPE>s.
	 * 
	 * @param CybVector4DH<_TYPE> vector A CybVector4DH<_TYPE> that it wants the difference of this.
	 * @return CybVector4DH<_TYPE> A CybVector4DH<_TYPE> that will be the difference of this with the parameter.
	 * 
	 */				
	 CybVector4DH<_TYPE> operator-(CybVector4DH<_TYPE> vector)
	 {
	 	CybVector3D<_TYPE> a = this->toVector3D();
	 	CybVector3D<_TYPE> b = vector.toVector3D();
	 	CybVector4DH<_TYPE> temp(this->elements[0]-vector[0], this->elements[1]-vector[1], this->elements[2]-vector[2],1);
	 	
	 	return temp;	 	
	 }

	 /**
	  * This operator multiplyes this CybVector4DH<_TYPE> with the _TYPE parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return CybVector4DH<_TYPE><_TYPE> The CybVector4DH<_TYPE><_TYPE> resultant. 
	  * 
	  */	
	 CybVector4DH<_TYPE> operator*(_TYPE k)
	 {
	 	CybVector4DH<_TYPE> temp(this->elements[0]*k, this->elements[1]*k, this->elements[2]*k, this->elements[3]*k);
	 	
	 	return temp;	 	
	 } 

	 /**
	  * This operator divides this by the _TYPE parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return CybVector4D<_TYPE> The CybVector4D<_TYPE> resultant. 
	  * 
	  */	
	 CybVector4DH<_TYPE> operator/(_TYPE k)
	 {
	 	CybVector4DH<_TYPE> temp(this->elements[0]/k, this->elements[1]/k, this->elements[2]/k, this->elements[3]/k);
	 	
	 	return temp;	 	
	 }	 

	 /** 
	 * This operator sets the coordenates (x, y) of the encapsuladed point.
	 * 
	 * @param _TYPE x The x coordenate of the point encapsuladed.
	 * @param _TYPE y The y coordenate of the point encapsuladed.
	 * @param _TYPE z The z coordenate of the point encapsuladed.
	 * @param _TYPE w The w coordenate of the point encapsuladed.
	 * @return CybVector4D<_TYPE> The criated object.
	 * 
	 */
	 CybVector4DH<_TYPE> operator()(_TYPE x,_TYPE y,_TYPE z, _TYPE w)
	 {
	 	this->elements[0] = x;
	 	this->elements[1] = y;	
		this->elements[2] = z;
		this->elements[2] = z;
	 	
	 	return *this; 	
	 }	

	/**
	* This method shows the vector
	*
	* @param void.
	* @return void.
	*
	*/	 
	 void show()
	 {
	 	cout << "(" << this->elements[0] << ", " << this->elements[1] << ", " << this->elements[2] << ", " << this->elements[3] << ")" << endl;
	 }

};

#endif /*_CYB_VERTEX4DH_H_*/

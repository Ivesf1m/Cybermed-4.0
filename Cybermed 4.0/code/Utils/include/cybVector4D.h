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

#include "cybVector.h"

#ifndef _CYB_VECTOR4D_H_
#define _CYB_VECTOR4D_H_

/**
 * @class CybVector4D 
 * @file cybVector4D.h 
 * @short This class implements an 4D point and its operations.
 *
 * This class defines a 4D point and the operations can that realized about its. 
  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */
 
template <class _TYPE = float> class CybVector4D : public CybVector<CybVector4D<_TYPE>,_TYPE>
{
	
public:

	_TYPE elements[4];	/**< Stores the elements of this class. */
	
	/** Constructor 
	 * 
	 * @param x The x axis coordenate.
	 * @param y The y axis coordenate.
	 * @param z The z axis coordenate.
	 * @param w The w axis coordenate.
	 * 
	 */
	CybVector4D<_TYPE>(_TYPE x = 0, _TYPE y = 0, _TYPE z = 0, _TYPE w = 0)
	{
		this->elements[0] = x;
		this->elements[1] = y;
		this->elements[2] = z;
		this->elements[3] = w;

		this->ELEMENTS = this->elements;
	}
	
	/** Destructor. */
	~CybVector4D<_TYPE>() { };

	/**
	 * This operator returns the dot product between this
	 * vector and an other (in parameter).
	 * 
	 * @param CybVector4D<_TYPE> vector The vector operand in dot product operation.
	 * @return float The dot product.
	 * 
	 */	
	 inline _TYPE operator^(CybVector4D<_TYPE> vector)
	 {
	 	return (this->elements[0]*vector[0] + this->elements[1]*vector[1] + this->elements[2]*vector[2] + this->elements[3]*vector[3]);	
	 }
	
	/**
	 * This operator does this _VECTOR_TYPE equal the other
	 * vector in parameter.
	 * 
	 * @param _CybVector4D<_TYPE> The vector operand in dot product operation.
	 * @return _VECTOR_TYPE This vector.
	 * 
	 */		
	CybVector4D<_TYPE> operator=(CybVector4D<_TYPE> vector)
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
	 bool operator==(CybVector4D<_TYPE> vector)
	 {
	 	return ((this->elements[0] == vector[0]) && (this->elements[1] == vector[1]) && (this->elements[2] == vector[2]) && (this->elements[3] == vector[3]));
	 }
	 
	 /**
	 * This operator returns the sum of two CybVector4D<_TYPE>s.
	 * 
	 * @param CybVector4D<_TYPE> vector A CybVector4D<_TYPE> that it wants the sum with this.
	 * @return CybVector4D<_TYPE> A CybVector4D<_TYPE> that will be the sum of parameter with this.
	 * 
	 */			
	 CybVector4D<_TYPE> operator+(CybVector4D<_TYPE> vector)
	 {
	 	CybVector4D<_TYPE> temp(this->elements[0]+vector[0], this->elements[1]+vector[1], this->elements[2]+vector[2], this->elements[3]+vector[3]);
	 	
	 	return temp;	 	
	 }
	 
	/**
	 * This operator returns the difference of two CybVector4D<_TYPE>s.
	 * 
	 * @param CybVector4D<_TYPE> vector A CybVector4D<_TYPE> that it wants the difference of this.
	 * @return CybVector4D<_TYPE> A CybVector4D<_TYPE> that will be the difference of this with the parameter.
	 * 
	 */				
	 CybVector4D<_TYPE> operator-(CybVector4D<_TYPE> vector)
	 {
	 	CybVector4D<_TYPE> temp(this->elements[0]-vector[0], this->elements[1]-vector[1], this->elements[2]-vector[2], this->elements[3]-vector[3]);
	 	
	 	return temp;	 	
	 }
	 
	 /**
	  * This operator multiplyes this CybVector4D<_TYPE> with the _TYPE parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return CybVector4D<_TYPE> The CybVector4D<_TYPE> resultant. 
	  * 
	  */	
	 CybVector4D<_TYPE> operator*(_TYPE k)
	 {
	 	CybVector4D<_TYPE> temp(this->elements[0]*k, this->elements[1]*k, this->elements[2]*k, this->elements[3]*k);
	 	
	 	return temp;	 	
	 } 
		 
	  /**
	  * This operator divides this by the _TYPE parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return CybVector4D<_TYPE> The CybVector4D<_TYPE> resultant. 
	  * 
	  */	
	 CybVector4D<_TYPE> operator/(_TYPE k)
	 {
	 	CybVector4D<_TYPE> temp(this->elements[0]/k, this->elements[1]/k, this->elements[2]/k, this->elements[3]/k);
	 	
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
	 CybVector4D<_TYPE> operator()(_TYPE x,_TYPE y,_TYPE z, _TYPE w)
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
	 	cout << "(" << this->element[0] << ", " << this->element[1] << ", " << this->element[2] << ", " << this->element[3] << ")" << endl;
	 }
};


#endif /*_CYB_VECTOR4D_H_*/

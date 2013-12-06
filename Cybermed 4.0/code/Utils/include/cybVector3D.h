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

#ifndef _CYB_VECTOR3D_H_
#define _CYB_VECTOR3D_H_

/**
 * @class CybVector3D 
 * @file cybVector3D.h 
 * @short This class implements an 3D point and its operations.
 *
 * This class defines a 3D point and the operations can that realized about its. 
  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.01
 * @date 2007, July
 * 
 */
 
template <class _TYPE = float> class CybVector3D : public CybVector<CybVector3D<_TYPE>,_TYPE>
{
	
public:

	_TYPE elements[3];	/**< Stores the elements of this class. */
	
	/** Constructor 
	 * 
	 * @param x The x axis coordenate.
	 * @param y The y axis coordenate.
	 * 
	 */
	CybVector3D<_TYPE>(_TYPE x = 0, _TYPE y = 0, _TYPE z = 0)
	{
		this->elements[0] = x;
		this->elements[1] = y;
		this->elements[2] = z;

		this->ELEMENTS = this->elements;
	}
	
	/** Destructor. */
	~CybVector3D<_TYPE>() { };

	/**
	 * This operator returns the dot product between this
	 * vector and an other (in parameter).
	 * 
	 * @param CybVector3D<_TYPE> vector The vector operand in dot product operation.
	 * @return float The dot product.
	 * 
	 */	
	 inline _TYPE operator^(CybVector3D<_TYPE> vector)
	 {
	 	return (this->elements[0]*vector[0] + this->elements[1]*vector[1] + this->elements[2]*vector[2]);	
	 }
	
	/**
	 * This operator does this _VECTOR_TYPE equal the other
	 * vector in parameter.
	 * 
	 * @param _CybVector3D<_TYPE> The vector operand in dot product operation.
	 * @return _VECTOR_TYPE This vector.
	 * 
	 */		
	CybVector3D<_TYPE> operator=(CybVector3D<_TYPE> vector)
	{
		this->elements[0] = vector[0];
		this->elements[1] = vector[1];
		this->elements[2] = vector[2];
		
		return *this;
	}		
	
	/**
	 * This operator returns if two CybVector3D<_TYPE>s are equals.
	 * 
	 * @param CybVector3D<_TYPE> vector A CybVector3D<_TYPE> compared with this.
	 * @return bool If the CybVector3D<_TYPE>s are equals.
	 * 
	 */	
	 bool operator==(CybVector3D<_TYPE> vector)
	 {
	 	return ((this->elements[0] == vector[0]) && (this->elements[1] == vector[1]) && (this->elements[2] == vector[2]));
	 }
	 
	 /**
	 * This operator returns the sum of two CybVector3D<_TYPE>s.
	 * 
	 * @param CybVector3D<_TYPE> vector A CybVector3D<_TYPE> that it wants the sum with this.
	 * @return CybVector3D<_TYPE> A CybVector3D<_TYPE> that will be the sum of parameter with this.
	 * 
	 */			
	 CybVector3D<_TYPE> operator+(CybVector3D<_TYPE> vector)
	 {
	 	CybVector3D<_TYPE> temp(this->elements[0]+vector[0], this->elements[1]+vector[1], this->elements[2]+vector[2]);
	 	
	 	return temp;	 	
	 }
	 
	/**
	 * This operator returns the difference of two CybVector3D<_TYPE>s.
	 * 
	 * @param CybVector3D<_TYPE> vector A CybVector3D<_TYPE> that it wants the difference of this.
	 * @return CybVector3D<_TYPE> A CybVector3D<_TYPE> that will be the difference of this with the parameter.
	 * 
	 */				
	 CybVector3D<_TYPE> operator-(CybVector3D<_TYPE> vector)
	 {
	 	CybVector3D<_TYPE> temp(this->elements[0]-vector[0], this->elements[1]-vector[1], this->elements[2]-vector[2]);
	 	
	 	return temp;	 	
	 }

	/**
	* This operator calculates the cross product between vector and this.
	*
	* @param CybVector3D<_TYPE> vector A CybVector3D<_TYPE> that will be crossed with this.
	* @return CybVector3D<_TYPE> The cross product.
	*
	*/
	 CybVector3D<_TYPE> operator*(CybVector3D<_TYPE> vector)
	 {
	 	CybVector3D<_TYPE> temp;

		temp[0] = this->elements[1]*vector[2] - this->elements[2]*vector[1];
		temp[1] = this->elements[2]*vector[0] - this->elements[0]*vector[2];
		temp[2] = this->elements[0]*vector[1] - this->elements[1]*vector[0];

		return temp;
	 }
	 
	 /**
	  * This operator multiplyes this CybVector3D<_TYPE> with the _TYPE parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return CybVector3D<_TYPE> The CybVector3D<_TYPE> resultant. 
	  * 
	  */	
	 CybVector3D<_TYPE> operator*(_TYPE k)
	 {
	 	CybVector3D<_TYPE> temp(this->elements[0]*k, this->elements[1]*k, this->elements[2]*k);
	 	
	 	return temp;	 	
	 } 
		 
	  /**
	  * This operator divides this by the _TYPE parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return CybVector3D<_TYPE> The CybVector3D<_TYPE> resultant. 
	  * 
	  */	
	 CybVector3D<_TYPE> operator/(_TYPE k)
	 {
	 	CybVector3D<_TYPE> temp(this->elements[0]/k, this->elements[1]/k, this->elements[2]/k);
	 	
	 	return temp;	 	
	 }	 

	 /** 
	 * This operator sets the coordenates (x, y) of the encapsuladed point.
	 * 
	 * @param _TYPE x The x coordenate of the point encapsuladed.
	 * @param _TYPE y The y coordenate of the point encapsuladed.
	 * @param _TYPE z The z coordenate of the point encapsuladed.
	 * @return CybVector3D<_TYPE> The criated object.
	 * 
	 */
	 CybVector3D<_TYPE> operator()(_TYPE x,_TYPE y,_TYPE z)
	 {
	 	this->elements[0] = x;
	 	this->elements[1] = y;	
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
	 	cout << "(" << this->elements[0] << ", " << this->elements[1] << ", " << this->elements[2] << ")" << endl;
	 }

	 /**
	 * This method calculates the norm of this vector.
	 *
	 * @param void
	 * @return double: the norm of this vector.
  	 */
	 double getNorm()
	 {
		double norma = sqrt(elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2]);
		return norma;
	 }

	 /**
	 * This method normalizes this vector.
	 *
	 * @param void
	 * @return void
	 */
	 void normalize()
	 {
		double norma = getNorm();
		if(norma == 0) return;
		elements[0] /= norma;
		elements[1] /= norma;
		elements[2] /= norma;
	 }

	/**
	* This method creates a new vector containing the maximum elements of this vector and the parameter vector.
	*
	* @param CybVector3D<_TYPE>& in: the parameter vector.
	* @return CybVector3D<_TYPE>&: the new vector containing the maximum values.
	*/
	CybVector3D<_TYPE>& max(CybVector3D<_TYPE>& in)
	{
		CybVector3D<_TYPE>* novo = new CybVector3D<_TYPE>(std::max(elements[0], in.elements[0]), 						   std::max(elements[1],in.elements[1]), std::max(elements[2],in.elements[2]));
		return *novo;
	}
	
	/**
	* This method creates a new vector containing the minimum elements of this vector and the parameter vector.
	*
	* @param CybVector3D<_TYPE>& in: the parameter vector.
	* @return CybVector3D<_TYPE>&: the new vector containing the minimum values.
	*/
	CybVector3D<_TYPE>& min(CybVector3D<_TYPE>& in)
	{
		CybVector3D<_TYPE>* novo = new CybVector3D<_TYPE>(std::min(elements[0], in.elements[0]), 						   std::min(elements[1],in.elements[1]), std::min(elements[2],in.elements[2]));
		return *novo;
	} 
};


#endif /*_CYB_VECTOR3D_H_*/

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

#ifndef _CYB_VECTOR2D_H_
#define _CYB_VECTOR2D_H_

/**
 * @class CybVector2D 
 * @file cybVector2D.h 
 * @short This class implements an 2D point and its operations.
 *
 * This class defines a 2D point and the operations can that realized about its.
 * The template _TYPE indicates the type stored in this vector.
 * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */
 
template <class _TYPE = float> class CybVector2D : public CybVector<CybVector2D<_TYPE>,_TYPE>
{
	
public:
	_TYPE elements[2];	/**< Stores the elements of this class. */

	/** Constructor 
	 * 
	 * @param x The x axis coordenate.
	 * @param y The y axis coordenate.
	 * 
	 */
	CybVector2D(_TYPE x = 0, _TYPE y = 0)
	{
		this->elements[0] = x;
		this->elements[1] = y;
		this->ELEMENTS = this->elements;
	}
	
	/** Destructor. */
	~CybVector2D<_TYPE>() 
	{ 
	};

	/**
	 * This operator returns the dot product between this
	 * vector and an other (in parameter).
	 * 
	 * @param CybVector2D<_TYPE> vector The vector operand in dot product operation.
	 * @return float The dot product.
	 * 
	 */	
	 _TYPE operator^(CybVector2D<_TYPE> vector)
	 {
	 	return (this->elements[0]*vector[0] + this->elements[1]*vector[1]);	
	 }
	
	/**
	 * This operator does this _VECTOR_TYPE equal the other
	 * vector in parameter.
	 * 
	 * @param _CybVector2D<_TYPE> The vector operand in dot product operation.
	 * @return _VECTOR_TYPE This vector.
	 * 
	 */		
	CybVector2D<_TYPE> operator=(CybVector2D<_TYPE> vector)
	{
		this->elements[0] = vector[0];
		this->elements[1] = vector[1];
		
		return *this;
	}		
	
	/**
	 * This operator returns if two CybVector2D<_TYPE>s are equals.
	 * 
	 * @param CybVector2D<_TYPE> vector A CybVector2D<_TYPE> compared with this.
	 * @return bool If the CybVector2D<_TYPE>s are equals.
	 * 
	 */	
	 bool operator==(CybVector2D<_TYPE> vector)
	 {
	 	return ((this->elements[0] == vector[0]) && (this->elements[1] == vector[1]));		
	 }
	 
	 /**
	 * This operator returns the sum of two CybVector2D<_TYPE>s.
	 * 
	 * @param CybVector2D<_TYPE> vector A CybVector2D<_TYPE> that it wants the sum with this.
	 * @return CybVector2D<_TYPE> A CybVector2D<_TYPE> that will be the sum of parameter with this.
	 * 
	 */			
	 CybVector2D<_TYPE> operator+(CybVector2D<_TYPE> vector)
	 {
	 	CybVector2D<_TYPE> temp(this->elements[0]+vector[0], this->elements[1]+vector[1]);
	 	
	 	return temp;	
	 }
	 
	/**
	 * This operator returns the difference of two CybVector2D<_TYPE>s.
	 * 
	 * @param CybVector2D<_TYPE> vector A CybVector2D<_TYPE> that it wants the difference of this.
	 * @return CybVector2D<_TYPE> A CybVector2D<_TYPE> that will be the difference of this with the parameter.
	 * 
	 */				
	 CybVector2D<_TYPE> operator-(CybVector2D<_TYPE> vector)
	 {
	 	CybVector2D<_TYPE> temp(this->elements[0]-vector[0], this->elements[1]-vector[1]);
	 	
	 	return temp;	 	
	 }
	 
	 /**
	  * This operator multiplyes this CybVector2D<_TYPE> with the _TYPE parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return CybVector2D<_TYPE> The CybVector2D<_TYPE> resultant. 
	  * 
	  */	
	 CybVector2D<_TYPE> operator*(_TYPE k)
	 {
	 	CybVector2D<_TYPE> temp(this->elements[0]*k, this->elements[1]*k);
	 	
	 	return temp;	 	
	 } 
		 
	  /**
	  * This operator divides this by the _TYPE parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return CybVector2D<_TYPE> The CybVector2D<_TYPE> resultant. 
	  * 
	  */	
	 CybVector2D<_TYPE> operator/(_TYPE k)
	 {
	 	CybVector2D<_TYPE> temp(this->elements[0]/k,this->elements[1]/k);
	 	
	 	return temp;	 	
	 }	 

	 /** 
	 * This operator sets the coordenates (x, y) of the encapsuladed point.
	 * 
	 * @param _TYPE x The x coordenate of the point encapsuladed.
	 * @param _TYPE y The y coordenate of the point encapsuladed.
	 * @return CybVector2D<_TYPE> The criated object.
	 * 
	 */
	 CybVector2D<_TYPE> operator()(_TYPE x,_TYPE y )
	 {
	 	this->elements[0] = x;
	 	this->elements[1] = y;	
	 	
	 	return *this; 	
	 }

	/**
	* This method shows the vector.
	*
	* @param void.
	* @return void.
	*
	*/	 
	 void show()
	 {
	 	cout << "(" << this->elements[0] << ", " << this->elements[1] << ")" << endl;
	 }
};


#endif /*_CYB_VECTOR2D_H_*/

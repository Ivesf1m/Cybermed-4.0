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

#include <iostream>
#include <cmath>

using namespace std;

#ifndef _CYB_VECTOR_H_
#define _CYB_VECTOR_H_

/**
 * @class CybVertex 
 * @file cybVertex.h 
 * @short INTERFACE of a type used in CyberMed classes.
 *
 * This class no implements methods. It indicates only
 * the form that all the methods that must will be
 * implemented in new type specified.
 * The template _VECTOR_TYPE indicates the son of this class.
 * The template _TYPE indicates the types storeds in son class.
 * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 *
 */

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

template <class _VECTOR_TYPE, class _TYPE> class CybVector
{

protected:
	_TYPE* ELEMENTS; 	/**< Stores the elements defineds in son class. */
	
public:	

	/** Constructor	*/
	CybVector()
	{	}
	
	/** Destructor	*/
	~CybVector()
	{	}
		
	/**
	 * This operator does this _VECTOR_TYPE equal the other
	 * vector in parameter.
	 * 
	 * @param _VECTOR_TYPE The vector operand in dot product operation.
	 * @return _VECTOR_TYPE The this vector.
	 * 
	 */		
	virtual _VECTOR_TYPE operator=(_VECTOR_TYPE) = 0;
	
	/**
	 * This operator returns if two _VECTOR_TYPEs are equals.
	 * 
	 * @param _VECTOR_TYPE A _VECTOR_TYPE compared with this.
	 * @return bool If the _VECTOR_TYPEs are equals.
	 * 
	 */	
	 virtual bool operator==(_VECTOR_TYPE) = 0;
	 
	 /**
	 * This operator returns if two _VECTOR_TYPEs are not equals.
	 * 
	 * @param _VECTOR_TYPE vector A _VECTOR_TYPE compared with this.
	 * @return bool If the _VECTOR_TYPEs are not equals.
	 * 
	 */		
	 bool operator!=(_VECTOR_TYPE vector)
	 {
	 	return !((*this) == vector);
	 }
	 
	 /**
	 * This operator returns the sum of two _VECTOR_TYPEs.
	 * 
	 * @param _VECTOR_TYPE A _VECTOR_TYPE that it wants the sum with this.
	 * @return _VECTOR_TYPE A _VECTOR_TYPE that will be the sum of parameter with this.
	 * 
	 */			
	 virtual _VECTOR_TYPE operator+(_VECTOR_TYPE) = 0;
	 
	 /**
	 * This operator returns the sum of two _VECTOR_TYPEs an modifies this _VECTOR_TYPE.
	 * 
	 * @param _VECTOR_TYPE A _VECTOR_TYPE that will be added with this.
	 * @return _VECTOR_TYPE A _VECTOR_TYPE that will be the sum of parameter with this.
	 * 
	 */			
	 _VECTOR_TYPE operator+=(_VECTOR_TYPE vector)
	 {
	 	return ((*this) = (*this) + vector);
	 }
	 
	/**
	 * This operator returns the difference of two _VECTOR_TYPEs.
	 * 
	 * @param _VECTOR_TYPE A _VECTOR_TYPE that it wants the difference of this.
	 * @return _VECTOR_TYPE A _VECTOR_TYPE that will be the difference of this with the parameter.
	 * 
	 */				
	 virtual _VECTOR_TYPE operator-(_VECTOR_TYPE) = 0;
	 
	/**
	 * This operator returns the diference of two _VECTOR_TYPEs an modifies this _VECTOR_TYPE to that value.
	 * 
	 * @param _VECTOR_TYPE A _VECTOR_TYPE that will minued with this.
	 * @return _VECTOR_TYPE A _VECTOR_TYPE that will be the minued of this with parameter.
	 * 
	 */		
	 _VECTOR_TYPE operator-=(_VECTOR_TYPE vector)
	 {
	 	return ((*this) = (*this) - vector);
	 }
	 
	  /**
	  * This operator multiplyes _VECTOR_TYPE in parameter with the float parameter.
	  * 
	  * @param _TYPE k The real constant associated with this operation.
	  * @return _VECTOR_TYPE The _VECTOR_TYPE resultant. 
	  * 
	  */		
	 virtual _VECTOR_TYPE operator*(_TYPE k) = 0;
	 
	 /**
	  * This operator multiplyes _VECTOR_TYPE in parameter with the float parameter.
	  * 
	  * @param _VECTOR_TYPE vector The _VECTOR_TYPE multiplied.
	  * @param _TYPE k The real constant associated with this operation.
	  * @return _VECTOR_TYPE The _VECTOR_TYPE resultant. 
	  * 
	  */		
	 friend _VECTOR_TYPE operator*(_TYPE k, _VECTOR_TYPE vector)
	 {
	 	return vector*k;	
	 }
	 
	 /**
	  * This operator multiplyes this (and modify it) with the float parameter.
	  * 
	  * @param _TYPE The real constant associated with this operation.
	  * @return _VECTOR_TYPE The _VECTOR_TYPE resultant. 
	  * 
	  */
	 _VECTOR_TYPE operator*=(_TYPE k)
	 {
	 	return ((*this) = (*this) * k);
	 }
	 
	  /**
	  * This operator divides this by the float parameter.
	  * 
	  * @param _TYPE The real constant associated with this operation.
	  * @return _VECTOR_TYPE The _VECTOR_TYPE resultant. 
	  * 
	  */	
	 virtual _VECTOR_TYPE operator/(_TYPE) = 0;
	 
	  /**
	  * This operator multiplyes this (and modify it) with the float parameter.
	  * 
	  * @param _TYPE The real constant associated with this operation.
	  * @return _VECTOR_TYPE The _VECTOR_TYPE resultant. 
	  * 
	  */	
	 _VECTOR_TYPE operator/=(_TYPE k)
	 {
	 	return ((*this) = (*this) / k);	
	 }

	/**
	* This operator returns the element in specified index.
	*
	* @param int index The index of element.
	* @return _TYPE The element of this index.
	*
	*/
	_TYPE &operator[](int index)
	{
		return this->ELEMENTS[index];
	}	
	
	/**
	 * This method converts the coordenates of this point to array reference.
	 * 
	 * @param void
	 * @return _TYPE* The array reference of coordenates.
	 * 
	 */	
	_TYPE* toArray()
	{
		return this->ELEMENTS;
	}
};

#endif /*_CYB_VECTOR_H_*/

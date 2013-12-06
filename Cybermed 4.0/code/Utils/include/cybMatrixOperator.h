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

#ifndef _CYB_MATRIX_OPERATOR_H_
#define _CYB_MATRIX_OPERATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/**
 * @class CybMatrixOperator
 * @file cybMatrixOperator.h
 * @short This class especifies operations that can be applied in a matrix.
 *
 * This class implements methods that operate in matrix of form
 *
 *  A11   ...	A12  ...  A1m
 *  A21   ... 	A22  ...  A2m
 *   .	  ...	 .   ...  .
 *   .	  ...	 .   ...  .
 *   .	  ...	 .   ...  .
 *  Am1	  ...	Am2  ...  Amm
 *
 * where m denotes the matrix's dimension.
 *
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */
class CybMatrixOperator
{

private:
	
	/** Constructor. */
	CybMatrixOperator();

public:

	/**
	* This method eliminate the line lin and colunn in col parameters of a matrix.
	* The template _TYPE indicates the type of matrix.
	*
	* @param float* m The matrix that want eliminate the line and colunn.
	* @param float* m2 The resultant matrix ((dimension-1) x (dimension-1)).
	* @param int lin The line that will be elimitated.
	* @param int col The column that will be eliminated.
	* @param int s The dimension of matrix.
	* 
	*/
	static void delLinCol(float *m, float *m2, int lin, int col, int s);

	/**
	* This method returns the determinat of matriz m x m.
	* The template _TYPE indicates the type of matrix.
	*
	* @param float* m The matrix to calculate the determinant,
	* where each line of matrix are the elements (m[x][y] = matrix[dimension*x+y]).
	* @param int dim The matrix dimension (dimension x dimension).
	* @return float The matrix's determinant.
	*
	*/
	static float matrixDeterminant(float *m, int dim);
	
	/**
	* This method returns the determinat of matriz m x m.
	* The template _TYPE indicates the type of matrix.
	*
	* @param double* m The matrix to calculate the determinant,
	* where each line of matrix are the elements (m[x][y] = matrix[dimension*x+y]).
	* @param int dim The matrix dimension (dimension x dimension).
	* @return double The matrix's determinant.
	*
	*/
	static double matrixDeterminant2(double *m, int dim);

	/**
	* This method calculates the inverse matrix.
	*
	* @param float* m The original matrix.
	* @param float* m_1 The inverse matrix (must be a vector with lenght dimension x dimension.
	* @param int s The dimension of matrix.	
	* @param float deterM The determinat of matrix (if call the method with determinant = 0 (default),
	* the determinant of matrix will be calculated inside the method.
	* 
	*/	
	static void matrixInverse(float *m, float *m_1, int s, float deterM);	
	
	/**
	* This method multiplies an especific matrix by a vector and modifies this vector to new values.
	*
	* @param float *covM The matrix that will be applied in vector.
	* @param _TYPE *difMeanV The vector that will be transformed.
	* @param int dim The dimension of vector [The matrix must have the dimension (dimension x dimension)].
	*
	*/
	static float matrixMult(float *covM, float *difMeanV, int dim);
};

#endif /*_CYB_MATRIX_OPERATOR_H_*/

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

#ifndef CYB_POINT_OPERATOR
#define CYB_POINT_OPERATOR

#include "cybThread.h"
#include "cybParameters.h"
#include "cybVector3D.h"
#include "cybVector4DH.h"

/**
 * @class CybPointOperator 
 * @file cybPointOperator.h 
 * @short This class especifies operations that can be applied in points.
 *
 * This class implements methods that operate in objects defined by cybPoint3D.
 * This methods implements the transformations that can be applied in a point of a object.
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	1.0
 * @date		2007, July
 * 
 */
class CybPointOperator
{
	
private:

	static double matrixInverse[16];	/**< Stores the inverse of matrix tranformation in graphics scene. */

public:

	/**
	 * This method calculates the determinant of a 3x3 matrix, represented for a,b,c,d,e,f,g,h and i elements.
	 *
	 * @param float a Represents the element a11 of matrix.
	 * @param float b Represents the element a12 of matrix.
	 * @param float c Represents the element a13 of matrix.
	 * @param float d Represents the element a21 of matrix.
	 * @param float e Represents the element a22 of matrix.
	 * @param float f Represents the element a23 of matrix.
	 * @param float g Represents the element a31 of matrix.
	 * @param float h Represents the element a32 of matrix.
	 * @param float i Represents the element a33 of matrix.
	 * @return float The determinant of the matix.
	 * 
	 */
	static double calculateDeterminant(double a, double b, double c,
			double d, double e, double f,
			double g, double h, double i );

	/**
	 * This method uses the matrix of graphics transformation scene to calculate its inverse.
	 * This inverse it's stores in matrixInverse attribute.
	 *
	 * @param int layer The layer that is interacted.
	 * @return void
	 * 
	*/
	static void calculateInverseMatrix(int layer);

	/**
	 * Calculates the transformation of a point with the transformatin scene inverse.
	 *
	 * @param CybVector3D<float> point The pointer to the point that represents the point will be transformed.
	 * @param int layer The layer interacted.
	 * @return CybVector3D<float> The point transformed.
	 * 
	 */
	static CybVector3D<float> executInverseTransformation(CybVector3D<float> point, int layer);

	/**
	 * The method uses the matrix MODELVIEW (stored in atribute transforMatrix, initialized in CybView)
	 * to calculate the geometrical transformations (Translattion, Rotation or Scaling) that are made on the
	 * point.
	 *
 	 * @param CybVector3D<float> point The pointer to the point that represents the point will be transformed.
 	 * @param int layer The layer interacted.
	 * @return CybVector3D<float> The point ttransformed.
 	 * 
	 */
	static CybVector3D<float> executTransformation(CybVector3D<float>, int layer);

	/**
	 * The method uses the attribute pointOfCollision for the aproximation of collision's 
	 * point to the nearest vertex. By this, the method can only be used after the 
	 * collisionDetection() method when its return will be true. It modifies the status of the attribute 
	 * vertexOfCollision.
	 *
	 * @param CybVector3D<float> vertex0 the 0 vertex of triangle (with the transformations).
	 * @param CybVector3D<float> vertex1 the 1 vertex of triangle (with the transformations).
	 * @param CybVector3D<float> vertex2 the 2 vertex of triangle (with the transformations).
	 * @param CybVector3D<float> point A point that you want find the closest vertex.
	 * @return int the index of the closest vertex (In this case, 0, 1 or 2).
	 * 
	 */
	static int executVertexAproximation(CybVector3D<float> vertex0,CybVector3D<float> vertex1,CybVector3D<float> vertex2,CybVector3D<float> point);
};

#endif /*CYB_POINT_OPERATOR*/

// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba.
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
#ifndef _CYBOBBDRAWER_H_
#define _CYBOBBDRAWER_H_

#define PI 3.1415

#include "cybVector3D.h"
#include "cybBoxHolder.h"
#include "cybBoxDrawer.h"
#include "cybMatrix.h"
#include <GL/glut.h>
#include <cmath>

/**
 * @class CybOBBDrawer
 * @file cybOBBDrawer.h 
 * @short This class implements a drawer for OBBs.
 *
 * This class defines a funtion to draw a OBB and apply the necessary transformations. 
  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 3.1
 * @date 2012, June
 * 
 */

class CybOBBDrawer : public CybBoxDrawer
{
	public:
		/*
		* Constructor.
		*
		* @param CybVector3D<double>* matrix: the OBB's orienting matrix.
		* @param CybVector3D<double>& center: the OBB's center.
		* @param CybVector3D<double>& sizes: the OBB's halfedge lengths.
		*/ 
		CybOBBDrawer(CybVector3D<double>*, CybVector3D<double>&, CybVector3D<double>&);

		/*
		* This method uses OpenGL primitives to draw the OBB.
		*
		* @param void.
		* @return void.
		*/
		void drawBox();
		
		/*
		* Getter for the center attribute.
		*
		* @param void.
		* @return CybVector3D<double>& center: the OBB's center.
		*/
		CybMatrix<double>* getCenter();
		
		/*
		* Getter for the scale attribute.
		*
		* @param void.
		* @return CybVector3D<double>& scale: the OBB's scale parameters.
		*/
		CybVector3D<double>& getScale();

		/*
		* Getter for the sizes attribute.
		*
		* @param void.
		* @return CybVector3D<double>& sizes: the OBB's halfedge lengths.
		*/
		CybMatrix<double>* getSizes();

		/*
		* Getter for the translation attribute.
		*
		* @param void.
		* @return CybVector3D<double>& translation: the OBB'S translation parameters.
		*/
		CybVector3D<double>& getTranslation();

		/*
		* Setter for the center attribute.
		*
		* @param CybVector3D<double>& center: the new center.
		* @return void.
		*/
		void setCenter(CybMatrix<double>*);

		/*
		* Setter for the scale attribute.
		*
		* @param CybVector3D<double>& scale: the new scale parameters.
		* @return void.
		*/
		void setScale(CybVector3D<double>&);

		/*
		* Setter for the sizes attribute.
		*
		* @param CybVector3D<double>& sizes: the new halfedge lengths.
		* @return void.
		*/
		void setSizes(CybMatrix<double>*);

		/*
		* Setter for the translation attribute.
		*
		* @param CybVector3D<double>& translation: the new translation parameters.
		* @return void.
		*/
		void setTranslation(CybVector3D<double>&);

		/*
		* This method updates the drawing properties when a local (OBB-space) rotation happens.
		*
		* @param CybVector3D<double>& newCenter: the center after the rotation.
		* @param CybVector3D<double>& newSizes: sizes after rotation.
		* @return void
		*/
		void updateLocalRotation(CybVector3D<double>&, CybVector3D<double>&);

		/*
		* This method updates the drawing properties when a local (OBB-space) scale happens.
		*
		* @param CybVector3D<double>& newCenter: the center after the scale.
		* @param CybVector3D<double>& newSizes: sizes after scale.
		* @return void
		*/
		void updateLocalScale(CybVector3D<double>&, CybVector3D<double>&);		

		/*
		* This method updates the drawing properties when a local (OBB-space) translation happens.
		*
		* @param CybVector3D<double>& newCenter: the center after the translation.
		* @return void
		*/
		void updateLocalTranslation(CybVector3D<double>&);

		/*
		* This method updates the drawing properties when a global rotation happens.
		*
		* @param int axis: the axis of rotation.
		* @param double angle: the angle of rotation (in degrees).
		* @return CybVector3D<double>&: the center after the rotation. Used to update the collision properties.
		*/
		CybVector3D<double>& updateGlobalRotation(int, double);

		/*
		* This method updates the drawing properties when a global scale happens.
		*
		* @param CybVector3D<double>& globScale: a vector containing the scale parameters.
		* @return void
		*/
		void updateGlobalScale(CybVector3D<double>&);

		/*
		* This method updates the drawing properties when a global translation happens.
		*
		* @param CybVector3D<double>& globTrans: a vector containing the translation parameters.
		* @return void
		*/
		void updateGlobalTranslation(CybVector3D<double>&);
		
		
	private:
		/*
		* This method calculates the transformation matrix from the vector space represented by the
		* first parameter to the vector space represented by the second parameter.
		*
		* @param CybMatrix<double>& initial: the vector space from which the transformation will occur.
		* @param CybMatrix<double>& goal: the vector space in which the vectors need to be represented.
		* @return CybMatrix<double>&: the transformation matrix.
		*/
		CybMatrix<double>& getTransformationMatrix(CybMatrix<double>&, CybMatrix<double>&);

		/*
		* This method solves equation systems of 3 variables and 3 equations using a upper triangular
		* matrix (Gauss' elimination method).
		*
		* @param CybMatrix<double>& matrix: the upper triangular matrix that represents the system.
		* @return double*: an array containing the results of the system.
		*/
		double* solveSystem(CybMatrix<double>&);


		CybVector3D<double> scale;			//The OBB's scale parameters.
		CybVector3D<double> translation;		//The OBB's translation parameters.
		CybVector3D<double> rotation;			//The OBB's rotation parameters.

		CybMatrix<double>* canonToOBB;			//Transformation matrix from world space to OBB space.
		CybMatrix<double>* OBBToCanon;			//Transformation matrix from OBB space to world space.
		CybMatrix<double>* centerMatrix;		//OBB center in world space coordinates.
		CybMatrix<double>* sizesMatrix;			//OBB sizes.
};

#endif // _CYBOBBDRAWER_H_

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

#ifndef _CYB_OBB_H_
#define _CYB_OBB_H_

#include "cybBroadCollision.h"
#include "cybNarrowCollision.h"
#include "cybCollisionObserver.h"
#include "cybVector3D.h"
#include <cybermed/cybTraits.h>
#include <cybermed/cybOBBDrawer.h>
#include <vector>
#include <iostream>

#define EPSILON 1e-10

using namespace std;

/**
 * @class CybOBB 
 * @file cybOBB.h 
 * @short Oriented Bounding Box class
 *
 * This class implements the Oriented Bounding Box collision test. 
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 3.0
 * @date 2012, July
 */

class CybOBB : public CybBroadCollision
{
	public:

		//Constructors.

		/*
		* Constructor 1.
		*
		* @param int layerID: the ID of the layer that contains the object that this OBB must bound.
		* @param CybInterator* interator: pointer to the interator associated with the bound object.
		* @param bool interatorBox: boolean value to define if this box will bound an interator or not.
		* @param bool draw: boolean value to define if this box must be drawn or not.
		*/
		CybOBB(int, CybInterator *, bool, bool);

		/*
		* Constructor 2.
		*
		* @param int layerID: the ID of the layer that contains the object that this OBB must bound.
		* @param int interatorID: ID of the interator associated with the bound object.
		* @param bool interatorBox: boolean value to define if this box will bound an interator or not.
		* @param bool draw: boolean value to define if this box must be drawn or not.
		*/
		CybOBB(int, int, bool, bool);

		/*
		* Constructor 3 (copy constructor).
		*
		* @param const CybOBB& box: reference to the OBB from which the propertied will be copied.
		*/ 
		CybOBB(const CybOBB&);
		
		/*
		* Constructor 4.
		*
		* @param CybNarrowCollision* narrowObj: a narrow collision object from which the interator and 
		*					the layer ID will be taken.
		* @param bool interatorBox: boolean value to define if this box will bound an interator or not.
		* @param bool draw: boolean value to define if this box must be drawn or not.
		*/
		CybOBB(CybNarrowCollision* , bool, bool);

		
		//Destructor.
		
		/*
		* Destructor.
		*
		* @param void
		*/
		~CybOBB();


		//Overloaded operators.

		/*
		* Overloaded assignment operator.
		*
		* @param const CybOBB& box: the box that will be assigned to this object.
		* @return CybOBB&: a reference to this object with the new values. Allows cascading.
		*/
		CybOBB& operator=(const CybOBB&);


		//Other methods.

		/*
		* This method add a pointer to an OBB to the test list of this object. This means that the object
		* referenced by the pointer will be included in the collision test.
		*
		* @param CybOBB* box: pointer to the box that must be included in the collision test list of this object.
		* @return void
		*/
		void addTest(CybOBB*);

		/*
		* This method implements the concrete OBB collision test, using the separating axis test.
		*
		* @param CybOBB& box: a reference to an OBB that will be tested for collision against this object.
		* @return bool: true if the OBBs are colliding, false otherwise.
		*/
		bool collision(CybOBB&);

		/*
		* This method prints a description of this OBB, showing its orientation matrix, its sizes and its center.
		*
		* @param void
		* @return void
		*/
		void describeBox();

		/*
		* This method destroys this thread.
		*
		* @param void
		* @return void
		*/
		void destroy();

		/*
		* Getter for the OBB's center.
		*
		* @param void
		* @return CybVector3D<double>&: a reference to the center of the OBB.
		*/
		CybVector3D<double>& getCenter();

		/*
		* Getter for the OBB's index (this is used by the collision observer).
		*
		* @param void
		* @return int: this OBB's index.
		*/
		int getObjectIndex();

		/*
		* Getter for the OBB's orientation matrix.
		*
		* @param void
		* @return CybVector3D<double>*: a pointer to the orientation matrix.
		*/
		CybVector3D<double>* getOrientation();

		/*
		* Getter for the OBB's sizes (the halfedge lengths)
		*
		* @param void
		* @return CybVector3D<double>&: a reference to the OBB's sizes.
		*/
		CybVector3D<double>& getSizes();

		/*
		* Getter for the OBB's test list.
		*
		* @param void
		* @return vector<CybOBB*>&: a reference to the test list.
		*/
		vector<CybOBB*>& getTestList();

		/*
		* This method initiates the thread's execution.
		*
		* @param void
		* @return void
		*/
		void init();

		/*
		* This method removes an OBB pointer from the test list (if it is into it).
		*
		* @param CybOBB* box: the pointer to the OBB that must be removed from the list.
		* @return void
		*/ 
		void removeTest(CybOBB*);

		/*
		* This method implements the task this thread must perform. In this case, conduct the collision
		* tests and pass the results to the collision observer.
		*
		* @param void
		* @return void
		*/
		void run();

		/*
		* Setter for the OBB's center.
		*
		* @param double x: the new x coordinate.
		* @param double y: the new y coordinate.
		* @param double z: the new z coordinate.
		* @return void
		*/
		void setCenter(double, double, double);

		/*
		* This method makes the necessary updates to the OBB, according to the transformations that have
		* occurred since its last execution.
		*
		* @param void
		* @return void
		*/
		void update();

	private:

		//Private methods.

		/*
		* This method begins the construction the OBB. It calculates de covariance matrix from
		* the mesh's triangles e passes it to the next method.
		*
		* @param void
		* @return void
		*/
		void buildFromTriangles();

		/*
		* This method finishes the construction of the OBB. It calculates the eigenvectors of the
		* covariance matrix, using them as the OBB's axes. The center and the halfedge lengths are
		* calculated by using the maximum and mininum coordinates that the mesh has when projected
		* onto this new vector space.
		*
		* @param CybVector3D<double>* covMatrix: the covariance matrix constructed in buildFromTriangles().
		* @param cybMesh<cybSurfaceTriTraits>* mesh: the mesh whose OBB is being built.
		* @return void
		*/
		void buildOBB(CybVector3D<double>*, cybMesh<cybSurfaceTriTraits>*);

		/*
		* This method implements Jacobi's numeric method for calculating eigenvectors and eigenvalues.
		*
		* @param CybVector3D<double>* covMatrix: the covariance matrix.
		* @param double* eigVal: an empty array that will receive the eigenvalues in the end.
		* @param CybVector3D<double>* eigVec: an empty 3x3 matrix that will receive the eigenvectors in the end.
		* @return void
		*/
		void calculateEigenSystem(CybVector3D<double>*, double*, CybVector3D<double>*);

		/*
		* Getter for the global (world space) transformation values that affect the interator.
		*
		* @param CybVector3D<double> *transf: a matrix that will receive the values.
		* @return void
		*/		
		void getInteratorGlobalTransformations(CybVector3D<double> *);

		/*
		* Getter for the local (OBB space) transformation values that affect the interator.
		*
		* @param CybVector3D<double> *transf: a matrix that will receive the values.
		* @return void
		*/
		void getInteratorLayerTransformations(CybVector3D<double> *);

		/*
		* Getter for the global (world space) transformation values that affect the mesh.
		*
		* @param CybVector3D<double> *transf: a matrix that will receive the values.
		* @return void
		*/
		void getMeshGlobalTransformations(CybVector3D<double> *);

		/*
		* Getter for the local (OBB space) transformation values that affect the mesh.
		*
		* @param CybVector3D<double> *transf: a matrix that will receive the values.
		* @return void
		*/
		void getMeshLayerTransformations(CybVector3D<double> *);	

		/*
		* This method transforms the matrix passed as parameter in an identity matrix.
		* It only works for square matrices.
		*
		* @param CybVector3D<double>* matrix: the matrix that will be transformed.
		* @param int dimension: the dimension of the matrix.
		*/
		void setIdentity(CybVector3D<double>*, int);

		/*
		* This method deals with local rotation, updating the center of the OBB.
		*
		* @param int axis: 0 for x axis, 1 for y axis and 2 for z axis.
		* @param double angle: the angle of rotation in degrees.
		* @return void
		*/
		void treatRotation(int, double);

		//Variables.

		CybVector3D<double> center;				//The OBB's center.
		CybVector3D<double> orientation[3];			//The OBB's orientation matrix.
		CybVector3D<double> sizes;				//The OBB's halfedge lengths.
		CybVector3D<double> initialSizes;			//The OBB's initial lengths.
		bool interatorBox;					//Marks if this is an interator OBB
		vector<CybOBB*> testList;				//The list of OBB pointers to test for collision.
		CybOBBDrawer* drawer;					//The drawer object responsible for drawing this OBB.
		CybVector3D<double> lastLayerTransf[3];			//An array containing the most recent local transformations.
		CybVector3D<double> lastGlobalTransf[3];		//An array containing the most recent global transfomations.


};


#endif //_CYB_OBB_H_

// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2011 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#ifndef _CYBAABB_H_
#define _CYBAABB_H_

#include "cybBroadCollision.h"
#include "cybNarrowCollision.h"
#include "cybCollisionObserver.h"
#include <cybermed/cybVector3D.h>
#include <cybermed/cybAABBDrawer.h>
#include <cybermed/cybTraits.h>
#include <list>
#include <cmath>
#include <algorithm>

#define PI 3.14159265

/**
@class		CybAABB
@file		cybAABB.h
@short
High level collision detection class.

Defines the AABB method for collision detection, using the center-radius model.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2011, September
*/

class CybAABB : public CybBroadCollision{
	public:
		/**
		* Constructor 1
		*
		* @param int layer: the number of the layer that the object will be detecting the collision.
		* @param CybInterator* interator: pointer to the interator that will be used to detect the collision.
		* @param bool isInteratorBox: true if this box is supposed to bound an interator object.
		* @param bool draw: true if this box is meant to be drawn.
		*/
		CybAABB(int, CybInterator *, bool, bool);
		/**
		* Constructor 2
		*
		* @param int layer: the number of the layer that the object will be detecting the collision.
		* @param int interatorId: the id of the interator that will be used to detect the collision.
		* @param bool isInteratorBox: true if this box is supposed to bound an interator object.
		* @param bool draw: true if this box is meant to be drawn.
		*/
		CybAABB(int, int, bool, bool);
		/**
		* Constructor 3 (copy constructor)
		*
		* @param const AABB& caixa: a reference to the AABB that is being used to build the new one.
		*/
		CybAABB(const CybAABB&);
		/**
		* Constructor 4
		*
		* @param CybNarrowCollision *narrow: pointer to a narrow collision detector.
		* @param bool isInteratorBox: true if this box is supposed to bound an interator object.
		* @param bool draw: true if this box is meant to be drawn.
		*/
		CybAABB(CybNarrowCollision* , bool, bool);
		/* Destructor */
		~CybAABB();
		/**
		* Overloaded assignment operator.
		* This method makes each member of the current object be equal to the members of the
		* object received as parameter.
		*
		* @param const AABB& caixa: a reference to the AABB whose members will be used in the assignment
		*  			    operation.
		* @return AABB& : a reference to the AABB (to allow the collateral effect of the operator and cascading)
		*/
		CybAABB& operator=(const CybAABB&);
		/**
		* This method adds a new AABB to the list of AABB's that this object must test for collision.
		*
		* @param CybAABB*: a pointer to the new AABB
		* @return void
		*/
		void addTest(CybAABB*);
		/**
		* This method detects collisions between two AABBs.
		*
		* @param const AABB& caixa: a reference to the AABB in which the collision test is being applied.
		* @return bool: true if the collision happened and false if it didn't.
		*/
		bool collision(CybAABB&);
		/**
		* This method prints a brief description of the AABB, with center coordinates and the size of each
		* axis.
		*
		* @param void
		* @return void
		*/
		void describeBox();
		/**
		* This is a virutal method inherited from CybCollision. It destroys the current thread.
		*
		* @param void
		* @return void
		*/
		void destroy();
		/**
		* This method returns a reference to the vector containing the coordinates of the AABB's center.
		*
		* @param void.
		* @return CybVector3D<float>&: reference to the vector containing the coordinates.
		*/
		CybVector3D<float>& getCenter();
		CybAABBDrawer* getDrawer();
		int getObjectIndex();
		/**
		* This method returns a reference to the vector containing the coordinates of the real AABB' center.
		* (the center after suffering scales, translations and/or rotations)
		*
		* @param void
		* @return CybVector3D<float>&: reference to the vector containing the real coordinates.
		*/
		CybVector3D<float>& getRealCenter();
		/**
		* This method returns a reference to the vector containing the real AABB's axis' sizes.
		* (the sizes after suffering scales, translations and/or rotations)
		*
		* @param void
		* @return CybVector3D<float>&: reference to the vector containing the real AABB's axis' sizes.
		*/
		CybVector3D<float>& getRealSizes();
		/**
		* This method returns a reference to the vector containing the AABB's axis' sizes.
		*
		* @param void.
		* @return CybVector3D<float>&: reference to the vector containing the sizes.
		*/
		CybVector3D<float>& getSizes();
		/**
		* This method returns the list of AABB pointers involved in the collision detection tests with this
		* object.
		*
		* @param void
		* @return list<CybAABB*>: the list of AABB pointers being tested.
		*/
		list<CybAABB*> getTestList();
		/**
		* This is a virtual method inherited from CybThread. It is only used to call the init method implemented
		* in CybThread so that the thread's execution is started.
		*
		* @param void
		* @param void
		*/
		void init();
		/**
		* This method removes one of the AABB pointers in the list, so that this object stop testing collision
		* with the object referenced by the pointer parameter.
		*
		* @param CybAABB*: the pointer that must be removed from the list of tests.
		* @return void
		*/
		void removeTest(CybAABB*);
		/**
		* This method starts the thread's execution.
		*
		* @param void.
		* @return void.
		*/
		void run();
		/**
		* This method sets the AABB's center's coordinates.
		*
		* @param CybVector3D<float>&: a reference to another vector, whose members will be used in the operation
		* @return void.
		*/

		void setCenter(CybVector3D<float>&);
		/**
		* This method sets the AABB's center's coordinates, receiving each value separately.
		*
		* @param float xc : the x coordinate of the center.
		* @param float yc: the y coordinate of the center.
		* @param float zc: the z coordinate of the center.
		* @return void.
		*/
		void setCenter(float, float, float);
		/**
		* This method sets the AABB's axis' sizes.
		*
		* @param CybVector3D<float>&: a reference to another vector, whose members will be used in the operation
		* @return void.
		*/
		void setSizes(CybVector3D<float>&);
		/**
		* This method sets the AABB's axis' sizes, receiving each value separately.
		*
		* @param float cx: the size of the box's x axis.
		* @param float cy: the size of the box's y axis.
		* @param float cz: the size of the box's z axis.
		* @return void
		*/
		void setSizes(float, float, float);
		/**
		* This is a virtual method inherited from CybCollision. It calls the update method int the super class
		* and updated the position of the AABB bounding the interator, based on the data on CybCollisionData.
		*
		* @param void
		* @return void
		*/
		void update();
		/**
		* This method updates the AABB's position by receiving the new center's coordinates.
		*
		* @param float xc: the new x coordinate of the center.
		* @param float yc: the new y coordinate of the center.
		* @param float zc: the new z coordinate of the center.
		* @return void.
		*/
		void updateBox(float, float, float);
	private:
		/**
		* This method calculates the center and the sizes of the box by scoping the model's point's coordinates
		* and searching the greatest and the lowest values for each axis and doing some simple math on them.
		*
		* @param char type: this parameter is used to update the AABB if a rotation occurs.
		* @return void
		*/
		void calculateCenterAndSizes();
		/**
		* This method calculates the real coordinates of the center of the box, after suffering the
		* transfomations in CybParameters (if it is a mesh AABB) or in CybInterator (if it is an interator
		* AABB).
		*
		* @param void
		* @return void
		*/
		void calculateRealCenter();
		/**
		* This method calculates the real sizes of each of the AABB's axis, after suffering the
		* transfomations in CybParameters (if it is a mesh AABB) or in CybInterator (if it is an interator
		* AABB).
		*
		* @param void
		* @return void
		*/
		void calculateRealSizes();
		/**
		* This method calculates the new sizes of the box after the object that it bounds suffers
		* a rotation.
		*
		* @param int axis: the axis around which the rotation occured (0 for x, 1 for y and 2 for z)
		* @param float angle: the angle of rotation in degrees.
		* @param float* values: an array to store the new sizes.
		* @return void
		*/
		void calculateRotatedSizes(int,float, float*);
		/**
		* This method converts an angle in degrees to and angle in radians.
		*
		* @param float angle: the angle in degrees.
		* @return float: the angle in radians.
		*/
		float degToRad(float);
		/**
  		* This method retrieves the values of the transformations that the interator bounded by this
        	* box has suffered.
        	*
        	* @param float* t: the pointer of an array that will store the values.
        	* @return void
        	*/
		void getInteratorTransformations(float *);
		/**
        	* This method retrieves the values of the transformations that the mesh bounded by this
        	* box has suffered.
        	*
        	* @param float* t: the pointer of an array that will store the values.
        	* @return void
        	*/
		void getMeshTransformations(float *);
		/**
		* This method makes the necessary changes in the AABB due to some rotation in one of the axis.
		*
		* @param char axis: one letter to indicate around which axis the rotation occured.
		* @param float angle: the rotated angle.
		* @ return void.
		*/
		void treatRotation(float *, bool *);
		CybVector3D<float> center; // vector of the center's coordinates.
		CybVector3D<float> sizes; // vector of the box's axis' sizes.
		list<CybAABB*> testList; //list containing the pointers of the AABB's that must be tested for collision.
		bool isInteratorBox; //boolean variable to indicate if this is an interator box or not.
		CybVector3D<float> realCenter; //vector representing the real center coordinates after transformations.
		CybVector3D<float> realSizes; //vector representing the real sizes of the box after transformations.
		float lastTransf[9]; //this variable stores the very last transformations suffered by this box
                            //using the following indexes: 0~2 = translation, 3~5 = scale, 6~8 = rotation
		CybVector3D<float> initialSizes; //the initial sizes in each axis of this box.
		CybAABBDrawer* drawer; //this object is responsible for drawing the AABB.
};

#endif //_CYBAABB_H_


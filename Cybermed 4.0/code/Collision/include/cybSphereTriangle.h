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
#include "cybPointOperator.h"
#include "cybNarrowCollision.h"

using namespace mf;

#ifndef _CYB_SPHERE_TRIANGLE_H_
#define _CYB_SPHERE_TRIANGLE_H_

/**
 *@class CybSphereTriangle
 *@file cybSphereTriangle.h
 *@short Implements the collision detection triangle-sphere method.
 *
 *This class implements the collision detection method sphere-triangle.
 *
 *@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 *@version 1.0
 *@date 2007, July
 */
 
class CybSphereTriangle : public CybNarrowCollision
{
private:
  
	float radius; /**< Stores the sphere's radius. */
	
	// attributes used in internal method.
	
	int triangle;					/**< it counts the number of triangles covered in triangle's list*/
	float delta[6];					/**< it stores the auxiliar values*/
	float det[3];					/**< it assists in calculations the triangle's point nearest of sphere's center	*/
	CybVector3D<float> P1_P0;			/**< stores original copies */
	CybVector3D<float> P2_P0;			/**< stores original copies */
	CybVector3D<float> P2_P1;			/**< stores original copies */
	CybVector3D<float> P0_C;			/**< stores original copies */
	CybVector3D<float> P1_C;			/**< stores original copies */
	CybVector3D<float> P2_C;			/**< stores original copies */
	CybVector3D<float> X_C;				/**< stores original copies */
	CybVector3D<float> sphereCenter;		/**< Center of sphere*/
	CybVector3D<float> pointClosest;		/**< it stores the closest point of triangle*/
	CybVector3D<float> vertex[3];			/**< Store the vertex of triangle */
	CybVector3D<float>* pointerPointClosest;	/**< pointer to the closest point */
	CybVector3D<float>* ver0;			/**< stores original copies */
	CybVector3D<float>* ver1;			/**< stores original copies */
	CybVector3D<float>* ver2;			/**< stores original copies */
	sVertex *vertex0;				/**< stores original copies */
	sVertex *vertex1; 				/**< stores original copies */
	sVertex *vertex2;				/**< stores original copies */
	
public:

	typedef cybSurfaceTriTraits::sCell sCell;
	typedef mfCellsIterator<cybSurfaceTriTraits> cybCellIterator;
  
	/**
	 * Constructor.
	 * 
	 * @param int layer The layer interacted.
	 * @param int interatorId The interator id.
	 * 
	 */
	CybSphereTriangle(int layer, int interatorId);
	
	/**
	 * Constructor.
	 * 
	 * @param int layer The layer interacted.
	 * @param CybInterator* interator Pointer to the interator.
	 *
	 */
	CybSphereTriangle(int layer, CybInterator* interator);

	/**
	 * Constructor.
	 *
	 * @param CybBroadCollision* broadObject The broad collision object associated.
	 * 
	 */
	CybSphereTriangle(CybBroadCollision* broadObject);

	/**
	 * This method returns the sphere's radius.
	 *
	 * @param void
	 * @return float the sphere's radius.
	 */
	float getRadius();

	/** The method verifies the collision between an object and the interactor and
	 * modifies the status of variable pointOfCollision and utilizes the method of collision detection sphere-triangle indicated
	 * by Bergen, G.V.(2004), Collision Detection in Interactive Environments 3D, Series in Interactive 3D Technology.
	 *
	 * @param void
	 * @return void
	 */
	void collision();

	/** The method verifies the collision between a list of triangles and the interactor and then
	 * modifies the status of variable pointOfCollision and utilizes the method of collision detection sphere-triangle indicated
	 * by Bergen, G.V.(2004), Collision Detection in Interactive Environments 3D, Series in Interactive 3D Technology.
	 *
	 * @param mfList<cybMesh<cybTraits>::sCell *>* list A reference to a of List of triangles.
	 * @return void
	 * 
	 */
	void collision(mfList<sCell *>* list);
	
	/**
	 * This method sets the sphere's radius.
	 *
	 * @param float radius The sphere's radius.
	 */
	void setRadius(float radius);

	/**
	 * This method will be called in thread executation.
	 * 
	 * @param void
	 * @return void
	 * 
	 */
	 virtual void run();
};

#endif /* _CYB_SPHERE_TRIANGLE_H_ */

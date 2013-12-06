#ifndef _CYBAABB_H_
#define _CYBAABB_H_

#include "cybBroadCollision.h"
#include "cybVector3D.h"
#include <list>

class CybAABB : public CybBroadCollision{
	public:
		/*Constructor 1
		* @param int layer: the number of the layer that the object will be detecting the collision.
		* @param CybInterator* interator: pointer to the interator that will be used to detect the collision.
		* @param cybMesh<cybTraits>* mesh: pointer to the mesh whose AABB will be calculated.
		*/
		CybAABB(int, CybInterator *, cybMesh<cybTraits>*);
		/*Constructor 2
		* @param int layer: the number of the layer that the object will be detecting the collision.
		* @param int interatorId: the id of the interator that will be used to detect the collision.
		* @param cybMesh<cybTraits>* mesh: pointer to the mesh whose AABB will be calculated.
		AABB(int, int);
		*/
		CybAABB(int, int, cybMesh<cybTraits>*);
		/*Constructor 3 (copy constructor)
		* @param const AABB& caixa: a reference to the AABB that is being used to build the new one.
		*/
		CybAABB(const CybAABB&);
		/* Destructor */
		virtual ~CybAABB();
		/*
		* Overloaded assignment operator.
		* This method makes each member of the current object be equal to the members of the
		* object received as parameter.
		*
		* @param const AABB& caixa: a reference to the AABB whose members will be used in the assignment
		*  			    operation.
		* @return AABB& : a reference to the AABB (to allow the collateral effect of the operator and cascading)
		*/
		CybAABB& operator=(const CybAABB&);
		/*
		* This method adds a new AABB the the list of AABB's that his object must test for collision.
		*
		* @param CybAABB*: a pointer to the new AABB
		* @return void
		*/
		void addTest(CybAABB*);
		/*
		* This method detects collisions between two AABBs.
		*
		* @param const AABB& caixa: a reference to the AABB in which the collision test is being applied.
		* @return bool: true if the collision happened and false if it didn't.
		*/		
		bool collision(CybAABB&);
		/*
		* This method prints a brief description of the AABB, with center coordinates and the size of each
		* axis.
		*
		* @param void
		* @return void
		*/
		void describeBox();
		/*
		* This method draws the AABB in wired form, to give a visual representation of what's happening in
		* the collision detection.
		*
		* @param void
		* @return void
		*/		
		void drawBox();
		/*
		* This method returns a reference to the vector containing the coordinates of the AABB's center.
		*
		* @param void.
		* @return CybVector3D<float>&: reference to the vector containing the coordinates.
		*/		
		CybVector3D<float>& getCenter();
		/*
		* This method returns a reference to the vector containing the AABB's axis' sizes.
		* 
		* @param void.
		* @return CybVector3D<float>&: reference to the vector containing the sizes.
		*/
		CybVector3D<float>& getSizes();
		/*
		* This method returns the list of AABB pointers involved in the collision detection tests with this
		* object.
		*
		* @param void
		* @return list<CybAABB*>: the list of AABB pointers being tested.
		*/		
		list<CybAABB*> getTestList();
		/*
		* This method removes one of the AABB pointer in the list, so that this object stop testing collision
		* with the object referenced by the pointer parameter.
		*
		* @param CybAABB*: the pointer that must be removed from the list of tests.
		* @return void
		*/ 
		void removeTest(CybAABB*);
		/*
		* This method starts the thread's execution.
		*
		* @param void.
		* @return void.
		*/		
		void run();
		/*
		* This method sets the AABB's center's coordinates.
		* 
		* @param CybVector3D<float>&: a reference to another vector, whose members will be used in the operation
		* @return void.
		*/

		void setCenter(CybVector3D<float>&);
		/*
		* This method sets the AABB's center's coordinates, receiving each value separately.
		*
		* @param float xc : the x coordinate of the center.
		* @param float yc: the y coordinate of the center.
		* @param float zc: the z coordinate of the center.
		* @return void.
		*/
		void setCenter(float, float, float);
		/*
		* This method sets the AABB's axis' sizes.
		*
		* @param CybVector3D<float>&: a reference to another vector, whose member will be used in the operation
		* @return void.
		*/
		void setSizes(CybVector3D<float>&);
		/*
		* This method sets the AABB's axis' sizes, receiving each value separately.
		*
		* @param float cx: the size of the box's x axis.
		* @param float cy: the size of the box's y axis.
		* @param float cz: the size of the box's z axis.
		* @return void
		*/
		void setSizes(float, float, float);
		/*
		* This method updates the AABB's position by receiving the new center's coordinates.
		* 
		* @param float xc: the new x coordinate of the center.
		* @param float yc: the new y coordinate of the center.
		* @param float zc: the new z coordinate of the center.
		* @return void.
		*/
		void updateBox(float, float, float);
	private:
		void calculateCenterAndSizes();
		CybVector3D<float> center; // vector of the center's coordinates
		CybVector3D<float> sizes; // vector of the box's axis' sizes.
		list<CybAABB*> testList; //list containing the pointers of the AABB's that must be tested for collision
		cybMesh<cybTraits>* mesh; //pointer to the mesh that will be bounded
};

#endif //_CYBAABB_H_

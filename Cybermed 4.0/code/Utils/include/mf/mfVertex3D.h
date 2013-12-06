#ifndef MFVERTEX3D_H
#define MFVERTEX3D_H

#include "mfMacros.h"
#include "mfSingularVertex.h"

namespace mf
{

/**
 *	@class		mfVertex2D
 *	@file		mfVertex2D.h
 *	@short
 *	Base class of the 3D vertex
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfVertex3D : public mfSingularVertex<3,_Traits>
{
public:

	typedef typename _Traits::space space;	/**< Space typename definition */

	/** Constructor */
	mfVertex3D();

	/** Constructor 
	 *
	 * \param x: x coordinate value to be initialized
	 * \param y: y coordinate value to be initialized
	 * \param z: z coordinate value to be initialized
	 *
     */
	mfVertex3D(space x, space y, space z);

	/** Destructor */
	~mfVertex3D();
};

template <class _Traits> mfVertex3D<_Traits>::mfVertex3D()
{
}

template <class _Traits> mfVertex3D<_Traits>::mfVertex3D(space x, space y, space z)
{
	this->setCoord(0,x);
	this->setCoord(1,y);
	this->setCoord(2,z);
}

template <class _Traits> mfVertex3D<_Traits>::~mfVertex3D()
{
}

}

#endif

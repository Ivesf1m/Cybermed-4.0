#ifndef MFVERTEX2D_H
#define MFVERTEX2D_H

#include "mfMacros.h"
#include "mfSingularVertex.h"

namespace mf
{

/**
 *	@class		mfVertex2D
 *	@file		mfVertex2D.h
 *	@short
 *	Base class of the 2D vertex
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfVertex2D : public mfSingularVertex<2,_Traits>
{
public:

	typedef typename _Traits::space space;	/**< Space typename definition */

	/** Constructor */
	mfVertex2D();

	/** Constructor 
	 *
	 * \param x: x coordinate value to be initialized
	 * \param y: y coordinate value to be initialized
	 *
     */
	mfVertex2D(space x, space y);
	
	/** Destructor */
	~mfVertex2D();
};

template <class _Traits> mfVertex2D<_Traits>::mfVertex2D()
{
}

template <class _Traits> mfVertex2D<_Traits>::mfVertex2D(space x, space y)
{
	this->setCoord(0,x);
	this->setCoord(1,y);
}


template <class _Traits> mfVertex2D<_Traits>::~mfVertex2D()
{
}

}

#endif

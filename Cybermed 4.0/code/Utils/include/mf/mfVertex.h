#ifndef MFVERTEX_H
#define MFVERTEX_H

#include "mfMacros.h"
#include "mfBase.h"

namespace mf
{

#define SPACE typename mfVertex<size,_Traits>::space

/**
 *	@class		mfVertex
 *	@file		mfVertex.h
 *	@short
 *	Base class of the vertex
 *	Size is the dimension of vertex:
 *		2 - 2D vertex (x,y)
 *		3 - 3D vertex (x,y,z)
 *
 *	_Traits must have typenames: space
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <int size, class _Traits> class mfVertex : public mfBase<_Traits>
{
public:
	typedef typename _Traits::space space;	/**< Space typename definition */

	/** Constructor */
	mfVertex();

	/** Destructor */
	virtual ~mfVertex();

	/**	Return a specified coordinate of a vertex
	 * 
	 *	\param pos: index of coordinate (1=x, 2=y, 3=z)
	 *	\return Value of the coordinate indexed by pos.
	 */
	space getCoord(int pos MF_DMUTEXVD);

	/**	Return a vector of all coordinates
	 *
	 *	\return Vector with coordinates values of the vertex.
	 */
	space *getCoords(MF_DMUTEXD);

	/**	Define the specified coordinate value
	 * 
	 * 	\param pos: index of coordinate (1=x, 2=y, 3=z)
	 * 	\param value: coordinate value
	 */
	void setCoord(int pos, space value MF_DMUTEXVD);

	/**	Define all coordinates values
	 *
	 *	\param values: vector with coordinates values
	 */
	void setCoords(space* values MF_DMUTEXVD);

	/**	Return the dimension of the vertex
	 *
	 *	\return Dimension of the vertex (2D or 3D).
	 */
	static inline int getDimension(){ return size;};

private:

	space coords[size];	/**< Vector of the vertex coordinates. */
};

template <int size, class _Traits> mfVertex<size,_Traits>::mfVertex()
{
}

template <int size, class _Traits> mfVertex<size,_Traits>::~mfVertex()
{
}

template <int size, class _Traits> SPACE mfVertex<size,_Traits>::getCoord(int pos MF_DMUTEXV)
{
	space c;

	MF_ASSERT((pos>=0) && (pos < size));

	MF_LOCK(smutex);
	c = coords[pos];
	MF_UNLOCK(smutex);

	return c;
}

template <int size, class _Traits> SPACE* mfVertex<size,_Traits>::getCoords(MF_DMUTEX)
{
	space *c;

	MF_LOCK(smutex);
	c = coords;
	MF_UNLOCK(smutex);

	return c;
}

template <int size, class _Traits> void mfVertex<size,_Traits>::setCoord(int pos, space value MF_DMUTEXV)
{
	MF_ASSERT((pos>=0) && (pos < size));

	MF_LOCK(smutex);
	coords[pos] = value;
	MF_UNLOCK(smutex);
}

template <int size, class _Traits> void mfVertex<size,_Traits>::setCoords(space *values MF_DMUTEXV)
{
	MF_LOCK(smutex);
	for(int i = 0; i < size; i++)
		coords[i] = values[i];
	MF_UNLOCK(smutex);
}

#undef SPACE

}

#endif

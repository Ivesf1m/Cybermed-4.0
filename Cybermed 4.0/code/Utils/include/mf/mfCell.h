#ifndef MFCELL_H
#define MFCELL_H

#include "mfMacros.h"
#include "mfBase.h"

namespace mf
{

#define IDS typename mfCell<size,_Traits>::ids

/**
 *	@class		mfCell
 *	@file		mfCell.h
 *	@short
 *	Base class of the cell
 *
 *	Cell types are:
 *		2D - triangles, quadrilaterals and hybrid surface
 *		3D - tetrahedra, hexahedra, prism, piramids and hybrid volumetric
 *
 *	_Traits must have typenames: ids
 *
 *	@author		Mario Lizier and Icaro da Cunha
 *	@version	1.0
 *	@date		2008, july
 */
template <int size, class _Traits> class mfCell : public mfBase<_Traits>
{
public:

	typedef typename _Traits::ids ids;	/**< Id typename definition */

	/**	Constructor
	 *
	 * 	Initialize vertices and mates ids
	 */
	mfCell();

	/**	Destructor
	 */
	virtual ~mfCell();

	/** Return the mate cell id of the specified index
	 *
	 * 	\param index: position of mate cell
	 *	\return mate cell id.
	 */
	ids	getMateId(int index MF_DMUTEXVD);

	/**	Return the vertex id of the specified index
	 *
	 * 	\param index: position of vertex
	 *  \return the vertex id.
	 */
	ids	getVertexId(int index MF_DMUTEXVD);

	/** Define the mate cell id of the specified index
	 *
	 * 	\param index: position of mate cell
	 * 	\param cell: the mate cell id
	 */
	void setMateId(int index, ids cell MF_DMUTEXVD);

	/** Define the vertex id of the specified index
	 *
	 * 	\param index: position of vertex
	 * 	\param vertex: the vertex id
	 */
	void setVertexId(int index, ids vertex MF_DMUTEXVD);

	/**	Reset the mate cells ids
	 *
	 * 	(Defines -1 for all positions)
	 */
	void clearMates(MF_DMUTEXD);

	/**	Return the position/index (in the cell) of the specified vertex id
	 *
	 * 	\param vertex: the vertex id
	 *  \return the vertex index.
	 */
	int getVertexIndex(ids vertex MF_DMUTEXVD);

	/**	Return the position/index (in the cell) of the specified mate cell id
	 *	
	 * 	\param cell: the mate cell id
	 *  \return the mate index.
	 */
	int	getMateIndex(ids cell MF_DMUTEXVD);

	/**	Return the opposite cell id of the specified vertex id.
	 *  To be used only in surface meshes
	 *
	 * 	\param cell: the vertex id
	 *  \return mate cell id.
	 */
	ids	getMateVertexId(ids vertex MF_DMUTEXVD);

	/**	Return the opposite vertex id of the specified mate cell id
	 *
	 * 	\param cell: the mate cell id
	 */
	ids	getVertexMateId(ids cell MF_DMUTEXVD);

	// corrigir
	/**	Return the dimension of this cell
	 */
	static inline int getDimension(){ return size-1;};

	/**	Return the number of vertices of this cell
	 */
	static inline int getNumberVerticesInCell(){ return size;};

	/**	Return the number of edges of this cell
	 */
	static inline int getNumberEdgesInCell(){ return size;};

protected:
	ids vertices[size];	/**< Cell's vertices ids, number of vertices vary accordingly to the type of cell */

	ids mates[size];	/**< Cell's mate cell ids, number of mates vary accordingly to the type of cell  */
};

template <int size, class _Traits> mfCell<size,_Traits>::mfCell()
{
#ifdef MF_THREADS
	pthread_mutex_lock(&this->smutex);
#endif

	for(int i = 0; i < size; i++)
	{
		vertices[i] = -1;
	}
	for(int i = 0; i < 3; i++)
	{
        mates[i] = -1;
    }

#ifdef MF_THREADS
	pthread_mutex_unlock(&this->smutex);
#endif
}

template <int size, class _Traits> mfCell<size,_Traits>::~mfCell()
{
}

template <int size, class _Traits> IDS mfCell<size,_Traits>::getMateId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < size));

	MF_LOCK(smutex);

	ids temp = mates[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <int size, class _Traits> IDS mfCell<size,_Traits>::getVertexId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < size));

	MF_LOCK(smutex);

	ids temp = vertices[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <int size, class _Traits> void mfCell<size,_Traits>::setMateId(int index, ids cell MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < size));

	MF_LOCK(smutex);

	mates[index] = cell;

	MF_UNLOCK(smutex);
}

template <int size, class _Traits> void mfCell<size,_Traits>::setVertexId(int index, ids vertex MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < size));

	MF_LOCK(smutex);

	vertices[index] = vertex;

	MF_UNLOCK(smutex);
}

template <int size, class _Traits> IDS mfCell<size,_Traits>::getMateVertexId(ids vertex MF_DMUTEXV)
{
	for(int i = 0; i < size; i++)
		if (getVertexId(i MF_MUTEXV) == vertex)
			return getMateId(i MF_MUTEXV);

	return -1;
}

template <int size, class _Traits> IDS mfCell<size,_Traits>::getVertexMateId(ids cell MF_DMUTEXV)
{
	for(int i = 0; i < size; i++)
		if (getMateId(i MF_MUTEXV) == cell)
			return getVertexId(i MF_MUTEXV);

	return -1;
}

template <int size, class _Traits> int mfCell<size,_Traits>::getMateIndex(ids cell MF_DMUTEXV)
{
	for(int i = 0; i < size; i++)
		if (getMateId(i MF_MUTEXV) == cell)
			return i;

	return -1;
}

template <int size, class _Traits> void mfCell<size,_Traits>::clearMates(MF_DMUTEX)
{
	for(int i = 0; i < size; i++)
		setMateId(i,-1 MF_MUTEXV);
}

template <int size, class _Traits> int mfCell<size,_Traits>::getVertexIndex(ids vertex MF_DMUTEXV)
{
	for(int i = 0; i < size; i++)
		if (getVertexId(i MF_MUTEXV) == vertex)
			return i;

	return -1;
}

#undef IDS

}

#endif

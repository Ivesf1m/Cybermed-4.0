#ifndef MFTETRACELL_H
#define MFTETRACELL_H

#include "mfMacros.h"
#include "mfCell.h"

namespace mf
{

#define IDS typename mfTetraCell<_Traits>::ids

/**
 *	@class		mfTetraCell
 *	@file		mfTetraCell.h
 *	@short
 *	Base class of the tetrahedron cell
 *
 *  Tetrahedron cell default format with vertex indices:
 *  2------3
 *  |     /|
 *  | \  / |
 *  |   /  |
 *  |  /   |
 *  | /  \ |
 *  |/     |
 *  0------1
 *  
 *	_Traits must have typenames: ids
 *
 *	@author		Mario Lizier and Icaro da Cunha
 *	@version	1.0
 *	@date		2008, july
 */
template <class _Traits> class mfTetraCell : public mfCell<4,_Traits>
{
public:

	typedef typename _Traits ::ids ids;	/**< Id typename definition */

	/** Constructor */
	mfTetraCell();

	/** Destructor */
	virtual ~mfTetraCell();

    /**	Return the edge id of the specified index
	 *
	 *	\param index: position of edge
	 */
	ids getEdgeId(int index MF_DMUTEXVD);

	/** Return the mate cell id of the specified index
	 *
	 * 	\param index: position of mate cell
	 */
	ids	getMateId(int index MF_DMUTEXVD);

    /** Define the edge id of the specified index
	 *
	 *	\param index: position of edge
	 *	\param vertex: the edge id
	 */
	void setEdgeId(int index, ids edge MF_DMUTEXVD);

    /** Define the mate cell id of the specified index
	 *
	 * 	\param index: position of mate cell
	 * 	\param cell: the mate cell id
	 */
	void setMateId(int index, ids cell MF_DMUTEXVD);

	/** Returns face index to the right of the edge defined by its 2 vertices
	 *
	 * 	\param index1: Index of the first vertex of the edge
	 * 	\param index2: Index of the second vertex of the edge
	 * 	\return index of the face
	 */
    int getRightFaceIndex(ids index1, ids index2);

	/** Returns face index to the left of the edge defined by its 2 vertices
	 *
	 * 	\param index1: Index of the first vertex of the edge
	 * 	\param index2: Index of the second vertex of the edge
	 * 	\return index of the face
	 */
    int getLeftFaceIndex(ids index1, ids index2);

	/**	Reset the mate cells ids
	 *
	 * 	Define -1 for all positions
	 */
	void clearMates(MF_DMUTEXD);

    /**	Return the position of the opposite vertex id of the specified mate cell id
	 *	Return the position of the specified mate cell id
	 *
	 * 	\param cell: the mate cell id
	 */
	int	getMateIndex(ids cell MF_DMUTEXVD);

	/**	Return the opposite cell id of the specified vertex id
	 *
	 * 	\param cell: the vertex id
	 */
	ids	getMateVertexId(ids vertex MF_DMUTEXVD);

	/**	Return the opposite vertex id of the specified mate cell id
	 *
	 * 	\param cell: the mate cell id
	 */
	ids	getVertexMateId(ids cell MF_DMUTEXVD);

    /**	Return the dimension of this cell
	 */
	static inline int getDimension(){ return 3;};

	/**	Return the number of vertices of this cell
	 */
    static inline int getNumberVerticesInCell(){ return 4;};

	/**	Return the number of edges of this cell
	 */
	static inline int getNumberEdgesInCell(){ return 6;};

	/**	Return the number of faces of this cell
	 */
	static inline int getNumberFacesInCell(){ return 4;};

private:
	ids edges[6];		/**< Cell's edges ids */
	ids mates[4];	/**< Cell's mate cell ids */
};

template <class _Traits> mfTetraCell<_Traits>::mfTetraCell()
{
#ifdef MF_THREADS
	pthread_mutex_lock(&this->smutex);
#endif

	for(int i = 0; i < 6; i++)
	{
		edges[i] = -1;
	}
	for(int i = 0; i < 4; i++)
	{
        mates[i] = -1;
    }

#ifdef MF_THREADS
	pthread_mutex_unlock(&this->smutex);
#endif
}

template <class _Traits> mfTetraCell<_Traits>::~mfTetraCell()
{
}

template <class _Traits> IDS mfTetraCell<_Traits>::getEdgeId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 6));

	MF_LOCK(smutex);

	ids temp = edges[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <class _Traits> IDS mfTetraCell<_Traits>::getMateId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 4));

	MF_LOCK(smutex);

	ids temp = mates[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <class _Traits> void mfTetraCell<_Traits>::setEdgeId(int index, ids edge MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 6));

	MF_LOCK(smutex);

	edges[index] = edge;

	MF_UNLOCK(smutex);
}

template <class _Traits> void mfTetraCell<_Traits>::setMateId(int index, ids cell MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 4));

	MF_LOCK(smutex);

	mates[index] = cell;

	MF_UNLOCK(smutex);
}

template <class _Traits> IDS mfTetraCell<_Traits>::getVertexMateId(ids cell MF_DMUTEXV)
{
	for(int i = 0; i < 4; i++)
		if (getMateId(i MF_MUTEXV) == cell)
			return this->getVertexId(i MF_MUTEXV);

	return -1;
}

template <class _Traits> int mfTetraCell<_Traits>::getMateIndex(ids cell MF_DMUTEXV)
{
	for(int i = 0; i < 4; i++)
		if (getMateId(i MF_MUTEXV) == cell)
			return i;

	return -1;
}

template <class _Traits> void mfTetraCell<_Traits>::clearMates(MF_DMUTEX)
{
	for(int i = 0; i < 4; i++)
		setMateId(i,-1 MF_MUTEXV);
}

template <class _Traits> int mfTetraCell<_Traits>::getRightFaceIndex(ids index1, ids index2)
{
	MF_ASSERT( (index1 >= 0)&&(index1<=3) );
	MF_ASSERT( (index2 >= 0)&&(index2<=3) );
	MF_ASSERT( index1 != index2 );

	switch(index1)
    {
		case 0:
             if(index2 == 1)
                 return 3;
             if(index2 == 2)
                 return 1;
             if(index2 == 3)
                 return 2;
		break;
		case 1:
             if(index2 == 0)
                 return 2;
             if(index2 == 2)
                 return 3;
             if(index2 == 3)
                 return 0;
		break;
		case 2:
             if(index2 == 0)
                 return 3;
             if(index2 == 1)
                 return 0;
             if(index2 == 3)
                 return 1;
		break;
		case 3:
             if(index2 == 0)
                 return 1;
             if(index2 == 1)
                 return 2;
             if(index2 == 2)
                 return 0;
		break;
    }

    /*if((index1==0)&&(index2==1)) return 3;
	if((index1==0)&&(index2==2)) return 1;
	if((index1==0)&&(index2==3)) return 2;
	if((index1==1)&&(index2==2)) return 3;
	if((index1==1)&&(index2==3)) return 0;
	if((index1==2)&&(index2==3)) return 1;

	if((index1==1)&&(index2==0)) return 2;
	if((index1==2)&&(index2==0)) return 3;
    if((index1==2)&&(index2==1)) return 0;
	if((index1==3)&&(index2==0)) return 1;
	if((index1==3)&&(index2==1)) return 2;
	if((index1==3)&&(index2==2)) return 0;*/

	return -1;
}

template <class _Traits> int mfTetraCell<_Traits>::getLeftFaceIndex(ids index1, ids index2)
{
	MF_ASSERT( (index1 >= 0)&&(index1<=3) );
	MF_ASSERT( (index2 >= 0)&&(index2<=3) );
	MF_ASSERT( index1 != index2 );

	switch(index1)
    {
		case 0:
             if(index2 == 1)
                 return 2;
             if(index2 == 2)
                 return 3;
             if(index2 == 3)
                 return 1;
		break;
		case 1:
             if(index2 == 0)
                 return 3;
             if(index2 == 2)
                 return 0;
             if(index2 == 3)
                 return 2;
		break;
		case 2:
             if(index2 == 0)
                 return 1;
             if(index2 == 1)
                 return 3;
             if(index2 == 3)
                 return 0;
		break;
		case 3:
             if(index2 == 0)
                 return 2;
             if(index2 == 1)
                 return 0;
             if(index2 == 2)
                 return 1;
		break;
    }

    /*if((index1==0)&&(index2==1)) return 2;
	if((index1==0)&&(index2==2)) return 3;
	if((index1==0)&&(index2==3)) return 1;
    if((index1==1)&&(index2==2)) return 0;
    if((index1==1)&&(index2==3)) return 2;
    if((index1==2)&&(index2==3)) return 0;

	if((index1==1)&&(index2==0)) return 3;
	if((index1==2)&&(index2==0)) return 1;
	if((index1==2)&&(index2==1)) return 3;
    if((index1==3)&&(index2==0)) return 2;
	if((index1==3)&&(index2==1)) return 0;
	if((index1==3)&&(index2==2)) return 1;*/

	return -1;
}

#undef IDS

}

#endif

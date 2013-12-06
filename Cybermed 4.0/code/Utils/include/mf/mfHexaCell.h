#ifndef MFHEXACELL_H
#define MFHEXACELL_H

#include "mfMacros.h"
#include "mfCell.h"

namespace mf
{

#define IDS typename mfHexaCell<_Traits>::ids

//


/**
 *	@class		mfHexaCell
 *	@file		mfHexaCell.h
 *	@short
 *	Base class of the hexahedron cell
 *
 *  Hexahedron cell default format with vertex indices:
 *      7----------6
 *     /|         /|
 *    /          / |
 *   /  |       /  |
 *  4----------5   |
 *  |   |      |   |
 *  |   3- -  -|- -2
 *  |  /       |  /
 *  |          | /
 *  |/         |/
 *  0----------1
 *
 *	_Traits must have typenames: ids
 *
 *	@author		Icaro da Cunha
 *	@version	1.0
 *	@date		2008, july
 */
template <class _Traits> class mfHexaCell : public mfCell<8,_Traits>
{
public:
	typedef typename _Traits ::ids ids;

	/* Constructor */
	mfHexaCell();

	/* Destructor */
	virtual ~mfHexaCell();

	/**	Return the edge id of the specified index
	 *
	 *	\param index: position of edge
	 */
	ids getEdgeId(int index MF_DMUTEXVD);
	
	ids getEdgeId(int vIndex1, int vIndex2);

	/** Return the mate cell id of the specified index
	 *
	 * 	\param index: position of mate cell
	 */
	void setEdgeId(int index, ids edge MF_DMUTEXVD);

	/** Return the mate cell id of the specified index
	 *
	 * 	\param index: position of mate cell
	 */
	ids	getMateId(int index MF_DMUTEXVD);

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
	
	int getFaceIndex(int v1, int v2, int v3);
	
	/** Determines if two vertices are adjacent
	 *
	 *  \param index1: Index of the first vertex
	 * 	\param index2: Index of the second vertex
	 */
	bool verticesAreAdjacent(ids index1, ids index2);

	/** Define the mate cell id of the specified index
	 *
	 * 	\param index: position of mate cell
	 * 	\param cell: the mate cell id
	 */
	void setMateId(int index, ids cell MF_DMUTEXVD);

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
	//ids	getMateVertexId(ids vertex MF_DMUTEXVD);

	/**	Return the opposite vertex id of the specified mate cell id
	 *
	 * 	\param cell: the mate cell id
	 */
	//ids	getVertexMateId(ids cell MF_DMUTEXVD);

	/**	Return the dimension of this cell
	 */
	static inline int getDimension(){ return 3;};

	/**	Return the number of vertices of this cell
	 */
	static inline int getNumberVerticesInCell(){ return 8;};

	/**	Return the number of edges of this cell
	 */
	static inline int getNumberEdgesInCell(){ return 12;};

	/**	Return the number of faces of this cell
	 */
	static inline int getNumberFacesInCell(){ return 6;};

private:
	ids mates[6];     /**< Cell's face mate ids */
	ids edges[12];    /**< Cell's edges ids */
};

template <class _Traits> mfHexaCell<_Traits>::mfHexaCell()
{
#ifdef MF_THREADS
	pthread_mutex_lock(&this->smutex);
#endif

	for(int i = 0; i < 12; i++)
	{
		edges[i] = -1;
	}
	for(int i = 0; i < 6; i++)
	{
		mates[i] = -1;
	}

#ifdef MF_THREADS
	pthread_mutex_unlock(&this->smutex);
#endif
}

template <class _Traits> mfHexaCell<_Traits>::~mfHexaCell()
{
}

template <class _Traits> IDS mfHexaCell<_Traits>::getEdgeId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 12));

	MF_LOCK(smutex);

	ids temp = edges[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <class _Traits> IDS mfHexaCell<_Traits>::getEdgeId(int vIndex1, int vIndex2)
{
	ids temp = -1;

	if(vIndex1 == 0)
	{
		if(vIndex2 == 1)
			temp = edges[0];
		if(vIndex2 == 2)
			temp = edges[1];
		if(vIndex2 == 3)
			temp = edges[2];
	}
	if(vIndex1 == 1)
	{
	}

	return temp;
}

template <class _Traits> void mfHexaCell<_Traits>::setEdgeId(int index, ids edge MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 12));

	MF_LOCK(smutex);

	edges[index] = edge;

	MF_UNLOCK(smutex);
}

template <class _Traits> IDS mfHexaCell<_Traits>::getMateId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 6));

	MF_LOCK(smutex);

	ids temp = mates[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <class _Traits> void mfHexaCell<_Traits>::setMateId(int index, ids cell MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 6));

	MF_LOCK(smutex);

	mates[index] = cell;

	MF_UNLOCK(smutex);
}

/*template <class _Traits> IDS mfHexaCell<_Traits>::getMateVertexId(ids vertex MF_DMUTEXV)
{
	for(int i = 0; i < 6; i++)
		if (getVertexId(i MF_MUTEXV) == vertex)
			return getMateId(i MF_MUTEXV);

	return -1;
}

template <class _Traits> IDS mfHexaCell<_Traits>::getVertexMateId(ids cell MF_DMUTEXV)
{
	for(int i = 0; i < 6; i++)
		if (getMateId(i MF_MUTEXV) == cell)
			return this->getVertexId(i MF_MUTEXV);

	return -1;
}*/

template <class _Traits> int mfHexaCell<_Traits>::getMateIndex(ids cell MF_DMUTEXV)
{
	for(int i = 0; i < 6; i++)
		if (getMateId(i MF_MUTEXV) == cell)
			return i;

	return -1;
}

template <class _Traits> void mfHexaCell<_Traits>::clearMates(MF_DMUTEX)
{
	for(int i = 0; i < 6; i++)
		setMateId(i,-1 MF_MUTEXV);
}

template <class _Traits> int mfHexaCell<_Traits>::getRightFaceIndex(ids index1, ids index2)
{
	MF_ASSERT( (index1 >= 0)&&(index1<=7) );
	MF_ASSERT( (index2 >= 0)&&(index2<=7) );
	MF_ASSERT( index1 != index2 );

	switch(index1)
	{
		case 0:
			if(index2 == 1)
				return 0;
			if(index2 == 3)
				return 4;
			if(index2 == 4)
				return 1;
			break;
		case 1:
			if(index2 == 0)
				return 1;
			if(index2 == 2)
				return 0;
			if(index2 == 5)
				return 2;
			break;
		case 2:
			if(index2 == 1)
				return 2;
			if(index2 == 3)
				return 0;
			if(index2 == 6)
				return 3;
			break;
		case 3:
			if(index2 == 0)
				return 0;
			if(index2 == 2)
				return 3;
			if(index2 == 7)
				return 4;
			break;
		case 4:
			if(index2 == 0)
				return 4;
			if(index2 == 5)
				return 1;
			if(index2 == 7)
				return 5;
			break;
		case 5:
			if(index2 == 1)
				return 1;
			if(index2 == 4)
				return 5;
			if(index2 == 6)
				return 2;
			break;
		case 6:
			if(index2 == 2)
				return 2;
			if(index2 == 5)
				return 5;
			if(index2 == 7)
				return 3;
			break;
		case 7:
			if(index2 == 3)
				return 3;
			if(index2 == 4)
				return 4;
			if(index2 == 6)
				return 5;
			break;
	}
	return -1;
}

template <class _Traits> int mfHexaCell<_Traits>::getLeftFaceIndex(ids index1, ids index2)
{
	MF_ASSERT( (index1 >= 0)&&(index1<=7) );
	MF_ASSERT( (index2 >= 0)&&(index2<=7) );
	MF_ASSERT( index1 != index2 );

	switch(index1)
	{
		case 0:
			if(index2 == 1)
				return 1;
			if(index2 == 3)
				return 0;
			if(index2 == 4)
				return 4;
			break;
		case 1:
			if(index2 == 0)
				return 0;
			if(index2 == 2)
				return 2;
			if(index2 == 5)
				return 1;
			break;
		case 2:
			if(index2 == 1)
				return 0;
			if(index2 == 3)
				return 3;
			if(index2 == 6)
				return 2;
			break;
		case 3:
			if(index2 == 0)
				return 4;
			if(index2 == 2)
				return 0;
			if(index2 == 7)
				return 3;
			break;
		case 4:
			if(index2 == 0)
				return 1;
			if(index2 == 5)
				return 5;
			if(index2 == 7)
				return 4;
			break;
		case 5:
			if(index2 == 1)
				return 2;
			if(index2 == 4)
				return 1;
			if(index2 == 6)
				return 5;
			break;
		case 6:
			if(index2 == 2)
				return 3;
			if(index2 == 5)
				return 2;
			if(index2 == 7)
				return 5;
			break;
		case 7:
			if(index2 == 3)
				return 4;
			if(index2 == 4)
				return 5;
			if(index2 == 6)
				return 3;
			break;
	}
	return -1;
}

template <class _Traits> int mfHexaCell<_Traits>::getFaceIndex(int v1, int v2, int v3)
{
	MF_ASSERT( (v1 >= 0)&&(v1<=7) );
	MF_ASSERT( (v2 >= 0)&&(v2<=7) );
	MF_ASSERT( (v3 >= 0)&&(v3<=7) );
	MF_ASSERT( (v1 != v2)&&(v1 != v3)&&(v2 != v3) );

	// First search is in order of the face orientation
	switch(v1)
	{
		case 0:
			if(v2 == 1 && v3 == 5)
				return 1;
			if(v2 == 4 && v3 == 7)
				return 4;
			if(v2 == 3 && v3 == 2)
				return 0;
			break;
		case 1:
			if(v2 == 0 && v3 == 3)
				return 0;
			if(v2 == 5 && v3 == 4)
				return 1;
			if(v2 == 2 && v3 == 6)
				return 2;
			break;
		case 2:
			if(v2 == 1 && v3 == 0)
				return 0;
			if(v2 == 6 && v3 == 5)
				return 2;
			if(v2 == 3 && v3 == 7)
				return 3;
			break;
		case 3:
			if(v2 == 2 && v3 == 1)
				return 0;
			if(v2 == 7 && v3 == 6)
				return 3;
			if(v2 == 0 && v3 == 4)
				return 4;
			break;
		case 4:
			if(v2 == 0 && v3 == 1)
				return 1;
			if(v2 == 7 && v3 == 3)
				return 4;
			if(v2 == 5 && v3 == 6)
				return 5;
			break;
		case 5:
			if(v2 == 4 && v3 == 0)
				return 1;
			if(v2 == 1 && v3 == 2)
				return 2;
			if(v2 == 6 && v3 == 7)
				return 5;
			break;
		case 6:
			if(v2 == 5 && v3 == 1)
				return 2;
			if(v2 == 2 && v3 == 3)
				return 3;
			if(v2 == 7 && v3 == 4)
				return 5;
			break;
		case 7:
			if(v2 == 6 && v3 == 2)
				return 3;
			if(v2 == 3 && v3 == 0)
				return 4;
			if(v2 == 4 && v3 == 5)
				return 5;
			break;
	}
	//if not found in first search, do an un-ordered search
	switch(v1)
	{
		case 0:
			if(v2 == 1)
			{
				if(v3 == 2 || v3 == 3)
				return 0;
				if(v3 == 4)
				return 1;
			}
			if(v2 == 2)
			{
				if(v3 == 1 || v3 == 3)
				return 0;
			}
			if(v2 == 3)
			{
				if(v3 == 1)
				return 0;
				if(v3 == 4 || v3 == 7)
				return 4;
			}
			if(v2 == 4)
			{
				if(v3 == 1 || v3 == 5)
				return 1;
				if(v3 == 3)
				return 4;
			}
			if(v2 == 5)
			{
				if(v3 == 1 || v3 == 4)
				return 1;
			}
			if(v2 == 7)
			{
				if(v3 == 4 || v3 == 3)
				return 4;
			}
			break;
		case 1:
			if(v2 == 0)
			{
				if(v3 == 2)
				return 0;
				if(v3 == 5 || v3 == 4)
				return 1;
			}
			if(v2 == 2)
			{
				if(v3 == 0 || v3 == 3)
				return 0;
				if(v3 == 5)
				return 2;
			}
			if(v2 == 3)
			{
				if(v3 == 0 || v3 == 2)
				return 0;
			}
			if(v2 == 4)
			{
				if(v3 == 0 || v3 == 5)
				return 1;
			}
			if(v2 == 5)
			{
				if(v3 == 0)
				return 1;
				if(v3 == 2 || v3 == 6)
				return 2;
			}
			if(v2 == 6)
			{
				if(v3 == 2 || v3 == 5)
				return 2;
			}
			break;
		case 2:
			if(v2 == 0)
			{
				if(v3 == 1 || v3 == 3)
				return 0;
			}
			if(v2 == 1)
			{
				if(v3 == 3)
				return 0;
				if(v3 == 5 || v3 == 6)
				return 2;
			}
			if(v2 == 3)
			{
				if(v3 == 0 || v3 == 1)
				return 0;
				if(v3 == 6)
				return 3;
			}
			if(v2 == 5)
			{
				if(v3 == 1 || v3 == 6)
				return 2;
			}
			if(v2 == 6)
			{
				if(v3 == 1)
				return 2;
				if(v3 == 3 || v3 == 7)
				return 3;
			}
			if(v2 == 7)
			{
				if(v3 == 3 || v3 == 6)
				return 3;
			}
			break;
		case 3:
			if(v2 == 0)
			{
				if(v3 == 2 || v3 == 1)
				return 0;
				if(v3 == 7)
				return 4;
			}
			if(v2 == 1)
			{
				if(v3 == 0 || v3 == 2)
				return 0;
			}
			if(v2 == 2)
			{
				if(v3 == 0)
				return 0;
				if(v3 == 7 || v3 == 6)
				return 3;
			}
			if(v2 == 4)
			{
				if(v3 == 0 || v3 == 7)
				return 4;
			}
			if(v2 == 6)
			{
				if(v3 == 2 || v3 == 7)
				return 3;
			}
			if(v2 == 7)
			{
				if(v3 == 2)
				return 3;
				if(v3 == 0 || v3 == 4)
				return 4;
			}
			break;
		case 4:
			if(v2 == 0)
			{
				if(v3 == 5)
				return 1;
				if(v3 == 3 || v3 == 7)
				return 4;
			}
			if(v2 == 1)
			{
				if(v3 == 0 || v3 == 5)
				return 1;
			}
			if(v2 == 3)
			{
				if(v3 == 0 || v3 == 7)
				return 4;
			}
			if(v2 == 5)
			{
				if(v3 == 0 || v3 == 1)
				return 1;
				if(v3 == 7)
				return 5;
			}
			if(v2 == 6)
			{
				if(v3 == 5 || v3 == 7)
				return 5;
			}
			if(v2 == 7)
			{
				if(v3 == 0)
				return 4;
				if(v3 == 5 || v3 == 6)
				return 5;
			}
			break;
		case 5:
			if(v2 == 0)
			{
				if(v3 == 1 || v3 == 4)
				return 1;
			}
			if(v2 == 1)
			{
				if(v3 == 0 || v3 == 4)
				return 1;
				if(v3 == 6)
				return 2;
			}
			if(v2 == 2)
			{
				if(v3 == 1 || v3 == 6)
				return 2;
			}
			if(v2 == 4)
			{
				if(v3 == 1)
				return 1;
				if(v3 == 6 || v3 == 7)
				return 5;
			}
			if(v2 == 6)
			{
				if(v3 == 2 || v3 == 1)
				return 2;
				if(v3 == 4)
				return 5;
			}
			if(v2 == 7)
			{
				if(v3 == 4 || v3 == 6)
				return 5;
			}
			break;
		case 6:
			if(v2 == 1)
			{
				if(v3 == 2 || v3 == 5)
				return 2;
			}
			if(v2 == 2)
			{
				if(v3 == 1 || v3 == 5)
				return 2;
				if(v3 == 7)
				return 3;
			}
			if(v2 == 3)
			{
				if(v3 == 2 || v3 == 7)
				return 3;
			}
			if(v2 == 4)
			{
				if(v3 == 5 || v3 == 7)
				return 5;
			}
			if(v2 == 5)
			{
				if(v3 == 2)
				return 2;
				if(v3 == 4 || v3 == 7)
				return 5;
			}
			if(v2 == 7)
			{
				if(v3 == 2 || v3 == 3)
				return 3;
				if(v3 == 5)
				return 5;
			}
			break;
		case 7:
			if(v2 == 0)
			{
				if(v3 == 4 || v3 == 3)
				return 4;
			}
			if(v2 == 2)
			{
				if(v3 == 3 || v3 == 6)
				return 3;
			}
			if(v2 == 3)
			{
				if(v3 == 2 || v3 == 6)
				return 3;
				if(v3 == 4)
				return 4;
			}
			if(v2 == 4)
			{
				if(v3 == 0 || v3 == 3)
				return 4;
				if(v3 == 6)
				return 5;
			}
			if(v2 == 5)
			{
				if(v3 == 4 || v3 == 6)
				return 5;
			}
			if(v2 == 6)
			{
				if(v3 == 3)
				return 3;
				if(v3 == 4 || v3 == 5)
				return 5;
			}
			break;
	}

	return -1;
}

template <class _Traits> bool mfHexaCell<_Traits>::verticesAreAdjacent(ids index1, ids index2)
{
	MF_ASSERT( (index1 >= 0)&&(index1<=7) );
	MF_ASSERT( (index2 >= 0)&&(index2<=7) );
	MF_ASSERT( index1 != index2 );

	switch(index1)
	{
		case 0:
			if(index2 == 1)
				return true;
			if(index2 == 3)
				return true;
			if(index2 == 4)
				return true;
			break;
		case 1:
			if(index2 == 0)
				return true;
			if(index2 == 2)
				return true;
			if(index2 == 5)
				return true;
			break;
		case 2:
			if(index2 == 1)
				return true;
			if(index2 == 3)
				return true;
			if(index2 == 6)
				return true;
			break;
		case 3:
			if(index2 == 0)
				return true;
			if(index2 == 2)
				return true;
			if(index2 == 7)
				return true;
			break;
		case 4:
			if(index2 == 0)
				return true;
			if(index2 == 5)
				return true;
			if(index2 == 7)
				return true;
			break;
		case 5:
			if(index2 == 1)
				return true;
			if(index2 == 4)
				return true;
			if(index2 == 6)
				return true;
			break;
		case 6:
			if(index2 == 2)
				return true;
			if(index2 == 5)
				return true;
			if(index2 == 7)
				return true;
			break;
		case 7:
			if(index2 == 3)
				return true;
			if(index2 == 4)
				return true;
			if(index2 == 6)
				return true;
			break;
	}
	return false;
}


#undef IDS

}

#endif

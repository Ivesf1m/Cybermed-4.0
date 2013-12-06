#ifndef MFQUADCELL_H
#define MFQUADCELL_H

#include "mfMacros.h"
#include "mfCell.h"

namespace mf
{

#define IDS typename mfQuadCell<_Traits>::ids

/**
 *	@class		mfQuadCell
 *	@file		mfQuadCell.h
 *	@short
 *	Base class of the quadrilateral cell
 *
 *	_Traits must have typenames: ids
 *
 *	@author		Icaro da Cunha
 *	@version	1.0
 *	@date		2008, july
 */
template <class _Traits> class mfQuadCell : public mfCell<4,_Traits>
{
public:

	typedef typename _Traits ::ids ids;	/**< Id typename definition */

	/** Constructor */
	mfQuadCell();

	/** Destructor */
	virtual ~mfQuadCell();

	/**	Return the edge id of the specified index
	 *
	 *	\param index: position of edge
	 */
	ids getEdgeId(int index MF_DMUTEXVD);

	/** Define the edge id of the specified index
	 *
	 *	\param index: position of edge
	 *	\param vertex: the edge id
	 */
	void setEdgeId(int index, ids edge MF_DMUTEXVD);

	/**	Return the dimension of this cell
	 */
	static inline int getDimension(){ return 2;};

private:
	ids edges[4];	/**< Cell's edges ids */
	ids mates[3];     /**< Cell's face mate ids */
};

template <class _Traits> mfQuadCell<_Traits>::mfQuadCell()
{
#ifdef MF_THREADS
	pthread_mutex_lock(&this->smutex);
#endif

	for(int i = 0; i < 4; i++)
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

template <class _Traits> mfQuadCell<_Traits>::~mfQuadCell()
{
}

template <class _Traits> IDS mfQuadCell<_Traits>::getEdgeId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 4));

	MF_LOCK(smutex);

	ids temp = edges[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <class _Traits> void mfQuadCell<_Traits>::setEdgeId(int index, ids edge MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 4));

	MF_LOCK(smutex);

	edges[index] = edge;

	MF_UNLOCK(smutex);
}

#undef IDS

}

#endif

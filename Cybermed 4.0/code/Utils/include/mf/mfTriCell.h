#ifndef MFTRICELL_H
#define MFTRICELL_H

#include "mfMacros.h"
#include "mfCell.h"

namespace mf
{

#define IDS typename mfTriCell<_Traits>::ids

/**
 *	@class		mfTriCell
 *	@file		mfTriCell.h
 *	@short
 *	Base class of the triangle cell
 *
 *	_Traits must have typenames: ids
 *
 *	@author		Mario Lizier and Icaro da Cunha
 *	@version	1.0
 *	@date		2008, july
 */
template <class _Traits> class mfTriCell : public mfCell<3,_Traits>
{
public:
	typedef typename _Traits ::ids ids;	/**< Id typename definition */

	/** Constructor */
	mfTriCell();

	/** Destructor */
	virtual ~mfTriCell();

	/**	Return the edge id of the specified index
	 *
	 * 	\param index: position of edge
	 */
	ids getEdgeId(int index MF_DMUTEXVD);

	/** Define the edge id of the specified index
	 *
	 * 	\param index: position of edge
	 * 	\param vertex: the edge id
	 */
	void setEdgeId(int index, ids edge MF_DMUTEXVD);

private:
	ids edges[3];	/**< Cell's edges ids */
	//ids mates[3];     /**< Cell's face mate ids */
};

template <class _Traits> mfTriCell<_Traits>::mfTriCell()
{
#ifdef MF_THREADS
	pthread_mutex_lock(&this->smutex);
#endif

	for(int i = 0; i < 3; i++)
	{
		edges[i] = -1;
	}
	/*for(int i = 0; i < 3; i++)
	{
        mates[i] = -1;
    }*/

#ifdef MF_THREADS
	pthread_mutex_unlock(&this->smutex);
#endif
}

template <class _Traits> mfTriCell<_Traits>::~mfTriCell()
{
}

template <class _Traits> IDS mfTriCell<_Traits>::getEdgeId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 3));

	MF_LOCK(smutex);

	ids temp = edges[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <class _Traits> void mfTriCell<_Traits>::setEdgeId(int index, ids edge MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < 3));

	MF_LOCK(smutex);

	edges[index] = edge;

	MF_UNLOCK(smutex);
}

#undef IDS

}

#endif

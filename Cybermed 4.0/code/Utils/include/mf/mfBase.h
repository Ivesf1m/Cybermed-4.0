#ifndef MFBASE_H
#define MFBASE_H

#include "mfMacros.h"

namespace mf
{

#define IDS typename mfBase<_Traits>::ids

/**
 *	@class		mfBase
 *	@file		mfBase.h
 *	@short
 *	Base Class
 *	Base Class for all elements of mesh
 *
 *	_Traits must have ids typename
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfBase
{
public:

	typedef typename _Traits::ids ids;	/**< Id typename definition*/

	/** Constructor
	 *
	 *  Initialize the mutex;
	 *  Set this element as out of mesh
	 */
	mfBase();

	/** Destructor
	 *
	 *  Destroy mutex
	 */
	virtual ~mfBase();

	/** Check if this element is in mesh
	 *
	 *  \return true, if this element is in mesh
	 */
	bool inMesh(MF_DMUTEXD);

	/** Set if this element is in mesh
	 *
	 *  \param value: the status of this element
	 */
	void setInMesh(bool value MF_DMUTEXVD);

	/** Set the next free element in vector
	 *
	 *  This position is stored in same place of flags
	 *
	 *  \param position: the index of next free position
	 */
	void setPosition(ids position MF_DMUTEXVD);

	/** Get the next free element
	 *
	 *  \return Return the next free element, if was not define, returned value is negative.
	 */
	ids  getPosition(MF_DMUTEXD);


#ifdef MF_THREADS

	/** Lock the element mutex
	 *
	 *  Used with MF_THREADS define
	 */
	void lock();

	/** Unlock the element mutex
	 *
	 *  Used with MF_THREADS define
	 */
	void unlock();

	/** Try lock the element mutex
	 *
	 *  Used with MF_THREADS define
	 */
	int  trylock();

#endif

protected:

    MF_FLAGS_TYPE flags; /**< Flag type definition */

#ifdef MF_THREADS
	pthread_mutex_t smutex; /**< Mutex thread definition */
#endif

};

template <class _Traits> mfBase<_Traits>::mfBase()
{
#ifdef MF_THREADS
	pthread_mutex_init(&smutex,0);
	pthread_mutex_lock(&smutex);
#endif
	flags = (MF_FLAGS_TYPE) 0;
	
#ifdef MF_THREADS
	pthread_mutex_unlock(&smutex);
#endif
}

template <class _Traits> mfBase<_Traits>::~mfBase()
{
#ifdef MF_THREADS
	pthread_mutex_destroy(&smutex);
#endif
}

template <class _Traits> bool mfBase<_Traits>::inMesh(MF_DMUTEX)
{
	MF_LOCK(smutex);
	
	bool temp = (flags & (1 << MF_FLAGS_INMESH)) != 0;
	
	MF_UNLOCK(smutex);
	
	return temp;
}

template <class _Traits> void mfBase<_Traits>::setInMesh(bool value MF_DMUTEXV)
{
	MF_LOCK(smutex);
	
	if(value)
		flags |= (1 << MF_FLAGS_INMESH);
	else
		flags &= ~(1 << MF_FLAGS_INMESH);
	
	MF_UNLOCK(smutex);
}

template <class _Traits> void mfBase<_Traits>::setPosition(ids position MF_DMUTEXV)
{
	MF_LOCK(smutex);

	flags = position;

	MF_UNLOCK(smutex);
}

template <class _Traits> IDS mfBase<_Traits>::getPosition(MF_DMUTEX)
{
	MF_LOCK(smutex);

	ids temp = flags;

	MF_UNLOCK(smutex);

	return temp;
}


#ifdef MF_THREADS
template <class _Traits> void mfBase<_Traits>::lock()
{
	pthread_mutex_lock(&smutex);
}

template <class _Traits> void mfBase<_Traits>::unlock()
{
	pthread_mutex_unlock(&smutex);
}

template <class _Traits> int mfBase<_Traits>::trylock()
{
	return pthread_mutex_trylock(&smutex);
}
#endif

#undef IDS

}

#endif

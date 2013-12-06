#ifndef MFFACE_H
#define MFFACE_H

#include "mfMacros.h"
#include "mfBase.h"

namespace mf
{

//#define IDS typename mfCell<size,_Traits>::ids

/**
 *	@class		mfFace
 *	@file		mfFace.h
 *	@short
 *	Base class of the face
 *
 *	@author		Icaro da Cunha
 *	@version	1.0
 *	@date		2008, july
 */
template <class _Traits> class mfFace : public mfBase<_Traits>
{
public:

	//typedef typename _Traits ::ids ids; /**< Id typename definition */

	/**	Constructor
	 *
	 *	Initialize vertices and mates ids
	 */
	mfFace();

	/**	Destructor
	 */
	virtual ~mfFace();

private:

};

template <class _Traits> mfFace<_Traits>::mfFace()
{
}

template <class _Traits> mfFace<_Traits>::~mfFace()
{
}

}

#endif

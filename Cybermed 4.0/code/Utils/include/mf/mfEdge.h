#ifndef MFEDGE_H
#define MFEDGE_H

#include "mfMacros.h"
#include "mfBase.h"

namespace mf
{

//#define IDS typename mfCell<size,_Traits>::ids

/**
 *	@class		mfEdge
 *	@file		mfEdge.h
 *	@short
 *	Base class of the edge
 *
 *	@author		Icaro da Cunha
 *	@version	1.0
 *	@date		2008, july
 */
template <class _Traits> class mfEdge : public mfBase<_Traits>
{
public:

	//typedef typename _Traits	::ids ids;

	/**	Constructor
	 *
	 *	Initialize vertices and mates ids
	 */
	mfEdge();

	/**	Destructor
	 */
	virtual ~mfEdge();

private:

	//ids vertices[2];
};

template <class _Traits> mfEdge<_Traits>::mfEdge()
{
}

template <class _Traits> mfEdge<_Traits>::~mfEdge()
{
}

}

#endif

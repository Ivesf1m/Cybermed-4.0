#ifndef MFSING_H
#define MFSING_H

#include "mfMacros.h"

namespace mf
{

#define SSING typename mfSing<_Traits>::sSing
#define IDS typename mfSing<_Traits>::ids

/**
 *	@class		mfSing
 *	@file		mfSing.h
 *	@short
 *	Base Class of singular component in vertex
 *
 *	_Traits must have: ids, sSing
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfSing
{
public:

	typedef typename _Traits::ids ids;	/**< Id typename definition */
	typedef mfSing<_Traits> sSing;		/**< Singular typename definition */

	/** Constructor */
	mfSing();

	/** Destrutor */
	~mfSing();

	/**	Return the next singular component
	 *
	 *	\return Instance of the next singular component
	 */
	sSing* getNext();

	/**	Define the next singular component
	 *
     *	\param next: the next component on the singular list
	 */
	void setNext(sSing* _next);
	
	/**	Return the cell of this singular component
	 *
	 *	\return ID of the cell of the singular component
	 */
	ids getCell();

	/**	Define the cell of this singular component
	 *
     *	\param cell: ID of the cell of the singular component
	 */
	void setCell(ids _cell);	

private:
	ids cell;	/**< Cell id */

	sSing *next;	/**< Next singular component */
};

template <class _Traits> mfSing<_Traits>::mfSing()
{
	next = NULL;
}

template <class _Traits> mfSing<_Traits>::~mfSing()
{
}

template <class _Traits> SSING* mfSing<_Traits>::getNext()
{
	return next;
}

template <class _Traits> void mfSing<_Traits>::setNext(sSing* _next)
{
	next = _next;
}

template <class _Traits> IDS mfSing<_Traits>::getCell()
{
	return cell;
}

template <class _Traits> void mfSing<_Traits>::setCell(ids _cell)
{
	MF_ASSERT(_cell >= 0);
	
	cell = _cell;
}

#undef IDS
#undef SSING

}

#endif

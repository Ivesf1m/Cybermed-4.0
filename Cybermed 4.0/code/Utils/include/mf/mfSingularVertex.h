#ifndef MFSINGULARVERTEX_H
#define MFSINGULARVERTEX_H

#include "mfMacros.h"
#include "mfVertex.h"
#include "mfSing.h"

namespace mf
{

#define SPACE typename mfSingularVertex<size,_Traits>::space
#define SSING typename mfSingularVertex<size,_Traits>::sSing
#define IDS typename mfSingularVertex<size,_Traits>::ids

/** Base class of singular vertex
 *
 *  _Traits must have typenames: ids, space, sSing
 *
/**
 *	@class		mfSingularVertex
 *	@file		mfSingularVertex.h
 *	@short
 *	Base class of the singular vertex
 *
 *  _Traits must have typenames: ids, space, sSing
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <int size, class _Traits> class mfSingularVertex : public mfVertex<size,_Traits>
{
public:

	typedef typename _Traits::ids ids;	/**< Id typename definition*/
	typedef typename _Traits::space space;	/**< Space typename definition*/
	typedef mfSing<_Traits> sSing;		/**< Singular typename definition*/

	/** Constructor */
	mfSingularVertex();

	/** Destructor */
	~mfSingularVertex();

	/** Return true if this vertex is singular
	 */
	bool isSingular(MF_DMUTEXD);

	/** Return the number of sSing (number of singular components)
	 */
	int	getNumberOfSings(MF_DMUTEXD);

	/** Return the first cell of each singular component
	 * 
	 *  \param pos: index of singular component
	 *  \return one cell of 'pos' singular component
	 */
	ids	getSingCell(int pos = 0 MF_DMUTEXVD);

	/** Set a singular component
	 *
	 *  \param	pos: index of singular component
	 *  \param	cell: cell to be set
	 *  \return true if 'pos' exist
	 * 
	 *  For add a singular component use addSing
	 */
	bool setSingCell(int pos, ids cell MF_DMUTEXVD);

	/** Add a singular component
	 * 
	 *  \param cell: cell to be add
	 *  \return index of added singular component
	 */
	int addSing(ids cell MF_DMUTEXVD);

	/** Delete a singular component
	 * 
	 *  \param pos: index of singular component
	 *  \return true if successful
	 */
	bool delSing(int pos MF_DMUTEXVD);

	/** Delete all singular components
	 */
	void clearSings(MF_DMUTEXD);

	/** Return the position of the specified cell in list of singular components
	 */
	int inSings(ids cell MF_DMUTEXVD);

	/** Return the first singular component
	 */
	sSing* getSing(MF_DMUTEXD);

private:

	sSing* sings;		/**< Singulars list */
};

template <int size, class _Traits> mfSingularVertex<size,_Traits>::mfSingularVertex()
{
#ifdef MF_THREADS
	pthread_mutex_lock(&this->smutex);
#endif

	sings = NULL;

#ifdef MF_THREADS
	pthread_mutex_unlock(&this->smutex);
#endif
}

template <int size, class _Traits> mfSingularVertex<size,_Traits>::~mfSingularVertex()
{
	clearSings();
}

template <int size, class _Traits> bool mfSingularVertex<size,_Traits>::isSingular(MF_DMUTEX)
{
	return (getNumberOfSings(MF_MUTEX) >= 2);
}

template <int size, class _Traits> int mfSingularVertex<size,_Traits>::getNumberOfSings(MF_DMUTEX)
{
	MF_LOCK(smutex);
	
	sSing* s = sings;

	int i = 0;
	
	while (s)
	{
		s = s->getNext();
		i++;
	}
	
	MF_UNLOCK(smutex);

	return i;
}

template <int size, class _Traits> IDS mfSingularVertex<size,_Traits>::getSingCell(int pos MF_DMUTEXV)
{
	MF_ASSERT(pos >= 0);

	MF_LOCK(smutex);
	sSing* s = sings;
	ids c = -1;

	int i = 0;
	
	while ((s)&&(i < pos))
	{
		s = s->getNext();
		i++;
	}
	
	if (s)
		c = s->getCell();

	MF_UNLOCK(smutex);
	
	return c;
}

template <int size, class _Traits> bool mfSingularVertex<size,_Traits>::setSingCell(int pos, ids cell MF_DMUTEXV)
{
	MF_ASSERT(pos >= 0);
	MF_ASSERT(cell >= 0);

	MF_LOCK(smutex);
	sSing* s = sings;

	int i = -1;

	while ((s)&&(i < pos))
	{
		i++;
		if (i == pos)
		{
			s->setCell(cell);

			MF_UNLOCK(smutex);
			return true;
		}
		s = s->getNext();
	}

	MF_UNLOCK(smutex);

	return false;
}

template <int size, class _Traits> int mfSingularVertex<size,_Traits>::addSing(ids cell MF_DMUTEXV)
{
	MF_ASSERT(cell >= 0);

	MF_LOCK(smutex);
	sSing *s = sings, *ss = NULL;
	bool sair = false;
	int pos = 0;

	if(s)
	{
		while(!sair)
		{
			if(s->getCell() == cell)
				sair = true;
			else
			{
				if(!s->getNext())
				{
					ss = new sSing();
					MF_ASSERT(ss);

					s->setNext(ss);
					sair = true;
				}
				s = s->getNext();
				pos++;
			}
		}
	}
	else
	{
		ss = new sSing();
		MF_ASSERT(ss);
		sings = ss;
	}

	if (ss != NULL)
		ss->setCell(cell);

	MF_UNLOCK(smutex);

	return pos;
}

template <int size, class _Traits> bool mfSingularVertex<size,_Traits>::delSing(int pos MF_DMUTEXV)
{
	MF_ASSERT(pos >= 0);

	MF_LOCK(smutex);
	sSing* s = sings;
	sSing* ant = NULL;

	int i = -1;

	while ((s)&&(i < pos))
	{
		i++;
		if (i == pos)
		{
			if(ant)
				ant->setNext(s->getNext());
			else
				sings = s->getNext();

			delete s;
			MF_UNLOCK(smutex);

			return true;
		}
		ant = s;
		s = s->getNext();
	}

	MF_UNLOCK(smutex);
	return false;
}

template <int size, class _Traits> void mfSingularVertex<size,_Traits>::clearSings(MF_DMUTEX)
{
#ifdef MF_THREADS
	if(mutex)
		MF_LOCK(smutex);
#endif
	
	for(int i = (getNumberOfSings(MF_MUTEXFALSE)-1); i >=0; i--)
		delSing(i MF_MUTEXFALSEV);
	
#ifdef MF_THREADS
	if(mutex)
		MF_UNLOCK(smutex);
#endif
}

template <int size, class _Traits> SSING* mfSingularVertex<size,_Traits>::getSing(MF_DMUTEX)
{
	MF_LOCK(smutex);
	
	sSing* s = sings;
	
	MF_UNLOCK(smutex);

	return s;
}

template <int size, class _Traits> int mfSingularVertex<size,_Traits>::inSings(ids cell MF_DMUTEXV)
{
	MF_LOCK(smutex);

	sSing* s = sings;
	int i = 0;

	while ((s)&&(s->getCell() != cell))
	{
		s = s->getNext();
		i++;
	}

	MF_UNLOCK(smutex);

	if(s)
		return i;
	else
		return (-1);
}

//template <int size, class _Traits> void mfSingularVertex<size,_Traits>::addSing( sSing *s MF_DMUTEXD)
//{
//	MF_LOCK(smutex);
//
//	sSing *temp = sings;
//
//	if( temp )
//	{
//		while( temp->getNext() )
//			temp = temp->getNext();
//
//		temp->setNext( s );
//	}
//	else
//		sings = s;	
//
//	MF_UNLOCK(smutex);	
//}

#undef SPACE
#undef SSING
#undef IDS

}

#endif

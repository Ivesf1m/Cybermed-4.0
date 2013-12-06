#ifndef MFCELLSITERATOR_H
#define MFCELLSITERATOR_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfIterator.h"

namespace mf
{

#define SCELL typename mfCellsIterator<_Traits>::sCell
#define IDS typename mfCellsIterator<_Traits>::ids

/**
 *	@class		mfCellsIterator
 *	@file		mfCellsIterator.h
 *	@short
 *	Cell iterator class
 *
 *  Iterator for the meshe's cell vector
 *
 *	_Traits must have typenames: ids, sCell, sMesh
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfCellsIterator : public mfIterator<_Traits>
{
public:
	typedef typename _Traits::sCell 	sCell;	/**< Cell typename definition*/
	typedef typename _Traits::ids 		ids;	/**< Id typename definition*/
	typedef typename _Traits::sMesh		sMesh;	/**< Mesh typename definition*/

	/** Constructor */
	mfCellsIterator(sMesh *_mesh);

	/** Destructor */
	~mfCellsIterator();

	bool initialize(ids init = 0);

	bool finish();
	bool notFinish();

	bool operator++();
	bool operator--();

	sCell *operator->();
	sCell *operator*();

	ids operator&();

private:
	ids iatu;	/**< Current cell id */
	ids iinit;	/**< Initial cell id */
	sCell *atu;	/**< Current cell instance */

	int status;	/**< Iterator status */
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior
};

template <class _Traits> mfCellsIterator<_Traits>::mfCellsIterator(sMesh *_mesh)
: mfIterator<_Traits>(_mesh)
{
	iatu = iinit = -1;
	status = 0;
}

template <class _Traits> mfCellsIterator<_Traits>::~mfCellsIterator()
{
}

template <class _Traits> bool mfCellsIterator<_Traits>::initialize(ids init)
{
	MF_ASSERT(init >= 0);

	iinit = init;

	status = 1;
	
	iatu = -1;
	
	atu = NULL;
	
	return ++(*this);
}

template<class _Traits> bool mfCellsIterator<_Traits>::operator++()
{

	if(status == 1)
	{
		if( this->mesh->getNumberOfCells() > 0 )
		{
			if(iatu < 0)
			{
				if( iinit > this->mesh->getCellMaxId() )
				{
					status = 3;
					return false;
				};

				iatu = iinit;
			}
			else
				iatu++;

			atu = this->mesh->getCell(iatu);

			while( (!atu->inMesh()) && (iatu + 1 <= this->mesh->getCellMaxId()) )
			{
				iatu++;
				atu = this->mesh->getCell(iatu);
			}
			
			if ( !atu->inMesh() )
			{
				status = 3;
				return false;
			}
			
			MF_ASSERT( atu );

			return true;
		}
		else
		{
			status = 3;
			return false;
		}
	}
	else
		return false;
}

template<class _Traits> bool mfCellsIterator<_Traits>::operator--()
{
	if(status == 1)
	{
		if( this->mesh->getNumberOfCells() > 0 )
		{
			if(iatu < 0)
			{
				if( iinit > this->mesh->getCellMaxId() )
				{
					// status = 3;
					return false;
				};
				
				iatu = iinit;

			}
			else
			{
				if( iatu == 0 )
				{
					status = 2;
					return false;
				}
				else
					iatu--;
			}

			atu = this->mesh->getCell(iatu);

			while( (!atu->inMesh()) && (iatu - 1 >= 0) )
			{
				iatu--;
				atu = this->mesh->getCell(iatu);
			}
			
			if ( !atu->inMesh() )
			{
				status = 2;
				return false;
			}
			
			MF_ASSERT( atu );

			return true;
		}
		else
		{
			status = 2;
			return false;
		}
	}
	else
		return false;
}

template<class _Traits> SCELL* mfCellsIterator<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* mfCellsIterator<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS mfCellsIterator<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool mfCellsIterator<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool mfCellsIterator<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SCELL
#undef IDS

}

#endif

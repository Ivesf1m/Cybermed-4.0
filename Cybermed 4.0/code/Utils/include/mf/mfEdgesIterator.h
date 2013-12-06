#ifndef MFEDGESITERATOR_H
#define MFEDGESITERATOR_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfIterator.h"

namespace mf
{

#define SEDGE typename mfEdgesIterator<_Traits>::sEdge
#define IDS typename mfEdgesIterator<_Traits>::ids

/**
 *	@class		mfEdgesIterator
 *	@file		mfEdgesIterator.h
 *	@short
 *	Edge iterator class
 *
 *  Iterator for the meshe's edge vector
 *
 *	_Traits must have typenames: ids, sEdge, sMesh
 *
 *	@author		Icaro da Cunha
 *	@version	1.0
 *	@date		2008, july
 */
template <class _Traits> class mfEdgesIterator : public mfIterator<_Traits>
{
public:
	typedef typename _Traits::sEdge 	sEdge;	/**< Edge typename definition*/
	typedef typename _Traits::ids 		ids;	/**< Id typename definition*/
	typedef typename _Traits::sMesh		sMesh;	/**< Mesh typename definition*/

	/** Constructor */
	mfEdgesIterator(sMesh *_mesh);

	/** Destructor */
	~mfEdgesIterator();

	bool initialize(ids init = 0);

	bool finish();
	bool notFinish();

	bool operator++();
	bool operator--();

	sEdge *operator->();
	sEdge *operator*();

	ids operator&();

private:

	ids iatu;	/**< Current edge id */
	ids iinit;	/**< Initial edge id */
	sEdge *atu;	/**< Current edge instance */

	int status;	/**< Iterator status */
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior
};

template <class _Traits> mfEdgesIterator<_Traits>::mfEdgesIterator(sMesh *_mesh)
: mfIterator<_Traits>(_mesh)
{
	iatu = iinit = -1;
	status = 0;
}

template <class _Traits> mfEdgesIterator<_Traits>::~mfEdgesIterator()
{
}

template <class _Traits> bool mfEdgesIterator<_Traits>::initialize(ids init)
{
	MF_ASSERT(init >= 0);

	iinit = init;

	status = 1;

	iatu = -1;

	atu = NULL;

	return ++(*this);
}

template<class _Traits> bool mfEdgesIterator<_Traits>::operator++()
{
	if(status == 1)
	{
		if(this->mesh->getNumberOfEdges() > 0)
		{
			if(iatu < 0)
			{
				if(iinit > this->mesh->getEdgeMaxId())
				{
					status = 3;
					return false;
				}

				iatu = iinit;
			}
			else
				iatu++;

			atu = this->mesh->getEdge(iatu);

			while((!atu->inMesh()) && (iatu + 1 <= this->mesh->getEdgeMaxId()))
			{
				iatu++;
				atu = this->mesh->getEdge(iatu);
			}

			if(!atu->inMesh())
			{
				status = 3;
				return false;
			}

			MF_ASSERT(atu);

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

template<class _Traits> bool mfEdgesIterator<_Traits>::operator--()
{
	if(status == 1)
	{
		if(this->mesh->getNumberOfEdges() > 0)
		{
			if(iatu < 0)
			{
				if(iinit > this->mesh->getEdgeMaxId())
				{
					// status = 3;
					return false;
				}

				iatu = iinit;
			}
			else
			{
				if(iatu == 0)
				{
					status = 2;
					return false;
				}
				else
					iatu--;
			}

			atu = this->mesh->getEdge(iatu);

			while((!atu->inMesh()) && (iatu - 1 >= 0))
			{
				iatu--;
				atu = this->mesh->getEdge(iatu);
			}

			if(!atu->inMesh())
			{
				status = 2;
				return false;
			}

			MF_ASSERT(atu);

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

template<class _Traits> SEDGE* mfEdgesIterator<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SEDGE* mfEdgesIterator<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS mfEdgesIterator<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool mfEdgesIterator<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool mfEdgesIterator<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SEDGE
#undef IDS

}

#endif

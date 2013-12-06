#ifndef MFVERTICESITERATOR_H
#define MFVERTICESITERATOR_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfIterator.h"

namespace mf
{

#define SVERTEX typename mfVerticesIterator<_Traits>::sVertex
#define IDS typename mfVerticesIterator<_Traits>::ids

/**
 *	@class		mfVerticesIterator
 *	@file		mfVerticesIterator.h
 *	@short
 *	Vertex iterator class
 *
 *  Iterator for the meshe's vertex vector
 *
 *	_Traits must have typenames: ids, sVertex, sMesh
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfVerticesIterator : public mfIterator<_Traits>
{
public:
	typedef typename _Traits::sVertex 	sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::ids 		ids;		/**< Id typename definition */
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition */

	/** Construtor */
	mfVerticesIterator(sMesh *_mesh);
	
	/** Destrutor */
	~mfVerticesIterator();
	
	/** Initializes the iterator at a determined position
     *
     * \param init: initial position of the iterator (0 by default)
     * \return true if the iterator is correctly initialized
     * */
    bool initialize(ids init = 0);

	/** Determines if iterator is at the end of the vertex vector
     * 
     */
    bool finish();
	
    /** Determines if iterator isn't at the end of the vertex vector
     *
     */
	bool notFinish();
	
	bool operator++();
	bool operator--();

	sVertex *operator->();
	sVertex *operator*();

	/** Operator that returns the id of the current vertex
     *
     */
    ids operator&();

private:
	
	ids iatu;	/**< Current vertex id */
	ids iinit;	/**< Initial vertex id */
	sVertex *atu;	/**< Current vertex instance */

	int status;	/**< Iterator status */
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior
};

template <class _Traits> mfVerticesIterator<_Traits>::mfVerticesIterator(sMesh *_mesh)
: mfIterator<_Traits>(_mesh)
{
	iatu = iinit = -1;
	status = 0;
}

template <class _Traits> mfVerticesIterator<_Traits>::~mfVerticesIterator()
{
}

template <class _Traits> bool mfVerticesIterator<_Traits>::initialize(ids init)
{
	MF_ASSERT(init >= 0);
	
	iinit = init;

	status = 1;
	
	iatu = -1;
	
	atu = NULL;
	
	return ++(*this);
}

template<class _Traits> bool mfVerticesIterator<_Traits>::operator++()
{

	if(status == 1)
	{
		if( this->mesh->getNumberOfVertices() > 0 )
		{
			if(iatu < 0)
			{
				if(iinit < 0)
					iinit = 0;
				else
					if( iinit > this->mesh->getVertexMaxId() )
					{
						status = 3;
						return false;
					};
				
				iatu = iinit;

			}
			else
				iatu++;

			atu = this->mesh->getVertex(iatu);

			while( (!atu->inMesh()) && (iatu + 1 <= this->mesh->getVertexMaxId()) )
			{
				iatu++;
				atu = this->mesh->getVertex(iatu);
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

template<class _Traits> bool mfVerticesIterator<_Traits>::operator--()
{

	if(status == 1)
	{
		if( this->mesh->getNumberOfVertices() > 0 )
		{
			if(iatu < 0)
			{
				if(iinit < 0)
					iinit = this->mesh->getVertexMaxId();
				else
					if( iinit > this->mesh->getVertexMaxId() )
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

			atu = this->mesh->getVertex(iatu);

			while( (!atu->inMesh()) && (iatu - 1 >= 0) )
			{
				iatu--;
				atu = this->mesh->getVertex(iatu);
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

template<class _Traits> SVERTEX* mfVerticesIterator<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SVERTEX* mfVerticesIterator<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS mfVerticesIterator<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool mfVerticesIterator<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool mfVerticesIterator<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SVERTEX
#undef IDS

}

#endif

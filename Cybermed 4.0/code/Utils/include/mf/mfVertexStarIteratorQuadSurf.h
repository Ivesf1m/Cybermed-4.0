#ifndef MFVERTEXSTARITERATORQUADSURF_H
#define MFVERTEXSTARITERATORQUADSURF_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfSing.h"
#include "mfIterator.h"
#include "mfList.h"

namespace mf
{

#define SCELL typename mfVertexStarIteratorQuadSurf<_Traits>::sCell
#define IDS typename mfVertexStarIteratorQuadSurf<_Traits>::ids

template <class _Traits> class mfVertexStarIteratorQuadSurf : public mfIterator<_Traits>
{
public:
	typedef typename _Traits::sCell 	sCell;		/**< Cell typename definition*/
	typedef typename _Traits::sVertex 	sVertex;	/**< Vertex typename definition*/
	typedef typename _Traits::ids 		ids;		/**< Id typename definition*/
	typedef mfSing<_Traits>			sSing;		/**< Singular typename definition*/
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition*/

	/** Construtor */
	mfVertexStarIteratorQuadSurf(sMesh *_mesh);

	/** Destrutor */
	~mfVertexStarIteratorQuadSurf();

	bool initialize(ids init);

	bool finish();
	bool notFinish();

	bool operator++();

	sCell *operator->();
	sCell *operator*();

	ids operator&();

private:
	ids iatu;		/**< Current cell id */
	ids iinit;		/**< Initial cell id */
	ids iv;			/**< Id of vertex center to the star iteration */
	sCell *atu;		/**< Current cell instance */
	sVertex *v;		/**< Instance of vertex center to the star iteration */

	mfList<ids> lista;	/**< List of cells to which the center vertex belongs to */
	mfList<ids> flags;	/**< List of flag cells to which the center vertex belongs to */

	int is;			/**< Current singular id */

	int status;		/**< Iterator status */
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior

	/** Adds neighbor of the current cell that have the center vertex of the iteration */
	void addNeighbor();
};

template <class _Traits> mfVertexStarIteratorQuadSurf<_Traits>::mfVertexStarIteratorQuadSurf(sMesh *_mesh)
: mfIterator<_Traits>(_mesh)
{
	is = iatu = iinit = iv = -1;
	status = 0;
	v = NULL;
}

template <class _Traits> mfVertexStarIteratorQuadSurf<_Traits>::~mfVertexStarIteratorQuadSurf()
{
}

template <class _Traits> bool mfVertexStarIteratorQuadSurf<_Traits>::initialize(ids init)
{
	MF_ASSERT(init >= 0);

	iv = init;
	v = this->mesh->getVertex(iv);

	status = 1;

	MF_ASSERT(v->inMesh());

	iatu = iinit = is = -1;

	atu = NULL;

	lista.clear();
	flags.clear();

	return ++(*this);
}

template<class _Traits> bool mfVertexStarIteratorQuadSurf<_Traits>::operator++()
{
	if(status == 1)
	{
		if(iatu < 0)
		{
			if(is < 0)
			{
				is = 0;
				iatu = v->getSingCell(is);

				MF_ASSERT(iatu >= 0);

				atu = this->mesh->getCell(iatu);
				MF_ASSERT( (atu) && (atu->inMesh()) );

				flags.insert(iatu);

				addNeighbor();

				iinit = iatu;
			}
		}
		else
		{
			MF_ASSERT( atu->getVertexIndex(iv) >= 0);

			if(lista.empty())
			{
				is++;
				iatu = v->getSingCell(is);

				if(iatu >= 0)
				{
					//MF_ASSERT(!flags.inList(iatu));
					lista.insert(iatu);
					flags.insert(iatu);
				}
				else
				{
					atu = NULL;
					iatu = -1;
					status = 3;
					return false;
				}
			}

			iatu = lista.first();
			lista.erase(0);

			atu = this->mesh->getCell(iatu);
			MF_ASSERT( (atu) && (atu->inMesh()) );

			addNeighbor();
		}

		return true;
	}
	else
		return false;
}

template<class _Traits> void mfVertexStarIteratorQuadSurf<_Traits>::addNeighbor()
{
	ids temp;

	temp = atu->getMateId((atu->getVertexIndex(iv)+3)%4);
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}
	temp = atu->getMateId(atu->getVertexIndex(iv));
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}

	MF_ASSERT( atu->getVertexIndex(iv) >= 0);
}

template<class _Traits> SCELL* mfVertexStarIteratorQuadSurf<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* mfVertexStarIteratorQuadSurf<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS mfVertexStarIteratorQuadSurf<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool mfVertexStarIteratorQuadSurf<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool mfVertexStarIteratorQuadSurf<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SCELL
#undef IDS

}

#endif

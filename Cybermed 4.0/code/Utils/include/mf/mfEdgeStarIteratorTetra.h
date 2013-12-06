#ifndef MFEDGESTARITERATORTETRA_H
#define MFEDGESTARITERATORTETRA_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfSing.h"
#include "mfIterator.h"
#include "mfList.h"

namespace mf
{

#define SCELL typename mfEdgeStarIteratorTetra<_Traits>::sCell
#define IDS typename mfEdgeStarIteratorTetra<_Traits>::ids

template <class _Traits> class mfEdgeStarIteratorTetra : public mfIterator<_Traits>
{
public:

	typedef typename _Traits::sCell 	sCell;
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::ids 		ids;

	typedef mfSing<_Traits>			sSing;
	typedef typename _Traits::sMesh		sMesh;

	/** Construtor */
	mfEdgeStarIteratorTetra(sMesh *_mesh);

	/** Destrutor */
	~mfEdgeStarIteratorTetra();

	bool initialize(ids idcell, int index1, int index2);

	bool finish();
	bool notFinish();

	bool operator++();

	sCell *operator->();
	sCell *operator*();

	ids operator&();
	
	int getV1Index();
	int getV2Index();

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
	
	ids idv1, idv2;

    int ie1, ie2;

	int iEdge1, iEdge2;

    int orientationStatus;

	void addNeighbor();
};

template <class _Traits> mfEdgeStarIteratorTetra<_Traits>::mfEdgeStarIteratorTetra(sMesh *_mesh)
: mfIterator<_Traits>(_mesh)
{
	is = iatu = iinit = iv = -1;
	ie1 = ie2 = -1;
	status = 0;
	v = NULL;
}

template <class _Traits> mfEdgeStarIteratorTetra<_Traits>::~mfEdgeStarIteratorTetra()
{
}

template <class _Traits> bool mfEdgeStarIteratorTetra<_Traits>::initialize(ids idcell, int index1, int index2)
{
	MF_ASSERT(idcell >= 0);
	MF_ASSERT((index1 >= 0)&&(index1 <= 3));
	MF_ASSERT((index2 >= 0)&&(index2 <= 3));

	ie1 = index1;
	iEdge1 = ie1;
	ie2 = index2;
	iEdge2 = ie2;
	iinit = idcell;
	//is = -1;

	//cout << "is " << is << endl;
	//cout << "iinit " << iinit << " ie1 "  << ie1 << " ie2 "  << ie2 << endl;

	orientationStatus = 1;

	status = 1;

	iatu = -1;

	atu = NULL;

	lista.clear();
	//flags.clear();

	return ++(*this);
}

/*template<class _Traits> bool mfEdgeStarIteratorTetra<_Traits>::operator++()
{
	if(status == 1)
	{
		if(iatu < 0)
		{
			atu = this->mesh->getCell(iinit);
			MF_ASSERT( (atu) && (atu->inMesh()) );

			flags.insert(iatu);

			addNeighbor();

			iatu = iinit;
		}
		else
		{
			if(lista.empty())
			{
				atu = NULL;
				iatu = -1;

				status = 3;
				return false;
			}
			else
			{
				iatu  = lista.pos(0);
				lista.erase(0);

				atu = this->mesh->getCell(iatu);
				MF_ASSERT( (atu) && (atu->inMesh()) );

				addNeighbor();
			}
		}
		return true;
	}
	else
		return false;
}

template<class _Traits> void mfEdgeStarIteratorTetra<_Traits>::addNeighbor()
{
	ids temp;

	temp = atu->getMateId(atu->getLeftFaceIndex(ie1, ie2));
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}
	temp = atu->getMateId(atu->getRightFaceIndex(ie1, ie2));
	if((temp >= 0)&&(!flags.inList(temp)))
	{
		flags.insert(temp);
		lista.insert(temp);
	}
}*/

template<class _Traits> bool mfEdgeStarIteratorTetra<_Traits>::operator++()
{
	//cout << "ok " << is << " ";
	if(status == 1)
	{
		if(iatu < 0)
		{
			if(is < 0)
			{
				//cout << "ok1\n ";
				is = 0;
				iatu = iinit;

				MF_ASSERT(iatu >= 0);

				atu = this->mesh->getCell(iatu);
				MF_ASSERT((atu) && (atu->inMesh()));

				idv1 = atu->getVertexId(ie1);
				iEdge1 = atu->getVertexIndex(idv1);
				idv2 = atu->getVertexId(ie2);
				iEdge2 = atu->getVertexIndex(idv2);

				addNeighbor();
			}
		}
		else
		{
			//MF_ASSERT(atu->getVertexIndex(iv) >= 0);

			if(lista.empty())
			{
				is++;
				//iatu = v->getSingCell(is);

				/*if(iatu >= 0)
				{
					lista.insert(iatu);
				}*/
				//else
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
			MF_ASSERT((atu) && (atu->inMesh()));

			iEdge1 = atu->getVertexIndex(idv1);
			iEdge2 = atu->getVertexIndex(idv2);

			addNeighbor();
		}

		return true;
	}
	else
		return false;
}

template<class _Traits> int mfEdgeStarIteratorTetra<_Traits>::getV1Index()
{
	return iEdge1;
}

template<class _Traits> int mfEdgeStarIteratorTetra<_Traits>::getV2Index()
{
	return iEdge2;
}

template<class _Traits> void mfEdgeStarIteratorTetra<_Traits>::addNeighbor()
{
	ids temp;

	//cout << "ok\n-orient: " << orientationStatus << endl;
	if(orientationStatus) //ccw
	{
		//temp = atu->getMateId((atu->getVertexIndex(iv)+2)%3);
		temp = atu->getMateId(atu->getLeftFaceIndex(iEdge1, iEdge2));
		//cout << "leftFace " << iEdge1 << " " << iEdge2 << " em " << iatu << ": " << atu->getLeftFaceIndex(iEdge1, iEdge2) << endl;
		//cout << "Vert Oposto " << atu->getVertexId(atu->getLeftFaceIndex(iEdge1, iEdge2)) << endl;
		//cout << "temp: " << temp << endl;

		if(temp >= 0 && temp != iinit)
		{
			lista.insert(temp);
		}
		else
		{
			if(temp != iinit || iinit == iatu)
			{
				//cout << "ok! temp = -1" << endl;
				orientationStatus = 0;

				sCell *aux;
				aux = this->mesh->getCell(iinit);
				//temp = aux->getMateId(aux->getVertexIndex(iv));
				temp = aux->getMateId(aux->getRightFaceIndex(ie1, ie2));
				//cout << "New temp: " << temp << endl;
				if(temp >= 0)
				{
					lista.insert(temp);
				}
			}
		}
	}
	else //cw
	{
		//temp = atu->getMateId(atu->getVertexIndex(iv));
		temp = atu->getMateId(atu->getRightFaceIndex(iEdge1, iEdge2));

		if(temp >= 0 && temp != iinit)
		{
			lista.insert(temp);
		}
	}

	MF_ASSERT( atu->getVertexIndex(iv) >= 0);
}

template<class _Traits> SCELL* mfEdgeStarIteratorTetra<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* mfEdgeStarIteratorTetra<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS mfEdgeStarIteratorTetra<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool mfEdgeStarIteratorTetra<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool mfEdgeStarIteratorTetra<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

#undef SCELL
#undef IDS

}

#endif

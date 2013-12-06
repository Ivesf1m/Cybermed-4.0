#ifndef MFBOUNDARYCELLITERATOR2D_H
#define MFBOUNDARYCELLITERATOR2D_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfIterator.h"

namespace mf
{

#define SCELL typename mfBoundaryCellIterator2D<_Traits>::sCell
#define IDS typename mfBoundaryCellIterator2D<_Traits>::ids

template <class _Traits> class mfBoundaryCellIterator2D : public mfIterator<_Traits>
{
public:
	typedef typename _Traits::sCell 	sCell;	/**< Cell typename definition*/
	typedef typename _Traits::ids 		ids;	/**< Id typename definition*/
	typedef typename _Traits::sMesh		sMesh;	/**< Mesh typename definition*/

	/** Construtor */
	mfBoundaryCellIterator2D(sMesh *_mesh);
	
	/** Destrutor */
	~mfBoundaryCellIterator2D();
	
	bool initialize(ids init, int edge = -1);

	bool finish();

	bool notFinish();
	
	bool operator++();
	bool operator--();

	sCell *operator->();
	sCell *operator*();

	ids operator&();
	
	int getEdge();

private:
	ids iatu;	/**< Current cell id */
	ids markc;
	sCell *atu;	/**< Current cell instance */

	int eatu;
	int marke;
	int status;	/**< Iterator status */
	// 0 - iterator sem posicao
	// 1 - iterator em posicao normal
	// 2 - iterator no limite inferior
	// 3 - iterator no limite superior
};

template <class _Traits> mfBoundaryCellIterator2D<_Traits>::mfBoundaryCellIterator2D(sMesh *_mesh)
: mfIterator<_Traits>(_mesh)
{
	status = 0;
	iatu = eatu = markc = marke = -1;
	atu = NULL;
}

template <class _Traits> mfBoundaryCellIterator2D<_Traits>::~mfBoundaryCellIterator2D()
{
}

template <class _Traits> bool mfBoundaryCellIterator2D<_Traits>::initialize(ids init, int edge)
{
	MF_ASSERT(init >= 0);

	iatu = init;
	markc = iatu;
	
	atu = this->mesh->getCell(iatu);
	
	MF_ASSERT(atu->inMesh());
	
	if(edge < 0)
	{
		if(atu->getMateId(0) < 0)
			eatu = 0;
		else if(atu->getMateId(1) < 0)
			eatu = 1;
		else if(atu->getMateId(2) < 0)
			eatu = 2;
	}
	else
		eatu = edge;
	
	marke = eatu;
	
	status = 1;

	return true;
}

template<class _Traits> bool mfBoundaryCellIterator2D<_Traits>::operator++()
{
	sCell *tempc = atu;
	int tempe = eatu, iant, itempc = iatu;
	
	if((status == 1)||(status == 2))
	{
		
		while(tempc->getMateId((tempe+1)%3) >= 0)
		{
			iant = itempc;
			itempc = tempc->getMateId((tempe+1)%3);
			tempc = this->mesh->getCell(itempc);
			tempe = tempc->getMateIndex(iant);
		}
		
		eatu = (tempe + 1)%3;
		atu = tempc;
		iatu = itempc;
	
		if((iatu == markc)&&(eatu == marke))
		{
			status = 3;
			return false;
		}
	}
	else
		return false;
	
	return true;
}

template<class _Traits> bool mfBoundaryCellIterator2D<_Traits>::operator--()
{
	sCell *tempc = atu;
	int tempe = eatu, iant, itempc = iatu;
	
	if((status == 1)||(status == 3))
	{
		
		while(tempc->getMateId((tempe+2)%3) >= 0)
		{
			iant = itempc;
			itempc = tempc->getMateId((tempe+2)%3);
			tempc = this->mesh->getCell(itempc);
			tempe = tempc->getMateIndex(iant);	
		}
		
		eatu = (tempe + 2)%3;
		atu = tempc;
		iatu = itempc;
	
		if((iatu == markc)&&(eatu == marke))
		{
			status = 2;
			return false;
		}
	}
	else
		return false;
	
	return true;
}

template<class _Traits> SCELL* mfBoundaryCellIterator2D<_Traits>::operator->()
{
	return atu;
}

template<class _Traits> SCELL* mfBoundaryCellIterator2D<_Traits>::operator*()
{
	return atu;
}

template<class _Traits> IDS mfBoundaryCellIterator2D<_Traits>::operator&()
{
	return iatu;
}

template<class _Traits> bool mfBoundaryCellIterator2D<_Traits>::finish()
{
	return ((status == 2)||(status == 3));
}

template<class _Traits> bool mfBoundaryCellIterator2D<_Traits>::notFinish()
{
	return ((status == 0)||(status == 1));
}

template<class _Traits> int mfBoundaryCellIterator2D<_Traits>::getEdge()
{
	if(status != 0)
		return eatu;
	
	return -1;
}

#undef SCELL
#undef IDS

}

#endif

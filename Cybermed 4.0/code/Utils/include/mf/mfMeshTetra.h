#ifndef MFMESHTETRA_H
#define MFMESHTETRA_H

#include "mfMacros.h"
#include "mfSing.h"
#include "mfMesh.h"
#include "mfMeshOper.h"
#include "mfVertexStarIterator3D.h"

namespace mf
{

/**
 *	@class		mfMeshTetra
 *	@file		mfMeshTetra.h
 *	@short
 *	Tetrahedron Mesh Operator Class
 *
 *	Operation Class for Tetrahedrons in 3D space (with oriented vertices)
 *
 *	_Traits must have: ids, sVertex, sCell , sSing, sMesh
 *
 *	@author		Mario Lizier
 *	@author		Icaro da Cunha
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfMeshTetra : public mfMeshOper<_Traits>
{
public:

	typedef typename _Traits::ids 			ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex 		sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell 		sCell;		/**< Cell typename definition */
	typedef typename _Traits::sGeometric	sGeometric; /**< Geometric operator typename definition */
	typedef mfSing<_Traits> 				sSing;		/**< Singular typename definition */
	typedef typename _Traits::sMesh			sMesh;		/**< Mesh typename definition */

	/**	Constructor
	 *
	 * \param _mesh: the mesh address that this class will manipulate
	 */
	mfMeshTetra(sMesh *_mesh);

	/**	Destructor */
	~mfMeshTetra();

	/** Add cell in mesh
	 *
	 *	\param idcell: cell id
	 * 	\param idvertices: vector with vertices ids of the cell
	 */
	 void addCell(ids idcell, ids *idvertices MF_DMUTEXVD);

	/**	Delete a cell
	 *
	 * 	\param idcell: cell id
	 */
	 void delCell(ids idcell MF_DMUTEXVD);

private:
	sGeometric geom;

	void searchFace(int idcell, int idvertex);
	void searchSings(int idvertex);
	bool setMate(int idcell, int idcellmate, int iq[]);
	int sameVertices(int idcell1, int idcell2, int iq[]);

#ifdef MF_THREADS
	void lockVertices(ids *idv, sVertex** v);
	void unlockVertices(ids *idv, sVertex** v);
#endif
};

template <class _Traits> mfMeshTetra<_Traits>::mfMeshTetra(sMesh *_mesh)
: mfMeshOper<_Traits>(_mesh)
{
	geom.setMesh(_mesh);
}

template <class _Traits> mfMeshTetra<_Traits>::~mfMeshTetra()
{
}

template <class _Traits> void mfMeshTetra<_Traits>::addCell(ids idcell, ids *idvertices MF_DMUTEXV)
{
	MF_ASSERT((idvertices[0] >= 0)&&(idvertices[1] >= 0)&&(idvertices[2] >= 0)&&(idvertices[3] >= 0));
	MF_ASSERT((idvertices[0] != idvertices[1])&&(idvertices[0] != idvertices[2])&&(idvertices[0] != idvertices[3]));
	MF_ASSERT((idvertices[1] != idvertices[2])&&(idvertices[1] != idvertices[3])&&(idvertices[2] != idvertices[3]));

	sCell* c = this->mesh->getCell(idcell);
	ids idv[4] = {idvertices[0], idvertices[1], idvertices[2], idvertices[3]};
	sVertex *v[4] = {this->mesh->getVertex(idv[0]), this->mesh->getVertex(idv[1]), this->mesh->getVertex(idv[2]), this->mesh->getVertex(idv[3])};
	int ns = 0 // Numero de vertices com singularidade igual a 0
		, temp;
	int i0 = 0, i1 = 1, i2 = 2, i3 = 3;
	int indTemp;

#ifdef MF_THREADS
	lockVertices(idv,v);
	c->lock();
#endif

	c->clearMates(MF_MUTEXFALSE);

	ns = geom.orientation3D(idv, v MF_MUTEXFALSEV);

	MF_ASSERT(ns != 0);
	
	ns = 0;

	if (v[0]->getNumberOfSings(MF_MUTEXFALSE) == 0)
		ns++;
	if (v[1]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		//temp = idv[0];
		//idv[0] = idv[1];
		//idv[1] = temp;
		indTemp = i0;
		i0 = i1;
		i1 = indTemp;
		ns++;
	}
	if (v[2]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		//temp = idv[0];
		//idv[0] = idv[2];
		//idv[2] = temp;
		indTemp = i0;
		i0 = i2;
		i2 = indTemp;
		ns++;
	}
	if (v[3]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		//temp = idv[0];
		//idv[0] = idv[3];
		//idv[3] = temp;
		indTemp = i0;
		i0 = i3;
		i3 = indTemp;
		ns++;
	}
	
	c->setVertexId(0, idv[0] MF_MUTEXFALSEV);
	c->setVertexId(1, idv[1] MF_MUTEXFALSEV);
	c->setVertexId(2, idv[2] MF_MUTEXFALSEV);
	c->setVertexId(3, idv[3] MF_MUTEXFALSEV);

	c->setMateId(0,-1 MF_MUTEXFALSEV);
	c->setMateId(1,-1 MF_MUTEXFALSEV);
	c->setMateId(2,-1 MF_MUTEXFALSEV);
	c->setMateId(3,-1 MF_MUTEXFALSEV);
	
	/*v[0] = this->mesh->getVertex(idv[0] MF_MUTEXFALSEV);
	v[1] = this->mesh->getVertex(idv[1] MF_MUTEXFALSEV);
	v[2] = this->mesh->getVertex(idv[2] MF_MUTEXFALSEV);
	v[3] = this->mesh->getVertex(idv[3] MF_MUTEXFALSEV);*/
	
	if(ns > 1)
	{
		// Nenhuma face em comum
		v[0]->addSing(idcell MF_MUTEXFALSEV);
		v[1]->addSing(idcell MF_MUTEXFALSEV);
		v[2]->addSing(idcell MF_MUTEXFALSEV);
		v[3]->addSing(idcell MF_MUTEXFALSEV);
	}
	else if(ns == 1)
	{
		// Apenas a face oposta a index1 pode ser comum
		searchFace(idcell,idv[i1]);

		v[i0]->addSing(idcell MF_MUTEXFALSEV);

		if (c->getMateId(i0 MF_MUTEXFALSEV) < 0)
		{
			// Nenhuma face em comum foi encontrada
			v[i1]->addSing(idcell MF_MUTEXFALSEV);
			v[i2]->addSing(idcell MF_MUTEXFALSEV);
			v[i3]->addSing(idcell MF_MUTEXFALSEV);
		}
	}
	else
	{
		// Qualquer face pode ser comum

		searchFace(idcell,idv[i0]);
		searchFace(idcell,idv[i1]);

		if(c->getMateId(i0) < 0 && c->getMateId(i1) < 0)
		{
			v[i0]->addSing(idcell MF_MUTEXFALSEV);
			v[i1]->addSing(idcell MF_MUTEXFALSEV);
			v[i2]->addSing(idcell MF_MUTEXFALSEV);
			v[i3]->addSing(idcell MF_MUTEXFALSEV);
		}
		else
		{
			if(c->getMateId(i0) < 0)
			{
				// Nenhuma face em comum foi encontrada
				v[i1]->addSing(idcell MF_MUTEXFALSEV);
				v[i2]->addSing(idcell MF_MUTEXFALSEV);
				v[i3]->addSing(idcell MF_MUTEXFALSEV);
			}
			if(c->getMateId(i1) < 0)
			{
				// Nenhuma face em comum foi encontrada
				v[i0]->addSing(idcell MF_MUTEXFALSEV);
				v[i2]->addSing(idcell MF_MUTEXFALSEV);
				v[i3]->addSing(idcell MF_MUTEXFALSEV);
			}
		}

		searchSings(idv[i0]);
		searchSings(idv[i1]);
		searchSings(idv[i2]);
		searchSings(idv[i3]);
	}
	
#ifdef MF_THREADS
	unlockVertices(idv,v);
	c->unlock();
#endif
}

template <class _Traits> void mfMeshTetra<_Traits>::delCell(ids idcell MF_DMUTEXV)
{
}

template <class _Traits> void mfMeshTetra<_Traits>::searchFace(int idcell, int idvertex)
{
	MF_ASSERT(this->mesh->getVertex(idvertex)->getNumberOfSings());
	mfVertexStarIterator3D<_Traits> ic(this->mesh);
	//mfList<ids> lista;

	int iq[4], ig;
	//ids c;

	for(ic.initialize(idvertex); ic.notFinish(); ++ic)
	{
		//MF_ASSERT(!lista.inList(&ic));
		//lista.insert(&ic);
		
		ig = sameVertices(&ic, idcell, iq);

		//MF_ASSERT(!((&ic != idcell)&&(ig == 4)));

		if((&ic != idcell)&&(ig == 3))
		{
			setMate(idcell, &ic, iq);
			setMate(&ic, idcell, iq);
		}
	}

	/*while(!lista.empty())
	{
		c = lista.first();
		lista.erase(0);

		ig = sameVertices(c, idcell, iq);

		MF_ASSERT(!((c != idcell)&&(ig == 4)));

		if((c != idcell)&&(ig == 3))
		{
			setMate(idcell, c, iq);
			setMate(c, idcell, iq);
		}
	}*/
}

template <class _Traits> int mfMeshTetra<_Traits>::sameVertices(int idcell1, int idcell2, int iq[])
{
	int i, j, v1, v2, nv = 0;
	sCell* c1 = this->mesh->getCell(idcell1);
	sCell* c2 = this->mesh->getCell(idcell2);

	for(i=0; i<4; i++)
	{
		v1 = c1->getVertexId(i);
		for(j=0; j<4; j++)
		{
			v2 = c2->getVertexId(j);
			if(v1 == v2)
			{
				iq[nv++] = v1;
				break;
			}
		}
	}

	return nv;
}

template <class _Traits> bool mfMeshTetra<_Traits>::setMate(int idcell, int idcellmate, int iq[])
{
	int temp;
	for(int i=0; i<4; i++)
	{
		temp = this->mesh->getCell(idcell)->getVertexId(i);
		if((temp != iq[0])&&(temp != iq[1])&&(temp != iq[2]))
		{
			if (temp >= 0)
			{
				this->mesh->getCell(idcell)->setMateId(i,idcellmate);
				return true;
			}
			else
				break;
		}
	}
	
	return false;
}

template <class _Traits> void mfMeshTetra<_Traits>::searchSings(int idvertex)
{
	mfList<ids> lista;
	mfList<ids> flags;
	sVertex *v = this->mesh->getVertex(idvertex);
	sSing *s = v->getSing();
	sSing *ants = s;
	sCell *atu;
	int i;
	ids iatu;

	lista.insert(s->getCell());
	flags.insert(s->getCell());
	s = s->getNext();

	while(!lista.empty())
	{
		iatu = lista.first();
		lista.erase(0);
		atu = this->mesh->getCell(iatu);

		for(i=0; i<4; i++)
			if ((atu->getMateId(i) >= 0)&&(atu->getVertexId(i)!= idvertex)&&(!flags.inList(atu->getMateId(i))))
			{
				lista.insert(atu->getMateId(i));
				flags.insert(atu->getMateId(i));
			}

		while((s != NULL)&&(lista.empty()))
		{
			if(!flags.inList(s->getCell()))
			{
				lista.insert(s->getCell());
				flags.insert(s->getCell());
				ants = s;
				s = s->getNext();
			}
			else
			{
				ants->setNext(s->getNext());
				delete s;
				s = ants->getNext();
			}
		}
	}

	lista.clear();
	flags.clear();
}

#ifdef MF_THREADS

template <class _Traits> void mfMeshTetra<_Traits>::lockVertices(ids *idv, sVertex** v)
{
	ids ordem[4];
	int temp,i,j;
	
	for(i = 0; i < 4; i++)
	{
		ordem[i] = i;
		for(j = i; j > 0; j--)
		{
			if(idv[ordem[j-1]] > idv[ordem[j]])
			{
				temp = ordem[j];
				ordem[j] = ordem[j-1];
				ordem[j-1] = temp;
			}
		}
	}
	
	v[ordem[0]]->lock();
	v[ordem[1]]->lock();
	v[ordem[2]]->lock();
	v[ordem[3]]->lock();
}

template <class _Traits> void mfMeshTetra<_Traits>::unlockVertices(ids *idv, sVertex** v)
{
	ids ordem[4];
	int temp,i,j;
	
	for(i = 0; i < 4; i++)
	{
		ordem[i] = i;
		for(j = i; j > 0; j--)
		{
			if(idv[ordem[j-1]] > idv[ordem[j]])
			{
				temp = ordem[j];
				ordem[j] = ordem[j-1];
				ordem[j-1] = temp;
			}
		}
	}
	
	v[ordem[3]]->unlock();
	v[ordem[2]]->unlock();
	v[ordem[1]]->unlock();
	v[ordem[0]]->unlock();
}

#endif

}

#endif

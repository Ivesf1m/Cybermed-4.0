#ifndef MFMESHHEXA_H
#define MFMESHHEXA_H

#include "mfMacros.h"
#include "mfSing.h"
#include "mfMesh.h"
#include "mfMeshOper.h"
#include "mfVertexStarIterator3D.h"

namespace mf
{

/**	Operation Class for Hexaedra in 3D space (with not oriented vertices)
 * 
 * 	_Traits must have: ids, sVertex, sCell, sSing, sMesh
 */

template <class _Traits> class mfMeshHexa : public mfMeshOper<_Traits>
{
public:

	typedef typename _Traits::ids 		ids;
	typedef typename _Traits::sVertex 	sVertex;
	typedef typename _Traits::sCell 	sCell;
	typedef typename _Traits::sGeometric sGeometric;
	typedef mfSing<_Traits> 		sSing;
	typedef typename _Traits::sMesh		sMesh;

	/**	Constructor
	 * 
	 * \param _mesh: the mesh address that this class will manipulate
	 */
	mfMeshHexa(sMesh *_mesh);

	/**	Destructor */
	~mfMeshHexa();

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

template <class _Traits> mfMeshHexa<_Traits>::mfMeshHexa(sMesh *_mesh)
: mfMeshOper<_Traits>(_mesh)
{
	geom.setMesh(_mesh);
}

template <class _Traits> mfMeshHexa<_Traits>::~mfMeshHexa()
{
}

template <class _Traits> void mfMeshHexa<_Traits>::addCell(ids idcell, ids *idvertices MF_DMUTEXV)
{
	MF_ASSERT((idvertices[0] >= 0)&&(idvertices[1] >= 0)&&(idvertices[2] >= 0)&&(idvertices[3] >= 0));
	MF_ASSERT((idvertices[4] >= 0)&&(idvertices[5] >= 0)&&(idvertices[6] >= 0)&&(idvertices[7] >= 0));
	/*MF_ASSERT((idvertices[0] != idvertices[1])&&(idvertices[0] != idvertices[2])&&(idvertices[0] != idvertices[3])&&(idvertices[0] != idvertices[4]));
	MF_ASSERT((idvertices[0] != idvertices[5])&&(idvertices[0] != idvertices[6])&&(idvertices[0] != idvertices[7])&&(idvertices[1] != idvertices[2]));
	MF_ASSERT((idvertices[1] != idvertices[3])&&(idvertices[1] != idvertices[4])&&(idvertices[1] != idvertices[5])&&(idvertices[1] != idvertices[6]));
	MF_ASSERT((idvertices[1] != idvertices[7])&&(idvertices[2] != idvertices[3])&&(idvertices[2] != idvertices[4])&&(idvertices[2] != idvertices[5]));
	MF_ASSERT((idvertices[2] != idvertices[6])&&(idvertices[2] != idvertices[7])&&(idvertices[3] != idvertices[4])&&(idvertices[3] != idvertices[5]));
	MF_ASSERT((idvertices[3] != idvertices[6])&&(idvertices[3] != idvertices[7])&&(idvertices[4] != idvertices[5])&&(idvertices[4] != idvertices[6]));
	MF_ASSERT((idvertices[4] != idvertices[7])&&(idvertices[5] != idvertices[6])&&(idvertices[5] != idvertices[7])&&(idvertices[6] != idvertices[7]));*/

	sCell* c = this->mesh->getCell(idcell);
	ids idv[8] = {idvertices[0], idvertices[1], idvertices[2], idvertices[3], idvertices[4], idvertices[5], idvertices[6], idvertices[7]};
	sVertex *v[8] = {this->mesh->getVertex(idv[0]), this->mesh->getVertex(idv[1]), this->mesh->getVertex(idv[2]), this->mesh->getVertex(idv[3]), this->mesh->getVertex(idv[4]), this->mesh->getVertex(idv[5]), this->mesh->getVertex(idv[6]), this->mesh->getVertex(idv[7])};
	int ns = 0; // Numero de vertices com singularidade igual a 0
	int temp;

#ifdef MF_THREADS
	lockVertices(idv,v);
	c->lock();
#endif

	c->clearMates(MF_MUTEXFALSE);

	//ns = geom.orientation3D(idv, v MF_MUTEXFALSEV);

	//MF_ASSERT(ns != 0);

	ns = 0;

	/*if (v[0]->getNumberOfSings(MF_MUTEXFALSE) == 0)
		ns++;
	if (v[1]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		temp = idv[0];
		idv[0] = idv[1];
		idv[1] = temp;
		ns++;
	}
	if (v[2]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		temp = idv[0];
		idv[0] = idv[2];
		idv[2] = temp;
		ns++;
	}
	if (v[3]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		temp = idv[0];
		idv[0] = idv[3];
		idv[3] = temp;
		ns++;
	}*/

	c->setVertexId(0, idv[0] MF_MUTEXFALSEV);
	c->setVertexId(1, idv[1] MF_MUTEXFALSEV);
	c->setVertexId(2, idv[2] MF_MUTEXFALSEV);
	c->setVertexId(3, idv[3] MF_MUTEXFALSEV);
	c->setVertexId(4, idv[4] MF_MUTEXFALSEV);
	c->setVertexId(5, idv[5] MF_MUTEXFALSEV);
	c->setVertexId(6, idv[6] MF_MUTEXFALSEV);
	c->setVertexId(7, idv[7] MF_MUTEXFALSEV);

	c->setMateId(0,-1 MF_MUTEXFALSEV);
	c->setMateId(1,-1 MF_MUTEXFALSEV);
	c->setMateId(2,-1 MF_MUTEXFALSEV);
	c->setMateId(3,-1 MF_MUTEXFALSEV);
	c->setMateId(4,-1 MF_MUTEXFALSEV);
	c->setMateId(5,-1 MF_MUTEXFALSEV);

	/*v[0]->addSing(idcell MF_MUTEXFALSEV);
	v[1]->addSing(idcell MF_MUTEXFALSEV);
	v[2]->addSing(idcell MF_MUTEXFALSEV);
	v[3]->addSing(idcell MF_MUTEXFALSEV);
	v[4]->addSing(idcell MF_MUTEXFALSEV);
	v[5]->addSing(idcell MF_MUTEXFALSEV);
	v[6]->addSing(idcell MF_MUTEXFALSEV);
	v[7]->addSing(idcell MF_MUTEXFALSEV);*/

	if (v[0]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		v[0]->addSing(idcell MF_MUTEXFALSEV);
	}
	else
	{
		searchFace(idcell, idv[0]);
		v[0]->addSing(idcell MF_MUTEXFALSEV);
	}
	if (v[1]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		v[1]->addSing(idcell MF_MUTEXFALSEV);
	}
	else
	{
		searchFace(idcell, idv[1]);
		v[1]->addSing(idcell MF_MUTEXFALSEV);
	}
	if (v[2]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		v[2]->addSing(idcell MF_MUTEXFALSEV);
	}
	else
	{
		searchFace(idcell, idv[2]);
		v[2]->addSing(idcell MF_MUTEXFALSEV);
	}
	if (v[3]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		v[3]->addSing(idcell MF_MUTEXFALSEV);
	}
	else
	{
		searchFace(idcell, idv[3]);
		v[3]->addSing(idcell MF_MUTEXFALSEV);
	}
	if (v[4]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		v[4]->addSing(idcell MF_MUTEXFALSEV);
	}
	else
	{
		searchFace(idcell, idv[4]);
		v[4]->addSing(idcell MF_MUTEXFALSEV);
	}
	if (v[5]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		v[5]->addSing(idcell MF_MUTEXFALSEV);
	}
	else
	{
		searchFace(idcell, idv[5]);
		v[5]->addSing(idcell MF_MUTEXFALSEV);
	}
	if (v[6]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		v[6]->addSing(idcell MF_MUTEXFALSEV);
	}
	else
	{
		searchFace(idcell, idv[6]);
		v[6]->addSing(idcell MF_MUTEXFALSEV);
	}
	if (v[7]->getNumberOfSings(MF_MUTEXFALSE) == 0)
	{
		v[7]->addSing(idcell MF_MUTEXFALSEV);
	}
	else
	{
		searchFace(idcell, idv[7]);
		v[7]->addSing(idcell MF_MUTEXFALSEV);
	}

	/*if(ns > 1)
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
		searchFace(idcell,idv[1]);

		v[0]->addSing(idcell MF_MUTEXFALSEV);

		if (c->getMateId(0 MF_MUTEXFALSEV) < 0)
		{
			// Nenhuma face em comum foi encontrada
			v[1]->addSing(idcell MF_MUTEXFALSEV);
			v[2]->addSing(idcell MF_MUTEXFALSEV);
			v[3]->addSing(idcell MF_MUTEXFALSEV);
		}
	}
	else
	{
		// Qualquer face pode ser comum

		searchFace(idcell,idv[0]);
		searchFace(idcell,idv[1]);

		if (c->getMateId(0 MF_MUTEXFALSEV) < 0)
		{
			// Nenhuma face em comum foi encontrada
			v[1]->addSing(idcell MF_MUTEXFALSEV);
			v[2]->addSing(idcell MF_MUTEXFALSEV);
			v[3]->addSing(idcell MF_MUTEXFALSEV);
		}

		if (c->getMateId(1) < 0)
		{
			// Nenhuma face em comum foi encontrada
			v[0]->addSing(idcell MF_MUTEXFALSEV);
			v[2]->addSing(idcell MF_MUTEXFALSEV);
			v[3]->addSing(idcell MF_MUTEXFALSEV);
		}

		searchSings(idv[0]);
		searchSings(idv[1]);
		searchSings(idv[2]);
		searchSings(idv[3]);
	}*/

#ifdef MF_THREADS
	unlockVertices(idv,v);
	c->unlock();
#endif
}

template <class _Traits> void mfMeshHexa<_Traits>::delCell(ids idcell MF_DMUTEXV)
{
}

template <class _Traits> void mfMeshHexa<_Traits>::searchFace(int idcell, int idvertex)
{
	MF_ASSERT(this->mesh->getVertex(idvertex)->getNumberOfSings());
	mfVertexStarIterator3D<_Traits> ic(this->mesh);
	mfList<ids> lista;

	for(ic.initialize(idvertex); ic.notFinish(); ++ic)
	{
		//MF_ASSERT(!lista.inList(&ic));
		lista.insert(&ic);
	}

	int iq[4], ig;
	ids c;

	while(!lista.empty())
	{
		c = lista.first();
		lista.erase(0);

		ig = sameVertices(c, idcell, iq);

		//MF_ASSERT(!((c != idcell)&&(ig == 4)));

		if((c != idcell)&&(ig == 3))
		{
			setMate(idcell, c, iq);
			setMate(c, idcell, iq);
		}
	}
}

template <class _Traits> int mfMeshHexa<_Traits>::sameVertices(int idcell1, int idcell2, int iq[])
{
	int i, j, v1, v2, nv = 0;
	//int vCell1[4], vCell2[4];
	sCell* c1 = this->mesh->getCell(idcell1);
	sCell* c2 = this->mesh->getCell(idcell2);

	for(i=0; i<7; i++)
	{
		v1 = c1->getVertexId(i);
		for(j=0; j<8; j++)
		{
			v2 = c2->getVertexId(j);
			if(v1 == v2)
			{
				//vCell1[nv] = i;
				//vCell2[nv] = j;

				iq[nv++] = v1;
				break;
			}
		}
		if(nv == 3)
			return 3;
	}

	return nv;
}

template <class _Traits> bool mfMeshHexa<_Traits>::setMate(int idcell, int idcellmate, int iq[])
{
	int temp;
	int v0, v1, v2;
	sCell* c = this->mesh->getCell(idcell);

	v0 = c->getVertexIndex(iq[0]);
	v1 = c->getVertexIndex(iq[1]);
	v2 = c->getVertexIndex(iq[2]);

	c->setMateId(c->getFaceIndex(v0,v1,v2),idcellmate);

	return true;

	/*for(int i=0; i<4; i++)
	{
		temp = this->mesh->getCell(idcell)->getVertexId(i);
		if((temp != iq[0])&&(temp != iq[1])&&(temp != iq[2]))
		{
			if (temp < 0)
			{
				this->mesh->getCell(idcell)->setMateId(i,idcellmate);
				return true;
			}
			else
				break;
		}
	}

	return false;*/
}

template <class _Traits> void mfMeshHexa<_Traits>::searchSings(int idvertex)
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

template <class _Traits> void mfMeshHexa<_Traits>::lockVertices(ids *idv, sVertex** v)
{
	ids ordem[8];
	int temp,i,j;

	for(i = 0; i < 8; i++)
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
	v[ordem[4]]->lock();
	v[ordem[5]]->lock();
	v[ordem[6]]->lock();
	v[ordem[7]]->lock();
}

template <class _Traits> void mfMeshHexa<_Traits>::unlockVertices(ids *idv, sVertex** v)
{
	ids ordem[8];
	int temp,i,j;

	for(i = 0; i < 8; i++)
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

	v[ordem[7]]->unlock();
	v[ordem[6]]->unlock();
	v[ordem[5]]->unlock();
	v[ordem[4]]->unlock();
	v[ordem[3]]->unlock();
	v[ordem[2]]->unlock();
	v[ordem[1]]->unlock();
	v[ordem[0]]->unlock();
}

#endif

}

#endif

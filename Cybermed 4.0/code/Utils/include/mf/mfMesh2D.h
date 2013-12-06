#ifndef MFMESH2D_H
#define MFMESH2D_H

#include "mfMacros.h"
#include "mfSing.h"
#include "mfMesh.h"
#include "mfMeshOper.h"

namespace mf
{

/**	Operation Class for Triangles in 2D space
 * 
 * 	_Traits must have: ids, sVertex, sCell, sSing, sMesh, sGeometric
 */
template <class _Traits> class mfMesh2D : public mfMeshOper<_Traits>
{
public:

	typedef typename _Traits::ids ids;
	typedef typename _Traits::sVertex sVertex;
	typedef typename _Traits::sCell sCell;
	
	typedef typename _Traits::sGeometric sGeometric;
	typedef typename _Traits::sTopology sTopology;
	
	typedef mfSing<_Traits> sSing;
	typedef typename _Traits::sMesh		sMesh;
	
	/**	Constructor
	 * 
	 * \param _mesh: the mesh address that this class will manipulate
	 */
	mfMesh2D(sMesh *_mesh);
	
	/**	Destructor */
	~mfMesh2D();
	
	/** Add cell in mesh
	 * 
	 *	\param idcell: cell id
	 * 	\param idvertices: vector with vertices ids of the cell
	 */
	void addCell(ids idcell, ids *idvertices MF_DMUTEXVD);
	void addCell(ids idcell, ids *idvertices, ids *idops MF_DMUTEXVD);

	/**	Delete a cell
	 *
	 * 	\param idcell: cell id
	 */
	void delCell(ids idcell MF_DMUTEXVD);

private:

	sGeometric geom;

#ifdef MF_THREADS
	void lockVertices(ids *idv, sVertex** v);
	void unlockVertices(ids *idv, sVertex** v);
#endif
};

template <class _Traits> mfMesh2D<_Traits>::mfMesh2D(sMesh *_mesh)
: mfMeshOper<_Traits>(_mesh)
{
	geom.setMesh(_mesh);
}

template <class _Traits> mfMesh2D<_Traits>::~mfMesh2D()
{
}

template <class _Traits> void mfMesh2D<_Traits>::addCell(ids idcell, ids *idvertices MF_DMUTEXV)
{
	MF_ASSERT((idvertices[0] >= 0)&&(idvertices[1] >= 0)&&(idvertices[2] >= 0));
	MF_ASSERT((idvertices[0] != idvertices[1])&&(idvertices[0] != idvertices[2])&&(idvertices[1] != idvertices[2]));

	sCell *c = this->mesh->getCell(idcell MF_MUTEXV);
	ids idv[3] = { idvertices[0], idvertices[1], idvertices[2]};
	sVertex *v[3] = { 	this->mesh->getVertex(idv[0] MF_MUTEXV),
				this->mesh->getVertex(idv[1] MF_MUTEXV),
				this->mesh->getVertex(idv[2] MF_MUTEXV)};

#ifdef MF_THREADS
	c->lock();
	lockVertices(idv,v);
#endif
	
	sCell *cop;
	sSing *s;
	ids icop;
	int i, pos;
	
	c->clearMates(MF_MUTEXFALSE);
	
	i = geom.orientation2D(idv, v MF_MUTEXFALSEV);

	MF_ASSERT(i != 0);
	
	c->setVertexId(0,idv[0] MF_MUTEXFALSEV);
	c->setVertexId(1,idv[1] MF_MUTEXFALSEV);
	c->setVertexId(2,idv[2] MF_MUTEXFALSEV);
		
	for(i = 0; i < 3 ; i++)
	{
		s = v[(i+2)%3]->getSing(MF_MUTEXFALSE);

		while (s)
		{
			icop = s->getCell();
			cop = this->mesh->getCell(icop MF_MUTEXFALSEV);
			if ( cop->getVertexId((cop->getVertexIndex(idv[(i+2)%3]) + 1)%3) == idv[(i+1)%3] )
			{
				c->setMateId(i, icop MF_MUTEXFALSEV);
				cop->setMateId((cop->getVertexIndex(idv[(i+2)%3]) + 2)%3, idcell);
				s = NULL;
			}
			else
				s = s->getNext();
		}
	}

	for(i = 0; i < 3; i++)
	{
		if (c->getMateId((i+2)%3 MF_MUTEXFALSEV) < 0)
		{
			if(c->getMateId((i+1)%3 MF_MUTEXFALSEV) >= 0)
			{
		  		pos = v[i]->inSings(c->getMateId((i+1)%3 MF_MUTEXFALSEV) MF_MUTEXFALSEV);
				v[i]->setSingCell(pos,idcell MF_MUTEXFALSEV);
			}
			else
				v[i]->addSing(idcell MF_MUTEXFALSEV);

		}
		else
		{
			if(c->getMateId((i+1)%3 MF_MUTEXFALSEV) >= 0)
			{
				icop = c->getMateId((i+1)%3 MF_MUTEXFALSEV);
				pos = v[i]->inSings(icop MF_MUTEXFALSEV);
				while((icop >= 0)&&(icop != idcell))
				{
					cop = this->mesh->getCell(icop MF_MUTEXFALSEV);
					icop = cop->getMateId((cop->getVertexIndex(idv[i])+1)%3);
					if(icop < 0)
						v[i]->delSing(pos MF_MUTEXFALSEV);
				}
			}
		}
	}
#ifdef MF_THREADS
	unlockVertices(idv,v);
	c->unlock();
#endif
}

template <class _Traits> void mfMesh2D<_Traits>::addCell(ids idcell, ids *idvertices, ids *idops MF_DMUTEXV)
{
	MF_ASSERT((idvertices[0] >= 0)&&(idvertices[1] >= 0)&&(idvertices[2] >= 0));
	MF_ASSERT((idvertices[0] != idvertices[1])&&(idvertices[0] != idvertices[2])&&(idvertices[1] != idvertices[2]));

	sCell *c = this->mesh->getCell(idcell MF_MUTEXV);

#ifdef MF_THREADS
	sVertex *v[3] = {	this->mesh->getVertex(idvertices[0] MF_MUTEXV),
				this->mesh->getVertex(idvertices[1] MF_MUTEXV),
				this->mesh->getVertex(idvertices[2] MF_MUTEXV)};

	c->lock();
	lockVertices(idvertices,v);
#endif
	
	c->setVertexId(0,idvertices[0] MF_MUTEXFALSEV);
	c->setVertexId(1,idvertices[1] MF_MUTEXFALSEV);
	c->setVertexId(2,idvertices[2] MF_MUTEXFALSEV);

	c->setMateId(0,idops[0] MF_MUTEXFALSEV);
	c->setMateId(1,idops[1] MF_MUTEXFALSEV);
	c->setMateId(2,idops[2] MF_MUTEXFALSEV);

#ifdef MF_THREADS
	unlockVertices(idvertices,v);
	c->unlock();
#endif
}

template <class _Traits> void mfMesh2D<_Traits>::delCell(ids idcell MF_DMUTEXV)
{
	int i,pos;
	sCell *cop, *c = this->mesh->getCell(idcell MF_MUTEXV);
	ids idv[3] = { c->getVertexId(0 MF_MUTEXV), c->getVertexId(1 MF_MUTEXV), c->getVertexId(2 MF_MUTEXV) };
	sVertex *v[3] = { this->mesh->getVertex(idv[0] MF_MUTEXV),
			  this->mesh->getVertex(idv[1] MF_MUTEXV),
			  this->mesh->getVertex(idv[2] MF_MUTEXV)};
	ids icop;

#ifdef MF_THREADS
	if(mutex)
	{
		c->lock();
		lockVertices(idv,v);
	}
#endif

	for(i = 0; i < 3; i++)
	{
		if(c->getMateId((i+2)%3 MF_MUTEXFALSEV) >= 0)
		{
			if(c->getMateId((i+1)%3 MF_MUTEXFALSEV) >= 0)
			{
				icop = c->getMateId((i+1)%3 MF_MUTEXFALSEV);
				while((icop >= 0)&&(icop != idcell))
				{
					cop = this->mesh->getCell(icop MF_MUTEXFALSEV);
					icop = cop->getMateId((cop->getVertexIndex(c->getVertexId(i MF_MUTEXFALSEV))+1)%3);
					if(icop < 0)
						v[i]->addSing(c->getMateId((i+1)%3 MF_MUTEXFALSEV) MF_MUTEXFALSEV);
					else if (icop == idcell)
						v[i]->getSing(MF_MUTEXFALSE)->setCell(c->getMateId((i+1)%3 MF_MUTEXFALSEV));
				}
			}
		}
		else
		{
			pos = v[i]->inSings(idcell MF_MUTEXFALSEV);
			if(c->getMateId((i+1)%3 MF_MUTEXFALSEV) >= 0)
				v[i]->setSingCell(pos,c->getMateId((i+1)%3 MF_MUTEXFALSEV) MF_MUTEXFALSEV);
			else
				v[i]->delSing(pos MF_MUTEXFALSEV);
		}
	}

	for(i=0; i < 3; i++)
	{
		icop = c->getMateId(i MF_MUTEXFALSEV);
		if(icop >= 0)
		{
			cop = this->mesh->getCell(icop);
			cop->setMateId(cop->getMateIndex(idcell),-1);
		}
	}

	c->setMateId(0,-1 MF_MUTEXFALSEV);
	c->setMateId(1,-1 MF_MUTEXFALSEV);
	c->setMateId(2,-1 MF_MUTEXFALSEV);

#ifdef MF_THREADS
	if(mutex)
	{
		unlockVertices(idv,v);
		c->unlock();
	}
#endif
}

#ifdef MF_THREADS

template <class _Traits> void mfMesh2D<_Traits>::lockVertices(ids *idv, sVertex** v)
{
	if(idv[0] < idv[1])
	{
		if(idv[0] < idv[2])
		{
			if(idv[1] < idv[2])
			{ v[0]->lock(); v[1]->lock(); v[2]->lock(); }
			else
			{ v[0]->lock(); v[2]->lock(); v[1]->lock(); }
		}
		else
		{ v[2]->lock(); v[0]->lock(); v[1]->lock(); }
	}
	else
	{
		if(idv[0] > idv[2])
		{
			if(idv[1] < idv[2])
			{ v[1]->lock(); v[2]->lock(); v[0]->lock(); }
			else
			{ v[2]->lock(); v[1]->lock(); v[0]->lock(); }
		}
		else
		{ v[1]->lock(); v[0]->lock(); v[2]->lock(); }
	}
}

template <class _Traits> void mfMesh2D<_Traits>::unlockVertices(ids *idv, sVertex** v)
{
	if(idv[0] < idv[1])
	{
		if(idv[0] < idv[2])
		{
			if(idv[1] < idv[2])
			{ v[2]->unlock(); v[1]->unlock(); v[0]->unlock(); }
			else
			{ v[1]->unlock(); v[2]->unlock(); v[0]->unlock(); }
		}
		else
		{ v[1]->unlock(); v[0]->unlock(); v[2]->unlock(); }
	}
	else
	{
		if(idv[0] > idv[2])
		{
			if(idv[1] < idv[2])
			{ v[0]->unlock(); v[2]->unlock(); v[1]->unlock(); }
			else
			{ v[0]->unlock(); v[1]->unlock(); v[2]->unlock(); }
		}
		else
		{ v[2]->unlock(); v[0]->unlock(); v[1]->unlock(); }
	}
	
}

#endif

}

#endif

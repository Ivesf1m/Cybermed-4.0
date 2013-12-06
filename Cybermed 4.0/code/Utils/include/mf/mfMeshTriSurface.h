#ifndef MFMESHTRISURFACE_H
#define MFMESHTRISURFACE_H

#include "mfMacros.h"
#include "mfSing.h"
#include "mfMesh.h"
#include "mfMeshOper.h"
//#include "mfVertexStarIteratorTriSurf.h"

namespace mf
{

/**
 *	@class		mfMeshTriSurface
 *	@file		mfMeshTriSurface.h
 *	@short
 *	Mesh Operator Class
 *
 *	Operation Class for Triangular surface in 3D space (with oriented triangles)
 *
 *	_Traits must have: ids, sVertex, sCell , sSing, sMesh
 *
 *	@author		Mario Lizier
 *	@author		Icaro da Cunha
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfMeshTriSurface : public mfMeshOper<_Traits>
{
public:

	typedef typename _Traits::ids		 ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex 	sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell 	sCell;		/**< Cell typename definition */

	typedef mfSing<_Traits> 		sSing;			/**< Singular typename definition */
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition */

	/**	Constructor
	 *
	 * \param _mesh: the mesh address that this class will manipulate
	 */
	mfMeshTriSurface(sMesh *_mesh);

	/**	Destructor */
	~mfMeshTriSurface();

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

#ifdef MF_THREADS
	void lockVertices(int num, sVertex* v);
	void unlockVertices(int num, sVertex* v);
#endif
};

template <class _Traits> mfMeshTriSurface<_Traits>::mfMeshTriSurface(sMesh *_mesh)
: mfMeshOper<_Traits>(_mesh)
{
}

template <class _Traits> mfMeshTriSurface<_Traits>::~mfMeshTriSurface()
{
}

template <class _Traits> void mfMeshTriSurface<_Traits>::addCell(ids idcell, ids *idvertices MF_DMUTEXV)
{
	MF_ASSERT((idvertices[0] >= 0)&&(idvertices[1] >= 0)&&(idvertices[2] >= 0));
	MF_ASSERT((idvertices[0] != idvertices[1])&&(idvertices[0] != idvertices[2])&&(idvertices[1] != idvertices[2]));

	sCell *c = this->mesh->getCell(idcell);
	ids idv[3] = { idvertices[0], idvertices[1], idvertices[2]};
	sVertex *v[3] = { this->mesh->getVertex(idv[0]), this->mesh->getVertex(idv[1]), this->mesh->getVertex(idv[2])};
	sCell *cop;
	sSing *s;
	ids icop;
	int i, pos;
	
	c->clearMates();
	
	//OF_ASSERT(geom.orientation(idv, v) != 0);
	
	//geom.orientation(idv, v);	
	
	c->setVertexId(0,idv[0]);
	c->setVertexId(1,idv[1]);
	c->setVertexId(2,idv[2]);
		
	for(i = 0; i < 3 ; i++)
	{
		s = v[(i+2)%3]->getSing();

		while (s)
		{
			icop = s->getCell();
			cop = this->mesh->getCell(icop);
			if ( cop->getVertexId((cop->getVertexIndex(idv[(i+2)%3]) + 1)%3) == idv[(i+1)%3] )
			{
				c->setMateId(i, icop);
				cop->setMateId((cop->getVertexIndex(idv[(i+2)%3]) + 2)%3, idcell);
				s = NULL;
			}
			else
				s = s->getNext();
		}
	}

	for(i = 0; i < 3; i++)
	{
		if (c->getMateId((i+2)%3) < 0)
		{
			if(c->getMateId((i+1)%3) >= 0)
			{
		  		pos = v[i]->inSings(c->getMateId((i+1)%3));
				v[i]->setSingCell(pos,idcell);
			}
			else
				v[i]->addSing(idcell);

		}
		else
		{
			if(c->getMateId((i+1)%3) >= 0)
			{
				icop = c->getMateId((i+1)%3);
				pos = v[i]->inSings(icop);
				while((icop >= 0)&&(icop != idcell))
				{
					cop = this->mesh->getCell(icop);
					icop = cop->getMateId((cop->getVertexIndex(idv[i])+1)%3);
					if(icop < 0)
						v[i]->delSing(pos);
				}
			}
		}
	}
}

//********** To test **********//
template <class _Traits> void mfMeshTriSurface<_Traits>::delCell(ids idcell MF_DMUTEXV)
{
	int i,pos;
	sCell *cop, *c = this->mesh->getCell(idcell);
	sVertex *v[3] = { this->mesh->getVertex(c->getVertexId(0)), this->mesh->getVertex(c->getVertexId(1)), this->mesh->getVertex(c->getVertexId(2))};
	ids icop;

	for(i = 0; i < 3; i++)
	{
		if(c->getMateId((i+2)%3) >= 0)
		{
			if(c->getMateId((i+1)%3) >= 0)
			{
				icop = c->getMateId((i+1)%3);
				while((icop >= 0)&&(icop != idcell))
				{
					cop = this->mesh->getCell(icop);
					icop = cop->getMateId((cop->getVertexIndex(c->getVertexId(i))+1)%3);
					if(icop < 0)
						v[i]->addSing(c->getMateId((i+1)%3));
					else if (icop == idcell)
						v[i]->getSing()->setCell(c->getMateId((i+1)%3));
				}
			}
		}
		else
		{
			pos = v[i]->inSings(idcell);
			if(c->getMateId((i+1)%3) >= 0)
				v[i]->setSingCell(pos,c->getMateId((i+1)%3));
			else
				v[i]->delSing(pos);
		}
	}
		
	for(i=0; i < 3; i++)
	{
		icop = c->getMateId(i);
		if(icop >= 0)
		{
			cop = this->mesh->getCell(icop);
			cop->setMateId(cop->getMateIndex(idcell),-1);
		}
	}
	
	c->setMateId(0,-1);
	c->setMateId(1,-1);
	c->setMateId(2,-1);
}

}

#endif

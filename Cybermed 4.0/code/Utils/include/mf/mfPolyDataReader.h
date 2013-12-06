#ifndef MFPOLYDATAREADER_H
#define MFPOLYDATAREADER_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfReader.h"

namespace mf
{

template <class _Traits> class mfPolyDataReader : public mfReader<_Traits>
{
public:
	typedef typename _Traits::space space;			/**< Space typename definition */
	typedef typename _Traits::ids ids;			/**< Id typename definition */
	typedef typename _Traits::sVertex sVertex;		/**< Vertex typename definition */
	typedef typename _Traits::sCell sCell;			/**< Cell typename definition */
	typedef typename _Traits::sMesh sMesh;			/**< Mesh typename definition */
	typedef typename _Traits::sGeometric sGeometric;	/**< Geometric typename definition */

	/** Constructor */
	mfPolyDataReader();

	/** Destructor */
	~mfPolyDataReader();

	void checkPoints(bool value);

	virtual bool read(sMesh* malha, const char* filename);

private:

	class sObject
	{
		public:
		sVertex *v;
		ids id;
	};

	class sObjectCompare
	{
		public:
		bool greater(sObject v1, sObject v2, int dim)
		{
			MF_ASSERT((dim == 0)||(dim == 1));
			return v1.v->getCoord(dim) > v2.v->getCoord(dim);
		};
	};
	
	bool cpoints;
	mfKdTree<sObject,sObjectCompare> kd;	
	mfVector<ids,ids> *vtx;
	sVertex vtemp;
	sObject vobj;
	sObject vresult;
	sGeometric geom;	/**< Geometric operations class instance */

	bool reader(ifstream &pf, sMesh* malha);
	int sameVertices(sCell *cell, ids *vtx);
	
};

template <class _Traits> mfPolyDataReader<_Traits>::mfPolyDataReader()
: kd(sVertex::getDimension())
{
	cpoints = false;
	vtx = NULL;
}

template <class _Traits> mfPolyDataReader<_Traits>::~mfPolyDataReader()
{
}

template <class _Traits> void mfPolyDataReader<_Traits>::checkPoints(bool value)
{
	cpoints = value;
}

template <class _Traits> bool mfPolyDataReader<_Traits>::read(sMesh* malha, const char *filename)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);
	
	geom.setMesh(malha);
	if(cpoints)
		vtx  = new mfVector<ids,ids>(malha->getBlockSize());

	ifstream pf(filename);
	
	bool ret = true;
	
	if( pf.is_open())
	{
			if(! reader(pf, malha))
				ret = false;
		
			pf.close();
	}
	else
		ret = false;
	
	if (vtx)
		delete vtx;
		
	return ret;
}

template <class _Traits> bool mfPolyDataReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	char auxstr[255];
	space coords[3];
	sCell cell;
	int i, nv, j, nc, k, idnv;
	int auxvtx[cell.getNumberVerticesInCell()];
	bool test;

	MF_ASSERT(auxstr);
	
	
	while( (! pf.eof())&&(strcmp(auxstr,"POINTS") != 0) )
		pf >> auxstr;
	
	if(! pf.eof())
	{
		pf >> nv;
		pf >> auxstr;
		
		MF_ASSERT(nv > 0);
	
		if(cpoints)

		for (i=0; i<nv; i++)
		{
			for(j = 0; j < 3; j++)
				pf >> coords[j];

			if(cpoints)
			{
				vobj.v = &vtemp;
				vobj.v->setCoords(coords);
				test = false;
				if(kd.size() > 0)
				{
					vresult = kd.nearest(vobj);
					test = geom.sameVertices(vresult.v, vobj.v);
				}
				if(test)
					(*vtx)[i] = vresult.id;
				else
				{
					(*vtx)[i] = malha->addVertex(coords);
					vobj.v = malha->getVertex((*vtx)[i]);
					vobj.id = (*vtx)[i];
					kd.insert(vobj);
				}
			}
			else
				malha->addVertex(coords);
		}
	}
	else 
		return false;


	while( (! pf.eof())&&(strcmp(auxstr,"POLYGONS") != 0) )
		pf >> auxstr;
	
	if( !pf.eof() )
	{
		pf >> nc;
		pf >> auxstr;
			
		MF_ASSERT(nc >= 0);
		
		mfVertexStarIteratorTriSurf<_Traits> itvs(malha);
		bool repetida;
		
		for (i=0; i<nc; i++)
		{
			pf >> idnv;
		
			MF_ASSERT(idnv <= cell.getNumberVerticesInCell());
		
			for (j=0; j < cell.idnv ; j++)
			{
				pf >> k;
				MF_ASSERT((k >= 0)&&(k < nv));
				if(cpoints)
					auxvtx[j] = (*vtx)[k];
				else
					auxvtx[j] = k;
			}
			for(j=idnv; j < cell.getNumberVerticesInCell(); j++)
			{
				auxvtx[j] = -1;
			}

			repetida = false;
			if(malha->getVertex(auxvtx[0])->getNumberOfSings() > 0)
				for(itvs.initialize(auxvtx[0]); itvs.notFinish(); ++itvs)
					if(sameVertices(*itvs, auxvtx) == 3)
					{
						repetida = true;
						break;
					}
		
			if(!repetida)
				malha->addCell(auxvtx);
		}
	}
	else
		return false;
		
	return true;
}

template <class _Traits> int mfPolyDataReader<_Traits>::sameVertices(sCell *cell, ids *vtx)
{
	int i, j, v1, v2, nv = 0;
	
	for(i=0; i<3; i++)
	{
		v1 = cell->getVertexId(i);
		for(j=0; j<3; j++)
		{
			v2 = vtx[j];
			if(v1 == v2)
			{
				nv++;
				break;
			}
		}
	}
	
	return nv;
}

}

#endif

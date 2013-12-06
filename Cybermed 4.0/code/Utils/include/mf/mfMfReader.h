#ifndef MFMFREADER_H
#define MFMFREADER_H

#include <fstream>

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfBinaryIO.h"
#include "mfReader.h"

using namespace std;

namespace mf
{

template <class _Traits> class mfMfReader : public mfReader<_Traits>
{
public:
	typedef typename _Traits::space 	space;		/**< Space typename definition */
	typedef typename _Traits::ids 		ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex 	sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell 	sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition */
	typedef mfBinaryIO<_Traits> 		sBinaryIO;	/**< Binary in/out typename definition */
	
	/** Constructor */
	mfMfReader();
	
	/** Destructor */
	~mfMfReader();
	
	virtual bool read(sMesh* malha, const char* filename);

private:
	sBinaryIO io;		/**< Binary in/out operator instance */

	bool checkVersion(ifstream &pf);
	bool readHeader(ifstream &pf, ids &nv, ids &nc);

	bool reader(ifstream &pf, sMesh* malha);
};

template <class _Traits> mfMfReader<_Traits>::mfMfReader()
{
}

template <class _Traits> mfMfReader<_Traits>::~mfMfReader()
{
}

template <class _Traits> bool mfMfReader<_Traits>::read(sMesh* malha, const char *filename)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);

	ifstream pf(filename, ios_base::in | ios_base::binary);

	if( pf.is_open())
	{
			if(! reader(pf, malha))
				return false;

			pf.close();
	}
	else
		return false;

	return true;
}

template <class _Traits> bool mfMfReader<_Traits>::checkVersion(ifstream &pf)
{
	char c;
	
	pf.read(&c, sizeof(char)); if(c != 'M') return false;
	pf.read(&c, sizeof(char)); if(c != 'F') return false;
	pf.read(&c, sizeof(char)); if(c != '-') return false;
	pf.read(&c, sizeof(char)); if(c != 'B') return false;
	pf.read(&c, sizeof(char)); if(c != 'I') return false;
	pf.read(&c, sizeof(char)); if(c != 'N') return false;
	pf.read(&c, sizeof(char)); if(c != 'A') return false;
	pf.read(&c, sizeof(char)); if(c != 'R') return false;
	pf.read(&c, sizeof(char)); if(c != 'Y') return false;
	pf.read(&c, sizeof(char)); if(c != '-') return false;
	pf.read(&c, sizeof(char)); if(c != 'V') return false;
	pf.read(&c, sizeof(char)); if(c != '1') return false;
	pf.read(&c, sizeof(char)); if(c != '.') return false;
	pf.read(&c, sizeof(char)); if(c != '0') return false;
	pf.read(&c, sizeof(char)); if(c != '0') return false;
	pf.read(&c, sizeof(char)); if(c != '1') return false;

	return true;	
}

template <class _Traits> bool mfMfReader<_Traits>::readHeader(ifstream &pf, ids &nv, ids &nc)
{
	if( ( io.idsLoad(pf) <= (int)sizeof(space) ) && ( io.idsLoad(pf) <= (int)sizeof(ids)) )
	{
		if( ( io.idsLoad(pf) == sVertex::getDimension() ) && ( io.idsLoad(pf) == sCell::getDimension() ) )
		{
			nv = io.idsLoad(pf);
			nc = io.idsLoad(pf);
		}
		else
			return false;
	}
	else
		return false;

	return true;
}


template <class _Traits> bool mfMfReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	sCell cell;
	space coords[3];
	int i, nv, j, nc, k;
	int auxvtx[cell.getNumberVerticesInCell()], auxop[cell.getNumberVerticesInCell()];

	if(!checkVersion(pf))
		return false;
	
	if(!readHeader(pf, nv, nc))
		return false;
		
	MF_ASSERT(nv > 0);
	
	for (i=0; i<nv; i++)
	{
		for(j = 0; j < sVertex::getDimension(); j++)
			coords[j] = io.spaceLoad(pf);

		malha->addVertex(coords);
	}

	MF_ASSERT(nc >= 0);
		
	for (i=0; i<nc; i++)
	{
		for (j=0; j< cell.getNumberVerticesInCell(); j++)
		{
			k = io.idsLoad(pf);
			MF_ASSERT((k >= 0)&&(k < nv));
			auxvtx[j] = k;
		}
		
		for (j=0; j < cell.getNumberVerticesInCell(); j++)
		{
			k = io.idsLoad(pf);
			auxop[j] = k;
		}
		
		malha->addCell(auxvtx, auxop);
	}

	sVertex *v;
	ids n;

	for (i=0; i<nv; i++)
	{
		k = io.idsLoad(pf);
		
		v = malha->getVertex(i); 
		
		for(j=0; j < k; j++)
		{
			n = io.idsLoad(pf);
			v->addSing(n);
		}
	}	
	
	return true;
}

}

#endif

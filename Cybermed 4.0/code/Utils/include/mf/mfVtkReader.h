#ifndef MFVTKREADER_H
#define MFVTKREADER_H

#include <fstream>

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfReader.h"

using namespace std;

namespace mf
{

template <class _Traits> class mfVtkReader : public mfReader<_Traits>
{
public:
	typedef typename _Traits::space		space;		/**< Space typename definition */
	typedef typename _Traits::ids		ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex	sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell		sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition */

	/** Constructor */
	mfVtkReader();

	/** Destructor */
	~mfVtkReader();

	virtual bool read(sMesh* malha, const char* filename);
	
	virtual bool readColor(float rgba[], const char *filename);

private:

	bool reader(ifstream &pf, sMesh* malha);
};

template <class _Traits> mfVtkReader<_Traits>::mfVtkReader()
{
}

template <class _Traits> mfVtkReader<_Traits>::~mfVtkReader()
{
}

template <class _Traits> bool mfVtkReader<_Traits>::read(sMesh* malha, const char *filename)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);

	ifstream pf(filename);

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

template <class _Traits> bool mfVtkReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	char auxstr[255];
	space coords[3];
	sCell cell;
	int i, nv, j, nc, k, idnv;
	int auxvtx[cell.getNumberVerticesInCell()];

	MF_ASSERT(auxstr);

	while( (! pf.eof())&&(strcmp(auxstr,"POINTS") != 0) )
		pf >> auxstr;

	if(! pf.eof())
	{
		pf >> nv;
		pf >> auxstr;

		MF_ASSERT(nv > 0);

		for (i=0; i<nv; i++)
		{
			for(j = 0; j < 3; j++)
				pf >> coords[j];

			malha->addVertex(coords);
		}
	}
	else
		return false;


	while( (! pf.eof())&&(strcmp(auxstr,"CELLS") != 0) )
		pf >> auxstr;

	if( !pf.eof() )
	{
		pf >> nc;
		pf >> auxstr;

		MF_ASSERT(nc >= 0);

		for (i=0; i<nc; i++)
		{
			pf >> idnv;

			MF_ASSERT(idnv <= cell.getNumberVerticesInCell());

			for (j=0; j < idnv ; j++) //cell.getNumberVerticesInCell()
			{
				pf >> k;
				MF_ASSERT((k >= 0)&&(k < nv));
				auxvtx[j] = k;
			}
			for(j = idnv; j < cell.getNumberVerticesInCell(); j++)
			{
				auxvtx[j] = -1;
			}

			malha->addCell(auxvtx);
		}
	}
	else
		return false;

	return true;
}

template <class _Traits> bool mfVtkReader<_Traits>::readColor(float rgba[], const char *filename) 
{
	return false;
}

}

#endif

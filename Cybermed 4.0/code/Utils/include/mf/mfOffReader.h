#ifndef MFOFFREADER_H
#define MFOFFREADER_H

#include <fstream>

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfReader.h"

using namespace std;

namespace mf
{

template <class _Traits> class mfOffReader : public mfReader<_Traits>
{
public:
	typedef typename _Traits::space space;		/**< Space typename definition */
	typedef typename _Traits::ids ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */

	/** Constructor */
	mfOffReader();
	
	/** Destructor */
	~mfOffReader();
	
	virtual bool read(sMesh* malha, const char* filename);

private:

	bool reader(ifstream &pf, sMesh* malha);
};

template <class _Traits> mfOffReader<_Traits>::mfOffReader()
{
}

template <class _Traits> mfOffReader<_Traits>::~mfOffReader()
{
}

template <class _Traits> bool mfOffReader<_Traits>::read(sMesh* malha, const char *filename)
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

template <class _Traits> bool mfOffReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	char auxstr[255];
	space coords[3];
	sCell cell;
	int i, nv, j, nc, k, idnv;
	ids auxvtx[cell.getNumberVerticesInCell()];

	MF_ASSERT(auxstr);
	
	while( (! pf.eof())&&(strcmp(auxstr,"OFF") != 0) )
		pf >> auxstr;
	
	if(! pf.eof())
	{
		pf >> nv;
		pf >> nc;
		pf >> k;

		MF_ASSERT(nv > 0);
	
		for (i=0; i<nv; i++)
		{
			for(j = 0; j < 3; j++)
				pf >> coords[j];

			malha->addVertex(coords);
		}

		MF_ASSERT(nc >= 0);

		//cout << "Vertices Lidos" << endl;

		for (i=0; i<nc; i++)
		{
			pf >> idnv;
		
			MF_ASSERT(idnv <= cell.getNumberVerticesInCell());
		
			for (j=0; j < idnv ; j++)
			{
				pf >> k;
				MF_ASSERT((k >= 0)&&(k < nv));
				auxvtx[j] = k;
			}
			for(j=idnv; j < 4; j++)
			{
				auxvtx[j] = -1;
			}

			//cerr << "c " << i << " " << auxvtx[0] << " " << auxvtx[1] << " " << auxvtx[2] << " " << auxvtx[3] << endl;

			malha->addCell(auxvtx);
		}
		//cerr << "Celulas Lidos" << endl;
	}
	else
		return false;
		
	return true;
}

}

#endif

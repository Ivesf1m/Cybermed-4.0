#ifndef MFOFFWRITER_H
#define MFOFFWRITER_H

#include <fstream>
#include <iomanip>

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfWriter.h"
#include "mfVerticesIterator.h"
#include "mfCellsIterator.h"

using namespace std;

namespace mf
{

//! Salva malhas em arquivo do tipo OFF sem dados
template <class _Traits>  class mfOffWriter : public mfWriter<_Traits>
{
public:
	typedef typename _Traits::space space;		/**< Space typename definition */
	typedef typename _Traits::ids ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */

	/** Constructor */
	mfOffWriter();
	
	/** Destructor */
	~mfOffWriter();
	
	virtual bool write(sMesh* malha, const char* filename);

private:

	bool writer(ofstream &pf, sMesh *malha);
};

template <class _Traits>  mfOffWriter<_Traits>::mfOffWriter()
{

}

template <class _Traits>  mfOffWriter<_Traits>::~mfOffWriter()
{
}

template <class _Traits> bool mfOffWriter<_Traits>::write(sMesh* malha, const char *filename)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);	
	
	ofstream pf(filename);
	
	if( pf.is_open())
	{
			if(! writer(pf, malha))
				return false;
		
			pf.close();
	}
	else
		return false;
	
	return true;
}

template <class _Traits> bool mfOffWriter<_Traits>::writer(ofstream &pf, sMesh* malha)
{
	int i = 0,j;
	sCell cell;
	
	pf << "OFF" << endl;
	pf << malha->getNumberOfVertices() << " ";
	pf << malha->getNumberOfCells() << " ";
	pf << "0" << endl;
	
	mfVerticesIterator<_Traits> itv(malha);
	
	mfVector<ids,ids> nvids(malha->getBlockSize());
	i = 0;
	for(itv.initialize(); itv.notFinish(); ++itv)
	{
		if (sVertex::getDimension() == 2)
			pf << setprecision(15) << itv->getCoord(0) << " " << setprecision(15) << itv->getCoord(1) << " 0.0" << endl;
		else if (sVertex::getDimension() == 3)
			pf << setprecision(15) << itv->getCoord(0) << " " << setprecision(15) << itv->getCoord(1) << " " << setprecision(15) << itv->getCoord(2) << endl;

		nvids[&itv] = i++;
	}
	
	mfCellsIterator<_Traits> itc(malha);
	
	for(itc.initialize(); itc.notFinish(); ++itc)
	{
		pf << itc->getNumberVerticesInCell();
	
		for(j = 0; j < itc->getNumberVerticesInCell(); j++)
			pf << " " << nvids[itc->getVertexId(j)];
		pf << endl;
	}
	
	return true;
}

}

#endif

#ifndef MFMFWRITER_H
#define MFMFWRITER_H

#include <fstream>
#include <iomanip>

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfBinaryIO.h"
#include "mfWriter.h"
#include "mfVerticesIterator.h"
#include "mfCellsIterator.h"

using namespace std;

namespace mf
{

template <class _Traits> class mfMfWriter : public mfWriter<_Traits>
{
public:
	typedef typename _Traits::space 	space;		/**< Space typename definition */
	typedef typename _Traits::ids 		ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex 	sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell 	sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition */
	typedef mfBinaryIO<_Traits> 		sBinaryIO;	/**< Binary in/out typename definition */

	/** Constructor */
	mfMfWriter();

	/** Destructor */
	~mfMfWriter();

	virtual bool write(sMesh* malha, const char* filename);

private:
	sBinaryIO io;
	
	void writeVersion(ofstream &pf);
	void writeHeader(ofstream &pf, ids nv, ids nc);
	
	bool writer(ofstream &pf, sMesh* malha);
};

template <class _Traits> mfMfWriter<_Traits>::mfMfWriter()
{
}

template <class _Traits> mfMfWriter<_Traits>::~mfMfWriter()
{
}

template <class _Traits> bool mfMfWriter<_Traits>::write(sMesh* malha, const char *filename)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);	
	
	ofstream pf(filename, ios_base::out | ios_base::binary | ios_base::trunc);
	
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

template <class _Traits> void mfMfWriter<_Traits>::writeVersion(ofstream &pf)
{
	pf.write("MF-BINARY-V1.001", 16*sizeof(char));
}

template <class _Traits> void mfMfWriter<_Traits>::writeHeader(ofstream &pf, ids nv, ids nc)
{
	sCell cell;

	io.idsStore(pf, sizeof(space) );
	io.idsStore(pf, sizeof(ids) );
	io.idsStore(pf, sVertex::getDimension() );
	io.idsStore(pf, cell.getNumberVerticesInCell() );
	io.idsStore(pf, nv);
	io.idsStore(pf, nc);
}


template <class _Traits> bool mfMfWriter<_Traits>::writer(ofstream &pf, sMesh* malha)
{

	int i, nv, j, nc;
	mfVector<ids,ids> nvids(malha->getBlockSize());
	mfVector<ids,ids> ncids(malha->getBlockSize());

	writeVersion(pf);
	
	nv = malha->getNumberOfVertices();
	nc = malha->getNumberOfCells();

	writeHeader(pf, nv, nc);

	mfVerticesIterator<_Traits> itv(malha);
	i = 0;
	for(itv.initialize(); itv.notFinish(); ++itv)
	{
		for(j = 0; j < sVertex::getDimension(); j++)
			io.spaceStore(pf, itv->getCoord(j));
		
		nvids[&itv] = i++;
	}

	mfCellsIterator<_Traits> itc(malha);
	i = 0;
	for(itc.initialize(); itc.notFinish(); ++itc)
		nvids[&itv] = i++;	
	
	for(itc.initialize(); itc.notFinish(); ++itc)
	{
		for(j = 0; j < itc->getNumberVerticesInCell(); j++)
			io.idsStore(pf, nvids[itc->getVertexId(j)]);

		for(j = 0; j < itc->getNumberVerticesInCell(); j++)
			if(itc->getMateId(j) >=0 )
				io.idsStore(pf, ncids[itc->getMateId(j)]);
			else
				io.idsStore(pf, -1);
	}
	
	for(itv.initialize(); itv.notFinish(); ++itv)
	{
		io.idsStore(pf,itv->getNumberOfSings());
		
		for(j=0; j < itv->getNumberOfSings(); j++)
			io.idsStore(pf,itv->getSingCell(j));
	}
	
	return true;
}

}

#endif

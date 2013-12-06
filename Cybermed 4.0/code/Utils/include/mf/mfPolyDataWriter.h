#ifndef MFPOLYDATAWRITER_H
#define MFPOLYDATAWRITER_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfWriter.h"

namespace mf
{

//! Salva malhas em arquivo do tipo VTK sem dados
template <class _Traits>  class mfPolyDataWriter : public mfWriter<_Traits>
{
public:
	typedef typename _Traits::space space;		/**< Space typename definition */
	typedef typename _Traits::ids ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */

	/** Constructor */
	mfPolyDataWriter();

	/** Destructor */
	~mfPolyDataWriter();

	virtual bool write(sMesh* malha, const char* filename);

private:

	bool writer(ofstream &pf, sMesh *malha);
};

template <class _Traits>  mfPolyDataWriter<_Traits>::mfPolyDataWriter()
{

}

template <class _Traits>  mfPolyDataWriter<_Traits>::~mfPolyDataWriter()
{
}

template <class _Traits> bool mfPolyDataWriter<_Traits>::write(sMesh* malha, const char *filename)
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

template <class _Traits> bool mfPolyDataWriter<_Traits>::writer(ofstream &pf, sMesh* malha)
{
	int j;
	sCell cell;

	pf << "# vtk DataFile Version 1.0" << endl;
	pf << "Mesh from mf" << endl;
	pf << "ASCII" << endl;
	pf << "DATASET UNSTRUCTURED_GRID" << endl;
	pf << "POINTS " << malha->getNumberOfVertices() << " float" << endl;

	mfVerticesIterator<_Traits> itv(malha);
	
	for(itv.initialize(); itv.notFinish(); ++itv)
	{
		if (sVertex::getDimension() == 2)
			pf << setprecision(15) << itv->getCoord(0) << " " << setprecision(15) << itv->getCoord(1) << " 0.0" << endl;
		else if (sVertex::getDimension() == 3)
			pf << setprecision(15) << itv->getCoord(0) << " " << setprecision(15) << itv->getCoord(1) << " " << setprecision(15) << itv->getCoord(2) << endl;
	}
	
	pf << endl << "POLYGONS " << malha->getNumberOfCells() << " " << (cell.getNumberVerticesInCell() + 1)*malha->getNumberOfCells() << endl;

	mfCellsIterator<_Traits> itc(malha);
	
	for(itc.initialize(); itc.notFinish(); ++itc)
	{
		pf << itc->getNumberVerticesInCell();
	
		for(j = 0; j < itc->getNumberVerticesInCell(); j++)
			pf << " " << itc->getVertexId(j);
		pf << endl; 
	}
	
//	pf << endl << "CELL_TYPES " << malha->getNumberOfCells() << endl;
//	
//	for (i=0; i<malha->getNumberOfCells(); i++)
//		pf << "5 ";
	
	return true;
}

}

#endif

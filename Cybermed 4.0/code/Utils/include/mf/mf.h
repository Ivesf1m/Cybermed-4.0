#ifndef MF_H
#define MF_H

// System includes ---------------------------------------------------------
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

#ifdef MF_THREADS
	#include <libpq-fe.h>
	#include <pthread.h>
#endif

#ifdef MF_DEBUG
	#include <assert.h>
#endif 

using namespace std;

// MF includes -------------------------------------------------------------
#include "mfMacros.h"
#include "mfBase.h"
#include "mfVector.h"
#include "mfList.h"
#include "mfKdTree.h"
#include "mfXmlParser.h"

#include "mfVertex.h"
#include "mfEdge.h"
#include "mfCell.h"
#include "mfFace.h"
#include "mfSing.h"

#include "mfSingularVertex.h"
#include "mfVertex2D.h"
#include "mfVertex3D.h"
//#include "mfCell2D.h"		// deve sair
//#include "mfCell3D.h"		// deve sair
#include "mfTriCell.h"
#include "mfQuadCell.h"
#include "mfHybrid2DCell.h"
#include "mfTetraCell.h"
//#include "mfHexaCell.h"
//#include "mfPrismCell.h"
//#include "mfPiramidCell.h"
//#include "mfHybrid3DCell.h"

#include "mfBoundaryCellIterator2D.h"
#include "mfBoundaryCellCIterator2D.h"
#include "mfCellsIterator.h"
#include "mfVerticesIterator.h"
//#include "mfVertexStarIterator2D.h"
//#include "mfVertexStarIterator3D.h"
#include "mfVertexStarIteratorTriSurf.h"
#include "mfVertexStarIteratorQuadSurf.h"
#include "mfVertexStarIteratorHybridSurf.h"
#include "mfVertexStarIteratorTetra.h"
#include "mfEdgeStarIteratorTetra.h"
#include "mfEdgesIterator.h"
//#include "mfEdgeStarIterator3D.h"	// deve sair

#include "mfMesh.h"
#include "mfMeshOper.h"
//#include "mfMesh2D.h"
//#include "mfMesh3D.h"		// deve dar lugar para o mfMeshTetra.h
#include "mfMeshTriSurface.h"
#include "mfMeshQuadSurface.h"
#include "mfMeshHybridSurface.h"
#include "mfMeshNOSurface.h"
#include "mfMeshTetra.h"
#include "mfDelaunay2D.h"
#include "mfGeometric.h"
#include "mfTopology.h"
#include "mfBinaryIO.h"

#include "mfReader.h"
#include "mfWriter.h"
#include "mfMfReader.h"
#include "mfVtkReader.h"
#include "mfPlyReader.h"
#include "mfPolyDataReader.h"
#include "mfOffReader.h"
#include "mfWrlReader.h"
#include "mfX3dReader.h"
#include "mfReaderFactory.h"
#include "mfReaderModel.h"
#include "mfMfWriter.h"
#include "mfVtkWriter.h"
#include "mfPolyDataWriter.h"
#include "mfOffWriter.h"

#include "mfTraits.h"

#include "mfTReader.h"
#include "mfPgReader.h"

#endif /* _MF_H */

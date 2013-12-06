#ifndef MFMESH_H
#define MFMESH_H

#include "mfMacros.h"
#include "mfVector.h"
#include <iostream>

using namespace std;

namespace mf
{

#define IDS typename mfMesh<_Traits>::ids
#define SVERTEX typename mfMesh<_Traits>::sVertex
#define SCELL typename mfMesh<_Traits>::sCell
#define SEDGE typename mfMesh<_Traits>::sEdge

/**
 *	@class		mfMesh
 *	@file		mfMesh.h
 *	@short
 *	Mesh Class
 *	This class must be initialized with elements types (vertices and cells) and the operation class.
 *	Operation class depends of the vertices and cells dimensions.
 *	_Traits must have: space, ids, sVertex, sCell, sEdge , sOper
 *
 *	@author		Mario Lizier
 *	@author		Icaro da Cunha
 *	@version	1.0
 *	@date		2007, july
 */
template <class _Traits> class mfMesh
{
public:

	typedef typename _Traits::space space;		/**< Space typename definition */
	typedef typename _Traits::ids ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell sCell;		/**< Cell typename definition */
	typedef typename _Traits::sEdge sEdge;		/**< Edge typename definition */
	typedef typename _Traits::sOper sOper;		/**< Operator typename definition */
	typedef typename _Traits::sTopology sTopology;	/**< Topology typename definition */

	//friend template<class _Traits> class sTopology;

	/**	Constructor
	 *
	 * 	\param block_size: size of vector blocks. The maximum size of vector is block_size * block_size
	 */
	mfMesh(ids block_size = 5000);

	/** Destructor */
	~mfMesh();

	/**	Add a vertex in mesh
	 *
	 *	\param coords: vector with the vertex coordinates
	 *
	 *	\return the vertex id in mesh
	 */
	ids addVertex(space *coords MF_DMUTEXVD);

	/**	Delete a vertex in mesh
	 *
	 *	\param idvertex: the vertex will be deleted
	 *
	 *	\return true if the vertex was deleted
	 */
	bool delVertex(ids idvertex MF_DMUTEXVD);

	/**	Return the number of vertices in mesh
	 */
	ids getNumberOfVertices(MF_DMUTEXD);

	/** Return the greater vertex id
	 */
	ids getVertexMaxId(MF_DMUTEXD);

	/**	Return the vertex address
	 *
	 *	\param idvertex: the vertex id
	 */
	sVertex* getVertex(ids idvertex MF_DMUTEXVD);

	/**	Return true if the specified vertex id is a vertex in mesh
	 */
	bool isVertex(ids idvertex MF_DMUTEXVD);

	/** Add a cell in mesh
	 *
	 *	\param idvertices: vector with vertices ids of the cell
	 *
	 *	\return the cell id in mesh
	 */
	ids addCell(ids *idvertices MF_DMUTEXVD);

	/** Delete a cell in mesh
	 *
	 *	\param idcell: the cell is
	 *
	 *	\return true if the cell was deleted
	 */
	bool delCell(ids idcell MF_DMUTEXVD);

	/** Return the number of cells in mesh
	 */
	ids getNumberOfCells(MF_DMUTEXD);

	/** Return the greater cell id in mesh
	 */
	ids getCellMaxId(MF_DMUTEXD);

	/**	Return the cell address
	 *
	 *	\param idcell: the cell id
	 */
	sCell* getCell(ids idcell MF_DMUTEXVD);

	/** Return if the specified cell id is a cell in mesh
	 */
	bool isCell(ids idcell MF_DMUTEXVD);

	/**	Define the number of vertices
	 *
	 * (DONT USE)
	 */
	void setNumberOfVertices(ids number MF_DMUTEXVD);

	/**	Define the number of cells
	 *
	 * (DONT USE)
	 */
	void setNumberOfCells(ids number MF_DMUTEXVD);

	/**	Add a vertex in specified position in mesh
	 *
	 *	\param idvertex: position of vertex
	 *	\param coords: vector with the vertex coordinates
	 *
	 *	\return the vertex id in mesh
	 */
	void addVertex(ids idvertex, space *coords MF_DMUTEXVD);

	/** Add a cell in specified position in mesh
	 *
	 *	\param idvertex: position of cell
	 *	\param idvertices: vector with vertices ids of the cell
	 *
	 *	\return the cell id in mesh
	 */
	void addCell(ids idcell, ids *idvertices MF_DMUTEXVD);

	ids addCell(ids *idvertices, ids *idops MF_DMUTEXVD);

	/** Add a edge in mesh
	 *
	 *	\return the edge id in mesh
	 */
	ids addEdge();

	/**	Return the number of edges in mesh
	 */
	ids getNumberOfEdges(MF_DMUTEXD);

	/** Return the greater edge id
	 */
	ids getEdgeMaxId(MF_DMUTEXD);
	
	/**	Return the edge address
	 *
	 *	\param idvertex: the vertex id
	 */
	sEdge* getEdge(ids idEdge MF_DMUTEXVD);

	/**	Return true if the specified edge id is a edge in mesh
	 */
	bool isEdge(ids idEdgex MF_DMUTEXVD);

	ids getBlockSize();

	void freeCell(ids idcell MF_DMUTEXVD);
	void freeVertex(ids idvertex MF_DMUTEXVD);
	void freeEdge(ids idedge MF_DMUTEXVD);

 protected:

	sOper oper;		/**< Mesh operator instance */

	ids bsize;

	mfVector<sVertex,ids> vertices;		/**< Vector of the mesh's vertices */
	mfVector<sCell,ids> cells;		/**< Vector of the mesh's cells */
	mfVector<sEdge,ids> edges;		/**< Vector of the mesh's edges */

#ifdef MF_THREADS
	pthread_mutex_t vertices_mutex;
	pthread_mutex_t cells_mutex;
	pthread_mutex_t edges_mutex;
#endif
};

template <class _Traits> mfMesh<_Traits>::mfMesh(ids block_size):
 oper(this), vertices(block_size), cells(block_size), edges(block_size)
{
	bsize = block_size;

#ifdef MF_THREADS
	pthread_mutex_init(&vertices_mutex,0);
	pthread_mutex_init(&cells_mutex,0);
	pthread_mutex_init(&edges_mutex,0);
#endif
}

template <class _Traits> mfMesh<_Traits>::~mfMesh()
{
#ifdef MF_THREADS
	pthread_mutex_destroy(&vertices_mutex);
	pthread_mutex_destroy(&cells_mutex);
#endif
}

template <class _Traits> IDS mfMesh<_Traits>::getBlockSize()
{
	return bsize;
}

// Vertices ***********************************************************************************

template <class _Traits> IDS mfMesh<_Traits>::addVertex(space *coords MF_DMUTEXV)
{
	ids idvertex;

	MF_ASSERT(coords);

	MF_LOCK(vertices_mutex);

	idvertex = vertices.getFree();

	MF_UNLOCK(vertices_mutex);

	addVertex(idvertex, coords MF_MUTEXV);

	return idvertex;
}

template <class _Traits> void mfMesh<_Traits>::addVertex(ids idvertex, space *coords MF_DMUTEXV)
{
	sVertex* v;

	MF_ASSERT(coords);

	v = &vertices[idvertex];
	v->setCoords(coords MF_MUTEXV);
}

template <class _Traits> bool mfMesh<_Traits>::delVertex(ids idvertex MF_DMUTEXV)
{
	MF_ASSERT(idvertex >= 0);

	bool temp;

	if(vertices[idvertex].getNumberOfSings(MF_MUTEX) == 0)
	{
		MF_LOCK(vertices_mutex);

		temp = vertices.free(idvertex);

		MF_UNLOCK(vertices_mutex);
	}
	else
		temp = false;	

	return temp;
}

template <class _Traits> IDS mfMesh<_Traits>::getNumberOfVertices(MF_DMUTEX)
{
	MF_LOCK(vertices_mutex);

	ids temp = vertices.getSize();

	MF_UNLOCK(vertices_mutex);

	return temp;
}

template <class _Traits> void mfMesh<_Traits>::setNumberOfVertices(ids number MF_DMUTEXV)
{
	MF_LOCK(vertices_mutex);

	vertices.setSize(number);

	MF_UNLOCK(vertices_mutex);
}

template <class _Traits> IDS mfMesh<_Traits>::getVertexMaxId(MF_DMUTEX)
{
	MF_LOCK(vertices_mutex);

	ids temp = vertices.getMaxId();

	MF_UNLOCK(vertices_mutex);

	return temp;
}

template <class _Traits> SVERTEX* mfMesh<_Traits>::getVertex(ids idvertex MF_DMUTEXV)
{
	MF_ASSERT(idvertex >= 0);
	return &vertices[idvertex];
}

template <class _Traits> bool mfMesh<_Traits>::isVertex(ids idvertex MF_DMUTEXV)
{
	return vertices[idvertex].inMesh(MF_MUTEX);
}

// Cells ***********************************************************************************

template <class _Traits> IDS mfMesh<_Traits>::addCell(ids *idvertices MF_DMUTEXV)
{
	MF_ASSERT(idvertices);
	MF_LOCK(cells_mutex);
	int idcell = cells.getFree();
	MF_UNLOCK(cells_mutex);
	oper.addCell(idcell, idvertices MF_MUTEXV);

	return idcell;
}

template <class _Traits> void mfMesh<_Traits>::addCell(ids idcell, ids *idvertices MF_DMUTEXV)
{
	MF_ASSERT(idvertices);

	oper.addCell(idcell, idvertices MF_MUTEXV);
}

template <class _Traits> bool mfMesh<_Traits>::delCell(ids idcell MF_DMUTEXV)
{
	MF_ASSERT( (idcell >= 0)&&(idcell <= getCellMaxId(MF_MUTEX)) );

	oper.delCell(idcell MF_MUTEXV);

	MF_LOCK(cells_mutex);

	cells.free(idcell);

	MF_UNLOCK(cells_mutex);

	return true;
}

template <class _Traits>  IDS mfMesh<_Traits>::getNumberOfCells(MF_DMUTEX)
{
	MF_LOCK(cells_mutex);

	ids temp = cells.getSize();

	MF_UNLOCK(cells_mutex);

	return temp;
}

template <class _Traits> void mfMesh<_Traits>::setNumberOfCells(ids number MF_DMUTEXV)
{
	MF_LOCK(cells_mutex);

	cells.setSize(number);

	MF_UNLOCK(cells_mutex);
}

template <class _Traits> IDS mfMesh<_Traits>::getCellMaxId(MF_DMUTEX)
{
	MF_LOCK(vertices_mutex);

	ids temp = cells.getMaxId();

	MF_UNLOCK(vertices_mutex);

	return temp;
}

template <class _Traits>  SCELL* mfMesh<_Traits>::getCell(ids idcell MF_DMUTEXV)
{
	MF_ASSERT(idcell >= 0);
	return &cells[idcell];
}

template <class _Traits> bool mfMesh<_Traits>::isCell(ids idcell MF_DMUTEXV)
{
	return cells[idcell].inMesh(MF_MUTEX);
}

template <class _Traits> IDS mfMesh<_Traits>::addCell(ids *idvertices, ids *idops MF_DMUTEXV)
{
	ids idcell;

	MF_ASSERT(idvertices);
	MF_ASSERT(idops);

	MF_LOCK(cells_mutex);

	idcell = cells.getFree();

	MF_UNLOCK(cells_mutex);

	oper.addCell(idcell, idvertices, idops MF_MUTEXV);

	return idcell;
}

// Edges ********************************

template <class _Traits> IDS mfMesh<_Traits>::addEdge()
{
	ids idedge;

	MF_LOCK(edges_mutex);

	idedge = edges.getFree();

	MF_UNLOCK(edges_mutex);

	return idedge;
}

template <class _Traits> IDS mfMesh<_Traits>::getNumberOfEdges(MF_DMUTEX)
{
	MF_LOCK(edges_mutex);

	ids temp = edges.getSize();

	MF_UNLOCK(edges_mutex);

	return temp;
}

template <class _Traits> IDS mfMesh<_Traits>::getEdgeMaxId(MF_DMUTEX)
{
	MF_LOCK(edges_mutex);

	ids temp = edges.getMaxId();

	MF_UNLOCK(edges_mutex);

	return temp;
}

template <class _Traits> SEDGE* mfMesh<_Traits>::getEdge(ids idEdge MF_DMUTEXV)
{
	MF_ASSERT(idEdge >= 0);
	return &edges[idEdge];
}

template <class _Traits> bool mfMesh<_Traits>::isEdge(ids idEdge MF_DMUTEXV)
{
	return edges[idEdge].inMesh(MF_MUTEX);
}

// Free ******************************************

template <class _Traits> void mfMesh<_Traits>::freeCell(ids idcell MF_DMUTEXVD)
{
	MF_LOCK(cells_mutex);

	cells.free(idcell);

	MF_UNLOCK(cells_mutex);
}

template <class _Traits> void mfMesh<_Traits>::freeVertex(ids idvertex MF_DMUTEXVD)
{
	MF_LOCK(vertices_mutex);

	vertices.free(idvertex);

	MF_UNLOCK(vertices_mutex);
}

template <class _Traits> void mfMesh<_Traits>::freeEdge(ids idedge MF_DMUTEXVD)
{
	MF_LOCK(edges_mutex);

	edges.free(idedge);

	MF_UNLOCK(edges_mutex);
}

#undef IDS
#undef SVERTEX
#undef SCELL
#undef SEDGE

}

#endif

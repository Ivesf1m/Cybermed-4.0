#ifndef MFHYBRIDCELL_H
#define MFHYBRIDCELL_H

#include "mfMacros.h"
#include "mfCell.h"

namespace mf
{

#define IDS typename mfHybridCell<_Traits>::ids

/** Base class of triangle
 *
*/
template <class _Traits> class mfHybridCell : public mfCell<4,_Traits>
{
public:

	typedef typename _Traits ::ids ids;	/**< Id typename definition */

	/** Constructor */
	mfHybridCell();

	/** Destructor */
	virtual ~mfHybridCell();

	/**	Return the edge id of the specified index
	 *
	 * 	\param index: position of edge
	 */
	ids getEdgeId(int index MF_DMUTEXVD);

	/** Define the edge id of the specified index
	 *
	 * 	\param index: position of edge
	 * 	\param edge: the edge id
	 */
	void setEdgeId(int index, ids edge MF_DMUTEXVD);

	/**	Return the dimension of this cell
	 */
	static inline int getDimension(){ return 2; };

	/**	Defines the number of edges of this cell
	 *
	 * 	\param value: number of edges
	 */
	//void setNumberVerticesInCell(int value);

	/**	Return the number of edges of this cell
	 */
	int getNumberVerticesInCell();

	/**	Defines the number of edges of this cell
	 *
	 * 	\param value: number of edges
	 */
	//void setNumberEdgesInCell(int value);

	/**	Return the number of edges of this cell
	 */
	int getNumberEdgesInCell();

private:
	//int numVertices;	/**< Number of vertices in cell */
	//int numEdges;		/**< Number of edges in cell */
	//ids vertices[4];
	ids edges[4];		/**< Cell's edges' ids vector */
	ids mates[4];     /**< Cell's face mate ids */
};

template <class _Traits> mfHybridCell<_Traits>::mfHybridCell()
{
#ifdef MF_THREADS
	pthread_mutex_lock(&this->smutex);
#endif

	for(int i = 0; i < 4; i++)
	{
		edges[i] = -1;
	}
	for(int i = 0; i < 4; i++)
	{
        mates[i] = -1;
    }
	
	//numVertices = 4;
	//numEdges = 4;

#ifdef MF_THREADS
	pthread_mutex_unlock(&this->smutex);
#endif
}

template <class _Traits> mfHybridCell<_Traits>::~mfHybridCell()
{
}

/*template <class _Traits> void mfHybridCell<_Traits>::setNumberEdgesInCell(int value)
{
	numEdges = value;
}*/

template <class _Traits> int mfHybridCell<_Traits>::getNumberEdgesInCell()
{
	if(edges[3] == -1)
		return 3;
	else
		return 4;
}

/*template <class _Traits> void mfHybridCell<_Traits>::setNumberVerticesInCell(int value)
{
	numVertices = value;
}*/

template <class _Traits> int mfHybridCell<_Traits>::getNumberVerticesInCell()
{
	if(this->vertices[3] == -1)
		return 3;
	else
		return 4;
}

template <class _Traits> IDS mfHybridCell<_Traits>::getEdgeId(int index MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < numEdges));

	MF_LOCK(smutex);

	ids temp = edges[index];

	MF_UNLOCK(smutex);

	return temp;
}

template <class _Traits> void mfHybridCell<_Traits>::setEdgeId(int index, ids edge MF_DMUTEXV)
{
	MF_ASSERT((index >= 0)&&(index < numEdges));

	MF_LOCK(smutex);

	edges[index] = edge;

	MF_UNLOCK(smutex);
}

#undef IDS

}

#endif

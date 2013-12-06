#ifndef MFITERATOR_H
#define MFITERATOR_H

#include "mfMacros.h"
#include "mfMesh.h"

namespace mf
{
 
/**
 *	@class		mfIterator
 *	@file		mfIterator.h
 *	@short
 *	Iterator base class
 *
 *	_Traits must have typenames: sMesh
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template<class _Traits> class mfIterator
{
public:

	typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */

	/** Set the mesh instance to which this class will manipulate.
	 *
	 * \param _mesh: the mesh address that this class will manipulate
	 */
	void setMesh( sMesh *_mesh);

protected:

	/** Constructor
	*
	* \param _mesh: the mesh instance that this class will manipulate
	*/
	mfIterator(sMesh *_mesh);

	/** Destrutor */
	~mfIterator();

	sMesh *mesh;	/**< The mesh that this class will manipulate */
};

template <class _Traits> mfIterator<_Traits>::mfIterator(sMesh *_mesh)
{
	MF_ASSERT(_mesh);
	mesh = _mesh;
}

template <class _Traits> mfIterator<_Traits>::~mfIterator()
{
}

template <class _Traits> void mfIterator<_Traits>::setMesh(sMesh *_mesh)
{
	MF_ASSERT(_mesh);
	mesh = _mesh;
}

}

#endif

#ifndef MFMESHOPER_H
#define MFMESHOPER_H

#include "mfMacros.h"
#include "mfMesh.h"

namespace mf
{

/**	Base Operation Class for mfMesh
 * 
 * 	_Traits must have: ids, sMesh
 */
template<class _Traits> class mfMeshOper
{
public:
	typedef typename _Traits::ids		ids;	/**< Id typename definition*/
	typedef typename _Traits::sMesh		sMesh;	/**< Mesh typename definition*/

protected:
	/** Constructor 
	*
	* \param _mesh: the mesh address that this class will manipulate
	*/
	mfMeshOper(sMesh *_mesh);

	/** Destrutor */
	~mfMeshOper();

	sMesh *mesh;	/** The mesh that this class will manipulate */
};

template <class _Traits> mfMeshOper<_Traits>::mfMeshOper(sMesh *_mesh)
{
	MF_ASSERT(_mesh);
	mesh = _mesh;
}

template <class _Traits> mfMeshOper<_Traits>::~mfMeshOper()
{
}

}

#endif

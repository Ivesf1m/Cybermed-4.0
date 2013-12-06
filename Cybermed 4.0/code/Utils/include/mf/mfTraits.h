#ifndef MFTRAITS_H
#define MFTRAITS_H

#include "mfVertex2D.h"
#include "mfVertex3D.h"
#include "mfEdge.h"
#include "mfTriCell.h"
#include "mfQuadCell.h"
#include "mfHybrid2DCell.h"
#include "mfFace.h"
#include "mfTetraCell.h"
#include "mfHexaCell.h"

//#include "mfCell3D.h"
#include "mfMesh2D.h"
//#include "mfMesh3D.h"
#include "mfMeshTriSurface.h"
#include "mfMeshQuadSurface.h"
#include "mfMeshHybridSurface.h"
#include "mfMeshTetra.h"
#include "mfMeshHexa.h"
#include "mfMeshNOSurface.h"
#include "mfGeometric.h"
#include "mfTopology.h"

/** Basic MF traits class
 */

namespace mf
{

// do equivalents to surfaces
/** Defines the features of a default 2D triangular mesh */
struct mfDefault2D
{
	typedef mfDefault2D			sTraits;	/**< Trait type definition*/
	typedef double				space;		/**< Space type definition */
	typedef int				ids;		/**< Id type definition*/

	typedef mfVertex2D<sTraits>		sVertex;	/**< 2D vertex definition */
	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
	typedef mfTriCell<sTraits>		sCell;		/**< Triangular cell definition */

	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */ //adapt
	typedef mfMesh2D<sTraits>		sOper;		/**< 2D mesh operation class definition */ //adapt

	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
};

// do equivalents to surfaces
/** Defines the features of a default 2D triangular mesh */
struct mfDefaultLong2D
{
	typedef mfDefaultLong2D			sTraits;	/**< Trait type definition*/
	typedef double				space;		/**< Space type definition */
	typedef int				ids;		/**< Id type definition*/

	typedef mfVertex2D<sTraits>		sVertex;	/**< 2D vertex definition */
	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
	typedef mfTriCell<sTraits>		sCell;		/**< Triangular cell definition */

	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */ //adapt
	typedef mfMesh2D<sTraits>		sOper;		/**< 2D mesh operation class definition */ //adapt

	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
};

/** Defines the features of a default tetrahedral mesh */
//struct mfDefault3D
//{
//	typedef mfDefault3D			sTraits;	/**< Trait type definition*/
//	typedef double				space;		/**< Space type definition */
//	typedef int				ids;		/**< Id type definition*/
//
//	typedef mfVertex3D<sTraits>		sVertex;	/**< 3D vertex definition */
//	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
//	typedef mfCell3D<sTraits>		sCell;		/**< Tetrahedral cell definition */ //mfTetraCell
//
//	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */
//	typedef mfMesh3D<sTraits>		sOper;		/**< Volumetric mesh operation class definition */ //mfMeshTetra
//
//	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
//	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
//};

/** Defines the features of a default tetrahedral mesh */
struct mfDefaultTetrahedra
{
	typedef mfDefaultTetrahedra			sTraits;	/**< Trait type definition*/
	typedef double				space;		/**< Space type definition */
	typedef int				ids;		/**< Id type definition*/

	typedef mfVertex3D<sTraits>		sVertex;	/**< 3D vertex definition */
	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
	typedef mfFace<sTraits>			sFace;
	typedef mfTetraCell<sTraits>		sCell;		/**< Tetrahedral cell definition */

	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */
	typedef mfMeshTetra<sTraits>		sOper;		/**< Volumetric mesh operation class definition */

	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
};

/** Defines the features of a default hexahedral mesh */
struct mfDefaultHexahedra
{
	typedef mfDefaultHexahedra			sTraits;	/**< Trait type definition*/
	typedef double				space;		/**< Space type definition */
	typedef int				ids;		/**< Id type definition*/

	typedef mfVertex3D<sTraits>		sVertex;	/**< 3D vertex definition */
	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
	typedef mfHexaCell<sTraits>		sCell;		/**< Hexahedral cell definition */

	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */
	typedef mfMeshHexa<sTraits>		sOper;		/**< Volumetric mesh operation class definition */

	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
};

/** Defines the features of a default triangular surface */
struct mfDefaultTriSurface
{
	typedef mfDefaultTriSurface		sTraits;	/**< Trait type definition*/
	typedef double				space;		/**< Space type definition */
	typedef int				ids;		/**< Id type definition*/

	typedef mfVertex3D<sTraits>		sVertex;	/**< 3D vertex definition */
	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
	typedef mfTriCell<sTraits>		sCell;		/**< Triangular cell definition */

	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */
	typedef mfMeshTriSurface<sTraits>	sOper;		/**< Surface mesh operation class definition */

	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
};

/** Defines the features of a default quadrangular surface */
struct mfDefaultQuadSurface
{
	typedef mfDefaultQuadSurface		sTraits;	/**< Trait type definition*/
	typedef double				space;		/**< Space type definition */
	typedef int				ids;		/**< Id type definition*/

	typedef mfVertex3D<sTraits>		sVertex;	/**< 3D vertex definition */
	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
	typedef mfQuadCell<sTraits>		sCell;		/**< Quadragular cell definition */

	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */
	typedef mfMeshQuadSurface<sTraits>	sOper;		/**< Surface mesh operation class definition */ //to test del cell

	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
};

/** Defines the features of a default hybrid surface */
struct mfDefaultHybridSurface
{
	typedef mfDefaultHybridSurface		sTraits;	/**< Trait type definition*/
	typedef double				space;		/**< Space type definition */
	typedef int				ids;		/**< Id type definition*/

	typedef mfVertex3D<sTraits>		sVertex;	/**< 3D vertex definition */
	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
	typedef mfHybrid2DCell<sTraits>		sCell;		/**< Hybrid cell definition */

	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */
	typedef mfMeshHybridSurface<sTraits>	sOper;		/**< Surface mesh operation class definition */ //to finish

	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
};

// to adapt
/** Defines the features of a default not oriented surface */
struct mfDefaultNOSurface
{
	typedef mfDefaultNOSurface		sTraits;	/**< Trait type definition*/
	typedef double				space;		/**< Space type definition */
	typedef int				ids;		/**< Id type definition*/

	typedef mfVertex3D<sTraits>		sVertex;	/**< 3D vertex definition */
	typedef mfEdge<sTraits>			sEdge;		/**< Edge definition */
	typedef mfTriCell<sTraits>		sCell;		/**< Triangular cell definition */

	typedef mfMesh<sTraits>			sMesh;		/**< Mesh definition */
	typedef mfMeshNOSurface<sTraits>	sOper;		/**< Surface mesh operation class definition */

	typedef mfGeometric<sTraits>		sGeometric;	/**< Geometric operations class definition */
	typedef mfTopology<sTraits>		sTopology;	/**< Topological operations class definition */
};

}

#endif

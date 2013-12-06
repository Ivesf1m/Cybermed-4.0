#ifndef _CYB_FFD_PARAMETERS_H_
#define _CYB_FFD_PARAMETERS_H_

#include <cmath>
#include "cybFFDNode.h"

class CybFFDParameters
{
public:
  
	typedef mfVerticesIterator<cybSurfaceTriTraits> vIterator;
	typedef mfVertexStarIteratorTriSurf<cybSurfaceTriTraits> vStarIterator;
	typedef cybVertex<cybSurfaceTriTraits> sVertex;
	
	CybFFDNode *listPoints;
	int layer;
	int nPontos;
	float translate, scale;

	double factorial(int n);

	double NewtonBinomial(int n, int k);

public:

	CybFFDParameters(int layer);
	
	void init();

	double BernsteinBase(float s, int m, int j);

	void calculateBoxVertex(int layer);

	void calculateControlPoints();

	CybVector3D<float> calculateCoordenate(CybFFDNode* e);
	
	CybVector3D<float> calculateNewPoint(CybFFDNode* e, CybVector3D<float> coordenate);
	
	void initListPoints();

	void toString();
	
};

#endif /*_CYB_FFD_NODE_H_*/

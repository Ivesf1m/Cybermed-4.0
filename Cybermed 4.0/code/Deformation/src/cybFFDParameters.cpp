#include "cybFFDParameters.h"

	CybFFDParameters::CybFFDParameters(int layer)
	{		
		this->translate = 10;
		this->scale = 10;
		this->layer = layer;
		this->listPoints = new CybFFDNode[CybParameters::getInstance()->nv[this->layer]]; 					
		this->init();
		//this->calculateControlPoints();
		this->initListPoints();
		//this->calculateBoxVertex(layer);		
	}
	
	void CybFFDParameters::init()
	{
		vIterator vIterator(CybParameters::getInstance()->mesh[this->layer]);
		for(vIterator.initialize(); vIterator.notFinish(); ++vIterator) nPontos++;
	}

	double CybFFDParameters::factorial(int n)
	{
		if(n >= 0)
		{
			if(n==0 || n==1) return 1;
	
			double aux = 1;
			for(int i=2; i<=n;i++)
				aux *= i;
			return aux;
		} 	
		return 0;
	}
	
	double CybFFDParameters::NewtonBinomial(int n, int k)
	{
		if(k == 0 || k == n) return 1;
		if(k == 1) return n; 
	
		if( k > n/2)
			return NewtonBinomial(n,n-k);
	
		if(n <= 10)
			return factorial(n)/(factorial(k)*factorial(n-k));
	
		double res = 1;	
		for(int i = n; i > n-k;i--)
			res *= i;
	
		return res/factorial(k);	
	}
	
	double CybFFDParameters::BernsteinBase(float s, int m, int j)
	{
		return (NewtonBinomial(m,j)*pow(1-s,m-j)*pow(s,j));	
	}
	
	void CybFFDParameters::initListPoints()
	{
		vIterator vIterator(CybParameters::getInstance()->mesh[this->layer]);
		vStarIterator itvs(CybParameters::getInstance()->mesh[this->layer]);
		vStarIterator  *neighbor;

		float menorX = 0,menorY = 0,menorZ = 0,maiorX = 0,maiorY = 0, maiorZ = 0;
		sVertex *vertex;

		CybVector3D<float> point;
		CybVector3D<float> vector;
		CybVector3D<float> newPoint;
		int nvertex = 0;
		CybFFDNode* element;
	
		for(vIterator.initialize(),nvertex=0; vIterator.notFinish(); ++vIterator,nvertex++)
		{	
			element = new CybFFDNode();
	
			vertex = *vIterator;
			element->vertex = vertex;
	
			element->point[0] = vertex->getCoord(0);
			element->point[1] = vertex->getCoord(1);
			element->point[2] = vertex->getCoord(2);
	
			//	element->neighbors.insertOnlyOne(nvertex);
	
			for( itvs.initialize( nvertex ); itvs.notFinish(); ++itvs) 		
			{	
				//cout << itvs->getVertexId( (itvs->getVertexIndex(nvertex)+1)%3 ) << " ";
				element->neighbors.insertOnlyOne(itvs->getVertexId( (itvs->getVertexIndex(nvertex)+1)%3));				
			}
			cout << endl;
			for( itvs.initialize( nvertex ); itvs.notFinish(); ++itvs) 
			{
				//cout << itvs->getVertexId( (itvs->getVertexIndex(nvertex)+2)%3 ) << " ";
				element->neighbors.insertOnlyOne(itvs->getVertexId( (itvs->getVertexIndex(nvertex)+2)%3));		
			}	
			int size = element->neighbors.size();
			/*for(int i=0; i < size ; i++)
			{
				for( itvs.initialize( element->neighbors.pos(i) ); itvs.notFinish(); ++itvs) 		
				{	
				//cout << itvs->getVertexId( (itvs->getVertexIndex(element->neighbors.pos(i) )+1)%3 ) << " ";
					element->neighbors.insertOnlyOne(itvs->getVertexId( (itvs->getVertexIndex(element->neighbors.pos(i) )+1)%3));				
				}
				cout << endl;
				for( itvs.initialize( element->neighbors.pos(i)  ); itvs.notFinish(); ++itvs) 
				{
				//cout << itvs->getVertexId( (itvs->getVertexIndex(element->neighbors.pos(i) )+2)%3 ) << " ";
					element->neighbors.insertOnlyOne(itvs->getVertexId( (itvs->getVertexIndex(element->neighbors.pos(i) )+2)%3));		
				}
			}
			*/
			for(int i=0; i < element->neighbors.size(); i++)
				cout << element->neighbors.pos(i) << " ";
	
			cout << endl;
	
			this->listPoints[nvertex] = *element;			
		}	
	
		for(vIterator.initialize(),nvertex=0; vIterator.notFinish(); ++vIterator,nvertex++)
		{	
			for(int i=0; i<element->neighbors.size(); i++)
			{
				element = &this->listPoints[nvertex];
				vertex  = this->listPoints[element->neighbors.pos(i)].vertex;
	
				point[0] = vertex->getCoord(0);
				point[1] = vertex->getCoord(1);
				point[2] = vertex->getCoord(2);
	
				if(point[0] < menorX) menorX = point[0];
				if(point[0] > maiorX) maiorX = point[0];
	
				if(point[1] < menorY) menorY = point[1];
				if(point[1] > maiorY) maiorY = point[1];
	
				if(point[2] < menorZ) menorZ = point[2];
				if(point[2] > maiorZ) maiorZ = point[2];				
			}	
	
			element->min[0] = menorX - translate;
			element->min[1] = menorY - translate;
			element->min[2] = menorZ - translate;
			element->max[0] = maiorX + translate;
			element->max[1] = maiorY + translate;
			element->max[2] = maiorZ + translate; 
	
			element->min[0] = menorX*scale ;
			element->min[1] = menorY*scale ;
			element->min[2] = menorZ*scale ;
			element->max[0] = maiorX*scale ;
			element->max[1] = maiorY*scale ;
			element->max[2] = maiorZ*scale ;
	
			element->min.show();
			element->max.show();
	
			vector = element->max - element->min;
			element->S[0] = vector[0];
			element->U[1] = vector[1];
			element->T[2] = vector[2];
	
			point[0] = 0;
			point[1] = 0;
			point[2] = 0;
			maiorX = 0;
			maiorY = 0;
			maiorZ = 0;
			menorX = 0;
			menorY = 0;
			menorZ = 0;
		}
	}
	
	CybVector3D<float> CybFFDParameters::calculateCoordenate(CybFFDNode* e)
	{
		CybVector3D<float> coordenate, point(e->vertex->getCoord(0),e->vertex->getCoord(1),e->vertex->getCoord(2));
	
		coordenate[0] = ((e->T*e->U)^(point - e->min))/((e->T*e->U)^e->S);
		coordenate[1] = ((e->S*e->T)^(point - e->min))/((e->S*e->T)^e->U); 
		coordenate[2] = ((e->S*e->U)^(point - e->min))/((e->S*e->U)^e->T);
	
		return coordenate;
	}
	
	CybVector3D<float> CybFFDParameters::calculateNewPoint(CybFFDNode* e, CybVector3D<float> coordenate)
	{
		vIterator vIterator(CybParameters::getInstance()->mesh[this->layer]);
		int size = e->neighbors.size(),k;
		CybFFDNode element;
		sVertex* vertex;
		CybVector3D<float> newPoint, p;
	
		//coordenate = calculateCoordenate(e);
		//coordenate.toString();
		//cout << "size: " << size << endl;
	
		cout << "aki" << endl;
	
		if(fabs(coordenate[0]) > 1 || fabs(coordenate[1]) > 1 || fabs(coordenate[2]) > 1)
			return e->point; 

		// p.x = e->vertex->getCoord(0);
		//  p.y = e->vertex->getCoord(1);
		//   p.z = e->vertex->getCoord(2);

		//	for(int j = 0; j < e->neighbors.size();j++)
		//		for(int k = 0; k < e->neighbors.size(); k++) 
		//			newPoint = newPoint + (p)*(BernsteinBase(coordenate.x,size,0)*BernsteinBase(coordenate.y,size,j)*BernsteinBase(coordenate.z,size,k));

		for(int i=0; i < e->neighbors.size();i++)	
			for(int j = 0; j < e->neighbors.size();j++)
				for(int k = 0; k < e->neighbors.size(); k++)
				{
					//	vertex =  this->listPoints[e->neighbors.pos(i)].vertex;
	
					//	p.x = vertex->getCoord(0);
					//	p.y = vertex->getCoord(1);
					//	p.z = vertex->getCoord(2);
					p = this->listPoints[e->neighbors.pos(i)].point;
	
					newPoint = newPoint + (p)*(BernsteinBase(coordenate[0],size-1,i)*BernsteinBase(coordenate[1],size-1,j)*BernsteinBase(coordenate[k],size-1,k));
					//cout << i << ": ";
					//newPoint.toString();
				}
		//newPoint.toString();	
		return newPoint*scale;
	}

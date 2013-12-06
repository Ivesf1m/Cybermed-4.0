#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "mf.h"

using namespace mf;

using namespace std;

int main()
{
	int numLayer, modoVis;
	char nomeArquivo[40] = { "./Modelos/EsferaPoucosQuadrados.wrl" };

	mfMesh<mfDefaultQuadSurface> malha;
	mfWrlReader<mfDefaultQuadSurface> entrada;
	mfQuadCell<mfDefaultQuadSurface> *c;
	mfVertexStarIteratorQuadSurf<mfDefaultQuadSurface> its(&malha);
	mfEdgesIterator<mfDefaultQuadSurface> eit(&malha);

	entrada.read(&malha, nomeArquivo);

	for(int i = 0; i<malha.getNumberOfCells(); i++)
	{
		c = malha.getCell(i);
		//cout << "num " << c->getNumberEdgesInCell() << endl;
		for(int j = 0; j < c->getNumberVerticesInCell(); j++)
		{
			cout << "vertex " << i << ":" << j << " :" << c->getVertexId(j) << endl;
			cout << "mate " << i << ":" << j << " :" << c->getMateId(j) << endl;
			//cout << "Edge " << i << ":" << j << " :" << c->getEdgeId(j) << endl;
			cout << "star\n";
			for(its.initialize(c->getVertexId(j));its.notFinish();++its)
			{
				cout << &its << " ";
			}
			cout << endl;
		}
	}

	cout << "Edges: " << endl;
	for(eit.initialize(0);eit.notFinish();++eit)
	{
		cout << &eit << " ";
	}
	cout << "\nNum Edge: " << malha.getNumberOfEdges() << endl;
}

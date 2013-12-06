#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

#include <iomanip>

#include "mf.h"

using namespace mf;

using namespace std;

int main()
{
	time_t inicio;
	float time;
	//char nomeArquivo[40] = { "./Modelos/Chinese_dragon.off" };
	//char nomeArquivo[40] = { "./Modelos/elephant-Face.off"};
	char nomeArquivo[40] = { "./Modelos/hand-olivier.off"};
	//char nomeArquivo[40] = { "./Modelos/TriNormal.wrl" };
	//char nomeArquivo[40] = { "./Modelos/TriTeste.wrl" };
	

	char *filename = { "teste123.txt" };

	//mfMesh<mfDefaultTriSurface> malha;
	//mfWrlReader<mfDefaultTriSurface> entrada;
	mfOffReader<mfDefaultTriSurface> entrada;
	mfTriCell<mfDefaultTriSurface> *c;
	//mfVertexStarIteratorTriSurf<mfDefaultTriSurface> its(&malha);

	ofstream pf(filename);

	for(int i=0; i<200; i++)
	{
		mfMesh<mfDefaultTriSurface> malha;
		inicio = clock();
		entrada.read(&malha, nomeArquivo);
		pf << ((float)(clock()-inicio)/CLOCKS_PER_SEC) << "\n";
		printf("%f\n", (float)(clock()-inicio)/CLOCKS_PER_SEC);
	}

	/*for(int i = 0; i<malha.getNumberOfCells(); i++)
	{
		c = malha.getCell(i);
		for(int j = 0; j < c->getNumberVerticesInCell(); j++)
		{
			//cout << "vertex " << i << ":" << j << " :" << c->getVertexId(j) << endl;
			//cout << "mate " << i << ":" << j << " :" << c->getMateId(j) << endl;
			//cout << "Edge " << i << ":" << j << " :" << c->getEdgeId(j) << endl;

			cout << "star " << c->getVertexId(j) << endl;
			inicio = clock();
			//for(int k=0; k<20000; k++)
			for(its.initialize(c->getVertexId(j));its.notFinish();++its)
			{
				cout << &its << " ";
			}
			//printf("%f\n", (float)(clock()-inicio)/CLOCKS_PER_SEC);
			cout << endl;
		}
	}*/

	/*cout << endl << "Estrela " << endl;
    for(int i=0; i<200; i++)
	{
		inicio = clock();
		for(int k=0; k<malha.getNumberOfVertices(); k++)
		{
			for(its.initialize(k);its.notFinish();++its)
			{
				//cout << &its << " ";
			}
			//cout << endl;
        }
        printf("%f\n", (float)(clock()-inicio)/CLOCKS_PER_SEC);
		//cout << endl;
	}*/
}

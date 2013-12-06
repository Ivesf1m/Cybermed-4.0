#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

#include <iomanip>

#include "mf.h"
#include "myTsReader.h"

using namespace mf;

using namespace std;

int main()
{
	time_t inicio;
	float time;
	//char nomeArquivo[40] = { "./Modelos/Chinese_dragon.off" };
	//char nomeArquivo[40] = { "./Modelos/TetraTeste.wrl" };
	//char nomeArquivo[40] = { "./Modelos/BunnyTetra.vtk" };
	char nomeArquivo[40] = { "./Modelos/spx.ts" };
	//char nomeArquivo[40] = { "./Modelos/tetrahedraFile.vtk"};

	char *filename = { "teste123.txt" };

	mfMesh<mfDefaultTetrahedra> malha;
	//mfWrlReader<mfDefaultTetrahedra> entrada;
	//mfVtkReader<mfDefaultTetrahedra> entrada;
	myTsReader<mfDefaultTetrahedra> entrada;
	//mfOffReader<mfDefaultTetrahedra> entrada;
	mfTetraCell<mfDefaultTetrahedra> *c;
	mfVertexStarIteratorTetra<mfDefaultTetrahedra> its(&malha);
	mfEdgeStarIteratorTetra<mfDefaultTetrahedra> ites(&malha);

	ofstream pf(filename);

	for(int i=0; i<200; i++)
	{
		mfMesh<mfDefaultTetrahedra> malha;
		inicio = clock();
		entrada.read(&malha, nomeArquivo);
		//entrada.read(&malha, nomeArquivo, 4);
		//pf << ((float)(clock()-inicio)/CLOCKS_PER_SEC) << "\n";
		printf("%f\n", (float)(clock()-inicio)/CLOCKS_PER_SEC);
	}

	/*for(int i = 0; i<malha.getNumberOfCells(); i++)
	{
		c = malha.getCell(i);
		cout << "->cell " << i << endl;
		for(int j = 0; j < c->getNumberVerticesInCell(); j++)
		{
			//cout << c->getNumberVerticesInCell() << " ";
			cout << "-vertex " << i << ":" << j << " :" << c->getVertexId(j) << endl;
			cout << ".mate " << i << ":" << j << " :" << c->getMateId(j) << endl;
			//cout << "Edge " << i << ":" << j << " :" << c->getEdgeId(j) << endl;

			cout << ".star " << c->getVertexId(j) << endl;
			inicio = clock();
			//for(int k=0; k<20000; k++)
			for(its.initialize(c->getVertexId(j));its.notFinish();++its)
			{
				cout << &its << " ";
			}
			//printf("%f\n", (float)(clock()-inicio)/CLOCKS_PER_SEC);
			cout << endl;
		}
	}

	cout << endl << endl << "edge star ";
	for(ites.initialize(0, 2, 1);ites.notFinish();++ites)
	{
		cout << &ites << ", ";
	}

	/*for(int i=0; i<200; i++)
	{
		//inicio = clock();
		for(int k=0; k<20000; k++)
		{
			for(its.initialize(2);its.notFinish();++its)
			{
				cout << &its << " ";
			}
            cout << endl;	
		}
        //printf("%f\n", (float)(clock()-inicio)/CLOCKS_PER_SEC);
		//cout << endl;
	}*/
}

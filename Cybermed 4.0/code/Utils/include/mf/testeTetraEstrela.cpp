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

	mfMesh<mfDefaultTetrahedra> malha;
	//mfWrlReader<mfDefaultTetrahedra> entrada;
	//mfVtkReader<mfDefaultTetrahedra> entrada;
	myTsReader<mfDefaultTetrahedra> entrada;
	//mfOffReader<mfDefaultTetrahedra> entrada;
	mfTetraCell<mfDefaultTetrahedra> *c;
	mfVertexStarIteratorTetra<mfDefaultTetrahedra> its(&malha);
	mfEdgeStarIteratorTetra<mfDefaultTetrahedra> ites(&malha);

	entrada.read(&malha, nomeArquivo);

	for(int i=0; i<200; i++)
	{
		inicio = clock();
		for(int k=0; k<malha.getNumberOfVertices(); k++)
		{
			for(its.initialize(1694);its.notFinish();++its)
			{
				//cout << &its << " ";
			}
            //cout << endl;	
		}
        printf("%f\n", (float)(clock()-inicio)/CLOCKS_PER_SEC);
		//cout << endl;
	}
}

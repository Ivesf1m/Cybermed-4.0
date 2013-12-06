#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>

#include <iomanip>

using namespace std;

int main()
{
	time_t inicio;
	char nomeArquivo[40] = { "./buste_quads.off" };
	//char nomeArquivo[40] = { "./mf/Modelos/EsferaMuitosTriangulos.wrl" };
	//char nomeArquivo[40] = { "Bacia-Pele.wrl" };
	//char nomeArquivo[40] = { "Bacia-Osso.wrl" };
	char filename[40] = { "buste_quads.obj" };
	int auxIndex;
	int index;
	int codVertex[4];
	double coords[3];
	//vector<double> vertices;
	//vector<int> cell;
	int *used;
	float *vertex[3];
	int *cell[4];
	int nV = 0, nC = 0;
	int vInC;
	int vId;
	int count;
	int i,j;

	bool notInList = true;

	ifstream pf(filename);
	ifstream pf1(filename);
	ofstream saida(nomeArquivo);
	
	saida << "OFF" << endl;
	saida << 0 << " " << 0 << " 0 " << endl;

	float coord;
	char aux;
	char auxstr[255];
	pf >> auxstr;
    while(strcmp(auxstr,"v") == 0)
	{
        pf >> coord;
		saida << coord << " ";
		pf >> coord;
		saida << coord << " ";
		pf >> coord;
		saida << coord << endl;
		pf >> auxstr;
		nV++;
	}
	
	float vtCrap;
	while(strcmp(auxstr,"vt") == 0)
	{
         pf >> vtCrap;
         pf >> vtCrap;
         pf >> auxstr;
    }

    while((strcmp(auxstr,"f") == 0) && (! pf.eof()))
	{
		saida << "4 ";

		pf >> vId;
		saida << vId-1 << " ";
		pf >> aux;
		pf>> vInC;

		pf >> vId;
		saida << vId-1 << " ";
		pf >> aux;
		pf>> vInC;

		pf >> vId;
		saida << vId-1 << " ";
		pf >> aux;
		pf>> vInC;

		pf >> vId;
		saida << vId-1 << " ";
		pf >> aux;
		pf>> vInC;

		saida << endl;
		nC++;
		pf >> auxstr;
	}
	
	saida << nV << " " << nC << endl;
}

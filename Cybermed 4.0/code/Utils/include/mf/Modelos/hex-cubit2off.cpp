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
	char nomeArquivo[40] = { "./mdg-1b.off" };
	//char nomeArquivo[40] = { "./mf/Modelos/EsferaMuitosTriangulos.wrl" };
	//char nomeArquivo[40] = { "Bacia-Pele.wrl" };
	//char nomeArquivo[40] = { "Bacia-Osso.wrl" };
	char filename[40] = { "mdg-1b.hex" };
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
	int nVert, nCell;
	int vInC;
	int vId;
	int count;
	int i,j;

	bool notInList = true;

	ifstream pf(filename);
	ifstream pf1(filename);
	ofstream saida(nomeArquivo);

	char c;
	int auxInt;
	pf >> c;
	pf >> nVert;
	pf >> nCell;

	saida << "OFF" << endl;
	saida << nVert << " " << nCell << " 0 " << endl;

	float coord;
	char aux;
	char auxstr[255];
	pf >> auxstr;
	while(strcmp(auxstr,"v") == 0)
	{
		pf >> coord;
		saida << setprecision(8) << coord << " ";
		pf >> coord;
		saida << setprecision(8) << coord << " ";
		pf >> coord;
		saida << setprecision(8) << coord << endl;
		pf >> auxstr;
		nV++;
	}

	int v0, v1, v2, v3, v4, v5, v6, v7;

	while((strcmp(auxstr,"h") == 0) && (! pf.eof()))
	{
		saida << "8 ";

		pf >> vId;
		v0 = vId-1;

		pf >> vId;
		v1 = vId-1;

		pf >> vId;
		v2 = vId-1;

		pf >> vId;
		v3 = vId-1;

		pf >> vId;
		v4 = vId-1;

		pf >> vId;
		v5 = vId-1;

		pf >> vId;
		v6 = vId-1;

		pf >> vId;
		v7 = vId-1;

		saida << v0 << " " << v1 << " " << v2 << " " << v3 << " " << v4 << " " << v5 << " " << v6 << " " << v7 << endl;
		nC++;
		pf >> auxstr;
	}
	
	saida << nV << " " << nC << endl;
}

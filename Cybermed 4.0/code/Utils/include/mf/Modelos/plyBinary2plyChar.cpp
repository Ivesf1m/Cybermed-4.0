#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>

#include <string>
#include <sstream>
#include <stdio.h>

#include <iomanip>

using namespace std;

int main()
{
    ifstream file[100];
    ofstream output;
    float di = 512, dj = 512, dk = 433;
    float ai = di/2, aj = dj/2, ak = dk/(2*1.3);
    float x, y, z;
    //space coord[3];
    int valor;
    unsigned char c;
    int i, j;
    //int aux = imageStart; //starting
    int cont = 0;

    FILE *pFile;
    
    pFile = fopen ("elephant2.ply","r+b");
    
    while (!feof(pFile))
    {
        fscanf (pFile, "%c", &c);

        valor = c;

        cout << valor;
    }
    
}

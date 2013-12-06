// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.
// *****************************************************************

#include "cybNaiveBayesIO.h"

CybNaiveBayesIO::CybNaiveBayesIO(char* file_name) : CybAssessIO(file_name, ".cyba_NB")
{
	
}
		
void CybNaiveBayesIO::write(void* nbObject)
{
	CybNaiveBayes* nb = (CybNaiveBayes*) nbObject;
	
	ofstream fout(this->getFile()); 
	
		if(fout.fail())
		{
			cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
			cout << flush;
			exit(0);
		}
		
	fout << "##" << nb->getVariablesNumber(); 

	fout << "\n\nSturges" << "\n[\n";
	
	fout << nb->getSturges();
	fout << "\n]";
	
	fout << "\n\nIntersections" << "\n[\n";
	fout << nb->getIntersections();
	fout << "\n]";

	fout << "\n\nTable" << "\n[\n";
	
	float*** table = nb->getTable();

	for(int i=0; i < nb->getVariablesNumber(); i++)
	{
		for(int j=0; j<nb->getSturges(); j++)
		{
			for(int k=0; k<TABLE_SIZE; k++)
			{
				fout << table[i][j][k];
				fout << " ";
			}
				fout << "\n";
		}
	}
	fout << "]";

	float*** intersectionTable = nb->getIntersectionTable();

	fout << "\n\nIntersectionTable" << "\n[\n";
	for(int i=0; i<nb->getSturges(); i++)
	{
		for(int j=0; j<nb->getSturges(); j++)
		{
			for(int k=0; k<nb->getSturges(); k++)
			{
				if (intersectionTable[i][j][k] > 0)
				{
					fout << i << " " << j << " " << k << " "<<  intersectionTable[i][j][k];
					fout << "\n";
				}
			}
		}
	}
	fout << "]";

	
	fout.close();
}
	
void* CybNaiveBayesIO::read()
{

	char bola;

	ifstream fin(this->getFile());

	
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
		exit(0);
	}
	

	char c = 'a';
	int number = 0;
	int intersections = 0;
	float*** table;
	float*** intersectionTable;
	int count = 0;
	int count2 = 0;
	int sturges = 0;
	int p, q, r, s = 0;
	fin >> c;
	fin >> c;
	fin >> number;

	
	CybNaiveBayes* nb = new CybNaiveBayes(number);
	
	while(c != '[')
		fin >> c;
	
	while(c != ']')
	{
		fin >> sturges;
		fin >> c;
		nb->setSturges(sturges);	
	}


	while(c != '[')
		fin >> c;

	while(c != ']')
	{
		fin >> intersections;
		fin >> c;
		nb->setIntersections(intersections);	
	}


	while(c != '[')
		fin >> c;

	table = nb->alocRefMatrix(number, sturges, TABLE_SIZE);

	if (table == NULL) cout << "null";

	for(int i=0; i<number; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<TABLE_SIZE; k++)
			{
				fin >> table[i][j][k];
			}
		}
	}

	nb->setTable(table);

	c = 'c';

	while(c != '[')
	{
		fin >> c;
	}


	intersectionTable = nb->alocRefMatrix(sturges, sturges, sturges);
	//STARTING ALL INTERSECTION TABLE VALUES AS ZEROS
	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				intersectionTable[i][j][k] = 0;
			}
		}
	}

	//READING THE INDEXES AND SETTING VALUES ON INTERSECTION TABLE

	for(int i=0; i < intersections; i++)
	{
		fin >> p;
		fin >> q;
		fin >> r;
		fin >> s;
		intersectionTable[p][q][r] = s;
	}

	nb->setIntersectionTable(intersectionTable);

	fin.close();
	
	return (void*) nb;
}		

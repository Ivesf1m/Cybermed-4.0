// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#include "cybFuzzyNaiveBayesIO.h"

CybFuzzyNaiveBayesIO::CybFuzzyNaiveBayesIO(char* file_name) : CybAssessIO(file_name, ".cyba_FNB")
{
	
}
		
void CybFuzzyNaiveBayesIO::write(void* fnbObject)
{
	CybFuzzyNaiveBayes* fnb = (CybFuzzyNaiveBayes*) fnbObject;
	
	ofstream fout(this->getFile()); 
	
		if(fout.fail())
		{
			cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
			cout << flush;
			exit(0);
		}
		
	fout << "##" << fnb->getVariablesNumber(); 

	fout << "\n\nSturges" << "\n[\n";
	
	fout << fnb->getSturges();
	fout << "\n]";

	fout << "\n\nIntersections" << "\n[\n";
	fout << fnb->getIntersections();
	fout << "\n]";

	fout << "\n\nHighest" << "\n[\n";
	fout << fnb->getHighest();
	fout << "\n]";

	fout << "\n\nTable" << "\n[\n";
	
	float*** table = fnb->getTable();

	for(int i=0; i < fnb->getVariablesNumber(); i++)
	{
		for(int j=0; j<fnb->getSturges(); j++)
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

	float*** intersectionTable = fnb->getIntersectionTable();

	fout << "\n\nIntersectionTable" << "\n[\n";
	for(int i=0; i<fnb->getSturges(); i++)
	{
		for(int j=0; j<fnb->getSturges(); j++)
		{
			for(int k=0; k<fnb->getSturges(); k++)
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
	
void* CybFuzzyNaiveBayesIO::read()
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
	int highest = 0;
	float*** table;
	float*** intersectionTable;
	int count = 0;
	int count2 = 0;
	int sturges = 0;
	int p, q, r, s = 0;
	fin >> c;
	fin >> c;
	fin >> number;

	CybFuzzyNaiveBayes* fnb = new CybFuzzyNaiveBayes(number);
	
	while(c != '[')
		fin >> c;
	
	while(c != ']')
	{
		fin >> sturges;
		fin >> c;
		fnb->setSturges(sturges);	
	}

	while(c != '[')
		fin >> c;

	while(c != ']')
	{
		fin >> intersections;
		fin >> c;
		fnb->setIntersections(intersections);	
	}

	while(c != '[')
		fin >> c;

	while(c != ']')
	{
		fin >> highest;
		fin >> c;
		fnb->setHighest(highest);	
	}


	while(c != '[')
		fin >> c;

	table = fnb->alocRefMatrix(number, sturges, TABLE_SIZE);

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

	fnb->setTable(table);

	c = 'c';

	while(c != '[')
	{
		fin >> c;
	}


	intersectionTable = fnb->alocRefMatrix(sturges, sturges, sturges);
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

	for(int i=0; i < intersections; i++)
	{
		fin >> p;
		fin >> q;
		fin >> r;
		fin >> s;
		intersectionTable[p][q][r] = s;
	}

	fnb->setIntersectionTable(intersectionTable);

	fin.close();
	
	return (void*) fnb;
}		

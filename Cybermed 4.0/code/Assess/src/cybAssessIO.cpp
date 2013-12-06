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

#include "cybAssessIO.h"

CybAssessIO::CybAssessIO(char* file_name, char* sufix)
{
	this->file_name = new char[strlen(file_name) + 1];
	
	for(int i=0; i < strlen(file_name); i++)
	{
		if(file_name[i] != '.')		
			this->file_name[i] = file_name[i];
		else
		{
			file_name[i] = '\0';
			break;
		}
	}
	
	this->file_name[strlen(file_name)] = '\0';
	
	this->sufix = sufix;
	validFile();
}
		
CybAssessIO::~CybAssessIO()
{
	delete[] this->file_name;
}
		
char* CybAssessIO::getFile()
{
	return this->file_name;
}

char* CybAssessIO::getDataFile()
{
	return this->data_file;
}

void CybAssessIO::validFile()
{
	int r = strlen(this->file_name);
	int s = strlen(this->sufix);
	int q = strlen(".cybaDATA");
	
	char* aux = new char[r+q+1];
	
	for(int i=0; i <= r+q; i++)
		aux[i] = '\0';
	
	strcat(aux, file_name);
	strcat(aux, ".cybaDATA");
	
	this->data_file = aux;	
	
	aux = new char[r+s+1];
	
	for(int i=0; i <= r+s; i++)
		aux[i] = '\0';
	
	strcat(aux, file_name);
	strcat(aux, sufix);
	
	this->file_name = aux;
}

void CybAssessIO::writeData(CybAssess* assess)
{
	ofstream fout(this->getDataFile()); 

	cout << "Escrevendo o arquivo " << this->getFile() << endl;

	
	if(fout.fail())
	{

		cout << "Problemas na abertura do arquivo de saida " << this->getFile() << endl;
		cout << flush;
		exit(0);
	}
	
	if(assess->getData()->size() == 0)
		return;
	
	int dimension = assess->getData()->pos(0)->getDimension();
	
	fout << "##" << dimension << "\n\n";
	
	fout << "Data:\n\n";
	
	for(int i=0; i < assess->getData()->size(); i++)
	{
		for(int j=0; j < dimension; j++)
			fout << assess->getData()->pos(i)->operator[](j) << " ";
		
		fout << "\n";
	}	
	
	fout.close();
}

mfList<CybVectorND<float>*>* CybAssessIO::readData()
{
	ifstream fin(this->getDataFile());

	cout << "Lendo o arquivo " << this->getFile() << endl;
		
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo de entrada " << this->getFile() << endl;
		exit(0);
	}
	
	char c;
	int dimension;
	CybVectorND<float>* vector;
	mfList<CybVectorND<float>*>* list = new mfList<CybVectorND<float>*>();
	
	fin >> c;
	fin >> c;
	fin >> dimension;
	
	while(c != ':')
		fin >> c;
	
	while(!fin.eof())
	{
		vector = new CybVectorND<float>(dimension);
		for(int i=0; i < dimension; i++)
			fin >> (*vector)[i];
		
		if(fin.eof())
		{
			fin.close();
			return list;
		}
		
		list->insert(vector);
	}	
}

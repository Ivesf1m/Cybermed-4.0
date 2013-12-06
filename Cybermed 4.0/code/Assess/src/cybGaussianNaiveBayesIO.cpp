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

#include "cybGaussianNaiveBayesIO.h"

CybGaussianNaiveBayesIO::CybGaussianNaiveBayesIO(char* file_name) : CybAssessIO(file_name, ".cyba_GNB")
{
	
}
		
void CybGaussianNaiveBayesIO::write(void* gnbObject)
{
	CybGaussianNaiveBayes* gnb = (CybGaussianNaiveBayes*) gnbObject;
	
	ofstream fout(this->getFile()); 
	
		if(fout.fail())
		{
			cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
			cout << flush;
			exit(0);
		}
		
	fout << "##" << gnb->getVariablesNumber(); 
	
	fout << "\n\nMean" << "\n[\n";
	
	for(int i=0; i < gnb->getVariablesNumber(); i++)
	{
		fout << gnb->getMean(i); 
	
			if(i < gnb->getVariablesNumber()-1)
				fout << ",\n";
	}
	fout << "\n]";

	fout << "\n\nVariance" << "\n[\n";
	
	for(int i=0; i < gnb->getVariablesNumber(); i++)
	{
		fout << gnb->getVariance(i); 
	
			if(i < gnb->getVariablesNumber()-1)
				fout << ",\n";
	}
	fout << "\n]";
		
	fout.close();
}
	
void* CybGaussianNaiveBayesIO::read()
{

	ifstream fin(this->getFile());

	
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
		exit(0);
	}
	
	char c = 'a';
	int number = 0;
	float mean;
	int count = 0;
	int count2 = 0;
	float variance = 0;
	
	fin >> c;
	fin >> c;
	fin >> number;
	
	
	CybGaussianNaiveBayes* gnb = new CybGaussianNaiveBayes(number);
	
	while(c != '[')
		fin >> c;
	
	while(c != ']')
	{
		fin >> mean;
		fin >> c;
	
		gnb->setMean(mean, count++);
		//cout << gnb->getMean(count-1);
	}


	while(c != '[')
		fin >> c;

	while(c != ']')
	{
		fin >> variance;
		fin >> c;
	
		gnb->setVariance(variance, count2++);	
		//cout << gnb->getVariance(count2-1);
	}

	fin.close();
	
	return (void*) gnb;
}		

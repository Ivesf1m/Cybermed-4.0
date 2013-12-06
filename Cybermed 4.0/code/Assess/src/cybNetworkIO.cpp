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

#include "cybNetworkIO.h"

	
CybNetworkIO::CybNetworkIO(char* file_name) : CybAssessIO(file_name, ".cyba_BN")
{
	
}
		
void CybNetworkIO::write(void* network)
{
	CybBayesianNetwork* net = (CybBayesianNetwork*) network;
	
	ofstream fout(this->getFile()); 
	
	if(fout.fail())
	{
		cout << "Problemas na abertura do arquivo de saida " << this->getFile() << endl;
		cout << flush;
		exit(0);
	}
		
	fout << "##" << net->getNodesNumber(); 
		
	fout << "\n\nMean" << "\n[\n";
	

	for(int i=0; i < net->getNodesNumber(); i++)
	{
		fout << net->getMean(i); 
	
			if(i < net->getNodesNumber()-1)
				fout << ",\n";
	}
	fout << "\n]\n\n";
	
	fout << "Dependency\n";
	fout << "[\n";
	cout << flush;
	mfList<int>* mix;
		
	for(int i=0; i<net->getNodesNumber(); i++)
	{
		mix = net->getParents(i);
		
		fout << i;
		
		if(mix->size() == 0)
		{		
			if(i < net->getNodesNumber() -1)
				fout << ";";
			fout << "\n";
			continue;
		}
		fout << ": ";
		
			for(int j=0; j<mix->size(); j++)
			{
				fout << mix->pos(j);
					if(j < mix->size()-1)
						fout << ", ";
					else if(i < net->getNodesNumber() -1)
						fout << ";";	
			}

		fout << "\n";				
	}
		fout << "]\n\n";
		
		fout << "Covariance\n[\n";
		
			for(int i=0; i < net->getNodesNumber(); i++)
			{
				for(int j=0; j < net->getNodesNumber(); j++)
					fout << net->getCovariance()[i* net->getNodesNumber() + j] << " ";
				fout << "\n";
			}
		fout << "]";	
	fout.close();
}
	
void* CybNetworkIO::read()
{
	ifstream fin(this->getFile());
	
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo de entrada " << this->getFile() << endl;
		exit(0);
	}
	
	char c = 'a';
	int number = 0;
	float mean;
	float variance;
	int id = 0;
	int parent;
	int count = 0;
	
	fin >> c;
	fin >> c;
	fin >> number;

	CybBayesianNetwork* net = new CybBayesianNetwork(number);
	
	while(c != '[')
		fin >> c;
	
	while(c != ']')
	{
		fin >> mean;
		fin >> c;
	
		net->setMean(mean, count++);	
	}	
	
	while(c != '[')
		fin >> c;	
					
	while(true)
	{
		if(c == ']')
		{
			break;
		}
		
		fin >> id;
		fin >> c;
		
		while(c != ';' && c != ']')
		{
			fin >> parent;						
			net->addArc(parent,id);
			fin >> c;      
		}			
	}	
	
	while(c != '[')
		fin >> c;	
	
	float* matrix = new float[net->getNodesNumber()*net->getNodesNumber()];
	
	for(int i=0; i < net->getNodesNumber()*net->getNodesNumber(); i++)
		fin >> matrix[i];
	
	net->setCovariance(matrix);
	
	net->initModel();
	
	fin.close();
	
	return (void*) net;
}		


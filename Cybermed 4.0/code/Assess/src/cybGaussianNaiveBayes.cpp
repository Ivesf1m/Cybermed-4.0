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

#include "cybGaussianNaiveBayes.h"

//Constructor
CybGaussianNaiveBayes::CybGaussianNaiveBayes(int variablesNumber)
{
	this->variablesNumber = variablesNumber;
	this->mean = new float[this->getVariablesNumber()];
	this->variance = new float[this->getVariablesNumber()];
}

//Destructor
CybGaussianNaiveBayes::~CybGaussianNaiveBayes()
{
	delete[] this->variance;
	delete[] this->mean;
}

//Sets 
void CybGaussianNaiveBayes::setVariance(float* variance)
{
	this->variance = variance;

}

void CybGaussianNaiveBayes::setVariance(float variance, int node_id)
{
	this->variance[node_id] = variance;

}

void CybGaussianNaiveBayes::setMean(float* newMean)
{
	this->mean = newMean;

}

void CybGaussianNaiveBayes::setMean(float newMean, int node_id)
{
	this->mean[node_id] = newMean;

}



//Gets
float* CybGaussianNaiveBayes::getVariance()
{
	return this->variance;
}

float CybGaussianNaiveBayes::getVariance(int node_id)
{
	return this->variance[node_id];
}

float* CybGaussianNaiveBayes::getMean()
{
	return this->mean;
}

float CybGaussianNaiveBayes::getMean(int node_id)
{
	return this->mean[node_id];
}

int CybGaussianNaiveBayes::getVariablesNumber()
{
	return this->variablesNumber;
}

void CybGaussianNaiveBayes::training()
{
	initData();
}

void CybGaussianNaiveBayes::initData()
{	
		for(int i=0; i < this->getVariablesNumber();i++) //X, Y, Z
		{
			float mean = 0; //mean variable
			
			for(int j=0; j < this->getData()->size(); j++) //from 0 to size do
				mean += this->getData()->pos(j)->operator[](i); //add value to mean 
			
			setMean(mean/this->getData()->size(), i); //divide mean by its size
		}

		for(int i=0; i < this->getVariablesNumber();i++) //X, Y, Z
		{	
			float variance = 0; //variance variable

			for(int j=0; j<this->getData()->size(); j++) //from 0 to size do
			{
				//variancia = variancia + pow((float_aux[j] - media), 2);
				variance += pow((this->getData()->pos(j)->operator[](i) - this->getMean(i)), 2); //add to variance 
			}
			
			setVariance(variance/this->getData()->size(), i); //divide variance by its size
		}	
}

double CybGaussianNaiveBayes::assessment(CybVectorND<>* data)
{
	float* aux = data->toArray();
	double naive = 0;
	int i=0;

	//cout << "Dimension: " << data->getDimension() << "\n";
	//cout << '\n';
	for(i=0; i<data->getDimension(); i++)
	{
		naive = naive - (0.5 * log(sqrt(this->getVariance(i)))) - (0.5 * pow((aux[i] - this->getMean(i)), 2) / this->getVariance(i));
		//cout << naive << " ";
	}

	return naive;
}

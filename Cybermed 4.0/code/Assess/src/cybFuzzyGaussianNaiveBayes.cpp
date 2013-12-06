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

#include "cybFuzzyGaussianNaiveBayes.h"

//Constructor
CybFuzzyGaussianNaiveBayes::CybFuzzyGaussianNaiveBayes(int variablesNumber)
{
	if (variablesNumber > 3)
	{
		cout << "variablesNumber > 3! Error!";
		exit(0);
	}
	this->variablesNumber = variablesNumber;
	this->mean = new float[this->getVariablesNumber()];
	this->variance = new float[this->getVariablesNumber()];
	this->intersectionTable = NULL;
	this->table = NULL;
	this->sturges = 0;
	this->intersections = 0;
	this->highest = HIGHER;
}

//Destructor
CybFuzzyGaussianNaiveBayes::~CybFuzzyGaussianNaiveBayes()
{
	delete[] this->variance;
	delete[] this->mean;
}

void CybFuzzyGaussianNaiveBayes::training()
{
	initData();
}

void CybFuzzyGaussianNaiveBayes::reTraining(float*** RefTable_2, float*** RefTable)
{

	int intersections = 0;
	int sturges;
	//STURGES NUMBER
	if (this->getData()->size() > 10000)
	{
		sturges = rintf(1 + 3.3 * log10(10000));
	}
	else
	{
		sturges = rintf(1 + 3.3 * log10(this->getData()->size()));
	}
	cout << "sturges: " << sturges << "\n";
	this->setSturges(sturges);

	//AUXILIARY TABLES
	float*** auxRefTable = RefTable;
	float*** auxRefTable_2 = RefTable_2;

	//INDEX ARRAY
	int* sturgesIndex = new int[this->getVariablesNumber()];

	//AUXILIARY VECTORS
	float* vector = new float[this->getData()->size()];
	float* vector_2 = new float[this->getVariablesNumber()];

	//SETTING A DISTRIBUTION TABLE USING STURGES INTERVALS
	for(int i=0; i<this->getVariablesNumber(); i++)
	{
		for (int j=0; j<this->getData()->size(); j++)
		{
			vector[j] = this->data->pos(j)->operator[](i);

		} //end for j data size
	
		auxRefTable[i] = reDistributeSturges(vector, RefTable[i]);

	} //end for i variables number
	this->setTable(auxRefTable);

	//COPYING THE DATA VECTOR TO THE AUXILIARY VECTOR AND LOCATING STURGES INTERVALS INDEXES FOR EACH VALUE
	for (int j=0; j<this->getData()->size(); j++)
	{
		for(int i=0; i<this->getVariablesNumber(); i++)
		{
			//THIS VECTOR WILL HAVE ONE VALUE FOR EACH VARIABLE
			vector_2[i] = this->data->pos(j)->operator[](i);
		}

		sturgesIndex = locateSturgesIndexes(vector_2, auxRefTable);

		if (sturgesIndex == NULL)
		{
			continue;

		}
		//INCREMENTING THE TABLE FROM STURGES INTERVAL INDEXES
		auxRefTable_2[sturgesIndex[0]][sturgesIndex[1]][sturgesIndex[2]] += 1;
	}
	this->setIntersectionTable(auxRefTable_2);

	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				if(auxRefTable_2[i][j][k] > 0) 
				{
					intersections++;
				} 

			}
		}
	}
	this->setIntersections(intersections);

	int higher = HIGHER;
	//LOCATING THE HIGHEST FREQUENCY
	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				if(auxRefTable_2[i][j][k] >= higher) 
				{
					higher = auxRefTable_2[i][j][k];
				} 

			}
		}
	}
	this->setHighest(higher);

}


void CybFuzzyGaussianNaiveBayes::initData()
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

	int sturges;
	//STURGES NUMBER
	if (this->getData()->size() > 10000)
	{
		sturges = rintf(1 + 3.3 * log10(10000));
	}
	else
	{
		sturges = rintf(1 + 3.3 * log10(this->getData()->size()));
	}
	cout << "sturges: " << sturges << "\n";
	this->setSturges(sturges);

	//AUXILIARY TABLES
	float*** auxRefTable;
	float*** auxRefTable_2;
	auxRefTable = alocRefMatrix(this->getVariablesNumber(), sturges, TABLE_SIZE);
	auxRefTable_2 = alocRefMatrix(sturges, sturges, sturges);
	
	//INDEX ARRAY
	int* sturgesIndex = new int[this->getVariablesNumber()];

	//AUXILIARY VECTORS
	float* vector = new float[this->getData()->size()];
	float* vector_2 = new float[this->getVariablesNumber()];

	//COUNTER
	int intersections = 0;


	//STARTING ALL INTERSECTION TABLE VALUES AS ZEROS
	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				auxRefTable_2[i][j][k] = 0;
			}
		}
	}

	//SETTING A DISTRIBUTION TABLE USING STURGES INTERVALS
	for(int i=0; i<this->getVariablesNumber(); i++)
	{
		for (int j=0; j<this->getData()->size(); j++)
		{
			vector[j] = this->data->pos(j)->operator[](i);

		} //end for j data size
	
		auxRefTable[i] = distributeSturges(vector);

	} //end for i variables number
	this->setTable(auxRefTable);

	//COPYING THE DATA VECTOR TO THE AUXILIARY VECTOR AND LOCATING STURGES INTERVALS INDEXES FOR EACH VALUE
	for (int j=0; j<this->getData()->size(); j++)
	{
		for(int i=0; i<this->getVariablesNumber(); i++)
		{
			//THIS VECTOR WILL HAVE ONE VALUE FOR EACH VARIABLE
			vector_2[i] = this->data->pos(j)->operator[](i);
		}

		sturgesIndex = locateSturgesIndexes(vector_2, auxRefTable);

		if (sturgesIndex == NULL)
		{
			//cout << "\nSturges index NULL";
			continue;
		}
		//INCREMENTING THE TABLE FROM STURGES INTERVAL INDEXES
		auxRefTable_2[sturgesIndex[0]][sturgesIndex[1]][sturgesIndex[2]] += 1;
	}
	this->setIntersectionTable(auxRefTable_2);

	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				if(auxRefTable_2[i][j][k] > 0) 
				{
					intersections++;
				} 

			}
		}
	}
	this->setIntersections(intersections);

	int higher = HIGHER;
	//LOCATING THE HIGHEST FREQUENCY
	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				if(auxRefTable_2[i][j][k] >= higher) 
				{
					higher = auxRefTable_2[i][j][k];
				} 

			}
		}
	}
	this->setHighest(higher);

}

double CybFuzzyGaussianNaiveBayes::assessment(CybVectorND<>* data)
{
	float* aux = data->toArray();
	double naive = 0;
	int i=0;
	float ***table = this->getTable();
	float ***intersectionTable = this->getIntersectionTable();
	int* sturgesIndex;

	//cout << "Dimension: " << data->getDimension() << "\n";
	//cout << '\n';
	for(i=0; i<data->getDimension(); i++)
	{
		naive = naive + (-0.5 * log(sqrt(this->getVariance(i)))) + (-0.5 * pow((aux[i] - this->getMean(i)), 2) / this->getVariance(i));
		//cout << naive << " ";
	}

	//LOCATING STURGES INTERVALS INDEXES FOR EACH VALUE
	sturgesIndex = locateSturgesIndexes(aux, table);
	if (sturgesIndex == NULL)
	{
		return (naive-100000);
	}


	naive = naive + log(intersectionTable[sturgesIndex[0]][sturgesIndex[1]][sturgesIndex[2]] / this->getHighest());

	return naive;
}

/* Gets */
float* CybFuzzyGaussianNaiveBayes::getVariance()
{
	return this->variance;
}

float CybFuzzyGaussianNaiveBayes::getVariance(int node_id)
{
	return this->variance[node_id];
}

float* CybFuzzyGaussianNaiveBayes::getMean()
{
	return this->mean;
}

float CybFuzzyGaussianNaiveBayes::getMean(int node_id)
{
	return this->mean[node_id];
}

int CybFuzzyGaussianNaiveBayes::getVariablesNumber()
{
	return this->variablesNumber;
}

int CybFuzzyGaussianNaiveBayes::getSturges()
{
	return this->sturges;
}

int CybFuzzyGaussianNaiveBayes::getIntersections()
{
	return this->intersections;
}

float*** CybFuzzyGaussianNaiveBayes::getTable()
{
	return this->table;
}

float*** CybFuzzyGaussianNaiveBayes::getIntersectionTable()
{
	return this->intersectionTable;
}

int CybFuzzyGaussianNaiveBayes::getHighest()
{
	return this->highest;
}

/* Sets */ 
void CybFuzzyGaussianNaiveBayes::setVariance(float* variance)
{
	this->variance = variance;

}

void CybFuzzyGaussianNaiveBayes::setVariance(float variance, int node_id)
{
	this->variance[node_id] = variance;

}

void CybFuzzyGaussianNaiveBayes::setMean(float* newMean)
{
	this->mean = newMean;

}

void CybFuzzyGaussianNaiveBayes::setMean(float newMean, int node_id)
{
	this->mean[node_id] = newMean;

}


void CybFuzzyGaussianNaiveBayes::setTable(float*** table)
{
	this->table = table;
}

void CybFuzzyGaussianNaiveBayes::setIntersectionTable(float*** table)
{
	this->intersectionTable = table;
}

void CybFuzzyGaussianNaiveBayes::setSturges(int sturges)
{
	this->sturges = sturges;
}

void CybFuzzyGaussianNaiveBayes::setIntersections(int intersections)
{
	this->intersections = intersections;
}

void CybFuzzyGaussianNaiveBayes::setHighest(int highest)
{
	this->highest = highest;
}

/* Extra methods */
float*** CybFuzzyGaussianNaiveBayes::alocRefMatrix(int quantity, int lines, int columns)
{
	float ***matrix;
	int l,y;

	if (lines < 1 || columns < 1 || quantity < 1)
	{
		printf ("** Error: Wrong parameter **\n");
		return (NULL);
	}
	
	matrix = (float ***) calloc (quantity, sizeof(float **));
	
	if (matrix == NULL)
	{
		printf ("** Error: Not enough memory **");
		return (NULL);
	}

	for (l=0; l<quantity; l++ )
	{
		matrix[l] = (float**) calloc (lines, sizeof(float *));
		if (matrix[l] == NULL)
		{
			printf ("** Error: Not enough memory **");
			return (NULL);
		}
        }

	for (l=0; l<quantity; l++ )
	{
		for (y=0; y<lines; y++)
		{
			matrix[l][y] = (float*) calloc (columns, sizeof(float));
			if (matrix[l][y] == NULL)
			{
				printf ("** Error: Not enough memory **");
				return (NULL);
			}
		}
	}
	return (matrix);
}

float*** CybFuzzyGaussianNaiveBayes::freeRefMatrix (int quantity, int lines, int columns, float ***matrix)
{
	int l,y;

	if (matrix == NULL)
	{
		return (NULL);
	}
	
	if (lines < 1 || columns < 1 || quantity < 1)
	{
		printf ("** Error: Wrong parameter **\n");
		return (matrix);
	}


	for (l=0; l<quantity; l++)
	{
		freeMatrix(lines, columns, matrix[l]);
	}

	free (matrix);
	
	return (NULL);
}


float** CybFuzzyGaussianNaiveBayes::freeMatrix (int lines, int columns, float **matrix)
{
	int l;

	if (matrix == NULL)
	{
		return (NULL);
	}
	
	if (lines < 1 || columns < 1)
	{
		printf ("** Erro: Wrong parameter **\n");
		return (matrix);
	}


	for (l=0; l<lines; l++)
	{
		free(matrix[l]);
	}

	free (matrix);
	
	return (NULL);
}


float** CybFuzzyGaussianNaiveBayes::alocMatrix (int lines, int columns)
{
	float **matrix; 
	int l;

	if (lines < 1 || columns < 1)
	{
		printf ("** Erro: Wrong parameter **\n");
		return (NULL);
	}
	
	matrix = (float **) calloc (lines, sizeof(float *));
	
	if (matrix == NULL)
	{
		printf ("** Erro: Not enough memory **");
		return (NULL);
	}

	for (l=0; l<lines; l++ )
	{
		matrix[l] = (float*) calloc (columns, sizeof(float));
		if (matrix[l] == NULL)
		{
			printf ("** Erro: Not enough memory **");
			return (NULL);
		}
    }
	return (matrix);
}

float** CybFuzzyGaussianNaiveBayes::distributeSturges (float* auxArray)
{

	float lower = LOWER;
	float higher = HIGHER;
	float last;
	float sampleAmplitude;
	float classAmplitude;
	float accumulator;
	int freqCounter = 0;


	float** auxTable;
	auxTable = alocMatrix(this->getSturges(), TABLE_SIZE);
	

	for(int i=0; i<this->getData()->size(); i++)
	{
		if (lower > auxArray[i])
		{
			lower = auxArray[i];
		}
		if (higher < auxArray[i])
		{
			higher = auxArray[i];
		}
	}

	sampleAmplitude = higher - lower;
	classAmplitude = sampleAmplitude / this->getSturges();
	accumulator = lower;

	for(int i=0; i<this->sturges; i++)
	{
		//writes the class intervals
		for(int j=0; j<2; j++)
		{
			auxTable[i][j] = accumulator;
			accumulator += classAmplitude;
		} //end for j<table
		accumulator -= classAmplitude;

		//rounds up the last interval
		if(i == (sturges-1))
		{
			auxTable[i][1] = ceil(auxTable[i][1]+1);
			last = auxTable[i][1];
		}

		//checking the interval
		for(int j=0; j<this->getData()->size(); j++)
		{
			if (auxArray[j] >= auxTable[i][0] && auxArray[j] < auxTable[i][1])
			{
				freqCounter++;
			}
		} //end for j<size	

		//writing the frequency
		auxTable[i][2] = freqCounter;
		auxTable[i][3] = auxTable[i][2] / this->getData()->size();
		freqCounter = 0;

	} //end for i<sturges

	return auxTable;
}

float** CybFuzzyGaussianNaiveBayes::reDistributeSturges (float* auxArray, float** table)
{

	int freqCounter = 0;
	float** auxTable = table;

	for(int i=0; i<this->sturges; i++)
	{
		//checking the interval
		for(int j=0; j<this->getData()->size(); j++)
		{
			if (auxArray[j] >= auxTable[i][0] && auxArray[j] < auxTable[i][1])
			{
				freqCounter++;
			}
		} //end for j<size	

		//writing the frequency
		auxTable[i][2] += freqCounter;
		freqCounter = 0;

	} //end for i<sturges

	for(int i=0; i<this->sturges; i++)
	{
		freqCounter += auxTable[i][2];
	} //end for i<sturges

	for(int i=0; i<this->sturges; i++)
	{
		auxTable[i][3] = auxTable[i][2]/freqCounter;
	} //end for i<sturges

	return auxTable;
}

int* CybFuzzyGaussianNaiveBayes::locateSturgesIndexes(float* auxVector, float*** auxRefTable)
{
	int* indexes = new int[this->getVariablesNumber()];
	int usedIndexes = 0;

	for(int i=0; i<this->getVariablesNumber(); i++)
	{
		for(int j=0; j<this->sturges; j++)
		{
			if (auxVector[i] >= auxRefTable[i][j][0] && auxVector[i] < auxRefTable[i][j][1])
			{
				indexes[i] = j;
				usedIndexes++;
			}
		}
	}

	if (usedIndexes != this->getVariablesNumber())
		return NULL;

	return indexes;

}

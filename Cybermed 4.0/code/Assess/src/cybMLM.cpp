#include "cybMLM.h"
#include "cybMatrixOperator.h"

CybMLM::CybMLM(int variablesNumber,float prioriProbability)
{
	this->variablesNumber = variablesNumber;
	this->precisionMatrix = NULL;
	this->prioriProbability = prioriProbability;
	this->variables = new mfList<int>;	
	this->mean = new float[getVariablesNumber()];
	this->covariance = new float[getVariablesNumber()*getVariablesNumber()];
	this->determinat = 0;
}

CybMLM::~CybMLM()
{
	delete[] this->mean;
	delete[] this->covariance;

	variables->clear();
	
	delete variables;
}

float CybMLM::getMean(int node_id)
{
	return this->mean[node_id];
}
	
float CybMLM::getVariance(int node_id)
{
	return this->covariance[node_id*getVariablesNumber() + node_id];
}

float CybMLM::getPrioriProbability()
{
	return this->prioriProbability;
}

void CybMLM::setMean(float newMean, int node_id)
{
	this->mean[node_id] = newMean;
}

float * CybMLM::getCovariance()
{
	return this->covariance;
}

int CybMLM::getVariablesNumber()
{
	return this->variablesNumber;
}

void CybMLM::setCovariance(float* newCovariance)
{
	this->covariance = newCovariance;
}

void CybMLM::initData()
{
	//it calculates the mean for each variable
	for(int i=0; i < this->getVariablesNumber();i++)
	{
		float mean = 0;
		
		for(int j=0; j < this->getData()->size(); j++)		
			mean += this->getData()->pos(j)->operator[](i);
		
		this->setMean(mean/this->getData()->size(), i);			
	}
		
	//it calculates the precisionMatrix matrix
	for(int i=0; i < this->getVariablesNumber();i++)		
		for(int j=0; j < this->getVariablesNumber();j++)	
		{		
			for(int k=0; k < this->getData()->size(); k++)
			{
				this->covariance[i*this->getVariablesNumber() + j] += 
				(this->getData()->pos(k)->toArray()[i]- this->getMean(i)) *
				(this->getData()->pos(k)->toArray()[j]- this->getMean(j));	
			}
				
			this->covariance[i*this->getVariablesNumber() + j] /= this->getData()->size();
		}
	
	checkVariables();
}

void CybMLM::checkVariables()
{
	for(int i=0; i < getVariablesNumber(); i++)
		if(getVariance(i))
			this->variables->insert(i);
	
	this->precisionMatrix = new float[getVariablesNumber()*getVariablesNumber()];
	
	this->determinat = CybMatrixOperator::matrixDeterminant(covariance, variables->size());
	
	CybMatrixOperator::matrixInverse(covariance,this->precisionMatrix,variables->size(),determinat);	
}

void CybMLM::training()
{
	initData();
}

double CybMLM::assessment(CybVectorND<>* data)
{
	return getFunctionResult(data->toArray(), this->variables) + log(prioriProbability);;
}

double CybMLM::getFunctionResult(float* data, mfList<int> * variables)
{
	float* aux1 = new float[variables->size()];
	float* aux2 = new float[variables->size()];
	float* matrix = this->precisionMatrix;
	float* inverse = new float[variables->size()*variables->size()];
	double res = 0.0;
	
	for(int i=0; i < variables->size(); i++)
		aux1[i] = (data[variables->pos(i)] - this->getMean(variables->pos(i)));
	
	for(int i=0; i < variables->size(); i++)
		for(int j=0; j < variables->size(); j++)
			aux2[i] += aux1[j] * matrix[j * variables->size() + i];
	
	for(int i=0; i < variables->size(); i++)
		res += aux1[i]*aux2[i];	
	
	int size = variables->size();
	
	delete[] aux1;
	delete[] aux2;
	
	return -log(abs(determinat)) - res;
}

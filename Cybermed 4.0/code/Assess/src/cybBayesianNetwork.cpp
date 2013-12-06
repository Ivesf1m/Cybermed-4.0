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

#include "cybBayesianNetwork.h"
#include "cybInfoNode.h"
	
CybBayesianNetwork::CybBayesianNetwork(int nodesNumber)
{
	this->nodesNumber = nodesNumber;
	this->mean = new float[getNodesNumber()];
	this->covariance = new float[getNodesNumber()*getNodesNumber()];
	this->allPaths = new mfList<mfList<int>*>*[this->getNodesNumber()];
	this->DAG = new bool[getNodesNumber()*getNodesNumber()];
	this->error = 1e-4;
	this->interationsNumber = 10000;

	for(int i=0; i < this->getNodesNumber(); i++)
	{
		this->allPaths[i] = new mfList<mfList<int>*>();
		
		for(int j=0; j < getNodesNumber(); j++)
		{
			DAG[i*getNodesNumber() + j] = false;
		}
	}
}

CybBayesianNetwork::~CybBayesianNetwork()
{
	delete[] this->covariance;
	delete[] this->mean;
	delete[] this->DAG;
	
	for(int i=0; i < getNodesNumber(); i++)
	{
		this->allPaths[i]->clear();
	}
	
	delete[] this->allPaths;
}

void CybBayesianNetwork::initData()
{	
		for(int i=0; i < this->getNodesNumber();i++)
		{
			float mean = 0;
			
			for(int j=0; j < this->getData()->size(); j++)		
				mean += this->getData()->pos(j)->operator[](i);
			
			this->setMean(mean/this->getData()->size(), i);			
		}
	
		for(int i=0; i < this->getNodesNumber();i++)
		{	
			for(int j=0; j < this->getNodesNumber();j++)	
			{		
					for(int k=0; k < this->getData()->size(); k++)
					{			
							this->covariance[i*this->getNodesNumber() + j] += 
							(this->getData()->pos(k)->toArray()[i]- this->getMean(i)) *
							(this->getData()->pos(k)->toArray()[j]- this->getMean(j));	
					}
					
				this->covariance[i*this->getNodesNumber() + j] /= this->getData()->size();
						
			}
		}	
}

void CybBayesianNetwork::find_closed_paths(int start, int end, mfList<mfList<int>*>* list)
{
	static mfList<int> current;
	mfList<int>* aux = NULL;
	
	if(current.inList(start))
		return;
	
	current.insert(start);
	
	if(start == end)
	{
		aux = new mfList<int>();
		for(int i = 0; i < current.size(); i++)
			aux->insert(current.pos(i));
		
		list->insert(aux);
		current.erase(current.search(start));	
		return;
	}	
	
	aux = getSons(start);
	
	for(int i=0; i < aux->size(); i++)
		find_closed_paths(aux->pos(i), end, list);

	aux->clear();
	delete aux;

	current.erase(current.search(start));
}

void CybBayesianNetwork::update_probability(int node_id)
{
	double sum = 0;
	double prob = 0;
	double aux = 0;
	float shift = 0;
	double old_score = 0, new_score = 0;
	int control = 0;
	double last_difference = 0.0;
	mfList<int>* parents = new mfList<int>;
	
	do
	{
		if(control > this->interationsNumber)
			return;
		
		old_score = this->score();
		
		for(int i=0; i < this->allPaths[node_id]->size(); i++)
			for(int w = 0; w < this->allPaths[node_id]->pos(i)->size(); w++)
				if(this->allPaths[node_id]->pos(i)->pos(w) != node_id)   
					parents->insertOnlyOne(this->allPaths[node_id]->pos(i)->pos(w));
		
		for(int i=0; i < parents->size(); i++)
		{
			for(int j=0; j < this->getData()->size(); j++)
			{
			prob = getProbability(this->getData()->pos(j)->toArray(), parents->pos(i));
			
			shift += prob*((this->getData()->pos(j)->toArray()[parents->pos(i)]) - this->getMean(parents->pos(i)));
			sum += prob;
			}
		}
		
		shift /= sum;
	
		if(isnan(shift) || isinf(shift))
			return;
		
		this->setMean(this->getMean(node_id) +shift, node_id);		
		
		new_score = this->score();
		control++;
				
		cout << "difference: " << new_score - old_score << endl;
		
	}while((last_difference = new_score - old_score) >= this->error);
}

void CybBayesianNetwork::initModel()
{	
	for(int i=0; i < this->getNodesNumber(); i++)
		this->allPaths[i]->clear();
	
	for(int i=0; i < this->getNodesNumber(); i++)
		for(int j=0; j < this->getNodesNumber(); j++)
		{
			mfList<int> * aux = getParents(i);
			if(i!= j && aux->size() == 0)
				find_closed_paths(i,j,this->allPaths[j]);	
			aux->clear();
			delete aux;
		}
	/*for(int i=0; i < this->getNodesNumber(); i++)
	{
		if(this->allPaths[i]->size())
			cout << "i: " << i << endl;
			for(int j=0; j < this->allPaths[i]->size(); j++)
			{
				for(int k=0; k < this->allPaths[i]->pos(j)->size(); k++)
					cout << this->allPaths[i]->pos(j)->pos(k) << "  ";
				
				cout << endl;
			}
	}*/
	
	//toString();
	
	//int k;
	//cout << "digite: " << endl;
	//cin >> k;
}

double CybBayesianNetwork::score()
{
	double prob = 0;
	double sco = 0;
	
	for(int i=0; i < this->getData()->size(); i++)
	{
		prob = getProbability(this->getData()->pos(i)->toArray());

		if(prob > 1 || isnan(prob) || isinf(prob))
			return -1e200;
		else
			sco += log(prob);
		//cout << "sco: " << sco << endl;
	}

	return sco;
}
	
void CybBayesianNetwork::setCovariance(float* covariance)
{
	this->covariance = covariance;
}

double CybBayesianNetwork::getJointProb(float* data, mfList<int>* parents)
{
	if(parents->size() == 1)
	{
		if(this->getVariance(parents->pos(0)) == 0)
		{
			if(this->getMean(parents->pos(0)) == data[parents->pos(0)])
				return 1;
			else return 0;
		}
		else
		{
			return exp(-pow(data[parents->pos(0)] - this->getMean(parents->pos(0)), 2)
				/(2*this->getVariance(parents->pos(0))))/sqrt(6.283185841);
		}
	}
	
	float* aux1 = new float[parents->size()];
	float* aux2 = new float[parents->size()];
	float* matrix = new float[parents->size()*parents->size()];
	float* inverse = new float[parents->size()*parents->size()];
	double res = 0.0;
	if(this->covariance == NULL) 		cout << "Covariance is NULL" << endl;
	for(int i=0; i < parents->size(); i++)
		for(int j=0; j < parents->size(); j++)
			matrix[i* parents->size() + j] = this->covariance[parents->pos(i)* this->getNodesNumber()+ parents->pos(j)];
		
	double determinat = CybMatrixOperator::matrixDeterminant(matrix, parents->size());
	
	if(determinat == 0)
	{
		double aux = 1.0;
		mfList<int> * nodes = new mfList<int>();
	
		for(int i=1; i < parents->size(); i++)
				nodes->insert(parents->pos(i));	
		
		aux = this->getJointProb(data, nodes);
		
		nodes->clear();
		nodes->insert(parents->pos(0));
		
		aux *= this->getJointProb(data, nodes);
		
		nodes->clear();
		delete nodes;
		return aux;
	}
	
	CybMatrixOperator::matrixInverse(matrix,inverse,parents->size(),(float)determinat);
	delete[] matrix;
	matrix = inverse;
	
	for(int i=0; i < parents->size(); i++)
		aux1[i] = (data[parents->pos(i)] - this->getMean(parents->pos(i)));
	
	for(int i=0; i < parents->size(); i++)
		for(int j=0; j < parents->size(); j++)
			aux2[i] += aux1[j] * matrix[j * parents->size() + i];
	
	for(int i=0; i < parents->size(); i++)
		res += aux1[i]*aux2[i];	
	
	int size = parents->size();
	
	delete[] aux1;
	delete[] aux2;
	delete[] matrix;

	return sqrt(1/determinat)*exp(-(res/2))*pow(6.283185841, -size/2.0);
}

double CybBayesianNetwork::getProbability(float* data)
{
	double res = 1.0;
	
	for(int i=0; i < this->getNodesNumber(); i++)
		res *= getProbability(data,i);
	return res;
}
	
float * CybBayesianNetwork::getCovariance()
{
	return this->covariance;
}

double CybBayesianNetwork::getProbability(float* data, int node_id)
{
	double parents = 0.0;
	double prob = 1;
	mfList<int> * aux = NULL;
	
	if(this->allPaths[node_id]->size() == 0)
	{
		//cout << "EH NULLOO" << endl;
		aux = new mfList<int>();
		aux->insert(node_id);
		prob = getJointProb(data, aux);
		
		aux->clear();
		delete aux;
		
	//	cout << "kkkkkkkkkk" << endl;
		
		return prob;
	}
	
	//cout << "nao anao " << endl;
	
		for(int i=0; i < this->allPaths[node_id]->size(); i++)
		{
		//	cout << "for" << endl;
			parents= 0.0;
			aux = getParents(node_id);
			//for(int j = 0; j < aux->size(); j++)
		//		cout << aux->pos(j) << "  ";
		//	cout << endl;
			//cout << "eeeeeeeee" << endl;
			for(int j = 0; j < aux->size(); j++)
				for(int k=0; k < this->allPaths[aux->pos(j)]->size(); k++)
					parents += getJointProb(data,this->allPaths[aux->pos(j)]->pos(k));
		//	cout << "pppppppppppp" << endl;
			if(parents)
				prob *= getJointProb(data,this->allPaths[node_id]->pos(i))/parents;
			else
				prob *= getJointProb(data,this->allPaths[node_id]->pos(i));
			
			aux->clear();
			delete aux;
		}
		
		return prob;
}

void CybBayesianNetwork::toString()
{
	for(int i=0; i < this->getNodesNumber(); i++)
	{
		for(int j=0; j< this->getNodesNumber(); j++)
			cout << DAG[i*getNodesNumber() + j] << " ";
	cout << endl;
	}
	
	for(int i=0; i < this->getNodesNumber(); i++)
	{
	cout << "id " << i << ": ";
	cout << "(" << this->getMean(i) << ", " <<
	this->getVariance(i) << ")";
	cout << endl;
	}
}

void CybBayesianNetwork::training()
{
		CybInfoNode* node = NULL;
		CybInfoNode* greater = NULL;
		bool hasMore = true;
		this->initData();
		this->initModel();
		double old_score; 
		int * control = new int[getNodesNumber()*getNodesNumber()];
		
		for(int i=0; i < getNodesNumber()*getNodesNumber(); i++)
			control[i] = 0;
		
		while(hasMore)
		{		
			
			old_score = this->score();
			hasMore = false;
			
			for(int i=0; i < getNodesNumber(); i++)
				for(int j=0; j < getNodesNumber(); j++)
					if(i!=j && !control[i*getNodesNumber() + j] && 
							!control[j*getNodesNumber() + i])
					{
						node = new CybInfoNode(this, i, j);	
						
						if(node->getScore() != -1e200)
						{						
							if(greater == NULL)
								greater = node;
							else if(node->getScore() > greater->getScore())
							{
								delete greater;
								greater = node;
							}else
								delete node;	
						}else
							delete node;
					}
			if(greater)
			{	
				if(greater->getScore() > old_score)
				{
					
					old_score = greater->getScore();
					control[greater->getParent() * this->getNodesNumber() + greater->getSon()] = 1;
					control[greater->getSon() * this->getNodesNumber() + greater->getParent()] = 1;
					
					this->addArc(greater->getParent(), greater->getSon());
					this->initModel();
					
					//cout << "---------- chamou ---------------" << endl;
					this->update_probability(greater->getSon());
					greater = NULL;
					hasMore = true;
				//	this->toString();
					
				}
			}
			
			
		}
		
		delete[] control;
		
		this->toString();
		
		cout << "finalize" << endl;
}
	
double CybBayesianNetwork::assessment(CybVectorND<>* vector)
{
	return this->getProbability(vector->toArray());
}

void CybBayesianNetwork::setMean(float newMean, int node_id)
{
	this->mean[node_id] = newMean;
}

mfList<int>* CybBayesianNetwork::getSons(int node_id)
{
	mfList<int>* ret = new mfList<int>();
	
	for(int i = 0; i < getNodesNumber(); i++)
		if(hasArc(node_id, i))
			ret->insertOnlyOne(i);
	return ret;
}

float CybBayesianNetwork::getMean(int node_id)
{
	return this->mean[node_id];
}

float CybBayesianNetwork::getVariance(int node_id)
{
	return this->covariance[node_id*getNodesNumber() + node_id];
}

void CybBayesianNetwork::addArc(int parent_id, int son_id )
{
	this->DAG[parent_id*getNodesNumber() + son_id] = true;
}

void CybBayesianNetwork::removeArc(int parent_id, int son_id )
{
	this->DAG[parent_id*getNodesNumber() + son_id] = false;
}

bool CybBayesianNetwork::hasArc(int parent_id, int son_id )
{
	return this->DAG[parent_id*getNodesNumber() + son_id];
}	
	
int CybBayesianNetwork::getNodesNumber()
{
	return this->nodesNumber;
}

mfList<int>* CybBayesianNetwork::getParents(int node_id)
{
	mfList<int>* ret = new mfList<int>();
	
	for(int i = 0; i < getNodesNumber(); i++)
		if(hasArc(i, node_id))
			ret->insertOnlyOne(i);
	return ret;
}





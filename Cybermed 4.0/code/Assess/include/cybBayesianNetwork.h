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

#include <iostream>
#include "cybMatrixOperator.h"
#include <math.h>
#include "cybAssess.h"

#ifndef CYBBAYESIANNETWORK_H_
#define CYBBAYESIANNETWORK_H_

class CybBayesianNetwork : public CybAssess
{
private:
	float* covariance;
	float* mean;
	bool* DAG;
	mfList<mfList<int>*>** allPaths;
	float error;
	int interationsNumber;
	int nodesNumber;
	
public:
	
	CybBayesianNetwork(int nodesNumber);

	virtual ~CybBayesianNetwork();
	
	void setCovariance(float*);
	
	double score();
	
	float * getCovariance();
	
	virtual void initModel();

	virtual void toString();
	
	virtual void training();
	
	virtual double assessment(CybVectorND<>*);
		
	float getMean(int node_id);
	
	float getVariance(int node_id);

	void addArc(int parent_id, int son_id );

	void removeArc(int parent_id, int son_id );
	
	bool hasArc(int parent_id, int son_id );

	int getNodesNumber();
	
	mfList<int>* getParents(int node_id);
	
	mfList<int>* getSons(int node_id);
	
	void setMean(float newMean, int node_id);
	
protected:
	
	virtual void initData();
	
	virtual double getJointProb(float*, mfList<int>*);
	
	virtual void update_probability(int);
	
	void find_closed_paths(int, int, mfList<mfList<int>*>*);
	
	virtual double getProbability(float*, int);

	virtual double getProbability(float*);
};

#endif /*CYBBAYESIANNETWORK_H_*/

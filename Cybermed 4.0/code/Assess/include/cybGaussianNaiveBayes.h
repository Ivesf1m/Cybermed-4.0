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

#include <iostream>
#include "cybAssess.h"

#ifndef CYBGAUSSIANNAIVEBAYES_H_
#define CYBGAUSSIANNAIVEBAYES_H_

/**
@class		CybGaussianNaiveBayes 
@file		cybGaussianNaiveBayes.h 
@short
	Class that implements the Gaussian Naive Bayes assessment.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2011, November
*/

class CybGaussianNaiveBayes : public CybAssess
{
private:

	float* mean;	//mean vector.
	float* variance;	//variance vector.
	int variablesNumber;	//number of variables (x, y, z, ...).

	
public:

	/**	Constructor.
	@param int variablesNumber.
	*/	
	CybGaussianNaiveBayes(int variablesNumber);

	~CybGaussianNaiveBayes();

	/**	Sets the mean vector as newMean.
	@param float* newMean.
	@return void.
	*/
	void setMean(float* newMean);

	/**	Sets the mean at node_id, as newMean.
	@param float newMean.
	@param int node_id.
	@return void.
	*/
	void setMean(float newMean, int node_id);

	/**	Sets the variance vector as newVariance.
	@param float* newVariance.
	@return void.
	*/
	void setVariance(float* newVariance);
	
	/**	Sets the variance at node_id, as newVariance.
	@param float newVariance.
	@param int node_id.
	@return void.
	*/
	void setVariance(float newVariance, int node_id);

	/**	Gets the mean vector.
	@return float*.
	*/
	float* getMean();

	/**	Gets the mean at node_id.
	@return float.
	*/
	float getMean(int node_id);

	/**	Gets the variance vector.
	@return float*.
	*/
	float* getVariance();

	/**	Gets the variance at node_id.
	@param void.
	@return float.
	*/
	float getVariance(int node_id);

	/**	Gets the variables number.
	@return int.
	*/	
	int getVariablesNumber();

	/** Method that implements the training based on Gaussian Naive Bayes Method.
	 @param void.
	 @return void.
	 */
	virtual void training();

	/** Method that implements the assessment based on Gaussian Naive Bayes Method.
	 @param CybVectorND<>* data.
	 @return double.
	 */
	virtual double assessment(CybVectorND<>* data);

protected:	
	
	/** Method that initializes the training.
	 @param void.
	 @return void.
	 */
	virtual void initData();
	
};

#endif

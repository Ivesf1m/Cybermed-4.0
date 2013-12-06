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
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "cybAssess.h"


#ifndef CYBFUZZYGAUSSIANNAIVEBAYES_H_
#define CYBFUZZYGAUSSIANNAIVEBAYES_H_
#define TABLE_SIZE 4	//CURRENT MAX TABLE SIZE
#define LOWER 65000
#define HIGHER -65000

class CybFuzzyGaussianNaiveBayes : public CybAssess
{
private:

	float* mean;	//mean vector.
	float* variance;	//variance vector.
	int variablesNumber;	//number of variables (x, y, z, ...).
	float*** intersectionTable;	//Tridimensional counter
	float*** table;	//Tridimensional table used to keep the sturges' intervals
	int sturges;	//Sturges' number
	int intersections;	//Number of valid intersections (>0)
	int highest;		//Highest frequency
	
public:

	/**	Constructor.
	@param int variablesNumber.
	*/	
	CybFuzzyGaussianNaiveBayes(int variablesNumber);

	~CybFuzzyGaussianNaiveBayes();

	/**	Sets the mean vector as newMean.
	@param float* newMean.
	@return void.
	*/
	void setMean(float* newMean);

	/**	Sets the mean at node_id, as newMean.
	@param float* newMean.
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

	/**	Sets the highest variable as highest.
	@param int highest.
	@return void.
	*/
	void setHighest(int highest);

	/**	Gets the highest frequency.
	@return int.
	*/
	int getHighest();

	/**	Gets the mean vector.
	@return float*.
	*/
	float* getMean();

	/**	Gets the mean at node_id.
	@param int node_id.
	@return float.
	*/
	float getMean(int node_id);

	/**	Gets the variance vector.
	@return float*.
	*/
	float* getVariance();

	/**	Gets the variance at node_id.
	@param int node_id.
	@return float*.
	*/
	float getVariance(int node_id);

	/**	Gets the variables number.
	@return int.
	*/	
	int getVariablesNumber();

	/**	Gets Sturges' number.
	@return int.
	*/
	int getSturges();

	/**	Gets the number of valid intersections.
	@return int.
	*/
	int getIntersections();

	/**	Gets the sturges table.
	@return float***.
	*/
	float*** getTable();

	/**	Gets the counter table.
	@return float***.
	*/
	float*** getIntersectionTable();


	/**	Sets the sturges table as table.
	@param float*** table.
	@return void.
	*/
	void setTable(float*** table);

	/**	Sets the counting table as table.
	@param float*** table.
	@return void.
	*/
	void setIntersectionTable(float*** table);

	/**	Sets the sturges' number as sturges.
	@param int sturges.
	@return void.
	*/
	void setSturges(int sturges);

	/**	Sets the valid intersections number as intersections.
	@param int intersections.
	@return void.
	*/
	void setIntersections(int intersections);

	/** Method that implements the training based on Fuzzy Naive Bayes Method.
	 @param void.
	 @return void.
	 */
	virtual void training();

	/** Method that implements the training based on Fuzzy Naive Bayes Method using an existing sturges table and counter table.
	 @param float*** RefTable_2.
	 @param float*** RefTable.
	 @return void.
	 */
	void reTraining(float*** RefTable_2, float*** RefTable);


	/** Method that implements the assessment based on Fuzzy Naive Bayes Method.
	 @param void.
	 @return double.
	 */	
	virtual double assessment(CybVectorND<>*);

	/** Method that dinamically alocates a tridimensional array.
	 @param int quantity.
	 @param int lines.
	 @param int columns.
	 @return float***.
	 */	
	float*** alocRefMatrix(int quantity, int lines, int columns);

	/** Method that frees a dinamically alocated tridimensional array.
	 @param int quantity.
	 @param int lines.
	 @param int columns.
	 @param float ***matrix.
	 @return float***.
	 */
	float*** freeRefMatrix (int quantity, int lines, int columns, float ***matrix);

	/** Method that dinamically alocates a bidimensional array.
	 @param int lines.
	 @param int columns.
	 @return float**.
	 */
	float **alocMatrix (int lines, int columns);

	/** Method that frees a dinamically alocated bidimensional array.
	 @param int lines.
	 @param int columns.
	 @param float **matrix.
	 @return float**.
	 */
	float** freeMatrix (int lines, int columns, float **matrix);

	/** Method that distributes auxArray values into sturges' intervals.
	 @param float* auxArray.
	 @return float**.
	 */
	float** distributeSturges (float* auxArray);

	/** Method that distributes auxArray values into existing sturges' intervals at table.
	 @param float* auxArray.
	 @param float** table.
	 @return float**.
	 */
	float** reDistributeSturges (float* auxArray, float** table);

	/** Method that finds out the indexes from the auxVector in the auxRefTable.
	 @param float* auxVector.
	 @param float*** auxRefTable.
	 @return int*.
	 */
	int* locateSturgesIndexes(float* auxVector, float*** auxRefTable);


protected:	
	
	/** Method that initializes the training.
	 @param void.
	 @return void.
	 */
	virtual void initData();

};

#endif

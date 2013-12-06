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

#ifndef CYBFUZZYNAIVEBAYES_H_
#define CYBFUZZYNAIVEBAYES_H_
#define TABLE_SIZE 4	//CURRENT MAX TABLE SIZE
#define LOWER 65000
#define HIGHER -65000

/**
@class		CybFuzzyNaiveBayes 
@file		cybFuzzyNaiveBayes.h 
@short
	Class that implements the Fuzzy Naive Bayes assessment.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2012, February
*/

class CybFuzzyNaiveBayes : public CybAssess
{
private:

	float*** intersectionTable;	//Tridimensional counter
	float*** table;	//Tridimensional table used to keep the sturges' intervals
	int variablesNumber;	//Number of variables
	int sturges;	//Sturges' number
	int intersections;	//Number of valid intersections (>0)
	int highest;		//Highest frequency


public:
	
	/**	Constructor.
	@param int variablesNumber.
	*/
	CybFuzzyNaiveBayes(int variablesNumber);

	virtual ~CybFuzzyNaiveBayes();

	/**	Gets the number of variables.
	@return int.
	*/
	int getVariablesNumber();

	/**	Gets Sturges' number.
	@return int.
	*/
	int getSturges();

	/**	Gets the sturges table.
	@return float***.
	*/
	float*** getTable();

	/**	Gets the counter table.
	@return float***.
	*/
	float*** getIntersectionTable();

	/**	Gets the number of valid intersections.
	@return int.
	*/
	int getIntersections();

	/**	Gets the highest frequency.
	@return int.
	*/
	int getHighest();

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

	/**	Sets the highest variable as highest.
	@param int highest.
	@return void.
	*/
	void setHighest(int highest);

	/** Method that implements the training based on Fuzzy Naive Bayes Method.
	 @param void.
	 @return void.
	 */
	virtual void training();

	/** Method that implements the training based on Fuzzy Naive Bayes Method using an existing sturges table and counting table.
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

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

#include "cybAssessIO.h"
#include "cybFuzzyNaiveBayes.h"

#ifndef _CYB_FUZZYNAIVEBAYESIO_H_
#define _CYB_FUZZYNAIVEBAYESIO_H_

/**
@class		cybFuzzyNaiveBayesIO 
@file		cybFuzzyNaiveBayesIO.h 
@short
	Class that implements the Fuzzy Naive Bayes IO.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2012, February
*/

class CybFuzzyNaiveBayesIO : public CybAssessIO
{
public:

	/**	Constructor.
	@param char*.
	*/		
	CybFuzzyNaiveBayesIO(char*);

	/**	Writes the atributes into a file.
	@param void*.
	@return void.
	*/		
	void write(void*);
	
	/**	Reads the atributes from a file.
	@param .
	@return void.
	*/		
	void* read();
};

#endif

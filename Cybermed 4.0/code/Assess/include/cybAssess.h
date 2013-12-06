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
using namespace std;
#include "mf/mfList.h"
#include "cybVectorND.h"

using namespace mf;

#ifndef _CYB_ASSES_H_
#define _CYB_ASSES_H_

/**
 * @class	CybAssess
 * @file	cybAssess.h
 * @short	The base class for all assess methods implemented for CyberMed System.
 *
 * This class does the specification for assess methods.
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	1.1
 * @date	2008, August
 * 
 */
class CybAssess
{	
protected:
	mfList<CybVectorND<float>*>* data; /**> Stores the data vectores used in assess (for training or assessment). */
	
public:
	
	/**
	 * Constructor.
	 */
	CybAssess();
	
	/**
	 * Destructor.
	 */
	~CybAssess();
	
	/**
	 * This method returns a reference for joint of data.
	 * 
	 * @param void.
	 * @return mfList<CybVectorND<float>*>* A reference for a list with data.
	 */
	mfList<CybVectorND<float>*>* getData();
	
	/**
	 * This methos add a new data in the list.
	 * 
	 * @param CybVectorND<float>* data The new data added.
	 * @return void.
	 */
	void addData(CybVectorND<float>* data);
	
	/**
	 * Virtual pure method. It will implement the training
	 * for the assess method.
	 * 
	 * @param void.
	 * @return void.
	 */
	virtual void training() = 0;	

	/**
	 * Virtual pure method. It will implement the assessment
	 * for a vector of data.
	 * 
	 * @param CybVectorND<float>* The classified data.
	 * @return void.
	 */
	virtual double assessment(CybVectorND<float>*) = 0;	
};

#endif /*_CYB_ASSES_H_*/

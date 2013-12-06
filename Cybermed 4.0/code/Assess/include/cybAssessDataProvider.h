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

#include "cybInterator.h"
#include "cybThread.h"
#include "cybVectorND.h"
#include "cybAssess.h"

#ifndef _CYB_ASSESS_DATA_PROVIDER_H_
#define _CYB_ASSESS_DATA_PROVIDER_H_

/**
 * @class	CybAssessDataProvider
 * @file	cybAssessDataProvider.h
 * @short	The base class for all data providers (See CybAssessLinker). 
 *
 * This class does take the data and catch it for the assess method.
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	1.0
 * @date	2008, August
 * 
 */
class CybAssessDataProvider : public CybThread
{
private:
	CybVectorND<float>* data;	/**> The current vector. */
	bool usedData;			/**> Indicates if the vector was catched. */
	
public:	
	
	/**
	 * Constructor.
	 */
	CybAssessDataProvider();

	/**
	 * This method returns the current data.
	 * 
	 * @param void.
	 * @return CybVectorND<float>* Returns the current data. 
	 */
	CybVectorND<float>* getData();		
	
	/**
	 * This method sets de current data.
	 * 
	 * @param CybVectorND<float>* data The new current data.
	 * @return void.
	 */
	void setData(CybVectorND<float>* data);
};

#endif /*_CYB_ASSESS_DATA_PROVIDER_H_*/


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

#include <fstream>
#include <iostream>

#include <cstring>
#include <cstdlib>

#include "cybAssess.h"

#ifndef _CYB_ASSESS_IO_H_
#define _CYB_ASSESS_IO_H_

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
class CybAssessIO
{
private:
	char* file_name;	/**> Strores the file name for the assess method. */
	char* sufix;		/**> Stores the sufix for the assess method associated. */
	char* data_file;	/**> Stroes the name for the data file. */
	
public:
	
		/**
		 * Constructor.
		 * 
		 * @param char* The file_name the file name.
		 * @param char* sufix The sufix this file name.
		 */
		CybAssessIO(char* file_name, char* sufix);
		
		/**
		 * Destructor.
		 */
		~CybAssessIO();
		
		/**
		 * Virtual pure method. It will must implement
		 * the code to read the assess model.
		 * 
		 * @param void.
		 * @return void* A reference for an assess object.
		 */
		virtual void* read() = 0;
		
		/**
		 * Virtual pure method. It will must implement
		 * the code to save the assess model.
		 * 
		 * @param void* A reference for the assess object.
		 * @return void.
		 */
		virtual void write(void*) = 0;
		
		/**
		 * This method returns the file name.
		 * 
		 * @param void.
		 * @return char* The file name.
		 */
		char* getFile();	
		
		/**
		 * This method verifies if the sufix is valid for
		 * this assess type and put  sufix if there isn't sufix.
		 * 
		 * @param void.
		 * @return void.
		 */
		void validFile();
		
		/**
		 * This method returns the file name of data.
		 * 
		 * @param void.
		 * @return char* The data file name.
		 */
		char* getDataFile();
		
		/**
		 * This method writes in a file the assess data.
		 * 
		 * @param CybAssess* assess A reference for assess object.
		 * @return void.
		 */
		void writeData(CybAssess* assess);
		
		/**
		 * This method returns the data saved in a file.
		 * 
		 * @param void.
		 * @return ofList<CybVectorND<float>*>* A list for the complete data.
		 */
		mfList<CybVectorND<float>*>* readData();	
};

#endif /*_CYB_ASSESS_IO_H_*/

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

#include "cybAssess.h"
#include "cybVectorND.h"
#include "cybThread.h"
#include "cybAssessIO.h"
#include "cybAssessDataProvider.h"

#ifndef _CYB_ASSESS_LINKER_H_
#define _CYB_ASSESS_LINKER_H_

/**
 * @class	CYB_ASSESS_MODE
 * @file	cybAssessLinker.h
 * @short	Define the assess states for the linker.
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	1.0
 * @date	2008, August
 * 
 */
enum CYB_ASSESS_MODE
{	
	DO_ASSESSMENT, /**> The assess do the assessment. */
	DO_NOTHING, 	/**> The assess do nothing.*/
	OBTAIN_DATA,	/**> The assess obtain data from the associated data provider. */
	OBTAIN_DATA_AND_DO_ASSESSMENT, /**> The assess obtain data from the associated data provider and do the assessment. */
	SAVE_ASSESS,	/**> Save the assess model. */
	SAVE_DATA,		/**> Save the assess data. */
	TRAINING		/**> Do the model training (must to be used last the assess take the data). */
};

/**
 * @class	CybAssessLinker
 * @file	cybAssessLinker.h
 * @short	The base class for all data linkers for the CyberMed System (See CybAssessDataProvider). 
 *
 * This class is the base for all specific assess simulator (Used only if you want to integrate with the CyberMed System).
 *
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	1.0
 * @date	2008, August
 * 
 */
class CybAssessLinker : public CybThread
{
protected:
	CybAssess* assess;			/**> The assess object associated. */
	CybAssessDataProvider* dataProvider;	/**> The data provider object. */
	CybAssessIO* io;						/**> The io object associated. */
	mfList<double>* resultSet;				/**> The joint of classification results (for all data). */ 
	CYB_ASSESS_MODE current_mode; 			/**> The current mode os assess life. */
	
public:

	/**
	 * Constructor.
	 * 
	 * @param CybAssess* assess The assess object associated.
	 * @param CybAssessDataProvider* dataProvider The data provider associated.
	 * @param CybAssessIO* io The io object associated.
	 */
	CybAssessLinker(CybAssess* assess, 
			CybAssessDataProvider* dataProvider,
			CybAssessIO* io);
	
	/**
	 * Destructor.
	 */
	~CybAssessLinker();
	
	/**
	 * This method returns the assess object associated.
	 * 
	 * @param void.
	 * @return CybAssess* the assess object associated.
	 */
	CybAssess* getAssess();
	
	/**
	 * Returns a Reference for the joint of result.
	 * 
	 * @param void.
	 * @return mfList<double>* A reference for the result list.
	 */
	mfList<double>* getResultSet();
	
	/**
	 * This method returns the io object associated.
	 * 
	 * @param void.
	 * @return CybAssessIO* A reference for the io object associated.
	 */
	CybAssessIO* getIO();
	
	/**
	 * This method returns a reference for the data provider associated.
	 * 
	 * @param void.
	 * @return CybAssessDataProvider* A reference for the data provider associated.
	 */
	CybAssessDataProvider* getDataProvider();
	
	/**
	 * This method is overloading the init() method from the CybThread class.
	 * 
	 * @param void.
	 * @return void.
	 */
	void init();
	
	/**
	 * This method returns the current mode in assess life cycle.
	 * 
	 * @param void.
	 * @return CYB_ASSESS_MODE The current assess mode.
	 */
	CYB_ASSESS_MODE getCurrentMode();
	
	/**
	 * This method sets the current assess mode.
	 * 
	 * @param CYB_ASSESS_MODE mode the new current mode.
	 * @return void.
	 */
	void setCurrentMode(CYB_ASSESS_MODE mode);

	/**
	 * This method is called by the thread and implement the
	 * assess life cycle.
	 * 
	 * @param void.
	 * @return void.
	 */
	void run();
	
	/**
	 * This method controls the assess life cycle.
	 * It is called by the current thread and is executed 
	 * before the run() method. It sets the states from 
	 * the life cycle assess.
	 * 
	 * @param void.
	 * @return void.
	 */
	virtual void update();	
};

#endif /*_CYB_ASSESS_LINKER_H_*/

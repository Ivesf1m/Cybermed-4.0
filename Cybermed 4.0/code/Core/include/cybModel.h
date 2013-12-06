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
#ifndef CYBMODEL_H_
#define CYBMODEL_H_

/**
	@class CybModel
	@file cybModel.h 
	@short
			
		This class is a interface to a type of model that contains two or more wrl models.
	
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2011, October
*/

#include <string>
#include "cybDevice.h"
#include "cybMultiModel.h"

using namespace std;

class CybUpdateModel;

using namespace std;
class CybModel {
	public:
		/** Destructor */
		virtual ~CybModel(); 
		/** Draw the model
		@param void
		@return void
		*/
		virtual void draw() = 0;
		/** Update the model according the CybUpdateModel
		@param void
		@return void
		*/
		void update(); 
		/** Sets the CybUpdateModel
		@param CybUpdateModel *
		@return void
		*/
		void setUpdate(CybUpdateModel *update);
		/** Return the CybUpdateModel object
		@param void
		@return CybUpdateModel *
		*/ 
		CybUpdateModel *getUpdate();
		/** Sets the CybUpdateModel according of the device's name
		@param string
		@return void
		*/
		virtual void setUpdateModel(string name) = 0; 
		/** Sets the device that utilize this model
		@param string
		@return void
		*/
		void setDevice(CybDevice *device); 
		/** Return a device reference
		@param void
		@return CybDevice
		*/
		CybDevice *getDevice();
		/** Return a reference to the wrl models
		@param void
		@return CybMultiModel	 
		*/
		CybMultiModel *getModels();
		
		/** Load several models at the same time
		@param string[], int
		@return bool	
		*/		
		bool loadModels(string arModels[], int numModels);
		
		/** Add a wrl model
		@param string
		@return void
		*/
		bool addModel(string model);
		
		/** Draw the model according your ID, the ID the order that the model are added
		@param int
		@return void 
		*/
		void drawModel(int meshID);
		
		
		
		
		
		
	private:
		CybMultiModel models; //Contains the models
		CybUpdateModel *pUpdate; //Contains the updateModel object
		CybDevice *device; //Contains the device utilized in the model
};
#endif

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
#ifndef CYBMULTIMODEL_H_
#define CYBMULTIMODEL_H_

/**
	@class CybMultiModel
	@file cybMultiModel.h 
	@short
			
		This class can load several wrl models.
	
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2011, October
*/

#include "mf/mf.h"
#include "cybTraits.h"
#include "cybMesh.h"
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace mf;
using namespace std;

class CybMultiModel {
public:
	/** Constructor */
	CybMultiModel();
	virtual ~CybMultiModel();
	
	/** Add a wrl model
	@param string
	@return void
	*/
	bool addModel(string model);
	/** Load several models at the same time
	@param string[], int
	@return bool	
	*/
	bool loadModels(string models[], int numModels);
	/** Draw the model according your ID, the ID the order that the model are added
	@param int
	@return void 
	*/
	void drawModel(int meshID);
	/** Return a reference to a specific wrl models
	@param int
	@return void
	*/
	mfReader<cybSurfaceTriTraits>::sMesh *getMesh(int meshID);
	
	
private:
	vector< cybMesh<cybSurfaceTriTraits>* > meshes; //vector that contains the models
	vector<GLuint> list;
	vector<GLuint> list2;
	
	/** Loads the model and add them to the vector
	@param ofVrmlReader<cybTraits>::sMesh *, string
	@return 	bool
	*/
	bool loadModel(mfReader<cybSurfaceTriTraits>::sMesh *pMesh, string model);
	bool firstTimeRight;
	bool firstTimeLeft;
	
};
#endif

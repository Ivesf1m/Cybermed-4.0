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

#ifndef CYBREMOTEHAPTICINTERATOR_H_
#define CYBREMOTEHAPTICINTERATOR_H_

#include "cybRemoteInterator.h"
#include "cybParameters.h"

#ifdef CYBHAPTICS_H
	#include "cybPhantom.h"
#endif

class CybRemoteHapticInterator: public CybRemoteInterator {
public:
	typedef cybMesh<cybSurfaceTriTraits> sMesh;
	typedef mfCellsIterator<cybSurfaceTriTraits> sCellIterator;
  
	CybRemoteHapticInterator();

	virtual void drawInterator();
#ifdef CYBHAPTICS_H
	virtual void setHapticMatrix(HLdouble* matrix);
#else
	virtual void setHapticMatrix(double* matrix);
#endif

	virtual ~CybRemoteHapticInterator();
	
	static CybRemoteInterator* getInterator();

protected:
#ifdef CYBHAPTICS_H
	HLdouble* hapticMatrix;
#else
	double* hapticMatrix;
#endif

};


#endif /* CYBREMOTEHAPTICINTERATOR_H_ */


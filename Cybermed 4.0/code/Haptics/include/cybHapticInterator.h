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

#ifndef CYBHAPTICINTERATOR_H_
#define CYBHAPTICINTERATOR_H_

#include "cybInterator.h"
#include "cybOpenHPhantom.h"

class CybHapticInterator : public CybInterator {
public:
	typedef cybMesh<cybSurfaceTriTraits> sMesh;
	typedef mfCellsIterator<cybSurfaceTriTraits> sCellIterator;

	CybHapticInterator();

	/**
	 *
	 */
	virtual CybDevice* getDevice();

	/**
	 *
	 */
	virtual void create(int id);

	/**
	 *
	 */
	void destroy();

	HLdouble* getHapticMatrix();

	/**
	 *
	 */
	void setHapticMatrix(double* matrix);

	/**
	 *
	 */
	void drawInterator();
	
	/**
	*
	*/
	
	static CybInterator* getInterator();


	virtual ~CybHapticInterator();

protected:
	HLdouble hapticMatrix[16];

private:
	CybOpenHPhantom* hapticDevice;

	void drawHapticsCursor();
};

#endif /* CYBHAPTICINTERATOR_H_ */

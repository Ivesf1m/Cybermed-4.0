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

#ifndef CYBLAYERLISTENER_H_
#define CYBLAYERLISTENER_H_

class CybLayerListener {

public:
	virtual void layerColorEventPerformed(int layer, float r, float g, float b, float a) = 0;

	//virtual void layerScaleEventPerformed(int layer, int scale);

	//virtual void layerTranslationEventPerformed(...);

	//virtual void layerRotationEventPerformed(...);

};

#endif /* CYBLAYERLISTENER_H_ */

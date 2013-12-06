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

#include "cybRemoteGloveInterator.h"
#include <cybermed/cybOpenHPhantom.h>
#include <cybermed/cybHapticInterator.h>
#include "cybRemoteHapticInterator.h"

class CybProcessRemoteInterators {

	public:
	 static void processGlovePosition(char* buffer, string ipStr, short int port, CybRemoteInterator* interator)  {
		int pos = 1;
		int arSize = 100;
		float *matrix = new float[arSize];

		memcpy(matrix, buffer + pos, sizeof(float)*arSize);
		pos += sizeof(float)*arSize;
		cout << "Vai chamar remoto" << endl;
		CybRemoteGloveInterator * rGloveInterator = dynamic_cast<CybRemoteGloveInterator *>(interator);
		rGloveInterator->setMatrix(matrix);
	}

	 static void processHapticPosition(char* buffer, string ipStr, short int port, CybRemoteInterator* interator)  {

		cout << "OLá!!" << endl;

		float x, y, z;
		//int ipLen = ipStr.length();

		int pos = 1;
		HLdouble* hapticMatrix = new HLdouble[16];
		memcpy(hapticMatrix, buffer + pos, sizeof(HLdouble)*16);
		pos += sizeof(HLdouble)*16;
		cout << "copia a matrix háptica: " << endl;

		CybRemoteHapticInterator * rHapticInterator = (CybRemoteHapticInterator*) interator;
		rHapticInterator->setHapticMatrix(hapticMatrix);	
		cout << "setou o interator remoto: " << endl;
	}

};

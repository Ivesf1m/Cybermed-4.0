  // *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2013 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#ifndef CYBABSTRACTDISPLAY_H_INCLUDED
#define CYBABSTRACTDISPLAY_H_INCLUDED

#include "cybParameters.h"
#include "cybShaderManager.h"

class CybAbstractDisplay
{
	public:
		virtual void display() = 0;
		virtual void uniforms() = 0;
		virtual void init() = 0;
		virtual void use() = 0;

		virtual CybShaderManager* getManager()
		{
			return manager;
		}

		virtual void setManager(CybShaderManager* m)
		{
			delete manager;
			manager = m;
		}

		virtual void setMatrices(mat4 mv, mat4 p)
		{
			ModelView = mv;
			Projection = p;
			CybLineMatrix::multiplyMatrices4D(ModelView, Projection, MVP);
			CybLineMatrix::createNormalMatrix(ModelView, NormalMatrix);
		}

	protected:
		CybShaderManager* manager;
		bool useDisplay;
		int numPasses;
		mat4 ModelView, Projection, MVP;
		mat3 NormalMatrix;
};

#endif

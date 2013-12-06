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

#include "cybMatrixOperator.h"

	CybMatrixOperator::CybMatrixOperator()
	{}

	
	float CybMatrixOperator::matrixDeterminant(float *m, int dim)
	{
		float detBuf = 0;
		float *m2;
		int col;
	
		if(dim == 0)
			return 0;
		if(dim == 1)
			return m[0];
		if(dim == 2)
			return (m[0]*m[3] - m[1]*m[2]);
		if(dim == 3)
		{
			return (m[0]*m[4]*m[8]) + (m[1]*m[5]*m[6]) + (m[3]*m[7]*m[2]) -
			((m[0]*m[5]*m[7]) + (m[1]*m[3]*m[8]) + (m[6]*m[4]*m[2]));
		}
		if(dim > 3)
		{
			m2 = new float[dim*(dim-1)];
	
			for(col = 0; col < dim; col++)
			{
				delLinCol(m, m2, 0, col, dim);
	
				if(!(col%2))
				{
					detBuf+= matrixDeterminant(m2, dim-1) * m[col];
				}
				else
				{
					detBuf-= matrixDeterminant(m2, dim-1) * m[col];
				}
			}
	
			delete m2;
		}
		return detBuf;
	}
	
	double CybMatrixOperator::matrixDeterminant2(double *m, int dim)
	{
		double detBuf = 0;
		double subBuf;
		double *mAux;
		int matPos;
	
		if(dim == 0)
			return 0;
		if(dim == 1)
			return m[0];
		if(dim == 2)
			return (m[0]*m[3] - m[1]*m[2]);
		if(dim == 3)
		{
			return (m[0]*m[4]*m[8]) + (m[1]*m[5]*m[6]) + (m[3]*m[7]*m[2]) -
			((m[0]*m[5]*m[7]) + (m[1]*m[3]*m[8]) + (m[6]*m[4]*m[2]));
		}
		if(dim > 3)
		{
			mAux = new double[(dim-1)*(dim)];
	
			for(int i = 1; i < dim; i++)
			{
				matPos = i*dim;
				for(int j = 1; j < dim; j++)
				{
					subBuf = m[matPos]*m[j];			
					mAux[(i-1)*(dim-1) + (j-1)] = ((m[matPos +j] * m[0]) - subBuf);			
				}
			}
			detBuf = matrixDeterminant2(mAux, dim-1);
		}
	
		for(int i = 0; i < (dim - 2); i++)
		{
			detBuf /= (m[0]);
		}
	
		delete mAux;
	
		return detBuf;
	}
	
	void CybMatrixOperator::delLinCol(float *m, float *m2, int lin, int col, int s)
	{
		int extraJumpc = 0;
		int extraJumpl = 0;
		int limit = s*(s-1);
	
		for(int cont = 0; cont < limit; cont++)
		{
			if(cont == lin*s)
				extraJumpl = s;
	
			m2[cont] = m[cont + extraJumpl];
		}
	
		limit = (s-1)*(s-1);
	
		for(int cont = 0; cont < limit; cont++)
		{
			if(!((cont-col)%(s-1)) && (cont >= col)) 
				extraJumpc++;
	
			m2[cont] = m2[cont + extraJumpc];		
		}
	}
	
	void CybMatrixOperator::matrixInverse(float *m, float *m_1, int s, float deterM)
	{
		float *mAux;
		float index = 1;
	
		if(s>1)
			mAux = new float[(s)*(s-1)];
	
		if(s == 1)
		{
			m_1[0] = (float)(1/m[0]);
		}
		else
		{
			if(s%2)
			{
				for(int l = 0; l< s; l++)
				{
					for(int c = 0; c < s; c++)
					{
						delLinCol(m, mAux, l, c, s);
						m_1[s*c+l] = index * (CybMatrixOperator::matrixDeterminant(mAux, s-1)/deterM);
						index *= -1;
					}
				}
			}
			else
			{
				for(int l = 0; l< s; l++)
				{
					for(int c = 0; c < s; c++)
					{
						delLinCol(m, mAux, l, c, s);
						m_1[s*c+l] = index * (CybMatrixOperator::matrixDeterminant(mAux, s-1)/deterM);
						index *= -1;
					}
					index *= -1;
				}
			}
			delete mAux;
		}
	}
	
	float CybMatrixOperator::matrixMult(float *covM, float *difMeanV, int dim)
	{
		float result = 0, intmult;
		int index;
	
		for(int i=0; i< dim; i++)
		{
			intmult=0;
			index = dim*i;
			for(int j=0; j<dim; j++)
			{
				intmult += (float)difMeanV[j]*covM[index + j];		
			}

			result += difMeanV[i]*intmult;
		}
	
		return result;
	}
	

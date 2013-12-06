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

#include "cybPointOperator.h"

	double CybPointOperator::matrixInverse[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}; // inicial inverse matrix (identity matrix)
	
	double CybPointOperator::calculateDeterminant(double a,double b,double c,double d,double e,double f,double g,double h,double i)
	{
		return (a*(e*i-h*f) + b*(f*g-d*i) + c*(d*h-e*g));
	}
	
	void CybPointOperator::calculateInverseMatrix(int layer)
	{
		CybParameters *cybCore = CybParameters::getInstance();
	
		double deter;     // Stores de matrix parameter
		float trans[16]; // Stores de matrix transformation
		float cofator[16]; // Stores the cofator of matrix transformation
	
		for(int i=0; i<16 ; i++)		
			trans[i] =  cybCore->transforMatrix[layer][i];			

		cofator[0] = CybPointOperator::calculateDeterminant(trans[5],trans[9],trans[13],trans[6],trans[10],trans[14],trans[7],trans[11],trans[15]);
		cofator[1] = -CybPointOperator::calculateDeterminant(trans[1],trans[9],trans[13],trans[2],trans[10],trans[14],trans[3],trans[11],trans[15]);
		cofator[2] = CybPointOperator::calculateDeterminant(trans[1],trans[5],trans[13],trans[2],trans[6],trans[3],trans[7],trans[11],trans[15]);
		cofator[3] = -CybPointOperator::calculateDeterminant(trans[1],trans[5],trans[9],trans[2],trans[6],trans[10],trans[3],trans[7],trans[11]);
	
		cofator[4] = -CybPointOperator::calculateDeterminant(trans[4],trans[8],trans[12],trans[6],trans[10],trans[14],trans[7],trans[11],trans[15]);
		cofator[5] = CybPointOperator::calculateDeterminant(trans[0],trans[8],trans[12],trans[2],trans[10],trans[14],trans[3],trans[11],trans[15]);
		cofator[6] = -CybPointOperator::calculateDeterminant(trans[0],trans[4],trans[12],trans[2],trans[6],trans[14],trans[3],trans[7],trans[15]);
		cofator[7] = CybPointOperator::calculateDeterminant(trans[0],trans[4],trans[8],trans[2],trans[6],trans[10],trans[3],trans[7],trans[11]);
	
		cofator[8] = CybPointOperator::calculateDeterminant(trans[4],trans[8],trans[12],trans[5],trans[9],trans[13],trans[7],trans[11],trans[15]);
		cofator[9] = -CybPointOperator::calculateDeterminant(trans[0],trans[8],trans[12],trans[1],trans[9],trans[13],trans[3],trans[11],trans[15]);
		cofator[10] = CybPointOperator::calculateDeterminant(trans[0],trans[4],trans[12],trans[1],trans[5],trans[13],trans[3],trans[7],trans[15]);
		cofator[11] = -CybPointOperator::calculateDeterminant(trans[0],trans[4],trans[8],trans[1],trans[5],trans[9],trans[3],trans[7],trans[11]);
	
		cofator[12] = -CybPointOperator::calculateDeterminant(trans[4],trans[8],trans[12],trans[5],trans[9],trans[13],trans[6],trans[10],trans[14]);
		cofator[13] = CybPointOperator::calculateDeterminant(trans[0],trans[8],trans[12],trans[1],trans[9],trans[13],trans[2],trans[10],trans[14]);
		cofator[14] = -CybPointOperator::calculateDeterminant(trans[0],trans[4],trans[12],trans[1],trans[5],trans[13],trans[2],trans[6],trans[14]);
		cofator[15] = CybPointOperator::calculateDeterminant(trans[0],trans[4],trans[8],trans[1],trans[5],trans[9],trans[2],trans[6],trans[10]);
	
		deter = 1.0/(trans[0]*cofator[0] + trans[1]*cofator[1] + trans[2]*cofator[2] +trans[3]*cofator[3]);
	
		CybPointOperator::matrixInverse[0] = cofator[0]*deter;
		CybPointOperator::matrixInverse[1] = cofator[1]*deter;
		CybPointOperator::matrixInverse[2] = cofator[2]*deter;
		CybPointOperator::matrixInverse[3] = cofator[3]*deter;
		CybPointOperator::matrixInverse[4] = cofator[4]*deter;
		CybPointOperator::matrixInverse[5] = cofator[5]*deter;
		CybPointOperator::matrixInverse[6] = cofator[6]*deter;
		CybPointOperator::matrixInverse[7] = cofator[7]*deter;
		CybPointOperator::matrixInverse[8] = cofator[8]*deter;
		CybPointOperator::matrixInverse[9] = cofator[9]*deter;
		CybPointOperator::matrixInverse[10] = cofator[10]*deter;
		CybPointOperator::matrixInverse[11] = cofator[11]*deter;
		CybPointOperator::matrixInverse[12] = cofator[12]*deter;
		CybPointOperator::matrixInverse[13] = cofator[13]*deter;
		CybPointOperator::matrixInverse[14] = cofator[14]*deter;
		CybPointOperator::matrixInverse[15] = cofator[15]*deter;
	}
	
	CybVector3D<float> CybPointOperator::executInverseTransformation(CybVector3D<float> point, int layer)
	{
		CybVector4DH<float> coordenate;
		
		coordenate[0] = CybPointOperator::matrixInverse[0]*point[0] +
		CybPointOperator::matrixInverse[4]*point[1] +
		CybPointOperator::matrixInverse[8]*point[2] + 
		CybPointOperator::matrixInverse[12];
		coordenate[1] = CybPointOperator::matrixInverse[1]*point[0] +
		CybPointOperator::matrixInverse[5]*point[1] +
		CybPointOperator::matrixInverse[9]*point[2] + 
		CybPointOperator::matrixInverse[13];
		coordenate[2] = CybPointOperator::matrixInverse[2]*point[0] + 
		CybPointOperator::matrixInverse[6]*point[1] +
		CybPointOperator::matrixInverse[10]*point[2]+
		CybPointOperator::matrixInverse[14];
		coordenate[3] = CybPointOperator::matrixInverse[3]*point[0] + 
		CybPointOperator::matrixInverse[7]*point[1] +
		CybPointOperator::matrixInverse[11]*point[2]+ 
		CybPointOperator::matrixInverse[15];
	
		return coordenate.toVector3D();
	}
	
	CybVector3D<float> CybPointOperator::executTransformation(CybVector3D<float> point, int layer)
	{
		CybParameters *cybCore = CybParameters::getInstance();
	
		CybVector4DH<float> coordenate;
	
		coordenate[0] = cybCore->transforMatrix[layer][0]*point[0]  +
		cybCore->transforMatrix[layer][4]*point[1]  +
		cybCore->transforMatrix[layer][8]*point[2]  +
		cybCore->transforMatrix[layer][12];
		coordenate[1] = cybCore->transforMatrix[layer][1]*point[0]  +
		cybCore->transforMatrix[layer][5]*point[1]  +
		cybCore->transforMatrix[layer][9]*point[2]  +
		cybCore->transforMatrix[layer][13];
		coordenate[2] = cybCore->transforMatrix[layer][2]*point[0]  +
		cybCore->transforMatrix[layer][6]*point[1]  +
		cybCore->transforMatrix[layer][10]*point[2] +
		cybCore->transforMatrix[layer][14];
		coordenate[3] = cybCore->transforMatrix[layer][3]*point[0]  +
		cybCore->transforMatrix[layer][7]*point[1]  +
		cybCore->transforMatrix[layer][11]*point[2] +
		cybCore->transforMatrix[layer][15];
	
		return coordenate.toVector3D();
	}
	
	int CybPointOperator::executVertexAproximation(CybVector3D<float> vertex0,CybVector3D<float> vertex1,CybVector3D<float> vertex2,CybVector3D<float> point)
	{
		double distance[3];    // It stores the distances of the point of collision to the triangles' vertexes
		CybVector3D<float> aux;
	
		aux = vertex0-point;
		// It counts the distance between the vertexes and the point of collision
		//VECTOR(aux,vertex0,pointOfCollision);
		distance[0] = (aux^aux);
	
		aux = vertex1-point;
		//VECTOR(aux,vertex1,pointOfCollision);
		distance[1] = (aux^aux);
	
		aux = vertex2-point;
		//VECTOR(aux,vertex2,pointOfCollision);
		distance[2] = (aux^aux);
	
		if(distance[0] <= distance[1])
		{
			if(distance[0] <= distance[2])
				return 0;  // if distance[0]<distance[1] and distance[0]<distance[2] then distance[0] is the smallest value
			else
				return 2;  // if distance[0]<distance[1] and distance[2]<distance[0] then distance[2] is the smallest value
		}
		else
		{
			if(distance[1] <= distance[2])
				return 1;  // if distance[1]<distance[0] and distance[1]<distance[2] then distance[1] is the smallest value
			else
				return 2;  // if distance[1]<distance[0] and distance[2]<distance[1] then distance[2] is the smallest value
		}
	}

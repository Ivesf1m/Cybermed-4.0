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

#include "cybDefaultShaderDisplay.h"

CybDefaultShaderDisplay::CybDefaultShaderDisplay(bool useDisplay = false, int numPasses = 1)
{
	ifstream vInput("DefaultShader.vert", ifstream::in);
	ifstream fInput("DefaultShader.frag", ifstream::in);
	manager = new CybShaderManager(vInput, fInput);
	this->useDisplay = useDisplay;
	this->numPasses = numPasses;
}

CybDefaultShaderDisplay::~CybDefaultShaderDisplay()
{
	delete manager;
}

void CybDefaultShaderDisplay::display()
{

}

void CybDefaultShaderDisplay::init()
{
	shaders->compile();
	shaders->getVertexShader()->bindInVariable(VERTEX_ATTRIB, "VertexPosition");
	shaders->getVertexShader()->bindInVariable(NORMAL_ATTRIB, "VertexNormal");
	shaders->link();
	cout << shaders->getLog() << endl;
	shaders->validate();
	cout << shaders->getLog() << endl;
	shaders->printActiveUniforms();
	shaders->printActiveAttributes();
}

void CybDefaultShaderDisplay::uniforms()
{
	CybParameters* cybCore = CybParameters::getInstance();
	vec4 lPos[6] = {cybCore->positionLight[0].elements, cybCore->positionLight[1].elements,
			cybCore->positionLight[2].elements, cybCore->positionLight[3].elements,
			cybCore->positionLight[4].elements, cybCore->positionLight[5].elements};
	vec4 lInt[6] = {cybCore->diffuseLight[0].elements, cybCore->diffuseLight[1].elements,
			cybCore->diffuseLight[2].elements, cybCore->diffuseLight[3].elements,
			cybCore->diffuseLight[4].elements, cybCore->diffuseLight[5].elements};
	vec3 Ka = {cybCore->ambientLight[0], cybCore->ambientLight[1], cybCore->ambientLight[2]};
	shaders->setUniformMat4("ModelViewMatrix", ModelView);
	shaders->setUniformMat4("ProjectionMatrix", Projection);
	shaders->setUniformMat4("NormalMatrix", NormalMatrix);
	shaders->setUniformMat4("MVP", MVP);
	shaders->setUniform("numLights", cybCore->nLights);
	glUniform4fv(glGetUniformLocation("lightPosition"), 6,  lPos);
	glUniform4fv(glGetUniformLocation("lightIntensity"), 6, lInt);
	shaders->setUniformVec3("Ka", Ka};
	shaders->setUniformVec3("Ks", cybCore->Ks.elements);
	shaders->setUniformVec3("Kd", cybCore->Kd.elements);
	shaders->setUniform("Shininess", cybCore->Shininess);
}

void CybDefaultShaderDisplay::use()
{
	manager->use();
}

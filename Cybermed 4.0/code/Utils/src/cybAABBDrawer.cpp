// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba.
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

#include "cybAABBDrawer.h"

CybAABBDrawer::CybAABBDrawer(CybVector3D<float>& center, CybVector3D<float>& sizes, CybVector3D<float>& scale, CybVector3D<float>& trans)
{
	this->center = center;
	this->sizes = sizes;
	this->scale = scale;
	this->translation = translation;
	CybBoxHolder::getInstance()->addBox(this);
}

void CybAABBDrawer::drawBox()
{
	glPushMatrix();
	glTranslated(translation[0], translation[1], translation[2]);
      	glScaled(scale[0], scale[1], scale[2]);
	glColor3d(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] - fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] - fabs(sizes[2]));
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex3d(center[0] - fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] - fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] - fabs(sizes[1]), center[2] + fabs(sizes[2]));
		glVertex3d(center[0] + fabs(sizes[0]), center[1] + fabs(sizes[1]), center[2] + fabs(sizes[2]));
	glEnd();
	glPopMatrix();
}

CybVector3D<float>& CybAABBDrawer::getCenter()
{
	return center;
}

CybVector3D<float>& CybAABBDrawer::getScale()
{
	return scale;
}

CybVector3D<float>& CybAABBDrawer::getSizes()
{
	return sizes;
}

CybVector3D<float>& CybAABBDrawer::getTranslation()
{
	return translation;
}

void CybAABBDrawer::setCenter(CybVector3D<float>& center)
{
	this->center = center;
}

void CybAABBDrawer::setScale(CybVector3D<float>& scale)
{
	this->scale = scale;
}

void CybAABBDrawer::setSizes(CybVector3D<float>& sizes)
{
	this->sizes = sizes;
}

void CybAABBDrawer::setTranslation(CybVector3D<float>& translation)
{
	this->translation = translation;
}

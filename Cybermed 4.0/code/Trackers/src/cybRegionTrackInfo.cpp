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

#include "cybRegionTrackInfo.h"

CybRegionTrackInfo::CybRegionTrackInfo()
{
	maxX = maxY = minX = minY = 0;
}

CybRegionTrackInfo::CybRegionTrackInfo(int maxX, int minX, int maxY, int minY)
{
	this->maxX = maxX;
	this->minX = minX;
	this->maxY = maxY;
	this->minY = minY;
}

CybRegionTrackInfo::CybRegionTrackInfo(const CBlob *blob)
{
	this->maxX = (int) blob->MaxX();
	this->minX = (int) blob->MinX();
	this->maxY = (int) blob->MaxY();
	this->minY = (int) blob->MinY();
}

CybRegionTrackInfo::~CybRegionTrackInfo()
{
}



int CybRegionTrackInfo::getMaxX(){	return maxX; }
int CybRegionTrackInfo::getMaxY(){	return maxY; }
int CybRegionTrackInfo::getMinX(){	return minX; }
int CybRegionTrackInfo::getMinY(){	return minY; }

double CybRegionTrackInfo::getArea(){	return ((maxX - minX)*(maxY - minY)); }

void CybRegionTrackInfo::setMaxX(int maxX){	this->maxX = maxX; }
void CybRegionTrackInfo::setMinX(int minX){	this->minX = minX; }
void CybRegionTrackInfo::setMaxY(int maxY){	this->maxY = maxY; }
void CybRegionTrackInfo::setMinY(int minY){	this->minY = minY; }

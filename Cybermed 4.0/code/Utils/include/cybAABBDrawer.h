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

#ifndef _CYBAABBDRAWER_H_
#define _CYBAABBDRAWER_H_

#include "cybVector3D.h"
#include "cybBoxHolder.h"
#include "cybBoxDrawer.h"
#include <GL/glut.h>

/**
 * @class CybAABBDrawer
 * @file cybAABBDrawer.h 
 * @short This class implements a box drawer for AABBs.
 *
 * This class is responsible for drawing AABBs on the screen and applying transformations in world space. 
 * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 3.0
 * @date 2012, March
 * 
 */

class CybAABBDrawer : public CybBoxDrawer
{
	public:
		/*
		* Constructor
		* 
		* @param CybVector3D<float>& center: the center of the AABB.
		* @param CybVector3D<float>& sizes: the sizes of the AABB.
		* @param CybVector3D<float>& scale: the scale parameters for this AABB.
		* @param CybVector3D<float>& trans: the translation parameters for this AABB.
		*/
		CybAABBDrawer(CybVector3D<float>&, CybVector3D<float>&, CybVector3D<float>&, CybVector3D<float>& );
		/*
		* This method draws the AABB.
		* 
		* @param void
		* @return void
		*/
		void drawBox();
		/*
		* Getter for the AABB's center.
		*
		* @param void
		* @return CybVector3D<float>&: the center of the box.
		*/
		CybVector3D<float>& getCenter();
		/*
		* Getter for the AABB's scale parameters.
		*
		* @param void
		* @return CybVector3D<float>&: the scale parameters of the box.
		*/
		CybVector3D<float>& getScale();
		/*
		* Getter for the AABB's sizes.
		*
		* @param void
		* @return CybVector3D<float>&: the sizes of the box.
		*/
		CybVector3D<float>& getSizes();
		/*
		* Getter for the AABB's translation parameters.
		*
		* @param void
		* @return CybVector3D<float>&: the translation parameters of the box.
		*/
		CybVector3D<float>& getTranslation();
		/*
		* Setter for the AABB's center.
		*
		* @param CybVector3D<float>& center: the new center of the box.
		* @return void
		*/
		void setCenter(CybVector3D<float>&);
		/*
		* Setter for the AABB's scale parameters.
		*
		* @param CybVector3D<float>& scale: the new scale parameters of the box.
		* @return void
		*/
		void setScale(CybVector3D<float>&);
		/*
		* Setter for the AABB's sizes.
		*
		* @param CybVector3D<float>& sizes: the new sizes of the box.
		* @return void
		*/
		void setSizes(CybVector3D<float>&);
		/*
		* Setter for the AABB's translation parameters.
		*
		* @param CybVector3D<float>& trans: the new translation parameters of the box.
		* @return void
		*/
		void setTranslation(CybVector3D<float>&);
	private:
		CybVector3D<float> center;			//The center of the AABB.
		CybVector3D<float> scale;			//The scale parameters for the AABB.
		CybVector3D<float> sizes;			//The sizes of the AABB.
		CybVector3D<float> translation;			//The translation parameters for the AABB.
};

#endif

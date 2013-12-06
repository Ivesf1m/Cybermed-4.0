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

#ifndef COLORTHRESOLD_H_
#define COLORTHRESOLD_H_

#ifdef CYBOPTICALTRACKER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <stdio.h>

/**
 * @class CybImageUtil
 * @file CybImageUtil.h 
 * @short This class defines some method used for image processing
 * 
 *
 *  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2008, July
 * 
 */

class CybImageUtil
{
public:

	/** Constructor */
	CybImageUtil();

	/** Destructor */
	virtual ~CybImageUtil();
	
    /**
	 * This method return a IplImage as result of a threshold color filter using RGB space color
	 * 
	 * @param IplImage *src
	 * @param int r_top
	 * @param int *r_down
	 * @param int *g_top
	 * @param int *g_down
	 * @param int *b_top
	 * @param int *b_down
	 * @return IplImage *
	 * 
  	 */ 
	IplImage *findRGBColor(IplImage * src,
	                       int r_top,
	                       int r_down,
	                       int g_top, 
	                       int g_down, 
	                       int b_top, 
	                       int b_down);
    /**
	 * This method return a IplImage as result of a threshold color filter using HSV space color
	 * 
	 * @param IplImage *src
	 * @param int hue_top
	 * @param int *hue_down
	 * @param int *saturation_top
	 * @param int *saturation_down
	 * @param int *value_top
	 * @param int *value_down
	 * @return IplImage *
	 * 
  	 */ 
	IplImage *findHSVColor(IplImage * src, 
		                       int hue_top,
		                       int hue_down,
		                       int saturation_top, 
		                       int saturation_down, 
		                       int value_top, 
		                       int value_down);
	 /**
	 * This method find the countor of an image using the canny algorithm
	 * 
	 * @param IplImage *src
	 * @return IplImage *
	 * 
  	 */ 

	IplImage *findCountor(IplImage *src);

	IplImage *image_tmp; /**< Image tmp used in processing*/
	IplImage *result; /**< Image result*/
};
#endif //CYBOPTICALTRACKER_H

#endif /*COLORTHRESOLD_H_*/

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

#ifndef CYBHAARTRACKER_H_
#define CYBHAARTRACKER_H_

#ifdef CYBOPTICALTRACKER_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "cybOpticalTracker.h"
#include "cybRegionTrackInfo.h"
#include "cybCam.h"
#include "cybStereo.h"
#include "cybThread.h"

/**
 * @class CybHaarTracker
 * @file CybHaarTracker.h 
 * @short This class defines a tracker based on Haar algorithm
 * 
 * The OpenCV implementation of Haar classifier was used
 *  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2008, July
 * 
 */

class CybHaarTracker : public CybOpticalTracker, public CybThread
{
public:

	/** Constructor*/
	CybHaarTracker();

	/** Destructor*/
	virtual ~CybHaarTracker();
	
	 /**
  	 * This method is used to detect the pattern used in a image
  	 * 
  	 * @param IplImage *img
  	 * @return CybRegionTrackInfo *
  	 * 
  	 */ 
	virtual CybRegionTrackInfo *detect(IplImage *img);

	 /**
  	 * This method return the 3D position of the tracked object
  	 * 
  	 * @param double *position
  	 * @return void
  	 * 
  	 */ 
	virtual void getPosition(float *position);

	 /**
  	 * This method is used to create and config an instance of Haar tracker
  	 * 
  	 * @param void *userdata
  	 * @return void
  	 * 
  	 */ 
	virtual void createTracker(void *userData);

	 /**
  	 * Set debug mode
  	 * 
  	 * @param bool
  	 * @return void
  	 * 
  	 */ 
	virtual void setDebug(bool dbg_mode);

	 /**
  	 * Get debug mode
  	 * 
  	 * @param void
  	 * @return bool
  	 * 
  	 */ 
	virtual bool getDebugStatus();

	 /**
  	 * Get the instance of stereo class
  	 * 
  	 * @param void
  	 * @return CybStereo *
  	 * 
  	 */ 	
	virtual CybStereo *getStereoInstance();
	
	virtual void initDevice();

	virtual void stopDevice();

	virtual void getMatrix(float *matrix);
	
	virtual void getInitialPosition(float *position);
	
private:
	CvMemStorage* storage; /**< A storage variable to memory management*/
	CvHaarClassifierCascade* cascade; /**< Haar classifier instance.*/
	CybCam *cams; /**< list of cams*/
	IplImage** frames; /**< list of frames*/
	IplImage* pyr_img[2]; /**< Image used to apply the pyramid filter*/
	bool dbg_mode; /**< debug mode*/
	
	CybRegionTrackInfo *region1; /**< Tracked region of first image*/
	CybRegionTrackInfo *region2; /**< Tracked region of second image*/
	CybStereo *stereo; /**< The stereo instance*/
	double point3D[3]; /**< the 3D point*/
	
    /**
       This method is call by thread system to execute the capture action
    */
	virtual void run();
};

#endif //CYBOPTICALTRACKER_H

#endif /*CYBHAARTRACKER_H_*/

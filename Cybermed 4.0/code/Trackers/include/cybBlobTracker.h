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


#ifndef CYBBLOBTRACKER_H_
#define CYBBLOBTRACKER_H_

#ifdef CYBOPTICALTRACKER_H

#include "cybOpticalTracker.h"
#include "cybThread.h"
#include <opencv/Blob.h>
#include <opencv/BlobResult.h>
#include "cybCam.h"
#include "cybImageUtil.h"
#include "cybStereo.h"

#include "cybRegionTrackInfo.h"


/**
 * @class CybBlobTracker
 * @file CybBlobTracker.h 
 * @short This class defines a optical tracker based on Blob find algorithm. 
 * 
 *
 *  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2008, July
 * 
 */



/*TODO: Este método ainda não é thread-safe, uma investigação deve ser feita para garantir 
sua execucao perfeita, note que algumas vezes quando utilizamos ele dá segmentation fault*/

class CybBlobTracker : public CybOpticalTracker, public CybThread {
public:
	/** Constructor */
	CybBlobTracker();

	/** Destructor */
	virtual ~CybBlobTracker();

	/**
  	 * This method returns the tracker position.
  	 * 
  	 * @param double *
  	 * @return void
  	 * 
  	 */ 
	virtual void getPosition(float *position);

	void getInitialPosition(float *position);

	void getMatrix(float *matrix);

	void initDevice();

	void stopDevice();

	/**
	 * This method creates a BlobTracker and config it.
	 *
	 * @param void* userData data needs to create the specific tracker
	 * @return void.
	 * 
	 */
	virtual void createTracker(void *userData);
	
	/**
	 * This method find the trackerd region using blob find algorithm.
	 *
	 * @param IplImage* src
	 * @return CybRegionTrackInfo *
	 * 
	 */
	virtual CybRegionTrackInfo *findRegion(IplImage *src);

	/**
	 * This method return the value of filter area.
	 *
	 * @return double
	 * 
	 */	
	virtual double getFilterAreaValue();

	/**
	 * This method set the value of filter area.
	 *
	 * @param double filterArea
	 * @return void
	 * 
	 */
	virtual void setFilterAreaValue(double filterArea);

	/**
	 * This method set the properties of the threshold color filter.
	 *
	 * @param int hue_top 
	 * @param int hue_down
	 * @param int saturation_top
	 * @param int saturation_down
	 * @param int value_top
	 * @param int value_down
	 *  
	 * @return void
	 * 
	 */	
	virtual void setStepColorProperties(int hue_top, int hue_down,
			int saturation_top, int saturation_down, int value_top,
			int value_down);

	/**
	 * This method return the CybStereo instance associated to tracker.
	 *
	 * @return CybStereo *
	 * 
	 */		
	virtual CybStereo *getStereoInstance();

	//Activate debug options
	
	void setDebug(bool dbg);
	bool getDebug();

	void configColorTrack(int, int, int, int, int, int);

protected:

	/**
	 * This method removes the blobs smaller than the ellipses defined by imageWidth and imageHeigth.
	 *
	 * @param CBlobResult *blobs
	 * @param int imageWitdh
	 * @param int imageHeigth
	 *
	 * @return CBlobResult *
	 * 
	 */		
	virtual CBlobResult *eliminateImageBlobs(CBlobResult *blobs,
			int imageWitdh, int imageHeigth);

	/**
	 * This method finds the best blob using like reference an ellipse defined by imageWidth and imageHeigth.
	 *
	 * @param CBlobResult *blobs
	 * @param int imageWitdh
	 * @param int imageHeigth
	 *
	 * @return CBlob *
	 * 
	 */	
	virtual CBlob *getBestBlobResult(CBlobResult *blobs, int imageWitdh,
			int imageHeigth);

private:
	CybCam *cams; /**< the list of cams*/
	IplImage** frames; /**< the list of frames*/
	CybImageUtil *imgUtil; /**< An instance of image util used for image processing*/
	IplImage *img1; /**< Image captured by right cam*/
	IplImage *img2; /**< Image captured by right cam*/
	double filterArea; /**<Filter the blobs smaller than this value */
	bool dbg /**< indicates if debugs tasks are enable*/;

	/**Value used by threshold color filter*/
	int hue_top;
	int hue_down;
	int saturation_top;
	int saturation_down;
	int value_top;
	int value_down;
	
	CybStereo *stereo; /**< An instance of CybStereo. Used to provide the 3D position*/

	/**Images used in intermediary steps*/
	IplImage *imgColorTracker1;
	IplImage *imgColorTracker2;
	IplImage *dst_1;
	IplImage *dst_2;

	/**< Region tracked in each image*/
	CybRegionTrackInfo *region1;
	CybRegionTrackInfo *region2;
	
	double position3D[3]; /**< The 3D position provided by CybStereo*/

	/** Thread method*/
	void run();

};

#endif //CYBOPTICALTRACKER_H

#endif /*CYBBLOBTRACKER_H_*/

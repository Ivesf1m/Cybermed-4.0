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

#ifndef CYBCAM_H_
#define CYBCAM_H_

#ifdef CYBOPTICALTRACKER_H

#include "cybThread.h"
#include <opencv/highgui.h>

/**
 * @class CybCam
 * @file CybCam.h 
 * @short This class defines a cam conected to Cybermed 
 * 
 *
 *  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2008, July
 * 
 */
 
class CybCam : public CybThread {
public:
	
	/**Destructor */
    virtual ~CybCam();

    /**
  	 * This method indenfity all cams installed on system and create prepare them for use in Cybermed
  	 * 
  	 * @param int numOfCam
  	 * @return void
  	 * 
  	 */ 
	virtual void createCams(int numOfCam);
	
    /**
  	 * This method a specific cam installed on system based on the index
  	 * 
  	 * @param int camera_index
  	 * @return void
  	 * 
  	 */ 	
	virtual void createCam(int camera_index);
	
    /**
  	 * This method return a list of IplImages acquired from cams
  	 * 
  	 * @return IpLImage **
  	 * 
  	 */ 
	virtual IplImage **getImageListFromCams();
	
    /**
  	 * This method copy a list of IplImages
  	 * 
  	 * @return IplImage **
  	 * 
  	 */ 
	virtual IplImage **copyImageList();
	
    /**
  	 * Set the delay to call the routine that acquire the images from cams
  	 * 
  	 * @param int time
  	 * @return void
  	 * 
  	 */ 
	virtual void setTimeToCapture(int time);
	
    /**
  	 * Return the delay to call the routine that acquire the images from cams
  	 * 
  	 * @return int
  	 * 
  	 */   
	virtual int getTimeToCapture();
	
	  /**
  	 * Return a specific property from a cam.
  	 * 
  	 * @param int camID the ID of the cam
  	 * @param int cv_property_id the ID of the property based on OpenCV property IDs
  	 * @return double
  	 * 
  	 */
	virtual double getCamProperty( int camID, int cv_property_id );

	  /**
  	 * Set a specific property from a cam.
  	 * 
  	 * @param int camID the ID of the cam
  	 * @param int cv_property_id the ID of the property based on OpenCV property IDs
  	 * @param double value
  	 * @return bool
  	 * 
  	 */
	virtual bool setCamProperty( int camID, int cv_property_id, double value );
	
	 /**
  	 * Set debug mode
  	 * 
  	 * @param bool dbug
  	 * @return void
  	 * 
  	 */
	void setDebug(bool dbug);
	
	 /**
  	 * Stop cams thread
  	 * 
  	 * @return void
  	 * 
  	 */    
    virtual void stopCams();
    
      /**
  	 * Release the list of images
  	 * 
  	 * @param IplImage **
  	 * @return void
  	 * 
  	 */
	void releaseImageList(IplImage **list);
	
	 /**
  	 * Return the num of cams connected in system
  	 * 
  	 * @return int
  	 * 
  	 */
	virtual int getNumOfCams();
	
	 /**
  	 * Return the unique instance of CybCam
  	 * 
  	 * @return CybCam *
  	 * 
  	 */
	static CybCam *getInstance() {
		if (camInstance == NULL)
			camInstance = new CybCam();
		return camInstance;
	}
	
	
	 /**
  	 * Return an IplImage
  	 * 
  	 * @param int camID the ID of the cam
  	 * @param int cv_property_id the ID of the property based on OpenCV property IDs
  	 * @param double value
  	 * @return bool
  	 * 
  	 */
	IplImage *getImage();

protected:
	
private:
	static CybCam *camInstance; /**< Unique instance of CybCam*/
	IplImage **camImageList; /**< List of images*/
	CvCapture **captureList; /**< List of CvCams (OpenCV representation of cam*/
	int numOfCam; /**< Number of cam on Cybermed*/
	bool retrieveError; /**< Indicate if an error has occurred*/
	bool imageAvaiable; /**< Indicates if there are images available*/
	int captureTime; /**< Delay time to run the capture routine*/
	bool dbug; /**< */

    /** Constructor */
	CybCam();

    /**
       This method is call by thread system to execute the capture action
    */
	void run();
};

#endif //CYBOPTICALTRACKER_H

#endif /*CYBCAM_H_*/

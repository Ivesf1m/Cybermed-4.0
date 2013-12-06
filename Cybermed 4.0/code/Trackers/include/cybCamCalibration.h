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

#ifndef CYBCAMCALIBRATION_H_
#define CYBCAMCALIBRATION_H_

#ifdef CYBOPTICALTRACKER_H

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>

using namespace std;

/**
 * @class CybCamCalibration
 * @file CybCamCalibration.h 
 * @short This class defines is used to calibrate cameras connected to Cybermed.
 * 
 * The ChessBoard method is used to calibrate the cameras
 *
 *  * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2008, July
 * 
 */

class CybCamCalibration
{

private:
	CvSize board_size; /**< Size of board*/
	float square_size , aspect_ratio;/**< size of square and its asptect ration */
	int i, image_count;/**< counts*/
	int flags; /**< Options to calibrate routine. Zero args passed nowday*/
	char imagename[1024];/**< Image name*/
	CvMemStorage* storage;/**< A CV storege variable to manage memory allocation*/
	CvSeq* image_points_seq;/**< A list of points*/
	int elem_size; /**< Element size*/
	int flip_vertical; /**< Value to flip vertical*/
	CvPoint2D32f* image_points_buf;/**< A buffer to store image points*/
	double _camera[9], _dist_coeffs[4];/**< Parameters captured from cams*/
	CvMat camera;/**< A matrix used to store the extrinsics parameters from cam*/
	CvMat dist_coeffs;/**< A matrix of coefficient of distortion*/
	CvMat *extr_params, *reproj_errs;/**< variables used to indicate erro on calibration*/
	double avg_reproj_err;/**< indicates error on reprojection average calc*/
	CvSize img_size;/**< Image size*/
	
protected:
	
    /**
  	 * This method computes an error factor based on camera parameters
  	 *
  	 * @param const CvMat* object_points
	 * @param const CvMat* rot_vects
	 * @param const CvMat* trans_vects
	 *	@param const CvMat* camera_matrix
    * @param const CvMat* dist_coeffs
	 *	@param const CvMat* image_points
	 * @param const CvMat* point_counts
	 *	@param CvMat* per_view_errors
  	 * @return double
  	 *
  	 */

	double compute_error( const CvMat* object_points,
	        const CvMat* rot_vects, const CvMat* trans_vects,
	        const CvMat* camera_matrix, const CvMat* dist_coeffs,
	        const CvMat* image_points, const CvMat* point_counts,
	        CvMat* per_view_errors );
	
    /**
  	 * This method calibrate the camera using its parameters and projection parameters
  	 *
  	 * @param CvSeq* image_points_seq
	 * @param CvSize img_size
	 * @param CvSize board_size
	 *	@param float square_size
    * @param float aspect_ratio
	 *	@param int flags
	 * @param CvMat* camera_matrix
	 *	@param CvMat* dist_coeffs
	 *	@param CvMat** extr_params
	 *	@param CvMat** reproj_errs
	 *	@param double* avg_reproj_err
  	 * @return int
  	 *
  	 */
	int calibration( CvSeq* image_points_seq, CvSize img_size, CvSize board_size,
	                     float square_size, float aspect_ratio, int flags,
	                     CvMat* camera_matrix, CvMat* dist_coeffs, CvMat** extr_params,
	                     CvMat** reproj_errs, double* avg_reproj_err );
	
public:

	/** Constructor */
	CybCamCalibration(int size_width, int size_height);
	
	/** Destructor */
	virtual ~CybCamCalibration();
	
    /**
  	 * This method generates data used by calibration routine
  	 *
  	 * @param IplImage *rgb_image
  	 * @return bool
  	 *
  	 */	
	bool generateDataToCalibration(IplImage *rgb_image);

    /**
  	 * This method run the calibration routines to n cams connected on system and try calibrate all them
  	 *
  	 * @param void
  	 * @return void
  	 *
  	 */	
	bool tryCalibrate();

    /**
  	 * This method prints the parameters generates by calibration routine in the standard output
  	 *
  	 * @param void
  	 * @return void
  	 *
  	 */	
	void printParams();

    /**
  	 * This method saves the parameters generates by calibration routine in a file
  	 *
  	 * @param void
  	 * @return void
  	 *
  	 */	
	void save_params(char *filename);
};

#endif //CYBOPTICALTRACKER_H

#endif /*CYBCAMCALIBRATION_H_*/

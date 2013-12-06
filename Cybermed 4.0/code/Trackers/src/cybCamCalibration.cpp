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

#include "cybCamCalibration.h"

CybCamCalibration::CybCamCalibration(int size_width, int size_height) {
	board_size = cvSize(size_width, size_height);
	square_size = 1.f; 
	aspect_ratio = 1.f; 
	image_count = 25;
	flags = 0;
	flip_vertical = 0;
	image_points_buf = 0;
	camera = cvMat( 3, 3, CV_64F, _camera);
	dist_coeffs = cvMat( 1, 4, CV_64F, _dist_coeffs);
	extr_params = 0;
	reproj_errs = 0;
	avg_reproj_err = 0;
	img_size = cvSize(0, 0);
	
    elem_size = board_size.width*board_size.height*sizeof(image_points_buf[0]);
    storage = cvCreateMemStorage( MAX( elem_size*4, 1 << 16 ));
    image_points_buf = (CvPoint2D32f*)cvAlloc( elem_size );
    image_points_seq = cvCreateSeq( 0, sizeof(CvSeq), elem_size, storage );
}

CybCamCalibration::~CybCamCalibration() {
}

double CybCamCalibration::compute_error(const CvMat* object_points,
		const CvMat* rot_vects, const CvMat* trans_vects,
		const CvMat* camera_matrix, const CvMat* dist_coeffs,
		const CvMat* image_points, const CvMat* point_counts,
		CvMat* per_view_errors) {

	CvMat* image_points2 = cvCreateMat(image_points->rows, image_points->cols,
			image_points->type);
	int i, image_count = rot_vects->rows, points_so_far = 0;
	double total_err = 0, err;

	for (i = 0; i < image_count; i++) {
		CvMat object_points_i, image_points_i, image_points2_i;
		int point_count = point_counts->data.i[i];
		CvMat rot_vect, trans_vect;

		cvGetCols(object_points, &object_points_i, points_so_far, points_so_far
				+ point_count);
		cvGetCols(image_points, &image_points_i, points_so_far, points_so_far
				+ point_count);
		cvGetCols(image_points2, &image_points2_i, points_so_far, points_so_far
				+ point_count);
		points_so_far += point_count;

		cvGetRow(rot_vects, &rot_vect, i);
		cvGetRow(trans_vects, &trans_vect, i);

		cvProjectPoints2( &object_points_i, &rot_vect, &trans_vect,
				camera_matrix, dist_coeffs, &image_points2_i, 0, 0, 0, 0, 0);
		err = cvNorm( &image_points_i, &image_points2_i, CV_L1);
		if (per_view_errors)
			per_view_errors->data.db[i] = err/point_count;
		total_err += err;
	}

	cvReleaseMat( &image_points2);
	return total_err/points_so_far;
}

int CybCamCalibration::calibration(CvSeq* image_points_seq, CvSize img_size, CvSize board_size,
		float square_size, float aspect_ratio, int flags, CvMat* camera_matrix,
		CvMat* dist_coeffs, CvMat** extr_params, CvMat** reproj_errs,
		double* avg_reproj_err) {
	int code;
	int image_count = image_points_seq->total;
	int point_count = board_size.width*board_size.height;
	CvMat* image_points = cvCreateMat( 1, image_count*point_count, CV_32FC2);
	CvMat* object_points = cvCreateMat( 1, image_count*point_count, CV_32FC3);
	CvMat* point_counts = cvCreateMat( 1, image_count, CV_32SC1);
	CvMat rot_vects, trans_vects;
	int i, j, k;
	CvSeqReader reader;
	cvStartReadSeq(image_points_seq, &reader);

	// initialize arrays of points
	for (i = 0; i < image_count; i++) {
		CvPoint2D32f* src_img_pt = (CvPoint2D32f*)reader.ptr;
		CvPoint2D32f* dst_img_pt = ((CvPoint2D32f*)image_points->data.fl) + i
				*point_count;
		CvPoint3D32f* obj_pt = ((CvPoint3D32f*)object_points->data.fl) + i
				*point_count;

		for (j = 0; j < board_size.height; j++)
			for (k = 0; k < board_size.width; k++) {
				*obj_pt++ = cvPoint3D32f(j*square_size, k*square_size, 0);
				*dst_img_pt++ = *src_img_pt++;
			}
		CV_NEXT_SEQ_ELEM( image_points_seq->elem_size, reader );
	}

	cvSet(point_counts, cvScalar(point_count) );

	*extr_params = cvCreateMat(image_count, 6, CV_32FC1);
	cvGetCols( *extr_params, &rot_vects, 0, 3);
	cvGetCols( *extr_params, &trans_vects, 3, 6);

	cvZero( camera_matrix );
	cvZero( dist_coeffs );

	if (flags & CV_CALIB_FIX_ASPECT_RATIO) {
		camera_matrix->data.db[0] = aspect_ratio;
		camera_matrix->data.db[4] = 1.;
	}

	cvCalibrateCamera2(object_points, image_points, point_counts, img_size,
			camera_matrix, dist_coeffs, &rot_vects, &trans_vects, flags);

	code = cvCheckArr(camera_matrix, CV_CHECK_QUIET) && cvCheckArr(dist_coeffs,
			CV_CHECK_QUIET) && cvCheckArr( *extr_params, CV_CHECK_QUIET);

	*reproj_errs = cvCreateMat( 1, image_count, CV_64FC1);
	*avg_reproj_err = compute_error(object_points, &rot_vects,
			&trans_vects, camera_matrix, dist_coeffs, image_points,
			point_counts, *reproj_errs);

	cvReleaseMat( &object_points);
	cvReleaseMat( &image_points);
	cvReleaseMat( &point_counts);

	return code;
}

bool CybCamCalibration::generateDataToCalibration(IplImage *rgb_image){

   IplImage *view_gray;
   int found = 0, count = 0;

   img_size = cvGetSize(rgb_image);

   found = cvFindChessboardCorners( rgb_image, board_size,
            image_points_buf, &count, CV_CALIB_CB_ADAPTIVE_THRESH );

   // improve the found corners' coordinate accuracy
   view_gray = cvCreateImage( cvGetSize(rgb_image), 8, 1 );
   cvCvtColor( rgb_image, view_gray, CV_BGR2GRAY );

   cvFindCornerSubPix( view_gray, image_points_buf, count, cvSize(11,11),
            cvSize(-1,-1), cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));

   cvReleaseImage( &view_gray );

   if( found )
   {
      cvSeqPush( image_points_seq, image_points_buf );

      sprintf( imagename, "image%03d.png", image_points_seq->total - 1 );
      cvSaveImage( imagename, rgb_image );
   }

   cvDrawChessboardCorners( rgb_image, board_size, image_points_buf, count, found );

   return ((unsigned)image_points_seq->total >= (unsigned)image_count);
}

bool CybCamCalibration::tryCalibrate(){

   int code = 0;

   cvReleaseMat( &extr_params );
   cvReleaseMat( &reproj_errs );

   code = calibration( image_points_seq, img_size, board_size,
                square_size, aspect_ratio, flags, &camera, &dist_coeffs, &extr_params,
                &reproj_errs, &avg_reproj_err );

   return (code != 0);
}

void CybCamCalibration::printParams(){
   cout << "Calibration params" << endl;

   cout << "Intrisic matrix: " << endl;

   for(int i = 0; i < 3;i++){
      cout << "| ";
      for(int j = 0; j < 3; j++)
         cout << cvmGet(&camera,i,j) << " ";
      cout  << "| "<< endl;
   }

   cout << "Distortions coeficients" << endl;

   cout << "[ ";
   for(int i = 0; i < 4;i++)
       cout << cvmGet(&dist_coeffs,0,i) << " ";
   cout << " ]" << endl;

}

void CybCamCalibration::save_params(char *filename){

   FILE *fp = NULL;
   fp = fopen(filename, "wb");

   if(fp){
	fprintf(fp,"#Intrisic params\n");
	for(int i = 0; i < 3; i++)
		fprintf(fp, "%.4f   %.4f   %.4f\n", cvmGet(&camera, i, 0), cvmGet(&camera, i,1), cvmGet(&camera,i,2));
   	fprintf(fp, "#Lens Distortion\n");
	fprintf(fp, "%.4f %.4f %.4f %.4f\n", cvmGet(&dist_coeffs,0,0), cvmGet(&dist_coeffs, 0,1), cvmGet(&dist_coeffs, 0,2), cvmGet(&dist_coeffs, 0,3));
   }else{
      cout << "Prblems open file to write\nAbortin..." << endl;
      return ;
   }
   fclose(fp);

}



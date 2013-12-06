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

#include "cybHaarTracker.h"

CybHaarTracker::CybHaarTracker() {
	cams = NULL;
	frames = NULL;
	dbg_mode = false;
}

CybHaarTracker::~CybHaarTracker() {

	cams = CybCam::getInstance();

	this->stop();
	this->destroy();
	
    cams->stop();
    cams->destroy();
	
    delete cams;
	cvDestroyAllWindows();

	if (dbg_mode) {
		cvDestroyWindow("Debug Cam 1");
		cvDestroyWindow("Debug Cam 2");
	}

}

void CybHaarTracker::createTracker(void *cascade_name) {

	cascade = (CvHaarClassifierCascade*)cvLoad((char *)cascade_name, 0, 0, 0);
	storage = cvCreateMemStorage(0);
	cams = CybCam::getInstance();

	stereo = new CybStereo();

	cams->createCams(2);
	cams->init();

	cvNamedWindow("Calibration Wizard Left");
	cvNamedWindow("Calibration Wizard Rigth");

	if (dbg_mode) {
		cvNamedWindow("Debug Cam 1");
		cvNamedWindow("Debug Cam 2");
	}
}

void CybHaarTracker::getPosition(float *position) {
	
	position[0] = point3D[0];
	position[1] = point3D[1];
	position[2] = point3D[2];
}

CybRegionTrackInfo *CybHaarTracker::detect(IplImage *img) {

	double scale = 1.3;
	CybRegionTrackInfo *region= NULL;
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);
	IplImage* small_img = cvCreateImage(cvSize(cvRound(img->width/scale),
			cvRound(img->height/scale)), 8, 1);

	cvCvtColor(img, gray, CV_BGR2GRAY);
	cvResize(gray, small_img, CV_INTER_LINEAR);
	cvEqualizeHist(small_img, small_img);
	cvClearMemStorage(storage);

	if (cascade) {
		double t = (double)cvGetTickCount();
		CvSeq* faces = cvHaarDetectObjects(small_img, cascade, storage, 1.1, 2,
				0/*CV_HAAR_DO_CANNY_PRUNING*/, cvSize(30, 30) );
		t = (double)cvGetTickCount() - t;

		if (faces && (faces->total > 0)) {
			CvRect* r = (CvRect*)cvGetSeqElem(faces, 0);

			region = new CybRegionTrackInfo((int)((r->x)*scale),
					(int)((r->x + r->width)*scale),
					(int)((r->y)*scale),
					(int)((r->y + r->height)*scale));

			int meanx = (region->getMaxX() + region->getMinX())/2;
			int meany = (region->getMaxY() + region->getMinY())/2;

			if (dbg_mode) {
				cvLine(img, cvPoint(meanx, meany), cvPoint(meanx, meany), 
				CV_RGB(50, 50 , 50), 4, 8, 0);
				cvRectangle(img, cvPoint((int)(region->getMinX()),
						(int)(region->getMinY())), cvPoint(
						(int)(region->getMaxX()), (int) (region->getMaxY())), 
				CV_RGB(150, 150, 150), 2, 8, 0);

			}
		}

	}

	cvReleaseImage( &gray);
	cvReleaseImage( &small_img);

	return region;
}

void CybHaarTracker::run() {

	frames = cams->getImageListFromCams();

	if (frames) {

		if (stereo) {
			if (!stereo->calibrated()) {

				stereo->calibrate_cams(frames[0], frames[1]);

				if (stereo->calibrated()) {
					cvDestroyWindow("Calibration Wizard Left");
					cvDestroyWindow("Calibration Wizard Rigth");
				}

				cvShowImage("Calibration Wizard Left", frames[0]);
				cvShowImage("Calibration Wizard Rigth", frames[1]);

				/*if (!dbg_mode)
					if (cvWaitKey(10) >= 0) {
					}*/
			}
		} else
			cout << "Stereo not initialized" << endl;

		region1 = detect(frames[0]);
		if (dbg_mode)
			cvShowImage("Debug Cam 1", frames[0]);

		region2 = detect(frames[1]);
		if (dbg_mode) {
			cvShowImage("Debug Cam 2", frames[1]);

			if (cvWaitKey(10) >= 0) {
				cams->stop();
				cams->destroy();
				//delete cams;
				this->destroy();
				return;
			}
		}

		if (cvWaitKey(10) >= 0) {
		}

		if (stereo && region1 && region2) {
			stereo->get3Dposition(region1, region2, point3D);
		} else
			cout << "Stereo not initialized" << endl;

		cams->releaseImageList(frames);

		delete region1;
		delete region2;
	}

}

void CybHaarTracker::setDebug(bool dbg_mode) {
	this->dbg_mode = dbg_mode;
}

bool CybHaarTracker::getDebugStatus() {
	return dbg_mode;
}

void CybHaarTracker::getInitialPosition(float *position) {

	position[0] = 0;
	position[1] = 0;
	position[2] = 0;

}
void CybHaarTracker::getMatrix(float *matrix){
	matrix[0] = 1;
	for(int i = 0; i < 16 ; i++){
	 if((i+1)%4 == 0)
	  matrix[i] = 1;
	else
	  matrix[i] = 0;
	}
}

void CybHaarTracker::initDevice(){
  init();
}

void CybHaarTracker::stopDevice(){

}

CybStereo *CybHaarTracker::getStereoInstance() {

	return this->stereo;
}

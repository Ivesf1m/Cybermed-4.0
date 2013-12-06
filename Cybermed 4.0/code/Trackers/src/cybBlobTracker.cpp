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

#include "cybBlobTracker.h"

CybBlobTracker::CybBlobTracker() {

	dbg = false;
	filterArea = 0;
	frames = NULL;

	hue_top = 2;
	hue_down = 255;
	saturation_top = 255;
	saturation_down = 175;
	value_top = 255;
	value_down = 50;

	stereo = NULL;
	imgColorTracker1= NULL;
	imgColorTracker2= NULL;
	dst_1= NULL;
	dst_2= NULL;
	region1= NULL;
	region2= NULL;

}

CybBlobTracker::~CybBlobTracker() {

	this->stop();
	this->destroy();

	cams->stop();
	cams->destroy();

	delete cams;
	delete imgUtil;

	cvDestroyAllWindows();

}

void CybBlobTracker::getPosition(float *position) {

	position[0] = position3D[0];
	position[1] = position3D[1];
	position[2] = position3D[2];
}

void CybBlobTracker::createTracker(void *userData) {

	
	cams = CybCam::getInstance();
	
	//TODO: Criar método para configurar estes arquivos como na classe Haar
	stereo = new CybStereo("CalibrationTools/teste.txt", "CalibrationTools/teste2.txt");

	//Initialize cams
	cams->createCams(2);
	cams->init();

	cvNamedWindow("Calibration Wizard Left");
	cvNamedWindow("Calibration Wizard Rigth");

	if (dbg) {
		cvNamedWindow("Debug Left");
		cvNamedWindow("Debug Rigth");
	}

	imgUtil = new CybImageUtil();
}

void CybBlobTracker::run() {

	frames = cams->getImageListFromCams();

	if (frames) {

		if (stereo) {
			if (!stereo->calibrated()) {//OK

				dst_1 = cvCreateImage(cvSize(frames[0]->width*2,
						frames[0]->height *2), 8, 3);
				dst_2 = cvCreateImage(cvSize(frames[1]->width*2,
						frames[1]->height *2), 8, 3);

				cvPyrUp(frames[0], dst_1);
				cvPyrUp(frames[1], dst_2);

				stereo->calibrate_cams(dst_1, dst_2);

				cvShowImage("Calibration Wizard Left", dst_1);
				cvShowImage("Calibration Wizard Rigth", dst_2);

				cvReleaseImage(&dst_1);
				cvReleaseImage(&dst_2);

				if (stereo->calibrated()) {
					cvDestroyWindow("Calibration Wizard Left");
					cvDestroyWindow("Calibration Wizard Rigth");
				}

				if (cvWaitKey(10) >= 0) {
				}
			}
		} else
			cout << "Stereo not initialized" << endl;

		imgColorTracker1 = imgUtil->findHSVColor(frames[0], hue_top, hue_down,
				saturation_top, saturation_down, value_top, value_down);
		img1 = imgUtil->findCountor(imgColorTracker1);

		imgColorTracker2 = imgUtil->findHSVColor(frames[1], hue_top, hue_down,
				saturation_top, saturation_down, value_top, value_down);
		img2 = imgUtil->findCountor(imgColorTracker2);

		region1 = findRegion(img1);
		region2 = findRegion(img2);

		//TODO: Organizar esta bagunça aquiiii!

		if (dbg) {
			
			if (region1 && region2) {
				printf("\nBLOB INFO\n");
				int iMaxx, iMinx, iMaxy, iMiny, iMeanx, iMeany;

				//First blob

				iMaxx=region1->getMaxX();
				iMinx=region1->getMinX();
				iMaxy=region1->getMaxY();
				iMiny=region1->getMinY();

				// find the average of the blob (i.e. estimate its centre)
				iMeanx=(iMinx+iMaxx)/2;
				iMeany=(iMiny+iMaxy)/2;

				// mark centre
				cvLine(img1, cvPoint(iMeanx, iMeany), cvPoint(iMeanx, iMeany), 
				CV_RGB(50, 50 , 50), 4, 8, 0);
				// mark box around blob
				cvRectangle(img1, cvPoint(iMinx, iMiny), cvPoint(iMaxx, iMaxy), 
				CV_RGB(150, 150, 150), 2, 8, 0);

				// print the blob centres
				printf("\nBlob 1 -> X: %d, Y: %d\n", iMeanx, iMeany);

				//Segundo Blob
				iMaxx=region2->getMaxX();
				iMinx=region2->getMinX();
				iMaxy=region2->getMaxY();
				iMiny=region2->getMinY();

				// find the average of the blob (i.e. estimate its centre)
				iMeanx=(iMinx+iMaxx)/2;
				iMeany=(iMiny+iMaxy)/2;

				// mark centre
				cvLine(img2, cvPoint(iMeanx, iMeany), cvPoint(iMeanx, iMeany), 
				CV_RGB(50, 50 , 50), 4, 8, 0);
				// mark box around blob
				cvRectangle(img2, cvPoint(iMinx, iMiny), cvPoint(iMaxx, iMaxy), 
				CV_RGB(150, 150, 150), 2, 8, 0);

				// print the blob centres
				printf("\nBlob 2 -> X: %d, Y: %d\n", iMeanx, iMeany);
				printf("\nEND BLOB INFO\n");
			}
			cvShowImage("Debug Left", img1);
			cvShowImage("Debug Rigth", img2);

		}

		//We need two regions
		if (stereo && region1 && region2) {

			if (stereo->calibrated()) {
				CybThread::lock();
				stereo->get3Dposition(region1, region2, position3D);
				CybThread::unlock();
			} else
				cout
						<< "Cameras not calibrated, please use the chessboar image to calibrate"
						<< endl;

		} else {
			if (dbg)
				printf("There aren't valid blos!\n");
			position3D[0] = 0;
			position3D[1] = 0;
			position3D[2] = 0;
		}

		if (cvWaitKey(10) >= 0) {			
		}

	
		cams->releaseImageList(frames);
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
		cvReleaseImage(&imgColorTracker1);
		cvReleaseImage(&imgColorTracker2);

		delete region1;
		delete region2;
	}

}

/*Métodos para extração e escolha dos blobs*/

//Método que elimina os blobs das bordas da imagem
CBlobResult *CybBlobTracker::eliminateImageBlobs(CBlobResult *blobs,
		int imageWitdh, int imageHeigth) {

	CBlobResult *blobsResult = new CBlobResult();
	CBlob Blob;

	int maxx, minx, maxy, miny, meanx, meany;

	int imageMeanX = imageWitdh/2;
	int imageMeanY = imageHeigth/2;
	for (int i = 0; i < blobs->GetNumBlobs(); i++) {

		Blob = blobs->GetBlob(i);
		maxx=(int)Blob.MaxX();
		minx=(int)Blob.MinX();
		maxy=(int)Blob.MaxY();
		miny=(int)Blob.MinY();

		meanx=(minx+maxx)/2;
		meany=(miny+maxy)/2;

		if ((meanx != imageMeanX) || (meany != imageMeanY)) {
			blobsResult->AddBlob(&Blob);
		}
	}

	return blobsResult;
}

CBlob *CybBlobTracker::getBestBlobResult(CBlobResult *blobs, int imageWitdh,
		int imageHeigth) {

	CBlob Blob;
	CBlob *betterBlob;

	int maxx, minx, maxy, miny;

	float areaAtual = 0.0, areaAnterior = 0.0;

	for (int i = 0; i < blobs->GetNumBlobs(); i++) {

		maxx=(int)blobs->GetBlob(i)->MaxX();
		minx=(int)blobs->GetBlob(i)->MinX();
		maxy=(int)blobs->GetBlob(i)->MaxY();
		miny=(int)blobs->GetBlob(i)->MinY();

		areaAtual = (maxy - miny)*(maxx - minx);

		if (areaAtual < filterArea)
			continue;

		if (areaAtual > areaAnterior) {
			betterBlob = blobs->GetBlob(i);
			areaAnterior = areaAtual;
		}
	}
	return betterBlob;
}

CybRegionTrackInfo *CybBlobTracker::findRegion(IplImage *src) {

	CBlobResult *blobs, *results;
	CBlob *blob;

	//Retorna todos os blobs da imagem
	blobs = new CBlobResult(src, NULL, 200, true);

	if (blobs->GetNumBlobs() != 0) {
		//Elimina os blobs referentes ás bordas da imagem
		results = eliminateImageBlobs(blobs, src->width, src->height);

		if (results->GetNumBlobs() != 0) {
			//Escolhe de forma simplificada o melhor blob (Escolhe o maior)
			blob = getBestBlobResult(results, src->width, src->height);
			delete results;
			delete blobs;

			CybRegionTrackInfo *info = new CybRegionTrackInfo(blob);
			return info;
		} else {
			delete results;
			delete blobs;
			return NULL;
		}
	}

	delete blobs;
	return NULL;
}

double CybBlobTracker::getFilterAreaValue() {
	return filterArea;
}

void CybBlobTracker::setFilterAreaValue(double filterArea) {
	this->filterArea = filterArea;
}

void CybBlobTracker::setStepColorProperties(int hue_top, int hue_down,
		int saturation_top, int saturation_down, int value_top, int value_down) {

	this->hue_top = hue_top;
	this->hue_down = hue_down;
	this->saturation_top = saturation_top;
	this->saturation_down = saturation_down;
	this->value_top = value_top;
	this->value_down = value_down;

}

void CybBlobTracker::setDebug(bool dbg) {
	this->dbg = dbg;
}

bool CybBlobTracker::getDebug() {
	return this->dbg;
}

void CybBlobTracker::configColorTrack(int hue_top, int hue_down,
		int saturation_top, int saturation_down, int value_top, int value_down) {

	this->hue_top = hue_top;
	this->hue_down = hue_down;
	this->saturation_top = saturation_top;
	this->saturation_down = saturation_down;
	this->value_top = value_top;
	this->value_down = value_down;
}

void CybBlobTracker::getInitialPosition(float *position) {

	position[0] = 0;
	position[1] = 0;
	position[2] = 0;

}

void CybBlobTracker::getMatrix(float *matrix){
	matrix[0] = 1;
	for(int i = 0; i < 16 ; i++){
	 if((i+1)%4 == 0)
	  matrix[i] = 1;
	else
	  matrix[i] = 0;
	}
}

void CybBlobTracker::initDevice(){
  init();
}

void CybBlobTracker::stopDevice(){

}

CybStereo *CybBlobTracker::getStereoInstance() {
	return this->stereo;
}

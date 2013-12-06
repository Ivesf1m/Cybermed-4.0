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

#include "cybCam.h"

CybCam *CybCam::camInstance= NULL;

CybCam::CybCam() {
	retrieveError = false;
	imageAvaiable = false;
	captureTime = 10;
}

CybCam::~CybCam() {

	//TODO: Está ocorrendo um error ao chamar o método releaseImageList
	cout << "Invoking ~CybCam() "<< endl;
	
	//Wait 1 sec to dealoc cameras
	CybThread::sleep(1000);
	stopCams();
}

void CybCam::createCams(int numOfCam = 1) {

	if (dbug)
		cout << "Entrando no método create da classe CybCam" << endl;
	this->numOfCam = numOfCam;

	captureList = new CvCapture* [this->numOfCam];
	camImageList = new IplImage* [this->numOfCam];

	for (int i = 0; i < this->numOfCam; i++) {
		captureList[i] = cvCaptureFromCAM(i);
	}

	if (dbug)
		cout << "Saindo do método create..." << endl;

}

void CybCam::createCam(int camera_index = 0) {

	this->numOfCam = 1;
	if (dbug)
		cout << "Entrando no método create da classe CybCam" << endl;
	this->numOfCam = numOfCam;

	captureList = new CvCapture* [this->numOfCam];
	camImageList = new IplImage* [this->numOfCam];

	captureList[0] = cvCaptureFromCAM(camera_index);

	if (dbug)
		cout << "Saindo do método create..." << endl;

}

IplImage **CybCam::getImageListFromCams() {

	if (dbug)
		cout << "Requisitando lista de imagens" << endl;

	if (!imageAvaiable) {
		if (dbug)
			cout << "Imagens ainda não estão acessíveis" << endl;
		return NULL;
	}
	return copyImageList();
}

void CybCam::run() {

	if (dbug)
		cout << "Iniciando thread de captura de imagens" << endl;

	for (;;) {

		CybThread::sleep(captureTime);

		CybThread::lock();
		for (int i = 0; i < numOfCam; i++) {
			if (!cvGrabFrame(captureList[i])) {
				cerr << "CybCam Error: Couldn't grab the image from camera "
						<< i << endl;
				retrieveError = true;
				break;
			}
		}
		
		CybThread::unlock();

		if (retrieveError) {
			cerr << "Stopping thread capture ... " << endl;
			break;
		}

		CybThread::lock();

		for (int i = 0; i < numOfCam; i++) {
			camImageList[i] = cvRetrieveFrame(captureList[i]);
		}

		CybThread::unlock();
		imageAvaiable = true;

	}

	stopCams();
	releaseImageList(camImageList);
	destroy();

	if (dbug)
		cout << "Saindo da thread de captura de imagens..." << endl;

}

IplImage **CybCam::copyImageList() {

	if (dbug)
		cout << "Copiando imagens" << endl;
	IplImage **copyList = new IplImage*[numOfCam];

	CybThread::lock();

	for (int i=0; i < numOfCam; i++)
		copyList[i] = cvCreateImage(cvSize(camImageList[i]->width,
				camImageList[i]->height), 8, 3);

	for (int i =0; i < numOfCam; i++)
		cvCopy(camImageList[i], copyList[i]);

	CybThread::unlock();

	if (dbug)
		cout << "Cópia feita com sucesso" << endl;
	return copyList;
}

void CybCam::releaseImageList(IplImage **list) {

	if (dbug)
		cout << "Relesing images ..." << endl;

	if (list) {

		for (int i = 0; i < numOfCam; i++)
			cvReleaseImage(&list[i]);
	}
	if (dbug)
		cout << "Relesase OK!" << endl;
}

void CybCam::stopCams() {

	if (dbug)
		cout << "Parando cameras" << endl;

	CybThread::lock();
	for (int i = 0; i < numOfCam; i++) {
		if (captureList[i])
			cvReleaseCapture( &captureList[i]);
	}
	CybThread::unlock();

	if (dbug)
		cout << "Câmeras paradas ... " << endl;
}

double CybCam::getCamProperty(int camID, int cv_property_id) {
	return cvGetCaptureProperty(captureList[camID], cv_property_id);
}

bool CybCam::setCamProperty(int camID, int cv_property_id, double value) {

	if (cvSetCaptureProperty(captureList[camID], cv_property_id, value) >= 0)
		return true;
	return false;
}

void CybCam::setTimeToCapture(int freq) {
	captureTime = freq;
}

int CybCam::getTimeToCapture() {
	return captureTime;
}

int CybCam::getNumOfCams() {
	return numOfCam;
}

void CybCam::setDebug(bool dbug) {
	this->dbug = dbug;
}


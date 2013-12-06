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

#include "cybStereo.h"

CybStereo::CybStereo(char *params_cam1, char *params_cam2) {

	double intrinsics[3][3];
	double distortion[4];

	getParams(params_cam1, intrinsics, distortion);
	parseCalibartionValues(&camera_intrinsics[0], intrinsics, distortion);

	getParams(params_cam2, intrinsics, distortion);
	parseCalibartionValues(&camera_intrinsics[1], intrinsics, distortion);

	this->etalon_width = 9;
	this->etalon_height = 6;
	this->square_size = 3;

	debug = false;
	isCalibrated = false;
}

CybStereo::CybStereo() {

	this->etalon_width = 9;
	this->etalon_height = 6;
	this->square_size = 3;

	debug = false;
	isCalibrated = false;
}

CybStereo::CybStereo(double intrisic_matrix_1[3][3],
		double intrisic_matrix_2[3][3], double distortion_1[4],
		double distortion_2[4]) {

	parseCalibartionValues(&camera_intrinsics[0], intrisic_matrix_1,
			distortion_1);
	parseCalibartionValues(&camera_intrinsics[1], intrisic_matrix_2,
			distortion_2);

	this->etalon_width = 9;
	this->etalon_height = 6;
	this->square_size = 3;

	debug = false;
	isCalibrated = false;

}

CybStereo::~CybStereo() {

}

void CybStereo::getParams(char *file_name, double intrisics_params[3][3],
		double distotion[4]) {
	string word;
	ifstream *in = new ifstream(file_name);

	*in >> word;
	cout << word << " ";

	*in >> word;
	cout << word;
	cout << endl;

	for (int i = 0; i < 3; i++)
		*in >> intrisics_params[i][0] >> intrisics_params[i][1]
				>> intrisics_params[i][2];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << " "<< intrisics_params[i][j];
		cout << endl;
	}

	*in >> word;
	cout << word << " ";

	*in >> word;
	cout << word;
	cout << endl;

	*in >> distotion[0] >> distotion[1] >> distotion[2] >> distotion[3];
	in->close();

	for (int i = 0; i < 4; i++)
		cout << " "<< distotion[i];

	cout << endl;
}

void CybStereo::parseCalibartionValues(Cv3dTrackerCameraIntrinsics *in,
		double matrix_intrinsic[3][3], double distortion[4]) {
	in->principal_point.x = (float)matrix_intrinsic[0][2];
	in->principal_point.y = (float)matrix_intrinsic[1][2];
	in->focal_length[0] = matrix_intrinsic[0][0];
	in->focal_length[1] = matrix_intrinsic[1][1];

	for (int i = 0; i < 4; i++)
		in->distortion[i] = (float)distortion[i];
}

/*Calibrate cameras for stereo reconstruction. Obs: The defaults values for etalon and square size 
 * are choosed to run calibration using the chessboard image include in cybermed package.
 */
void CybStereo::calibrate_cams(IplImage *letf_img, IplImage *rigth_img) {

	IplImage *samples[2] = { letf_img, rigth_img };

	if (!isCalibrated) {
		cout << "Not Calibrated yet!" << endl;
		if (cv3dTrackerCalibrateCameras(2, camera_intrinsics, cvSize(
				etalon_width, etalon_height), square_size, samples, camera_info)) {
			isCalibrated = true;
			cout << "Calibration performed ..." << endl;
		}
	}
}

bool CybStereo::calibrated() {
	return isCalibrated;
}

void CybStereo::decalibrate() {
	isCalibrated = false;
}

void CybStereo::get3Dposition(CybRegionTrackInfo *left_cam,
		CybRegionTrackInfo *right_cam, double point[3]) {

	if (isCalibrated) {
		Cv3dTracker2dTrackedObject objects[2];
		Cv3dTrackerTrackedObject objects_tracked;

		objects[0].id = 0; //top left
		objects[0].p.x = (left_cam->getMinX() + left_cam->getMaxX())/2;
		objects[0].p.y = (left_cam->getMinY() + left_cam->getMaxY())/2;

		objects[1].id = 0;
		objects[1].p.x = (right_cam->getMinX() + right_cam->getMaxX())/2;
		objects[1].p.y = (right_cam->getMinY() + right_cam->getMaxY())/2;

		if (debug) {
			cout << "Regions tracked " << endl;

			cout << "Info: " << objects[0].p.x << " " << objects[0].p.y << endl;
			cout << "Info: " << objects[1].p.x << " " << objects[0].p.y << endl;
		}

		cv3dTrackerLocateObjects(2, 1, camera_info,
				(Cv3dTracker2dTrackedObject *)objects, &objects_tracked);

		if (debug) {
			cout << "Pontos rastreados" << endl;

			cout << "Value: " << objects_tracked.id << " Ponto: "
					<< objects_tracked.p.x << " " << objects_tracked.p.y
					<< " " << objects_tracked.p.z << endl;
		}
		
		point[0] = objects_tracked.p.x;
		point[1] = objects_tracked.p.y;
		point[2] = objects_tracked.p.z;

	} else
		cout << "Impossible acquire 3D point, not calibrated" << endl;

}

void CybStereo::stereo_config(int etalon_width, int etalon_height,
		int square_size) {

	this->etalon_width = etalon_width;
	this->etalon_height = etalon_height;
	this->square_size = square_size;

}

void CybStereo::camera_params(char *cam_left, char *cam_rigth) {

	double intrinsics[3][3];
	double distortion[4];

	getParams(cam_left, intrinsics, distortion);
	parseCalibartionValues(&camera_intrinsics[0], intrinsics, distortion);

	getParams(cam_rigth, intrinsics, distortion);
	parseCalibartionValues(&camera_intrinsics[1], intrinsics, distortion);
}

void CybStereo::camera_params(double intrisic_matrix_1[3][3],
		double intrisic_matrix_2[3][3], double distortion_1[4],
		double distortion_2[4]) {

	parseCalibartionValues(&camera_intrinsics[0], intrisic_matrix_1,
			distortion_1);
	parseCalibartionValues(&camera_intrinsics[1], intrisic_matrix_2,
			distortion_2);
}

void CybStereo::setDebug(bool debug){
	this->debug = debug;
}

bool CybStereo::getDebugStatus(){
	return this->debug;
}

// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "cyb5DTGlove.h"

using namespace std;

Cyb5DTGlove::Cyb5DTGlove() {
	#ifdef __linux__
		port = "/dev/usb/hiddev0";
	#elif defined WIN32	
		port = "usb0";
	#else
		port = "";
	#endif
}

Cyb5DTGlove::Cyb5DTGlove(string port) {	
	this->port = port;
}

Cyb5DTGlove::~Cyb5DTGlove() {
	stopDevice();
}

//------------------------------
string Cyb5DTGlove::getGloveName() {
	string szType = " ";
	int glovetype = fdGetGloveType(glove);
	switch (glovetype) {
		case FD_GLOVENONE:    szType = "None"; break;
		case FD_GLOVE5U:      szType = "Data Glove 5 Ultra"; break;
		case FD_GLOVE5UW:     szType = "Data Glove 5 Ultra W"; break;
		case FD_GLOVE5U_USB:  szType = "Data Glove 5 Ultra USB"; break;
		case FD_GLOVE7:       szType = "Data Glove 5"; break;
		case FD_GLOVE7W:      szType = "Data Glove 5W"; break;
		case FD_GLOVE16:      szType = "Data Glove 16"; break;
		case FD_GLOVE16W:     szType = "Data Glove 16W"; break;
		case FD_GLOVE14U:     szType = "DG14 Ultra serial"; break;
		case FD_GLOVE14UW:    szType = "DG14 Ultra W"; break;
		case FD_GLOVE14U_USB: szType = "DG14 Ultra USB"; break;
	}
	return szType;
}

//-----------------------------
void Cyb5DTGlove::initDevice() {
	cout << "Attempting to open glove on " << port << endl; 
	
	glove = fdOpen(const_cast<char *>(port.c_str()));
	
	if (glove == NULL) {
		cout << "failed!" << endl;				
	}	
	cout << "succeeded!" << endl;
}

void Cyb5DTGlove::stopDevice() {
	if (glove != NULL) {
		fdClose(glove);
		glove = NULL;	
	}
		
}

//-----------------------------
int Cyb5DTGlove::getGloveHand() {
	return fdGetGloveHand(glove);
}

int Cyb5DTGlove::getGloveType() {
	return fdGetGloveType(glove);
}

int Cyb5DTGlove::getNumSensors() {
	return fdGetNumSensors(glove);
}

//-----------------------------
void Cyb5DTGlove::getSensorRawAll(unsigned short *data) {
	fdGetSensorRawAll(glove, data);
}

unsigned short Cyb5DTGlove::getSensorRaw(int sensor) {
	return fdGetSensorRaw(glove, sensor);
}

void Cyb5DTGlove::setSensorRawAll(unsigned short *data) {
	fdSetSensorRawAll(glove, data);
}

void Cyb5DTGlove::setSensorRaw(int sensor, unsigned short raw) {
	fdSetSensorRaw(glove, sensor, raw);
}

//------------------------------
void Cyb5DTGlove::getSensorScaledAll(float *data) {
	fdGetSensorScaledAll(glove, data);
}

float Cyb5DTGlove::getSensorScaled(int sensor) {
	return fdGetSensorScaled(glove, sensor);
}

//-------------------------------
int Cyb5DTGlove::getNumGestures() {
	return fdGetNumGestures(glove);
}

int Cyb5DTGlove::getGesture() {
	return fdGetGesture(glove);
}

//-------------------------------
void Cyb5DTGlove::getCalibrationAll(unsigned short *pUpper, unsigned short *pLower) {
	fdGetCalibrationAll(glove, pUpper, pLower);
}

void Cyb5DTGlove::getCalibration(int sensor, unsigned short *pUpper, unsigned short *pLower) {
	fdGetCalibration(glove, sensor, pUpper, pLower);
}

void Cyb5DTGlove::setCalibrationAll(unsigned short *pUpper, unsigned short *pLower) {
	fdSetCalibrationAll(glove, pUpper, pLower);
}

void Cyb5DTGlove::setCalibration(int sensor, unsigned short nUpper, unsigned short nLower) {
	fdSetCalibration(glove, sensor, nUpper, nLower);
}

void Cyb5DTGlove::resetCalibration(int sensor) {
	fdResetCalibration(glove, sensor);
}

void Cyb5DTGlove::resetCalibration() {
	#ifdef __linux__
		fdResetCalibration(glove);
	#elif defined WIN32	
		fdResetCalibrationAll(glove);
	#else
		fdResetCalibrationAll(glove);
	#endif

}

//----------------------------------
void Cyb5DTGlove::getSensorMaxAll(float *pMax) {
	fdGetSensorMaxAll(glove, pMax);
}

float Cyb5DTGlove::getSensorMax(int sensor) {
	return fdGetSensorMax(glove, sensor);
}

void Cyb5DTGlove::setSensorMaxAll(float *pMax) {
	fdSetSensorMaxAll(glove, pMax);
}

void Cyb5DTGlove::setSensorMax(int sensor, float fMax) {
	fdSetSensorMax(glove, sensor, fMax);
}

//-----------------------------------
void Cyb5DTGlove::getThresholdAll(float *pUpper, float *pLower) {
	fdGetThresholdAll(glove, pUpper, pLower);
}

void Cyb5DTGlove::getThreshold(int sensor, float *pUpper, float *pLower) {
	fdGetThreshold(glove, sensor, pUpper, pLower);
}

void Cyb5DTGlove::setThresholdAll(float *pUpper, float *pLower) {
	fdSetThresholdAll(glove, pUpper, pLower);
}

void Cyb5DTGlove::setThreshold(int sensor, float pUpper, float pLower) {
	fdSetThreshold(glove, sensor, pUpper, pLower);
}

//------------------------------------
void Cyb5DTGlove::getGloveInfo(unsigned char *data) {
	fdGetGloveInfo(glove, data);
}

string Cyb5DTGlove::getDriverInfo() {
	unsigned char cInfo[32];
	char temp[32];	
	fdGetDriverInfo(glove, cInfo);
	sprintf(temp, "%s", cInfo);
	string sInfo(temp);
	return sInfo;	
}

void Cyb5DTGlove::setCallback(void (*func)()) {
	fdSetCallback(glove, reinterpret_cast<void*>(func), static_cast<void*>(glove));
}

int Cyb5DTGlove::getPacketRate() {
	return fdGetPacketRate(glove);	
}

bool Cyb5DTGlove::newData() {
	return fdNewData(glove);	
}

int Cyb5DTGlove::getFWVersionMajor() {
	return fdGetFWVersionMajor(glove);
}

int Cyb5DTGlove::getFWVersionMinor() {
	return fdGetFWVersionMinor(glove);
}

//--------------------------------------
bool Cyb5DTGlove::getAutoCalibrate() {
	return fdGetAutoCalibrate(glove);
}

bool Cyb5DTGlove::setAutoCalibrate(bool bAutoCalibrate) {
	return fdSetAutoCalibrate(glove, bAutoCalibrate);
}

bool Cyb5DTGlove::saveCalibration(string fileName) {
	return fdSaveCalibration(glove, fileName.c_str());
}

bool Cyb5DTGlove::loadCalibration(string fileName) {
	return fdLoadCalibration(glove, fileName.c_str());
}

//---------------------------------------------
int Cyb5DTGlove::scanUSB(unsigned short *aPID, int &NumMax) {
	return fdScanUSB(aPID, NumMax);
}







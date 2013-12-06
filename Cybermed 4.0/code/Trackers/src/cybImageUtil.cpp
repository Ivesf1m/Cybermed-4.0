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

#include "cybImageUtil.h"

CybImageUtil::CybImageUtil() {

}

CybImageUtil::~CybImageUtil() {
}

IplImage *CybImageUtil::findRGBColor(IplImage * src, int r_top, int r_down,
		int g_top, int g_down, int b_top, int b_down) {

	CvScalar s;
	CvScalar thresholdColor;

	IplImage *result = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);

	for (int i =0; i < src->width; i++) {
		for (int j =0; j < src->height; j++) {
			s=cvGet2D(src, j, i);
			if ((s.val[2] <= (float)r_top && s.val[2] >= (float)r_down)
					&&((s.val[1] <= (float)g_top)
							&& (s.val[1] >= (float)g_down)) && (s.val[0]
					<= (float)b_top && (s.val[0] >= (float)b_down))) {

				thresholdColor.val[0] = thresholdColor.val[1]
						= thresholdColor.val[2] = 255;
				cvSet2D(result, j, i, thresholdColor);

			} else {
				thresholdColor.val[0] = thresholdColor.val[1]
						= thresholdColor.val[2] = 0;
				cvSet2D(result, j, i, thresholdColor);

			}
		}
	}

	return result;

}

IplImage *CybImageUtil::findHSVColor(IplImage * src, int hue_top, int hue_down,
		int saturation_top, int saturation_down, int value_top, int value_down) {

	CvScalar s;
	CvScalar thresholdColor;
	IplImage *image_tmp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
	IplImage *result = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);

	cvCvtColor(src, image_tmp, CV_BGR2HSV);

	if (hue_top >= hue_down) {

		for (int i =0; i < image_tmp->height; i++) {
			for (int j =0; j < image_tmp->width; j++) {

				s=cvGet2D(image_tmp, i, j);
				if ((s.val[0]*2 <= (float)hue_top && s.val[0]*2
						>= (float)hue_down) &&((s.val[1]
						<= (float)saturation_top) && (s.val[1]
						>= (float)saturation_down)) && (s.val[2]
						<= (float)value_top && (s.val[2] >= (float)value_down))) {

					thresholdColor.val[0] = thresholdColor.val[1]
							= thresholdColor.val[2] = 255;

					s = cvGet2D(src, i, j);
					cvSet2D(result, i, j, thresholdColor);

				} else {
					thresholdColor.val[0] = thresholdColor.val[1]
							= thresholdColor.val[2] = 0;
					cvSet2D(result, i, j, thresholdColor);

				}
			}
		}
	} else {

		for (int i =0; i < image_tmp->height; i++) {
			for (int j =0; j < image_tmp->width; j++) {

				s=cvGet2D(image_tmp, i, j);

				if ((s.val[0]*2 <= (float)hue_top || s.val[0]*2
						>= (float)hue_down) &&((s.val[1]
						<= (float)saturation_top) && (s.val[1]
						>= (float)saturation_down)) && (s.val[2]
						<= (float)value_top && (s.val[2] >= (float)value_down))) {

					thresholdColor.val[0] = thresholdColor.val[1]
							= thresholdColor.val[2] = 255;

					s = cvGet2D(src, i, j);
					cvSet2D(result, i, j, thresholdColor);

				} else {
					thresholdColor.val[0] = thresholdColor.val[1]
							= thresholdColor.val[2] = 0;
					cvSet2D(result, i, j, thresholdColor);

				}

			}
		}
	}
	cvReleaseImage(&image_tmp);
	return result;

}


IplImage *CybImageUtil::findCountor(IplImage *src){
	
	IplImage *cannyResult = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	cvCanny(src, cannyResult, 0.5, 0.5, 5);
	
	return cannyResult;
}

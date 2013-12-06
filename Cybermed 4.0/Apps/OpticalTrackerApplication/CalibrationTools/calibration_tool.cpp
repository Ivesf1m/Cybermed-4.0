#include <iostream>
#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <CybCamCalibration.h>
#include <CybCam.h>

using namespace std;

void usage() {
	cout << "Usage: ./calib <cam_index> <output_file>" << endl;
}

int main(int argc, char **argv) {

	if (argc < 3) {
		usage();
		cout << "Invalid number of args!\nAborting..." << endl;
		return -1;
	}


	CybCam *cam = CybCam::getInstance();
	int camera_id = atoi(argv[1]);

	cam->createCam(camera_id);

	IplImage **frames;
	IplImage *dst = cvCreateImage(cvSize(320,240), 8, 3);
	bool findAllData = false;

	cam->setCamProperty(0, CV_CAP_PROP_FRAME_WIDTH, 160.0);
	cam->setCamProperty(0, CV_CAP_PROP_FRAME_HEIGHT, 120.0);

	cvNamedWindow("Calibration Wizard", CV_WINDOW_AUTOSIZE);

	CybCamCalibration *calibration = new CybCamCalibration(9,6);
	
	cam->setTimeToCapture(10);
	cam->init();
	
	for (;;) {

		frames = cam->getImageListFromCams();
		if (frames) {
			
			if (frames[0]){
			   cvPyrUp(frames[0], dst);	
			   findAllData = calibration->generateDataToCalibration(dst);

			}

			cvShowImage("Calibration Wizard", dst);

			if (cvWaitKey(10) >= 0) {
				break;
			}

			if (findAllData)
				break;
		}
		
	}

	if (findAllData) {
		if (calibration->tryCalibrate() == true) {
			cout << "Calibration performed" << endl;
		} else
			cout << "Could not calibrate! \nAborting..." << endl;

	} else
		cout << "Could not calibrate! \nAborting..." << endl;

	cvDestroyWindow("Calibration Wizard");
 
	cam->stopCams();
	
	calibration->printParams();
	calibration->save_params(argv[2]);
	cvReleaseImage(&dst);
	return 0;
}

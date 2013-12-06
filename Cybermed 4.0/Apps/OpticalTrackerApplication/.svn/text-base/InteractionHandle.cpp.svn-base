#include "InteractionHandle.h"

InteractionHandle::InteractionHandle(CybHaarTracker *tracker, CybParameters *core)
{
	this->tracker = tracker;
	this->core = core;
}

InteractionHandle::~InteractionHandle()
{
}

void InteractionHandle::initialize(){
	
	tracker = new CybHaarTracker();
	tracker->setDebug(true);

	//First create tracker
	tracker->createTracker((void *)"haardata/haarcascade_frontalface_alt.xml");
	tracker->getStereoInstance()->setDebug(false);
	
	//Set stereo params
	tracker->getStereoInstance()->camera_params("haardata/teste.txt",
			"haardata/teste2.txt");
	
	tracker->init();
}

void InteractionHandle::run(){
	
	CybThread::sleep(100);
	float position[3];
	
	tracker->getPosition(position);
	core->setLayerTranslation(0, position[0], position[1], position[2]);
	
	cout << "Position: " << position[0] << " " << position[1] << " " << position[2] << endl;
	
}

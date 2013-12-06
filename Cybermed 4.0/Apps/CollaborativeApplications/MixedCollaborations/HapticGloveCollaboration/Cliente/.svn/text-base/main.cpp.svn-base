#include <cybermed/cybMagneticTracker.h>
#include <cybermed/cybCore.h>
#include <cybermed/cybFOB6DOFTracker.h>
#include <cybermed/cybInteratorFactory.h>
#include "cybHandModel.h"
#include "myViewMono.h"
#include <cybermed/cyb5DTGlove.h>
#include <GL/glut.h>
#include <fob/fob.h>

int main() {
	int scale_model = 1;
	int numLayer = 1;
	int numInterator = 2;
	CybModel *handModel = new CybHandModel(); 
	CybModel *handModel2 = new CybHandModel();
	
	CybDataObtainer<cybTraits> data(numLayer,numInterator);

	MyViewMono view;
	
	CybParameters *cybCore = CybParameters::getInstance();
	
	//Glove Configuration 1------------------------------------------
	CybInterator* glove = CybInteratorFactory::getInterator(GLOVE_5DT_INTERATOR);
	if (glove == NULL) {
		cout << "Luva não instanciada!" << endl;
		return 1;
	}
	glove->create(0);
	data.loadInteratorModel(0, handModel);
	glove->setScale(0.8, 0.8, 0.8);
	glove->setTranslation(-25, 0, 0);
	glove->setRotation(0, 0, 180);
	//--------------------------------------------------------------
	
	
	//Glove Configuration 2------------------------------------------
	CybInterator* glove2 = CybInteratorFactory::getInterator(GLOVE_5DT_INTERATOR);
	if (glove2 == NULL) {
		cout << "Luva não instanciada!" << endl;
		return 1;
	}
	
	Cyb5DTGlove *glove5dt = dynamic_cast<Cyb5DTGlove *>(glove2->getDevice());
	glove5dt->setPort("/dev/usb/hiddev1");
	
	glove2->create(1);
	data.loadInteratorModel(1, handModel2);
	glove2->setScale(0.8, 0.8, 0.8);
	glove2->setTranslation(25, 0, 0);
	glove2->setRotation(0, 0, 180);
	//--------------------------------------------------------------	
	
	
	

	/*//Tracker Configuration -----------------------------------------
	CybInterator *interator = CybInteratorFactory::getInterator(TRACKER_MAGNETIC_INTERATOR);
	
	interator->create(1);	
	
	data.startInterator(1, 0);
	interator->setColor(1, 1, 0.7, 0.9);
		
	((CybFOB6DOFTracker*) interator->getDevice())->createTracker(NULL);
	interator->setScale(scale_model,scale_model,scale_model);
	//---------------------------------------------------------------*/
	data.startParameters(numLayer);
	
	cybCore->setColor(0,1,1,0.7,0.9);
	
	view.setWindowName("2 Gloves");
	
	
	view.init();
	
}


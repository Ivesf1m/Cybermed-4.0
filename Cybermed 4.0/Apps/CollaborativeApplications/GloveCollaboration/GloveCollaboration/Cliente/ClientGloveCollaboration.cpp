/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybGloveCollaboration.h>

#include <cybermed/cybGlove.h>
#include <cybermed/cybModel.h>
#include "cybHandModel.h"
#include "cybHandModel_Remote.h"
#include "myViewMono.h" //Define keyboard functions
#include <cybermed/cybRemoteModelFactory.h>

#define HANDMODEL_REMOTE 0

using namespace std;

class MyFactory : public CybRemoteModelFactory {
	public:
		CybRemoteModel *getModel(int id) {			
			return new CybRemoteModel(new CybHandModel_Remote());
		}
};

int main(int argc, char** argv) {

	if(argc != 2){
		cout << "Error: Invalid number of arguments!" << endl;
		cout << "Please, place collaboration creator ip address." << endl;
		cout << "Stopping app..." << endl;
		return -1;
	}

	CybGloveCollaboration* cybCollaboration = new CybGloveCollaboration(5000, UNICAST_UDP);
	cybCollaboration->setPortName("/dev/usb/hiddev0");

	int numLayer = 1;
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer,numInterator);

	MyViewMono view;
	
	CybParameters *cybCore = CybParameters::getInstance();
	
	cybCollaboration->setDataObtainer(&data);
	cybCollaboration->setModelFactory(new MyFactory());
	cybCollaboration->joinCollab(string("Test"),  HANDMODEL_REMOTE, argv[1], 5001);	

	//Access the parameters information of scene and graphical objects

	data.loadInteratorModel(0, new CybHandModel());
	
	
	//Glove Initialization
	CybInterator* glove = (CybInterator*) cybCollaboration->getInterator();
	if (glove == NULL) {
		cout << "Interator is null" << endl;
		return 1;
	}
	
	glove->setScale(0.8, 0.8, 0.8);
	glove->setTranslation(25, 0, 0);
	glove->setRotation(0, 0, 180);

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);
	

	//Set the window name
	view.setWindowName("Simple Visualization");
	
	
	/*Initialize visualization*/
	view.init();

}




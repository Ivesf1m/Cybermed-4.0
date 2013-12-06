/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybHapticCollaboration.h>
#include <cybermed/cybHapticAssistedCollab.h>

#include "../../../InteratorModelFactory.h"

class TrafficMonitor : public CybThread {

private: CybCollaboration *collab;
	 int collectTime; 	
	 int time;

public:	TrafficMonitor(CybCollaboration *collab, int collectTime) {		
		this->collab = collab;
		this->collectTime = collectTime;
		time = 0;
	}

	void run() {
		this->setTime(1000);			
		cout << time << endl;

		if (time > collectTime) {
			collab->getCollaborationPerformance()->reportPerformance();
			delete collab;	
		}		
		time++;
	}	
};

int main(int argc, char** argv) {

	if(argc != 2){
		cout << "Error: Invalid number of arguments!" << endl;
		cout << "Please, place collaboration creator ip address." << endl;
		cout << "Stopping app..." << endl;
		return -1;
	}

	CybHapticCollaboration* cybCollaboration = new CybHapticCollaboration(5001, MULTICAST, "224.0.0.1");
	//CybHapticCollaboration* cybCollaboration = new CybHapticCollaboration(5000, UNICAST_UDP);
	TrafficMonitor *traffic = new TrafficMonitor(cybCollaboration, 20);
	//traffic->init();
		
	char *fileName = "esfera.wrl";
	
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);// Transfer the OF data to CybParameters structure

	cybCollaboration->setDataObtainer(&data);

	CybViewMono view;

	cout << "ViewMono Created" << endl;

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	cybCollaboration->setModelFactory(new InteratorModelFactory());
	
	cybCollaboration->joinCollab("Bruno", InteratorModelFactory::NEDDLE , argv[1], 5001);
	cout << "JOIN REQUESTED" << endl;
	
	data.loadInteratorModel(0, 0, "agulha_unida2.wrl");
	data.startInterator(0, 0);

	CybInterator* interator = cybCollaboration->getInterator();
	CybOpenHPhantom* phantom = (CybOpenHPhantom*)interator->getDevice();
	phantom->createHapticLayers(1, true);

	interator->setColor(1, 0, 0, 1);

	/*Load the model from VRML file (layerID, fileName)*/
	//data.loadModel(0, fileName);	
	sMesh *mesh = new sMesh[numLayer];
	mfReaderModel<cybSurfaceTriTraits> in;
	in.read(&mesh[0], fileName);
	data.readColor(fileName, 0);
	data.loadModel(mesh);
	
	cout << "loadModel()" << endl;


	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);
	cout << "startParameters()" << endl;

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);

	//Set the window name
	view.setWindowName("Simple Visualization");
	cout << "setWindowName()" << endl;


	/*Initialize visualization*/
	view.init();

}






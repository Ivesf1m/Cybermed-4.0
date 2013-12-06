#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>

#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include "InteractionHandle.h"

int main(int argc, char** argv)
{ 
	char *fileName = "monkey.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 0;

	CybDataObtainer<cybTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure
	
	CybViewMono view;
	
	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();
	
	/*Load the model from VRML file (layerID, fileName)*/
	data.loadModel(0, fileName);
	
	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	cybCore->setKeyboardOff();
	
	
	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,0.9);
	
	//Set the window name
	view.setWindowName("Simple Visualization");
	
	CybHaarTracker *blob;
	CybCam *cams = CybCam::getInstance();
	InteractionHandle *handle = new InteractionHandle(blob, cybCore);
	handle->initialize();
	cams->setDebug(false);
	
	handle->init();
	
	/*Initialize visualization*/
	view.init();
	
}

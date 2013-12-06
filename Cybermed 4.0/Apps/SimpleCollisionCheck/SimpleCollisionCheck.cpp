#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybSphereTriangle.h>
//#include <cybermed/cybInteratorFactory.h>
#include<cybermed/cybMouseInterator.h>
#include "collisionCheck.h"
#include <cybermed/mf/mfVtkReader.h>


int main(int argc, char** argv)
{
	char *fileName = "monkey.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure
	CybViewMono view;			// Monoscopic Visualization
	
	//CybInterator* interator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);
	CybInterator* interator = CybMouseInterator::getInterator();

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();
	
	/*Load the model from VRML file (layerID, fileName)*/
	//data.loadModel(0, fileName);
	
	// =============
	/* Read Mesh File */
	mfReaderModel<cybSurfaceTriTraits> in;
	sMesh *mesh = new sMesh[numLayer];
	in.read(&mesh[0], fileName);
	data.loadModel(mesh);
	//===========

	data.loadInteratorModel(0, 0, "esfera.wrl");

	data.startInterator(0,0);	
	interator->setColor(0, 1, 0, 1);

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);
	
	//Set the object color (layerID, r, g, b,a)

	cybCore->setColor(0,1,1,0.7,1);
	//cybCore->setLayerScale(0, 50, 50, 50);
	
	//Set the window name
	view.setWindowName("Simple Collison Check");
	
	//Create a materrial property context, use by collision, haptics and deformation
	cybCore->createMaterialPropertyContext(numLayer);
	
	//Passing a layerID for collision
	collisionCheck *collCheck = new collisionCheck(0, 0);
	
	//Initialize the collison
	collCheck->getCollisionInstance()->init();
	
	//Initialize collision check thread
	collCheck->init();
	
	/*Initialize visualization*/
	view.init();	
}

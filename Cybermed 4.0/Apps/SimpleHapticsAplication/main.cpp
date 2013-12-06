/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybHaptics.h>
#include <cybermed/cybCore.h>

////
#include <cybermed/cybSphereTriangle.h>
#include <cybermed/cybMassSpring.h>
#include <cybermed/cybCollision.h>
////

#include <cybermed/cybViewMono.h>
#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include <cybermed/cybHapticInterator.h>
#include <GL/glut.h>



int main(int argc, char** argv)
{
	char *fileName = "monkey.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure

	cout << "Starting View" << endl;
	CybViewMono view;
	
	//Access the parameters information of scene and graphical objects
	cout << "Starting Parameters" << endl;
	CybParameters *cybCore = CybParameters::getInstance();

	cout << "Starting Haptic " << HAPTIC_INTERATOR << endl;
	CybInterator* interator = CybHapticInterator::getInterator();
	//CybInterator* mouseInterator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);

	cout << "Creating Interator" << endl;
	interator->create(0);

	data.loadInteratorModel(0, 0, "esfera.wrl");
	cout <<  "Interator File loaded" << endl;

	data.startInterator(0, 0);

	/* Read Mesh File */
	mfWrlReader<cybSurfaceTriTraits> in;

	sMesh *mesh = new sMesh[numLayer];

	cout << "Reading File: " << fileName << endl;
	in.read(&mesh[0], fileName);
	
	/*Load the model from VRML file (layerID, fileName)*/
	data.loadModel(mesh);
	
	interator->setColor(1, 0, 0, 1);
	
	interator->setScale(0.05,0.05,0.05);
	
	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	/*Gets the Phantom device*/
	CybOpenHPhantom* phantom = (CybOpenHPhantom*)interator->getDevice();
	phantom->createHapticLayers(1, true);

		
	//Set the window name
	view.setWindowName("Simple Haptic Deformation");

	///////
	cybCore->createMaterialPropertyContext(numLayer);
	
	//Set properties material properties to monkey skin
	cybCore->setMaterialPropertyValue(0,  STIFFNESS, 0.1);
	cybCore->setMaterialPropertyValue(0,  DAMPING, 0.7);
	
	//Create a object of collision
	CybSphereTriangle *collisionObj = new CybSphereTriangle(0, interator);
	
	//Create a object of deformation and set the collision object used
	CybMassSpring *deformationObj = new CybMassSpring(collisionObj, DEF_GO_AND_BACK);
	
	//Update the deformation properties
	deformationObj->update();
		
	//Initialize collision check thread
	deformationObj->init();
	///////

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);
	
	/*Initialize visualization*/
	view.init();	
}

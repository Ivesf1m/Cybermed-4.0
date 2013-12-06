/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybSphereTriangle.h>
#include <cybermed/cybMassSpring.h>
#include <cybermed/cybCollision.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>

#include <cybermed/mf/mfReaderModel.h>

int main(int argc, char** argv)
{
	char *fileName = "monkey.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybInterator* interator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);
	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure
	CybViewMono view;			// Monoscopic Visualization

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();
	
	/*Load the model from VRML file*/
	data.loadInteratorModel(0, 0, "esfera.wrl");
	
	/*Load the model from VRML file (layerID, fileName)*/
	//data.loadModel(0, fileName);
	/* Read Mesh File */
	mfReaderModel<cybSurfaceTriTraits> in;
	sMesh *mesh = new sMesh[numLayer];
	
	cout << "Reading File: " << fileName << endl;
	in.read(&mesh[0], fileName);
	cout << " Volume Mesh " << mesh[0].getNumberOfVertices() << " " << mesh[0].getNumberOfCells() << endl;
	
	/*Load the model from VRML file (layerID, fileName)*/
	cout << "Loading File" << endl;
	data.loadModel(mesh);
	
	
	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	/*Initialize the meshes parameters*/
	data.startInterator(0,0);
	
	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);
	//cybCore->setLayerScale(0, 50, 50, 50);
	
	//Set the window name
	view.setWindowName("Simple Deformation Check");
	
	//Create a materrial property context, use by collision, haptics and deformation
	cybCore->createMaterialPropertyContext(numLayer);
	
	//Set properties material properties to monkey skin
	cybCore->setMaterialPropertyValue(0,  STIFFNESS, 0.5);
	cybCore->setMaterialPropertyValue(0,  DAMPING, 0.7);
	
	//Create a object of collision
	CybSphereTriangle *collisionObj = new CybSphereTriangle(0, interator);
	
	//Create a object of deformation and set the collision object used
	CybMassSpring *deformationObj = new CybMassSpring(collisionObj, DEF_GO_AND_BACK);
	cybCore->addDeformableLayer(0);
	
	//Update the deformation properties
	deformationObj->update();
		
	//Initialize collision check thread
	deformationObj->init();
	
	/*Initialize visualization*/
	view.init();
	
}

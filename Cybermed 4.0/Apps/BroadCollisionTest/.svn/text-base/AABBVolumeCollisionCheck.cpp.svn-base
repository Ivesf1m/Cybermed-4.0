/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybAABB.h>
#include <cybermed/cybCollisionManager.h>
#include <cybermed/mf/mfVtkReader.h>
//#include <cybermed/cybVector3D.h>
//#include <cybermed/cybAABBDrawer.h>
#include <string>
#include <cstring>
#include <iostream>


using namespace std;


int main(int argv, char **argc)
{
	string s1 = "BunnyTetra.vtk"; //model name
	char* filename = const_cast<char*>(s1.c_str());
	int numLayer = 1; //number of layers used in this application
	int numInterator = 1;
	
	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator); // Transfer the OF data to the CybParameters structure
	CybViewMono view; // Monoscopic Visualization
	CybInterator* interator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	// =============
	// Read Mesh File 
	mfVtkReader<cybTetraTraits> in;
	sTetraMesh *mesh = new sTetraMesh[numLayer];
	cout << "Reading File: " << filename << endl;
	in.read(&mesh[0], filename);
	cout << " Volume Mesh " << mesh[0].getNumberOfVertices() << " " << mesh[0].getNumberOfCells() << endl;
	/*Load the model from VRML file (layerID, fileName)*/
	cout << "Loading File" << endl;
	data.loadModel(mesh);
	//===========
	
	//Load the model from VRML file (layerID, fileName)
	//data.loadModel(0, filename);
	string s2 = "agulha_unida.wrl";
	char *aux = const_cast<char*>(s2.c_str());
	data.loadInteratorModel(0,0, aux);
	data.startInterator(0,0);
	interator->setColor(0,1,0,1);

	//Initialize the meshes parameters
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);

	//cybCore->setLayerScale(0, 50, 50, 50);
	//CybVector3D<float> scale(50,50,50);
	//Set the window name
	string s3 = "Teste";
	char *aux2 = const_cast<char*>(s3.c_str());
	view.setWindowName(aux2);

	//Create a materrial property context, used by collision, haptics and deformation
	cybCore->createMaterialPropertyContext(numLayer);

	//Creating the AABBs
	CybAABB *caixaInter = new CybAABB(0,0,true, true);
	CybAABB *caixaModel = new CybAABB(0,0,false, true);
	//caixaModel->getDrawer()->setScale(scale);
	caixaInter->describeBox();
	caixaModel->describeBox();
	caixaInter->addTest(caixaModel);
	caixaModel->addTest(caixaInter);
	
	//Creating the Collision Manager objects.
	CybCollisionManager* colMan1 = new CybCollisionManager(caixaInter, true);
	CybCollisionManager* colMan2 = new CybCollisionManager(caixaModel, false);

	//Initializing boxes and managers
	caixaInter->init();
	caixaModel->init();
	colMan1->init();
	colMan2->init();

	//Initializing visualization
	view.init();
	
}

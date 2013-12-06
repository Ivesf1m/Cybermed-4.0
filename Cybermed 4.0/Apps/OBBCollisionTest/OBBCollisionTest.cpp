#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybOBB.h>
#include <cybermed/cybCollisionManager.h>
#include <cybermed/mf/mfReaderModel.h>
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>


using namespace std;

struct timeval inicio, fim;
double total;

int main(int argv, char **argc)
{
	string s1 = "medulanova.wrl"; //model name
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
	mfReaderModel<cybSurfaceTriTraits> in;
	sMesh *mesh = new sMesh[numLayer];
	in.read(&mesh[0], filename);
	//data.readColor(filename, 0);
	data.loadModel(mesh);
	//===========
	
	//Load the model from VRML file (layerID, fileName)
	//data.loadModel(0, filename);
	string s2 = "esfera.wrl";
	char *aux = const_cast<char*>(s2.c_str());
	data.loadInteratorModel(0,0, aux);
	data.startInterator(0,0);
	interator->setColor(0,1,0,1);

	//Initialize the meshes parameters
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);

	//Set the window name
	string s3 = "Teste";
	char *aux2 = const_cast<char*>(s3.c_str());
	view.setWindowName(aux2);

	//Create a material property context, used by collision, haptics and deformation
	cybCore->createMaterialPropertyContext(numLayer);
	

	cout << "antes da obb" << endl;
	//Creating the OBBs
	CybOBB *caixaInter = new CybOBB(0,0,true, true);
	gettimeofday(&inicio, NULL);
	CybOBB *caixaModel = new CybOBB(0,0,false, true);
	gettimeofday(&fim, NULL);
	total = (fim.tv_sec - inicio.tv_sec) * 1000000 + (fim.tv_usec - inicio.tv_usec);
	cout << "A construcao da OBB levou " << total << " microssegundos." << endl;
	cout << "Passei dos construtores" << endl;
	//caixaInter->describeBox();
	caixaModel->describeBox();
	caixaInter->addTest(caixaModel);
	caixaModel->addTest(caixaInter);

	cout << "depois da OBB" << endl;
	
	//Creating the Collision Manager objects.
	CybCollisionManager* colMan1 = new CybCollisionManager(caixaInter, true);
	CybCollisionManager* colMan2 = new CybCollisionManager(caixaModel, false);

	//Initializing boxes and managers
	caixaInter->init();
	caixaModel->init();
	colMan1->init();
	colMan2->init();

	cout << "passei da aguias" << endl;

	//Initializing visualization
	view.init();
	
}

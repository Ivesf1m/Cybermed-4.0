#include <cybermed/cybCore.h>
#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include <cybermed/cybViewShutter.h>
#include <cybermed/mf/mfVtkReader.h>


#define NUM_LAYER 1
#define NUM_INTERATOR 1
#define MONKEY 0


int main(int argc, char** argv)
{
	Cyb3DWorld *view;
	if(argc != 2){
		
		cout << "Error: Invalid number of arguments!" << endl;
		cout << "Please, place 1 to Anaglyph view or 2 for Shutter view." << endl;
		cout << "Stopping app..." << endl;
		return -1;
	}
	
	char *fileName = "BunnyTetra.vtk"; //Model name

	CybDataObtainer<cybSurfaceTriTraits> data(NUM_LAYER, NUM_INTERATOR);		// Transfer the OF data to CybParameters structure
	
	if(argv[1][0] == '2')
		view = new CybViewShutter();
	else
		view = new CybViewAnaglyph();	

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();
	
	CybInterator* interator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);


	data.loadInteratorModel(0, 0, "esfera.wrl");
	data.startInterator(0, 0);

	interator->setColor(1, 1, 1, 1);
	
	// =============
	/* Read Mesh File */
	mfVtkReader<cybTetraTraits> in;
	sTetraMesh *mesh = new sTetraMesh[NUM_LAYER];
	in.read(&mesh[0], fileName);
	data.loadModel(mesh);
	//===========

	/*Load the model from VRML file (layerID, fileName)*/
	//data.loadModel(MONKEY, fileName);
	
	/*Initialize the meshes parameters*/
	data.startParameters(NUM_LAYER);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(MONKEY,1,1,0.7,0.9);
	cybCore->setLayerScale(0, 50, 50, 50);
	
	//Set the window name
	view->setWindowName("Stereo Visualization");
	
	/*Initialize visualization*/
	view->init();
	
	return 0;
	
}

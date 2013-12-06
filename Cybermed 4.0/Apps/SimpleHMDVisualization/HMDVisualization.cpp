/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewHMD.h>

#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>

#include <cybermed/cybInteratorFactory.h>

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
//#include <cybermed/cybHaptics.h>
#include <cybermed/mf/mfReaderModel.h>


#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include <cybermed/cybInteratorFactory.h>


int main(int argc, char** argv)
{
	char *fileName = "monkey.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure

	CybViewHMD view;

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();
	
	CybInterator* interator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);
	
	data.loadInteratorModel(interator->getId(), 0, "esfera.wrl");

	data.startInterator(interator->getId(), 0);

	interator->setColor(0, 0, 1, 1);

	/* Read Mesh File */
	mfReaderModel<cybSurfaceTriTraits> in;

	sMesh *mesh = new sMesh[numLayer];
	//for(int i = 0; i < numLayer; i++)

	cout << "Reading File: " << fileName << endl;
	//data.readColor(fileName, 0);
	in.read(&mesh[0], fileName);
	cout << " Volume Mesh " << mesh[0].getNumberOfVertices() << " " << mesh[0].getNumberOfCells() << endl;
	//data.readColor(fileName, 0);

	/*Load the model from VRML file (layerID, fileName)*/
	cout << "Loading File" << endl;
	data.loadModel(mesh);

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,0,0.1,1);
	
	//cybCore->setLayerScale(0, 50, 50, 50);

	cout << "Surface Mesh: " << cybCore->mesh[0]->getNumberOfVertices() << " " << cybCore->mesh[0]->getNumberOfCells() << endl;
	cout << "Volumetric Mesh: " << cybCore->tetraMesh[0]->getNumberOfVertices() << " " << cybCore->tetraMesh[0]->getNumberOfCells() << endl;

	//Set the window name
	view.setWindowName("Simple Volume Visualization");
	view.setResolution(600,600);

	/*Initialize visualization*/
	view.init();
}

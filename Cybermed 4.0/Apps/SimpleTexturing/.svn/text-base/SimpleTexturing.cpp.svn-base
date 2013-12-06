/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include "TextureView.h"
#include <cybermed/mf/mfReader.h>

int main(int argc, char** argv)
{
	char *fileName = "monkey.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 0;

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure
	
	TextureView view;
	//CybViewMono view;

	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();

	CybInterator* interator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);
	data.loadInteratorModel(interator->getId(), 0, "esfera.x3d");
	data.startInterator(interator->getId(), 0);

	//Allocate space for some textures
	cybCore->createTextures(1);
	cybCore->texName[0] = "orange.bmp";
	//cybCore->texName[1] = "/home/alysson/Desktop/teste.bmp";
	//cybCore->texName[2] = "/home/alysson/Desktop/moderno.bmp";

	sMesh *mesh = new sMesh[numLayer];
	mfReaderModel<cybSurfaceTriTraits> in;
	in.read(&mesh[0], fileName);
	data.loadModel(mesh);
	
	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,0.9);
	
	//Set the window name
	view.setWindowName("Simple Visualization");
	
	/*Initialize visualization*/
	view.init();

}

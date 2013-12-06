/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include "myViewMono.h"
#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include <cybermed/cybInteratorFactory.h>
#include "cybHandModel.h"
#include <GL/glut.h>
#include <cybermed/cyb5DTGlove.h>


int main(int argc, char** argv)
{
	char *fileName = "esfera.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;
	CybModel *model = new CybHandModel();
	
	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the MF data to CybParameters structure	
	MyViewMono view;
	//Access the parameters information of scene and graphical objects
	CybParameters *cybCore = CybParameters::getInstance();
	CybInterator* interator = CybInteratorFactory::getInterator(GLOVE_5DT_INTERATOR);
	if (interator == NULL) {
		cout << "interator is null" << endl;
		return 0;
	}
	//Em caso de ser outra porta
	/*Cyb5DTGlove *glove = dynamic_cast<Cyb5DTGlove *>(interator->getDevice());
	glove->setPort("/dev/usb/hiddev0");*/
	//CybInterator* mouseInterator = CybInteratorFactory::getInterator(MOUSE_INTERATOR);	
	interator->create(0);
	data.loadInteratorModel(0, model);
	data.startInterator(0, 0); //<- Não precisa para modelos tipo CybModel
	/*Load the model from VRML file (layerID, fileName)*/
	
	/*mfReaderModel<cybSurfaceTriTraits> in;

	sMesh *mesh = new sMesh[numLayer];

	in.read(&mesh[0], fileName);
	
	data.loadModel(mesh);*/	
	
	interator->setRotation(0, 0, 180);
	
	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);
	cybCore->setColor(0,1, 0, 0, 1);
	
	//Set the window name
	view.setWindowName("Simple Glove Application");
	
	/*Initialize visualization*/
	view.init();
	
}


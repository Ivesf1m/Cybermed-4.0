/*
 * @author	LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version	3.0
 * @date	2012, June
*/

#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
//#include <cybermed/cybHaptics.h>

#include <cybermed/cybViewAnaglyph.h>
#include <cybermed/cybViewColorAnaglyph.h>
#include <cybermed/cybDefaultShaderDisplay.h>
#include <cybermed/cybColorDisplay.h>

#include <cybermed/cybMouseInterator.h>
#include <cybermed/cybMouseInteraction.h>

int main(int argc, char** argv)
{
	char *fileName = const_cast<char*>("cubo.x3d"); //Model name
	int numLayer = 1; //Number of layers used in this application
	int numInterator = 1;
	CybParameters *cybCore = CybParameters::getInstance();
	cybCore->setWindowSize(800, 600);

	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);		// Transfer the OF data to CybParameters structure
	cout << "data ok" << endl;

	CybDefaultShaderDisplay* d = new CybDefaultShaderDisplay();
	vec4 color;
	color[0] = color[3] = 1.0; color[1] = color[2] = 0.0;
	CybColorDisplay* cd = new CybColorDisplay(color);
	CybViewMono view(NULL, cd);

	//Access the parameters information of scene and graphical objects

	CybInterator* interator = CybMouseInterator::getInterator();
	CybMouseInteraction::getInstance()->setMouseInterator((CybMouseInterator*)interator);
	cout << "interator ok" << endl;

	data.loadInteratorModel(interator->getId(), 0, const_cast<char*>("esfera.wrl"));

	data.startInterator(interator->getId(), 0);

	//interator->setColor(1, 1, 0, 1);

	/* Read Mesh File */
	mfX3dReader<cybSurfaceTriTraits> in;	/**< Acess the OF Vrml reader*/

	sMesh *mesh = new sMesh[numLayer];
	//for(int i = 0; i < numLayer; i++)

	in.read(&mesh[0], fileName);

	data.readColor(fileName, 0);

	/*Load the model from VRML file (layerID, fileName)*/
	data.loadModel(mesh);

	/*Initialize the meshes parameters*/
	data.startParameters(numLayer);

	//Set the object color (layerID, r, g, b,a)
	cybCore->setColor(0,1,1,0.7,1);

	//cybCore->setLayerScale(0, 10, 10, 10);
	//Set the window name
	view.setWindowName(const_cast<char*>("Simple Visualization"));
	cout << "antes do view init" << endl;
	/*Initialize visualization*/
	view.init();
}

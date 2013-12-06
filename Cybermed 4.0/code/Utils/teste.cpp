#include <cybermed/cybMatrixStack>
#include <cybermed/cybPerspectiveProjection.h>
#include <cybermed/cybShaderManager.h>
#include <cybermed/cybTriangleBatch.h>
#include <cybermed/cybCore.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <fstream>

using namespace std;

CybFrame frame;
CybPerspectiveProjection frustum;
CybTriangleBatch batch;
CybMatrixStack mvStack, pStack;
CybShaderManager* sm;

void init()
{
    ifstream vArq("flat.vert", ios::in);
    ifstream fArq("flat.frag", ios::in);
    sm = new ShaderManager(vArq, fArq);
    sm->compile();

}

int main(int argc, char** argv)
{
    char *fileName = "monkey.wrl"; //Model name
	int numLayer = 1; //Number of layers used in this application
	CybParameters *cybCore = CybParameters::getInstance();
	CybDataObtainer<cybSurfaceTriTraits> data(numLayer, numInterator);
	mfWrlReader<cybSurfaceTriTraits> in;
	sMesh *mesh = new sMesh[numLayer];
	in.read(&mesh[0], fileName);
	data.readColor(fileName, 0);
	data.loadModel(mesh);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cybermed with Shaders");

    glutDisplayFunc(display);

    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
    }

    init();
    glutMainLoop();
    return 0;
}

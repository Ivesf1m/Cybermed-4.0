// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.
// *****************************************************************

#include "cyb3DWorld.h"

char *Cyb3DWorld::windowName = "";
CybMouse* Cyb3DWorld::mouse = NULL;
Cyb3DWorld* Cyb3DWorld::this_object = 0;
int Cyb3DWorld::viewNumber = 1;

Cyb3DWorld::Cyb3DWorld(CybMouse* mouse, bool stereo, CybAbstractDisplay* d)
{
    if(mouse == NULL) mouse = CybMouse::getInstance();
    else Cyb3DWorld::mouse = mouse;
    viewMode = GL_TRIANGLES;
    initLightsParameters();
    this_object = this;
    this->swap = false;
    freePos = 0;
    this->stereo = stereo;
    this->d = d;
}

void Cyb3DWorld::enableWire()
{
    this->viewMode = GL_LINE_LOOP;
}

void Cyb3DWorld::disableWire()
{
    this->viewMode = GL_TRIANGLES;
}

bool Cyb3DWorld::isWire()
{
    return (viewMode == GL_LINE_LOOP);
}

GLenum Cyb3DWorld::getViewMode()
{
    return viewMode;
}

/* The auxiliar functions make possible that derived classes override these methods */

/** Auxiliar Drawing Function
 @param void
 @return void
*/
inline  void Cyb3DWorld::mainDisplay()
{
    this_object->display();
}

/** Auxiliar Reshape Function
 @param int width
 @param int height
 @return void
*/
inline void Cyb3DWorld::mainReshape(int width, int height)
{
    this_object->reshape(width, height);
}

/** Auxiliar Idle Function
 @param void
 @return void
*/
inline void Cyb3DWorld::mainIdle()
{
    this_object->glutIdle();
}

/** Auxiliar Keyboard Function
 @param unsigned char key
 @param int x
 @param int y
 @return void
*/
inline void Cyb3DWorld::mainKeyboard(unsigned char key, int x, int y)
{
    this_object->keyboard(key, x, y);
}

/** Auxiliar Special Key Function
 @param int key
 @param int x
 @param int y
 @return void
*/
inline void Cyb3DWorld::mainSpecialKey(int key, int x, int y)
{
    this_object->specialKey(key, x, y);
}

/** Auxiliar Mouse Function
 @param int button
 @param int state
 @param int x
 @param int y
 @return void
*/
inline void Cyb3DWorld::mainMouseFunc(int button, int state, int x, int y)
{
    this_object->mouseFunc(button, state, x, y);
}

/** Auxiliar Mouse Motion Function
 @param int x
 @param int y
 @return void
*/
inline void Cyb3DWorld::mainMouseMotionFunc(int x, int y)
{
    this_object->mouseMotionFunc(x, y);
}

/** Auxiliar Passive Mouse Motion Function
 @param int key
 @param int x
 @param int y
 @return void
*/
inline void Cyb3DWorld::mainMousePassiveMotionFunc(int x, int y)
{
    this_object->mousePassiveMotionFunc(x, y);
}

inline int Cyb3DWorld::ImageLoad(char *filename, Image *image)
{
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1)
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
        printf("File Not Found : %s\n",filename);
        return 0;
    }

    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1)
    {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);

    // read the height
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1)
    {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);

    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1)
    {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }

    if (planes != 1)
    {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1)
    {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }

    if (bpp != 24)
    {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }

    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data.
    image->data = (char *) malloc(size);
    if (image->data == NULL)
    {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }

    if ((i = fread(image->data, size, 1, file)) != 1)
    {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }

    for (i=0; i<size; i+=3) // reverse all of the colors. (bgr -> rgb)
    {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }

    // we're done.
    return 1;
}

// Load Bitmaps And Convert To Textures
inline void Cyb3DWorld::loadBMPTexture(char* path, int idTex)
{
    CybParameters *cybCore = CybParameters::getInstance();

    // Load Texture
    Image *image;

    // allocate space for texture
    image = (Image *) malloc(sizeof(Image));
    if (image == NULL)
    {
        printf("Error allocating space for image");
        exit(0);
    }

    if (!ImageLoad(path, image))
    {
        exit(1);
    }

    // Create Texture
    glGenTextures(1, &(cybCore->texture[idTex]));
    glBindTexture(GL_TEXTURE_2D, cybCore->texture[idTex]);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
};

/**	Initializes the visualization, creates the window and draws the objects.
@param  void
@return void
*/
void Cyb3DWorld::init()
{
    CybParameters *cybCore = CybParameters::getInstance();
    int p[1] = { 1 };
    char **config = new char*[2];
    config[0] = windowName;
    config[1] = NULL;


    cybCore->viewType = viewNumber;

    if(viewNumber != 5)
    {

        glutInit(p, config);

        if(stereo)
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO );
        else
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

        glutInitWindowSize(cybCore->Resx, cybCore->Resy);
        glutInitWindowPosition(50, 50);
        double aspect = (double)cybCore->Resx / (double)cybCore->Resy
                        frustum = new CybPerpectiveFrustum(PI / 3.0, aspect, 1, 100);

        glutCreateWindow(windowName);

        /*If texturing is active*/
        if(cybCore->nTextures)
        {
            for(int j=0; j < cybCore->nTextures; j++)
                loadBMPTexture(cybCore->texName[j],j);
        }
        glutDisplayFunc(mainDisplay);
        glutReshapeFunc(mainReshape);
        glutIdleFunc(mainIdle);

        if(cybCore->isKeyboardEnable())
        {
            glutKeyboardFunc(mainKeyboard);
            glutSpecialFunc(mainSpecialKey);
        }
        glutMouseFunc(mainMouseFunc);
        glutMotionFunc(mainMouseMotionFunc);
        glutPassiveMotionFunc(mainMousePassiveMotionFunc);
        loadObjects();
        glutMainLoop();

    }
    else
    {

        glutInit(p, config);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

        if(!defResolution)
        {
            std::cout << "Warning: Resolution has not been defined!. Using default 800x600 Resolution." << std::endl;
        }

        glutInitWindowSize(horResolution, verResolution);
        double aspect = (double)horResolution / (double)verResolution;
        frustum = new CybPerpectiveFrustum(PI / 3.0, aspect, 1, 100);

        /*If texturing is active*/
        if(cybCore->nTextures)
        {
            for(int j=0; j < cybCore->nTextures; j++)
                loadBMPTexture(cybCore->texName[j],j);
        }


        //Left Window
        if(swap)
        {
            glutInitWindowPosition(horResolution, 0);
        }
        else
        {
            glutInitWindowPosition(0, 0);
        }

        leftWindow = glutCreateWindow(windowName);
        glutSetWindow(leftWindow);

        glutDisplayFunc(mainDisplay);
        glutReshapeFunc(mainReshape);
        glutIdleFunc(mainIdle);

        if(cybCore->isKeyboardEnable())
        {
            glutKeyboardFunc(mainKeyboard);
            glutSpecialFunc(mainSpecialKey);
        }
        glutMouseFunc(mainMouseFunc);
        glutMotionFunc(mainMouseMotionFunc);
        glutPassiveMotionFunc(mainMousePassiveMotionFunc);


        //Right Window

        if(swap)
        {
            glutInitWindowPosition(0, 0);
        }
        else
        {
            glutInitWindowPosition(horResolution, 0);
        }

        rightWindow = glutCreateWindow(windowName);
        glutSetWindow(rightWindow);

        glutDisplayFunc(mainDisplay);
        glutReshapeFunc(mainReshape);
        glutIdleFunc(mainIdle);

        if(cybCore->isKeyboardEnable())
        {
            glutKeyboardFunc(mainKeyboard);
            glutSpecialFunc(mainSpecialKey);
        }
        glutMouseFunc(mainMouseFunc);
        glutMotionFunc(mainMouseMotionFunc);
        glutPassiveMotionFunc(mainMousePassiveMotionFunc);
        loadObjects2();
        glutMainLoop();

    }
}
/**	Set ambient light
@param float r
@param float g
@param float b
@param float a
@return void
*/
void Cyb3DWorld::setAmbientLight(float r, float g, float b, float a)
{
    CybParameters *cybCore = CybParameters::getInstance();

    cybCore->ambientLight[0] = r;
    cybCore->ambientLight[1] = g;
    cybCore->ambientLight[2] = b;
    cybCore->ambientLight[3] = a;
}

/**	Set diffuse light
* Sets the diffuse light values for the light identified by light id.
@param int light_id
@param float r
@param float g
@param float b
@param float a
@return void
*/
void Cyb3DWorld::setDiffuseLight(int light, float r, float g, float b, float a)
{
    CybParameters *cybCore = CybParameters::getInstance();

    if(light >= 6)
    {
        cout << "Error. There can only be up to 6 lights." << endl;
        exit(0);
    }
    cybCore->diffuseLight[light][0] = r;
    cybCore->diffuseLight[light][1] = g;
    cybCore->diffuseLight[light][2] = b;
    cybCore->diffuseLight[light][3] = a;
}

/**	Set position of light sources.
* Sets the position of light values for the light identified by light id.
@param int light_id
@param float x
@param float y
@param float z
@param float w
@return void
*/
void Cyb3DWorld::setLightPosition(int light, float x, float y, float z, float w)
{
    CybParameters *cybCore = CybParameters::getInstance();

    if(light >= 6)
    {
        cout << "Error. There can only be up to 6 lights.\n" << endl;
        exit(0);
    }
    cybCore->positionLight[light][0] = x;
    cybCore->positionLight[light][1] = y;
    cybCore->positionLight[light][2] = z;
    cybCore->positionLight[light][3] = w;
}

/**	Set number of light sources.
@param int number_of_lights
@return void
*/
void Cyb3DWorld::setNLights(int n)
{
    CybParameters *cybCore = CybParameters::getInstance();

    if(n > 6)
    {
        cout << "Error. There can only be up to 6 lights.\n" << endl;
        exit(0);
    }
    cybCore->nLights = n;
}

/**	Set specular light
* Sets the specular light values for the light identified by light id.
@param int light_id
@param float r
@param float g
@param float b
@param float a
@return void
*/
void Cyb3DWorld::setSpecularLight(int light, float r, float g, float b, float a)
{
    CybParameters *cybCore = CybParameters::getInstance();

    if(light >= 6)
    {
        cout << "Error. There can only be up to 6 lights.\n" << endl;
        exit(0);
    }
    cybCore->specularLight[light][0] = r;
    cybCore->specularLight[light][1] = g;
    cybCore->specularLight[light][2] = b;
    cybCore->specularLight[light][3] = a;
}

/** Function that sets the texture file's name. To next version
@param char *texture_file
@return void
*/
void Cyb3DWorld::setTextureFile(char *textureFile) {}

/**	Function that sets the graphic window's name
@param char *window
@return void
*/
void Cyb3DWorld::setWindowName(char *window)
{
    windowName = window;
}

char *Cyb3DWorld::getWindowName()
{
    return windowName;
}

/**	Display function.
There's no renderization of the graphical objects in this method. It should be overrided at derived classes
@param void
@return void
*/
void Cyb3DWorld::display()
{
    CybParameters *cybCore = CybParameters::getInstance();
    double frustumAssimetry;
    static bool k = false;

    sVertex *v0, *v1, *v2;
    int l;

    glColorMask(1,1,1,1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
    glDrawBuffer(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Left Eye
    if(cybCore->viewType == 4)
        glDrawBuffer(GL_BACK_LEFT);

    //glMatrixMode(GL_PROJECTION);

    if(cybCore->modified == 1)
    {
        frustumAssimetry = cybCore->StereoProjection(-6.4, 6.4, -6.4, 6.4, 6.0, -6.0, 180, 14.5, -cybCore->getStereoMagnitude(), cybCore->getParalaxe());
        cybCore->rightFrustumLeftEye = cybCore->widthProportion*(cybCore->dfXRange/2 - frustumAssimetry);
        cybCore->leftFrustumLeftEye = cybCore->widthProportion*(-cybCore->dfXRange/2 - frustumAssimetry);
        if(cybCore->viewType != 2 && cybCore->viewType !=3) //redundant
            cybCore->modified = 0;
    }
    pStack.loadIdentity();


    frustum->setPerspective(cybCore->leftFrustumLeftEye, cybCore->rightFrustumLeftEye, cybCore->widthProportion*cybCore->FrustumBase, cybCore->heightProportion*cybCore->FrustumTop, cybCore->dfNearClipDistance, cybCore->dfFarClipDistance);
    pStack.pushMatrix(frustum.getProjectionMatrix());

    if((cybCore->viewType == 2) || (cybCore->viewType == 3))
    {
        mat4 t1;
        CybLineMatrix::createTranslationMatrix4D(t1, -cybCore->dfXMidpoint - cybCore->dfStereoCameraOffset, 0, 0);
        pStack.multMatrix(t1);
    }

    //gluLookAt(0, 0, cybCore->camPosZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    frame.moveForward(cybCore->camPosZ);

    //glMatrixMode(GL_MODELVIEW);
    mvStack.loadIdentity();

    mat4 t1, t2, t3, s1, r1, r2, r3;

    for(int j=0; j < cybCore->numLayer; j++)
    {
        if(cybCore->habLayer[j] == 1)
        {
            // graphical transforms
            CybLineMatrix::createTranslationMatrix4D(t1, cybCore->xTrans + cybCore->layerTrans[j][0], cybCore->yTrans + cybCore->layerTrans[j][1], cybCore->zTrans + cybCore->layerTrans[j][2]);
            CybLineMatrix::createScaleMatrix4D(s1, cybCore->xScale * cybCore->layerSca[j][0], cybCore->yScale * cybCore->layerSca[j][1], cybCore->zScale * cybCore->layerSca[j][2]);
            CybLineMatrix::createTranslationMatrix4D(t2, cybCore->cX, cybCore->cY, cybCore->cZ);
            CybLineMatrix::createRotationMatrix4D(r1, cybCore->getXAngle() + cybCore->layerRot[j][0],1,0,0);
            CybLineMatrix::createRotationMatrix4D(r2, cybCore->getYAngle() + cybCore->layerRot[j][1],0,1,0);
            CybLineMatrix::createRotationMatrix4D(r3, cybCore->getZAngle() + cybCore->layerRot[j][2],0,0,1);
            CybLineMatrix::createTranslationMatrix4D(t3, -cybCore->cX, -cybCore->cY, -cybCore->cZ);
            mvStack.multMatrix(t1);
            mvStack.multMatrix(s1);
            mvStack.multMatrix(t2);
            mvStack.multMatrix(r1);
            mvStack.multMatrix(r2);
            mvStack.multMatrix(r3);
            mvStack.multMatrix(t3);

            mvStack.getMatrix(cybCore->transforMatrix[j]);

            mvStack.loadIdentity();
        }
    }

    if(!k)
    {
        cybCore->transforChange = true;
        k = true;
    }

    glFlush();
    mvStack.loadIdentity();
    glutSwapBuffers();
}

/**	Function that calls the glutPostRedisplay function while the system is in idle state.
@param void
@return void
*/
void Cyb3DWorld::glutIdle()
{
    if(viewNumber == 5)
    {
        glutSetWindow(leftWindow);
        glutPostRedisplay();
        glutSetWindow(rightWindow);
    }
    glutPostRedisplay();
}

/**	Initializes the lights' default values
@param void
@return void
*/
void Cyb3DWorld::initLightsParameters()
{
    CybParameters *cybCore = CybParameters::getInstance();

    int i;

    cybCore->nLights = 1;

    // Initialize diffuseLight and specularLight:
    for(i=0; i<6; i++)
    {
        cybCore->diffuseLight[i][0] = 1;
        cybCore->diffuseLight[i][1] = 1;
        cybCore->diffuseLight[i][2] = 1;
        cybCore->diffuseLight[i][3] = 1;

        cybCore->specularLight[i][0] = 1;
        cybCore->specularLight[i][1] = 1;
        cybCore->specularLight[i][2] = 1;
        cybCore->specularLight[i][3] = 1;
    }

    // Initialize ambient light
    cybCore->ambientLight[0] = 0.5;
    cybCore->ambientLight[1] = 0.5;
    cybCore->ambientLight[2] = 0.5;
    cybCore->ambientLight[3] = 0.5;

    // initialize positionLight:
    cybCore->positionLight[0][0] = 0;
    cybCore->positionLight[0][1] = 1;
    cybCore->positionLight[0][2] = 0;
    cybCore->positionLight[0][3] = 0;

    cybCore->positionLight[1][0] = 1;
    cybCore->positionLight[1][1] = 0;
    cybCore->positionLight[1][2] = 0;
    cybCore->positionLight[1][3] = 0;

    cybCore->positionLight[2][0] = 0;
    cybCore->positionLight[2][1] = 0;
    cybCore->positionLight[2][2] = 1;
    cybCore->positionLight[2][3] = 0;

    cybCore->positionLight[3][0] = 0;
    cybCore->positionLight[3][1] = -1;
    cybCore->positionLight[3][2] = 0;
    cybCore->positionLight[3][3] = 0;

    cybCore->positionLight[4][0] = -1;
    cybCore->positionLight[4][1] = 0;
    cybCore->positionLight[4][2] = 0;
    cybCore->positionLight[4][3] = 0;

    cybCore->positionLight[5][0] = 0;
    cybCore->positionLight[5][1] = 0;
    cybCore->positionLight[5][2] = -1;
    cybCore->positionLight[5][3] = 0;

    setDiffuseCoefficient(0.8, 0.8, 0.8);
    setSpecularCoefficient(0.2, 0.2, 0.2);
}

/**	Keyboard interaction function
@param unsigned char key
@param int x
@param int y
@return void
*/
void Cyb3DWorld::keyboard(unsigned char key, int x, int y)
{
    CybParameters *cybCore = CybParameters::getInstance();
    CybVector4D<float> color;
    switch (key)
    {
    case 'p':
        cybCore->initParameters();
        cybCore->transforChange = true;
        break;

    case 't':
        cybCore->xScale = cybCore->xScale / 1.1;
        cybCore->transforChange = true;
        break;
    case 'g':
        cybCore->xScale = cybCore->xScale * 1.1;
        cybCore->transforChange = true;
        break;
    case 'y':
        cybCore->yScale = cybCore->yScale / 1.1;
        cybCore->transforChange = true;
        break;
    case 'h':
        cybCore->yScale = cybCore->yScale * 1.1;
        cybCore->transforChange = true;
        break;
    case 'u':
        cybCore->zScale = cybCore->zScale / 1.1;
        cybCore->transforChange = true;
        break;
    case 'j':
        cybCore->zScale = cybCore->zScale * 1.1;
        cybCore->transforChange = true;
        break;

    case 'n':
        cybCore->setParalaxe(cybCore->getParalaxe() - 0.005);
        cybCore->modified = 1;
        break;
    case 'm':
        cybCore->setParalaxe(cybCore->getParalaxe() + 0.005);
        cybCore->modified = 1;
        break;
    case 'v':
        cybCore->setStereoMagnitude(cybCore->getStereoMagnitude() - 0.01);
        cybCore->modified = 1;
        break;
    case 'b':
        cybCore->setStereoMagnitude(cybCore->getStereoMagnitude() + 0.01);
        cybCore->modified = 1;
        break;

    case '0':
        cybCore->objChosen = 0;
        break;
    case '1':
        cybCore->objChosen = 1;
        break;
    case '2':
        cybCore->objChosen = 2;
        break;
    case '3':
        cybCore->objChosen = 3;
        break;
    case '4':
        cybCore->objChosen = 4;
        break;
    case '5':
        cybCore->objChosen = 5;
        break;
    case '6':
        cybCore->objChosen = 6;
        break;
    case '7':
        cybCore->objChosen = 7;
        break;
    case '8':
        cybCore->objChosen = 8;
        break;
    case '9':
        cybCore->objChosen = 9;
        break;

    case 'a':
        cybCore->habLayer[cybCore->objChosen] = 1;
        break;
    case 'd':
        cybCore->habLayer[cybCore->objChosen] = 0;
        break;

        // Active mouse interaction
    case 'i':
        if(cybCore->isInteractionEnable())
        {
            cybCore->mouseOn = true;
            CybMouseInteraction* mouseInteraction = CybMouseInteraction::getInstance();
            CybInterator* mouseInterator = mouseInteraction->getMouseInterator();
            if (mouseInterator != NULL)
            {
                mouseInterator->setEnabled(true);
            }


            glutDetachMenu(GLUT_RIGHT_BUTTON);

            glutSetCursor(GLUT_CURSOR_NONE);
            CybParameters::setCollisionStatus(true);
        }
        break;

        // Deactive mouse interaction
    case 'k':
        if(cybCore->isInteractionEnable())
        {
            cybCore->mouseOn = false;
            CybMouseInteraction* mouseInteraction = CybMouseInteraction::getInstance();
            CybInterator* mouseInterator = mouseInteraction->getMouseInterator();
            if (mouseInterator != NULL)
            {
                mouseInterator->setEnabled(false);
            }
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
            CybParameters::setCollisionStatus(false);
        }
        break;

        // alpha
    case '-':
        color = cybCore->getColor(cybCore->objChosen);
        if(color[3] > 0.1)
        {
            color[3] -= 0.1;
            cybCore->setColor(cybCore->objChosen, color);
        }
        break;
    case '+':
        color = cybCore->getColor(cybCore->objChosen);
        if(color[3] < 1)
        {
            color[3] += 0.1;
            cybCore->setColor(cybCore->objChosen, color);
        }
        break;

        // exit
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

/**	Function called by the glutMouseFunc function.
@param int button
@param int state
@param int x
@param int y
@return void
*/
void Cyb3DWorld::mouseFunc(int button, int state, int x, int y)
{
    CybParameters *cybCore = CybParameters::getInstance();
    CybMouseInteraction *mouseInteraction = CybMouseInteraction::getInstance();
    CybMouseInterator* mouseInterator = mouseInteraction->getMouseInterator();

    if (mouseInterator != NULL && mouseInterator->isEnabled())
    {
        mouseInteraction->mouseInteraction(button, state, x, y);
    }
    else
    {
        Cyb3DWorld::mouse->mouse(button, state, x, y);
    }
}

/**	Function called by the glutMotionFunc function.
@param int x
@param int y
@return void
*/
void Cyb3DWorld::mouseMotionFunc(int x, int y)
{
    CybParameters *cybCore = CybParameters::getInstance();
    CybMouseInteraction *mouseInteraction = CybMouseInteraction::getInstance();
    CybMouseInterator* mouseInterator = mouseInteraction->getMouseInterator();

    if (mouseInterator != NULL && mouseInterator->isEnabled())
    {
        mouseInteraction->mouseMoveInteraction(x, y);
    }
    else
    {
        Cyb3DWorld::mouse->mouseMove(x, y);
    }
}

/**	Function called by the glutPassiveMotionFunc function.
@param int x
@param int y
@return void
*/
void Cyb3DWorld::mousePassiveMotionFunc(int x, int y)
{
    CybParameters *cybCore = CybParameters::getInstance();
    CybMouseInteraction *mouseInteraction = CybMouseInteraction::getInstance();
    CybMouseInterator* mouseInterator = mouseInteraction->getMouseInterator();

    if (mouseInterator != NULL)
    {
        if (mouseInterator->isEnabled())
        {
            mouseInteraction->mousePassiveMoveInteraction(x, y);
        }
    }
}

/**	Reshapes the objects when window is resized.
@param int width
@param int height
@return void
*/
void Cyb3DWorld::reshape(int width, int height)	// adjust
{
    CybParameters *cybCore = CybParameters::getInstance();

    cybCore->Resx = width;
    cybCore->Resy = height;
    if(width > height)
    {
        cybCore->widthProportion = (float) width/height;
        cybCore->heightProportion = 1;
        cybCore->modified = 1;
    }
    else if(width == height)
    {
        cybCore->widthProportion = 1;
        cybCore->heightProportion = 1;
        cybCore->modified = 1;
    }
    else
    {
        cybCore->widthProportion = 1;
        cybCore->heightProportion = (float) height/width;
        cybCore->modified = 1;
    }
    glViewport(0, 0, (GLint) width, (GLint) height);
    mvStack.loadIdentity();
}

/**	Special key interaction function
@param int key
@param int x
@param int y
@return void
*/
void Cyb3DWorld::specialKey(int key, int x, int y)
{
    CybParameters *cybCore = CybParameters::getInstance();

    if (key == GLUT_KEY_RIGHT)
    {
        cybCore->xTrans = cybCore->xTrans + 1;
        cybCore->transforChange = true;
    }
    if (key == GLUT_KEY_LEFT)
    {
        cybCore->xTrans = cybCore->xTrans - 1;
        cybCore->transforChange = true;
    }

    if (key == GLUT_KEY_UP)
    {
        cybCore->yTrans = cybCore->yTrans + 1;
        cybCore->transforChange = true;
    }
    if (key == GLUT_KEY_DOWN)
    {
        cybCore->yTrans = cybCore->yTrans - 1;
        cybCore->transforChange = true;
    }

    if (key == GLUT_KEY_PAGE_UP)
    {
        cybCore->zTrans = cybCore->zTrans + 1;
        cybCore->transforChange = true;
    }
    if (key == GLUT_KEY_PAGE_DOWN)
    {
        cybCore->zTrans = cybCore->zTrans - 1;
        cybCore->transforChange = true;
    }

    glutPostRedisplay();
}

void Cyb3DWorld::loadObjects()
{
	CybParameters* cybCore = CybParameters::getInstance();
	sVertex *v0, *v1, *v2;
	CybVector3D<float> aux;

	for(int j = 0; j < cybCore->numLayer; ++j){
		int l = 0;
		mfCellsIterator<cybSurfaceTriTraits> itc(cybCore->mesh[j]);
		objects.push_back(new CybTriangleBatch());
		//objects[j].begin();
		for(itc.initialize(), l = 0; itc.notFinish(); ++itc, ++l){
			v0 = cybCore->mesh[j]->getVertex(itc->getVertexId(0));
			v1 = cybCore->mesh[j]->getVertex(itc->getVertexId(1));
			v2 = cybCore->mesh[j]->getVertex(itc->getVertexId(2));
			vec3 verts[3] = {v0, v1, v2};
			vec3 norms[3];
			vec2 tc[3];
			aux = v0->getNormal();
			norms[0][0] = aux[0]; norms[0][1] = aux[1]; norms[0][2] = aux[2];
			aux = v1->getNormal();
			norms[1][0] = aux[0]; norms[1][1] = aux[1]; norms[1][2] = aux[2];
			aux = v2->getNormal();
			norms[2][0] = aux[0]; norms[2][1] = aux[1]; norms[2][2] = aux[2];
			objects[j].addTriangle(verts, norms, tc);
		}
		objects[j].end();
	}
}

void Cyb3DWorld::setAbstractDisplay(CybAbstractDisplay* d)
{
	this->d = d;
}

CybAbstractDisplay* Cyb3DWorld::getAbstractDisplay()
{
	return d;
}

void Cyb3DWorld::setDiffuseCoefficient(float k1, float k2, float k3)
{
	CybParameters* cybCore = CybParameters::getInstance();
	cybCore->Kd[0] = k1;
	cybCore->Kd[1] = k2;
	cybCore->Kd[2] = k3;
}

void Cyb3DWorld::setSpecularCoefficient(float k1, float k2, float k3)
{
	CybParameters* cybCore = CybParameters::getInstance();
	cybCore->Ks[0] = k1;
	cybCore->Ks[1] = k2;
	cybCore->Ks[2] = k3;
}



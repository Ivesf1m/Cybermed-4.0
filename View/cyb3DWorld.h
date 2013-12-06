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


#ifndef CYB3DWORLD_H_INCLUDED
#define CYB3DWORLD_H_INCLUDED

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>
#include <cybermed/cybBoxHolder.h>
#include "mf/mf.h"
#include "cybTraits.h"
#include "cybParameters.h"
#include "cybMouse.h"
#include "cybInterator.h"
#include "cybMouseInteraction.h"
#include "cybThread.h"
#include "cybPerspectiveProjection.h"
#include "cybFrame.h"
#include "cybMatrixStack.h"
#include "cybTriangleBatch.h"
#include "cybAbstractDisplay.h"

using namespace std;

typedef cybSurfaceTriTraits::sVertex sVertex;

/* Image type - contains height, width, and data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

/**
@class		Cyb3DWorld
@file		cyb3DWorld.h
@short
	3D world class.
	This class is an upgrade from the previous version, that has been being used since CyberMed 1.0.

	Obs.: The display method here is only used in cases of interaction without visualization of graphical objects.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	4.0
@date		2013, May
*/

class Cyb3DWorld
{

	private:
		static CybMouse* mouse;
		bool stereo;

	protected:
		static char *windowName;		/**< Graphic window name */
		static Cyb3DWorld* this_object; /**< Dinamic Reference */
		GLint rightWindow,leftWindow; /** For Multiple Window Classes **/
		GLenum viewMode;
		int verResolution, horResolution;
		bool defResolution;
		bool swap;

		int freePos;
		vector<CybBatch*> objects;
		CybPerspectiveProjection* frustum;
		CybFrame frame;
		CybMatrixStack mvStack, pStack;
		CybAbstractDisplay* d;

    public:
		static int viewNumber; /**< Visualization type */
		void loadObjects();
		void loadObjects2();

        /** Constructor */
        Cyb3DWorld(CybMouse* mouse = NULL, bool stereo = false, CybAbstractDisplay* d = NULL);

        /* The auxiliar functions make possible that derived classes override these methods */

        /** Auxiliar Drawing Function
        @param void
        @return void
        */
        inline static void mainDisplay();

        /** Auxiliar Reshape Function
        @param int width
        @param int height
        @return void
        */
        inline static void mainReshape(int width, int height);

        /** Auxiliar Idle Function
        @param void
        @return void
        */
        inline static void mainIdle();

        /** Auxiliar Keyboard Function
        @param unsigned char key
        @param int x
        @param int y
        @return void
        */
        inline static void mainKeyboard(unsigned char key, int x, int y);

        /** Auxiliar Special Key Function
        @param int key
        @param int x
        @param int y
        @return void
        */
        inline static void mainSpecialKey(int key, int x, int y);

        /** Auxiliar Mouse Function
        @param int button
        @param int state
        @param int x
        @param int y
        @return void
        */
        inline static void mainMouseFunc(int button, int state, int x, int y);

        /** Auxiliar Mouse Motion Function
        @param int x
        @param int y
        @return void
        */
        inline static void mainMouseMotionFunc(int x, int y);

        /** Auxiliar Passive Mouse Motion Function
        @param int key
        @param int x
        @param int y
        @return void
        */
        inline static void mainMousePassiveMotionFunc(int x, int y);

        /** Bitmap loader for 24 bit bitmaps with 1 plane only.
        See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
        @param  char* filename
        @param  Image* image
        @return int
        */
        static int ImageLoad(char *filename, Image *image);


        /** Load Bitmaps And Convert To Textures
        @param  char* path
        @param  int idTex
        @return void
        */
        static void loadBMPTexture(char* path, int idTex);


        /**	Initializes the visualization, creates the window and draws the objects.
        @param  void
        @return void
        */
        /*static */void init();

        /**	Set ambient light
        @param float r
        @param float g
        @param float b
        @param float a
        @return void
        */
        void setAmbientLight(float r, float g, float b, float a);

        /**	Set diffuse light
        * Sets the diffuse light values for the light identified by light id.
        @param int light_id
        @param float r
        @param float g
        @param float b
        @param float a
        @return void
        */
        void setDiffuseLight(int light, float r, float g, float b, float a);

        /**	Set position of light sources.
        * Sets the position of light values for the light identified by light id.
        @param int light_id
        @param float x
        @param float y
        @param float z
        @param float w
        @return void
        */
        void setLightPosition(int light, float x, float y, float z, float w);
        /**	Set number of light sources.
        @param int number_of_lights
        @return void
        */
        void setNLights(int n);

        /**	Set specular light
        * Sets the specular light values for the light identified by light id.
        @param int light_id
        @param float r
        @param float g
        @param float b
        @param float a
        @return void
        */
        void setSpecularLight(int light, float r, float g, float b, float a);


        /** Function that sets the texture file's name. To next version
        @param char *texture_file
        @return void
        */
        void setTextureFile(char *textureFile);

        /**	Function that sets the graphic window's name
        @param char *window
        @return void
        */
        void setWindowName(char *window);

        char *getWindowName();

        void enableWire();

        void disableWire();

        bool isWire();

	void setAbstractDisplay(CybAbstractDisplay* d);

	CybAbstractDisplay* getAbstractDisplay();

	void setDiffuseCoefficient(float k1, float k2, float k3);

	void setSpecularCoefficient(float k1, float k2, float k3);

    protected:
        /**	Display function.
        There's no renderization of the graphical objects in this method. It should be overrided at derived classes
        @param void
        @return void
        */

        virtual void display();

        /**	Secondary Display function.
        There's no renderization of the graphical objects in this method. It should be overrided at derived classes
        @param void
        @return void
        */

        virtual void glutIdle();

        /**	Initializes the lights' default values
        @param void
        @return void
        */
        void initLightsParameters();

        /**	Keyboard interaction function
        @param unsigned char key
        @param int x
        @param int y
        @return void
        */
        virtual void keyboard(unsigned char key, int x, int y);

        /**	Ilumination initializer function.
        @param void
        @return void
        */
        static void lights();

        /**	Function called by the glutMouseFunc function.
        @param int button
        @param int state
        @param int x
        @param int y
        @return void
        */
        virtual void mouseFunc(int button, int state, int x, int y);

        /**	Function called by the glutMotionFunc function.
        @param int x
        @param int y
        @return void
        */
        virtual void mouseMotionFunc(int x, int y);

        /**	Function called by the glutPassiveMotionFunc function.
        @param int x
        @param int y
        @return void
        */
        virtual void mousePassiveMotionFunc(int x, int y);

        /**	Reshapes the objects when window is resized.
        @param int width
        @param int height
        @return void
        */
        virtual void reshape(int width, int height);

        /**	Special key interaction function
        @param int key
        @param int x
        @param int y
        @return void
        */
        virtual void specialKey(int key, int x, int y);


        GLenum getViewMode();
};

#endif // CYB3DWORLD_H_INCLUDED

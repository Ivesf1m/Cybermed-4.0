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

#ifndef CYBPARAMETERS_H
#define CYBPARAMETERS_H
#include "GL/glew.h"
#include "GL/glut.h"
#include "GL/gl.h"
#include "mf/mfMesh.h"
#include "cybMaterialPropertyDefinitions.h"
#include "cybTraits.h"
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include "cybVector3D.h"
#include "cybVector4D.h"
#include "cybInterator.h"
#include "cybLayerListener.h"

using namespace mf;

typedef cybMesh<cybSurfaceTriTraits> sMesh;
typedef mfMesh<cybTetraTraits> sTetraMesh;
typedef cybSurfaceTriTraits::sVertex sVertex;
typedef vector<CybInterator*> tInteratorsList;
typedef list<CybLayerListener*> tLayerListeners;


/**
@class		CybParameters
@file		cybParameters.h
@short
Visualization parameters class.

Stores the visualization parameters and a copy of the object's data stored in the OF data structure.
The objects to be stored must be represented by triangular meshes.

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.5
@date		2009, November
*/
class CybParameters
{

	typedef struct Property
	{
		float stiffness;
		float damping;
		float static_friction;
		float dynamic_friction;
		float popthrough;
		float mass;
		EnumFace propertyFace[6];
		Property()
		{
			stiffness = 0.51f;
			damping = 0.3f;
			static_friction = 0.0f;
			dynamic_friction = 0.0f; 
			popthrough = 1.0f;
			mass = 1.0f;
		}
	}MaterialProperties; /** Structures that contains the haptic property representation*/
	
private: 
	static bool collisionStatus;	/**< Collision status flag */
	/*static bool systemSet;*/		/**< Indicates that system is fully set and the thread is enabled to start */
	static CybParameters singletonInstance;		/**< The unique instance*/
	
	int collisionHabilitated;		/**< Indicates which collision detection method is to be used. */
	bool keyboardOn;			/**< Indicates if keyboard use is habilitated. */
	bool interactionHabilitated;		/**< Flag that indicates if interaction is habilitated to be used. */
	bool menuHabiltated;			/**< Flag that indicates if menu is habilitated to be created. */
	
	double paralaxe;			/**< Variable that adjusts the paralaxe intensity */
	double stereoMagnitude;			/**< Variable that adjusts the stereo magnitude effect */
	
	char **layerName;			/**< Layer name for the interactive menu. */

	float xAngle;				/**< Rotation transformation parameters */
	float yAngle;				/**< Rotation transformation parameters */
	float zAngle;

	bool sceneEditable; 		/**< Indicates if the user can modify the scene layer's properties (rotation, position...) */

	CybVector4D<float> *color;			/**< Objects'color in RGBA. */			// [layer][RGBA]

	tInteratorsList interators;
	tInteratorsList::iterator it;

	tLayerListeners layerListenersList;
	tLayerListeners::iterator itLayer;

	int numInterators;			/**< Indicates number of created interators. */
	bool dualWindowActive;
	int rightWindow, leftWindow;

public:
	
	/*World Parameters*/
	int nLights;			/**< Number of lights */ //default = 1
	int nTextures; 			/**< Number of textures */ //default = 0
	char **texName;			/**< Name of the textures */
	GLuint *texture;		/**< Array to storage textures*/
	char *windowName[1];		/**< Graphic window name */
	CybVector4D<float> ambientLight;	/**< Ambient light values */
	CybVector4D<float> diffuseLight[6];	/**< Diffuse lights colors */
	CybVector4D<float> specularLight[6];	/**< Specular lights colors */
	CybVector4D<float> positionLight[6];	/**< Lights' positions */
	CybVector3D<float> Ks;			/** Specular Coefficient */
	CybVector3D<float> Kd;			/** Diffuse Coefficient */
	float Shininess;			/** Specular Shininess */
	
	
	CybVector3D<int> **v;			/**< List of triangles and index to it's coordinates. */	// [layer][idTriangle][ponto]
	CybVector3D<float> **coordList;		/**< List of coordinates */			// [camada][idPonto][eixo]
	CybVector3D<float> **vNormal;		/**< List of normal vectors of the points. */	// [camada][idPonto][eixo]
	CybVector3D<float> **vNormalCell;	/**< List of normal vectors of the cells. */ // [eixo][camada][idTriangulo]

	CybVector4D<float> *interatorColor;
	CybVector3D<float> *layerRot;		/**< Rotation transformation parameters for each individual layers. *///[axis][layer]
	CybVector3D<float> *layerTrans;		/**< Translation transformation parameters for each individual layers. */
	CybVector3D<float> *layerSca;		/**< Scale transformation parameters for each individual layers. */
//	CybVector3D<float> *interatorRot;	/**< Rotation transformation parameters for each individual interaction object. */
//	CybVector3D<float> *interatorTrans;	/**< Translation transformation parameters for each individual interaction object. */
//	CybVector3D<float> *interatorSca;	/**< Scale transformation parameters for each individual interaction object. */
//	CybVector3D<float> *interatorStartPosition;	/**< Start position of each interaction object. */
	
	int *nt;				/**< Number of triangles in the object. */
	int *nv;				/**< Number of vertexes in the object. */
	int numLayer;				/**< Number of objects. */
	int numInteractionObj;			/**< Number of interaction objects*/
	int *habLayer;				/**< Indicates if layer is habilitated to be drawn on the scene, by default, all objects are drawed at the first time. */

	int Resx;				/**< Window size parameters for x-axis */
	int Resy;				/**< Window size parameters for y-axis */
	int viewType;				/**< Visualization type (monoscopic, anaglif, polarized light or obtured). The polarized light and obtured visualizations types are not yet implemented. */
	int modified;				/**< Indicates if parameters were modified */
	int moving;				/**< Indicates if object is being rotated by mouse interaction */
	int objChosen;				/**< Indicates which object is chosen */
	float widthProportion;			/**< Reshaping proportions for the width of the window */
	float heightProportion;			/**< Reshaping proportions for the width of the window */

	float xSum;				/**< Centralization parameters for rotation transformation */
	float MinX;				/**< Centralization parameters for rotation transformation */
	float cX;				/**< Centralization parameters for rotation transformation */
	float ySum;				/**< Centralization parameters for rotation transformation */
	float MinY;				/**< Centralization parameters for rotation transformation */
	float cY;				/**< Centralization parameters for rotation transformation */
	float zSum;				/**< Centralization parameters for rotation transformation */
	float MinZ;				/**< Centralization parameters for rotation transformation */
	float cZ;				/**< Centralization parameters for rotation transformation */
	CybVector3D<float> *layerGeometricCenter;		/**< Geometric center of each leayer */

	float initialX;				/**< Mouse rotation parameters */
	float initialY;				/**< Mouse rotation parameters */
						/**< Rotation transformation parameters */
	float xTrans;				/**< Translation transformation parameters */
	float yTrans;				/**< Translation transformation parameters */
	float zTrans;				/**< Translation transformation parameters */
	float xScale;				/**< Scale transformation parameters */
	float yScale;				/**< Scale transformation parameters */
	float zScale;				/**< Scale transformation parameters */
	GLfloat **transforMatrix;		/**< Geometric Transformation Matrix */
	GLdouble modelviewMatrix[16];		/**< Modelview Matrix for calculating the interactive object's position. */
	GLdouble projectionMatrix[16];		/**< Projection Matrix for calculating the interactive object's position. */
	GLint viewportMatrix[4];		/**< Viewport Matrix for calculating the interactive object's position. */

	double leftFrustumRightEye;		/**< Frustum parameter for the right eye */
	double rightFrustumRightEye;		/**< Frustum parameter for the right eye */
	double leftFrustumLeftEye;		/**< Frustum parameter for the left eye */
	double rightFrustumLeftEye;		/**< Frustum parameter for the left eye */
	double FrustumBase;			/**< Frustum parameter */
	double FrustumTop;			/**< Frustum parameter */
	double dfNearClipDistance;		/**< Frustum parameter */
	double dfFarClipDistance;		/**< Frustum parameter */
	double dfXMidpoint;			/**< Frustum parameter */
	double dfStereoCameraOffset;		/**< Frustum parameter */
	double dfXRange;			/**< Frustum parameter */
	double camPosZ;				/**< Camera Position on z axis. */

	bool *isaloc;				/**< Indicates if coordinate list is allocated. */

	bool trackerOn;				/** Flag that shows if tracker is enable **/
	bool phantomOn;				/**< Flag that indicates if phantom is habilitated. */
	bool mouseOn;				/**< Flag that indicates if mouse is habilitated. */
	bool gloveOn;
	bool trackersPlugged[1];		/** Flag that shows if tracker device is plugger.*/
	bool hapticsPlugged[2];			/**< Flag that indicates if haptic device is on. */

	bool transforChange;			/**< Indicates if there has been a change on the geometric transformations. */
	bool interatorPosChange;		/**< Indicates if there has been a change on the interator's position. */
	bool layerInteractionChoosen;		/**< Indicates if a layer to be interacted was choosen. */

	int activeInterator;			/**< Id of the active interaction object mesh. */
	int layerInteracted;			/**< Layer to be interacted. */
	
	EnumProperty material;			/**< Material properties. */
	MaterialProperties *properties;		/**< Reference to material property data. */
	bool materialFaceModified;		/**< Indicates if material was modified. */
	bool materialContexIsEnable;		/**< Indicates if the material proporties is enabled. */
	EnumFace *activeFaces;			/**< Indicates the that is enabled for material properties*/

	sMesh **mesh;				/**< Objects mesh reference. */
	sTetraMesh **tetraMesh;
	sMesh **interatorMesh;			/**< Interaction objects mesh reference. */

	vector<int> deformableLayers;

private:
	/** Constructor */
	CybParameters();

public: 
	/** Destructor */
	~CybParameters();

	/**	Returns collision status.
	@param void
	@return bool
	*/
	static bool getCollisionStatus();

	/**	Sets collision status.
	@param bool
	@return void
	*/
	static void setCollisionStatus(bool status);
	
	/**	Return the singleton instance of CybParameters.
	@param void
	@return CybParameters
	 */
	static CybParameters *getInstance();
	
	/**	Stores the triangles' coordinates of the layer identified by id.
	@param int Layer_id
	@param float point_1
	@param float point_2
	@param float point_3
	@return void
	*/
	void addTriangle(int idLayer, int p1, int p2, int p3);

	/**	Add a vertex to the vertex list of a layer identified by Layer_id.
	@param int Layer_id
	@param float vertex_x_coord
	@param float vertex_y_coord
	@param float vertex_z_coord
	@return void
	*/
	void addVertex(int idLayer, float x, float y, float z);

	/**	Visualization parameters inicializer.
	@param void
	@return void
	*/
	void initParameters();

	/**	Sets which type collision method to be used.
	@param int collision_detection_type
	@return void
	*/
	void setCollisionHabilitated(int collisionType);

	/**	Stores the color values for the layers.
	@param float *color[3]
	@return void
	*/
	void setColor(CybVector4D<float> *colors);
	
	/**	Stores the color values for the layers.
	@param int layerID
	@param float r
	@param float g
	@param float b
	@param float a
	@return void
	 */
	void setColor(int layerID, float r, float g, float b, float a);
	

	void setColor(int layer, CybVector4D<float> color);

	/**	Function that deactivates the interaction
	@param void
	@return void
	 */
	void setInteractionOff();
	
	/**	Function that activates the interaction
	@param void
	@return void
	 */
	void setInteractionOn();
	
	/**	Verify if the interaction is enable
	@param void
	@return bool
	 */
	bool isInteractionEnable();

	bool isSceneEditable();

	void setSceneEditable(bool editable);

	/**	Function that deactivates the use of keyboard
	@param void
	@return void
	 */
	void setKeyboardOff();
	
	/**	Function that activates the use of keyboard
	@param void
	@return void
	 */
	void setKeyboardOn();
	
	/**	Verify if the keyboard is enable
	@param void
	@return bool
	 */
	bool isKeyboardEnable();

	void setAngle(float xAngle, float yAngle, float zAngle);

	/**	Sets a layer's rotation transformation parameters.
	@param int Layer_id
	@param float x_coord
	@param float y_coord
	@param float z_coord
	@return void
	*/
	void setLayerRotation(int layerId, float x, float y, float z);
	
	/**	Sets a layer's scale transformation parameters.
	@param int Layer_id
	@param float x_coord
	@param float y_coord
	@param float z_coord
	@return void
	*/
	void setLayerScale(int layerId, float x, float y, float z);

	/**	Sets a layer's translation transformation parameters.
	@param int Layer_id
	@param float x_coord
	@param float y_coord
	@param float z_coord
	@return void
	*/
	void setLayerTranslation(int layerId, float x, float y, float z);

	/**	Sets a interator's rotation transformation parameters.
	@param int interator_id
	@param float x_coord
	@param float y_coord
	@param float z_coord
	@return void
	*/
	//void setInteratorRotation(int interatorId, float x, float y, float z);

	/**	Sets a interator's scale transformation parameters.
	@param int interator_id
	@param float x_coord
	@param float y_coord
	@param float z_coord
	@return void
	*/
	//void setInteratorScale(int interatorId, float x, float y, float z);

	/**	Sets a interator's translation transformation parameters.
	@param int interator_id
	@param float x_coord
	@param float y_coord
	@param float z_coord
	@return void
	*/
	//void setInteratorTranslation(int interatorId, float x, float y, float z);

	/**	Function that deactivates the menu
	@param void
	@return void
	*/
	void setMenuOff();
	
	/**	Function that activates the menu
	@param void
	@return void
	 */
	void setMenuOn();
	
	/**	Function that activates the menu
	@param void
	@return void
	 */
	bool isMenuOn();

	/**	Function that sets the values of paralaxe
	@param double paralaxe
	@return void
	*/
	void setParalaxe(double paralaxe);
	
	/**	Function that sets the values of the stereo magnitude
	@param double stereoMagnitude
	@return void
	*/
	void setStereoMagnitude(double stereoMagnitude);

	CybVector4D<float> getColor(int layer);

	float getXAngle();

	float getYAngle();

	float getZAngle();

	/**	Function that get the values of paralaxe 
	@param void 
	@return float
	 */
	double getParalaxe();
	
	/**	Function that get the values of magnitude 
	@param void 
	@return float
	 */
	double getStereoMagnitude();
	
	/**	Function that set the name of a layer
	@param void 
	@return float
	 */	
	void setLayerName(char *stringName, int numLayer);
	
	/**	Function that get the name of a layer
	@param void 
	@return float
	 */	
	char *getLayerName(int numLayer);


	/**	Sets the initial size of the data.
	@param int Number_of_triangles
	@param int Number_of_vertexes
	@param int Layer_id
	@return void
	*/
	void setSizeOfData(int triangles, int vertex, int idLayer);

	/**	Stores the Vertexes Normal Vectors of the layer identified by id.
	@param ofMesh<ofDefaultSurface> mesh
	@param int idLayer
	@return void
	*/
	void setVertexNormalVector(sMesh *_mesh, int idLayer);

	/**	Sets the window dimensions
	@param int window_x
	@param int window_y
	@return void
	*/
	void setWindowSize(int windowX, int windowY);

	/**	Starts CybParameters with alocations of its atributes.
	@param void
	@return void
	*/
	void startParameters();

	/** 
	 Calculates stereo parameters. This method is called when the stereoscopics data is initialize or when the stereo magnitude
	 or paralaxe are changed.
	@param double dfLeftBorder
	@param double dfRightBorder
	@param double dfBottomBorder
	@param double dfTopBorder
	@param double dfNearBorder
	@param double dfFarBorder
	@param double dfTargetPlane
	@param double dfCameraToTargetDistance
	@param double dfStereoMagnitudeAdj
	@param double dfParallaxBalanceAdj
	@return double
	*/
	double StereoProjection(double dfLeftBorder, double dfRightBorder, double dfBottomBorder,
				double dfTopBorder, double dfNearBorder, double dfFarBorder,
				double dfTargetPlane, double dfCameraToTargetDistance,
				double dfStereoMagnitudeAdj, double dfParallaxBalanceAdj);

	/** Create context for material property 
	@param int numLayers
	@return void 
	 */
	void createMaterialPropertyContext(int _numlayer);

	/** Aloc and initialize the material properties parameters
	@param int numLayers
	@return void 
	 */
	void genMaterialProperties(int _numlayer);
	
	/** Indicates if the material context was created
	@return bool
	 */
	bool materialPropertyContextCreated();
		
	/** Indicates when a property face was modified
	@return bool
	 */
	bool propertyFaceModified();
	
	/** Set value of the specifc material property
	@param int layer 
	@param EnumProperty property
	@param float value
	@return void 
	 */
	void setMaterialPropertyValue(int layer, EnumProperty property, float value);
	
	/** Get value of the specif material property
	@param int layer
	@param EnumProperty property
	@return float
	 */
	float getMaterialPropertyValue(int layer, EnumProperty property);

	/** Set face that material property will be enabled
	@param int layer
	@param EnumFace face 
	@return void
	 */	
	void setLayerFace(int layer, EnumFace face);

	/** Get face that material property will be enabled
	@param int layer
	@return EnumFace
	 */
	EnumFace getLayerFace(int layer);

	/** Set face that material property will be applied
	@param int layer
	@param EnumProperty property
	@param EnumFace face 
	@return void
	 */
	void setMaterialFace(int layer, EnumProperty property, EnumFace face);

	/** Get the face of material property
	@param int layer
	@param EnumProperty property
	@return EnumFace 
	 */	
	EnumFace getMaterialFace(int layer, EnumProperty property);

	/** Allocate space for the texture parameters
	@param int numberOfTextures
	@return void
	 */
	void createTextures(int numTextures);
	
	/** Get the list of interators in the environment.
	 * @return Vector<CybInterator> list of interators.
	 */
	tInteratorsList getInteratorList();

	/**
	 *
	 */
	CybInterator* getInterator(int idInterator);

	int getNumInterators();

	/** Add an interator to the interator's list.
	 * @return void
	 */
	void addInterator(CybInterator* interator);

	/** Remove an interator from the list.
	 * @param CybInterator interator
	 */
	void removeInterator(CybInterator* interator);

	void addLayerListener(CybLayerListener* listener);

	void addDeformableLayer(int numLayer);

	void removeDeformableLayer(int numLayer);

	bool isDeformableLayer(int numLayer);
	
	void changeDualWindowState(bool state);

	bool isDualWindowContextActive();

	int getLeftWindow();
	
	int getRightWindow();

	void setRightWindow(int identifier);

	void setLeftWindow(int identifier);
	
private:
	/**	Alocates the memory space for storing data of the layer identified by id.
	@param int number_of_triangles
	@param int number_of_vertexes
	@param int Layer_id
	@return void
	*/
	void aloc(int triangles, int vertex, int idLayer);

	/**	Alocates the memory space for storing data about the layers.
	@param void
	@return void
	*/
	void alocParameters();

	/**	Dealocates the stored data of the layer identified by id.
	@param int Layer_id
	@return void
	*/
	void daloc(int idLayer);

};

#endif

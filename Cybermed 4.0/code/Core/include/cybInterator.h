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

#ifndef CYBINTERATOR_H
#define CYBINTERATOR_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <list>
#include "cybDevice.h"
#include "cybInteratorListener.h"
#include <cybermed/cybVector3D.h>
#include <cybermed/cybVector4D.h>
#include "mf/mfMesh.h"
#include "cybTraits.h"
#include "cybModel.h"

//Obs: Esses mesmos valores estão definidos no cybInteratorFactory.h
#define MOUSE_INTERATOR 0
#define HAPTIC_INTERATOR 1
#define TRACKER_INTERATOR 2
#define REMOTE_INTERATOR 3
#define REMOTE_HAPTIC_INTERATOR 4
#define TRACKER_HAAR_INTERATOR 5
#define TRACKER_BLOB_INTERATOR 6
#define GLOVE_5DT_INTERATOR 7
#define REMOTE_GLOVE_INTERATOR 8


using namespace mf;

typedef cybSurfaceTriTraits::sVertex sVertex;
typedef list<CybInteratorListener*> tInteratorListeners;


/**
@class		CybInterator 
@file		cybInterator.h 
@short
	Interactivce object's data class

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	1.0
@date		2007, July
*/
class CybInterator
{
private:
	int id;
	int activeMesh;
	bool activeMeshChange;
	int graphicObjectId;
	CybVector3D<float> lastPosition;
	CybVector3D<float> lastRotation;
	CybVector3D<float> position;
	CybVector3D<float> orientation;
	cybMesh<cybSurfaceTriTraits> *interatorMesh;
	cybMesh<cybSurfaceTriTraits> interatorMesh2;
	tInteratorListeners listenersList;
	tInteratorListeners::iterator it;
	bool enabled;
	CybModel *models; /*Some devices utilize this object in your interator class intead of interatorMesh*/

	CybVector3D<float> interatorRot;	/**< Rotation transformation parameters for each individual interaction object. */
	CybVector3D<float> interatorTrans;	/**< Translation transformation parameters for each individual interaction object. */
	CybVector3D<float> interatorSca;	/**< Scale transformation parameters for each individual interaction object. */
	CybVector3D<float> interatorStartPosition;	/**< Start position of each interaction object. */

	CybVector4D<float> interatorColor;

	int interatorType;

protected:
	void setPosition(float x, float y, float z);

	void setInteratorType(int type);

public:

	CybInterator();

	/**
	 *
	 */
	virtual CybDevice* getDevice() = 0;

	/**
	 *
	 */
	virtual void create(int id) = 0;
	
	/**
	 *
	 */
	virtual void destroy() = 0;
	
	/**
	 *
	 */
	virtual void drawInterator();


	void addListener(CybInteratorListener* listener);

	CybVector3D<float> getRotation();
	CybVector3D<float> getScale();
	CybVector3D<float> getTranslation();
	CybVector4D<float> getColor();

	CybVector3D<float> getPosition();
	CybVector3D<float> getStartPosition();
	CybVector3D<float> getOrientation();
	cybMesh<cybSurfaceTriTraits>* getMesh(int idMesh);
	CybModel *getCybModel();

	int getId();
	int getGraphicObjectId();
	int getInteratorType();
	int getActiveMesh();
	bool isEnabled();
	bool isActiveMeshChange();

	void setRotation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setTranslation(float x, float y, float z);
	void setId(int id);
	void setGraphicObjectId(int graphicObjectId);
	void setEnabled(bool enabled);
	void setAttribute(float x, float y, float z);
	void setMesh(int idMesh, cybMesh<cybSurfaceTriTraits>* interatorMesh);
	void setColor(float r, float g, float b, float alfa);
	void setActiveMesh(int idMesh);
	void setActiveMeshChange(bool change);
	void setCybModel(CybModel *m);

	void restartMesh();

	virtual ~CybInterator();

};

#endif

/*
 * CybTrackerInterator.cpp
 *
 *  Created on: Feb 4, 2010
 *      Author: brunorasales
 */

#include "cybTrackerInterator.h"

CybTrackerInterator::CybTrackerInterator(std::string type) {

#ifdef CYBOPTICALTRACKER_H	
	if(type.compare("haar") == 0){
	  this->trackerDevice = new CybHaarTracker();
	}
	else if (type.compare("blob") == 0) {
		this->trackerDevice = new CybBlobTracker();
	}
#endif //CYBOPTICALTRACKER_H	
#ifdef CYBMAGNETICTRACKER_H
	if (type.compare("magnetic") == 0) {
		this->trackerDevice = new CybFOB6DOFTracker();
	}
#endif //CYBMAGNETICTRACKER_H
	else {
	  std::cout << "[Warning]: Failed when trying create a tracker!"<< std::endl;
	}
	
}

void CybTrackerInterator::create(int id) {
	setId(id);
	setEnabled(true);
	this->trackerDevice->initDevice();
}

void CybTrackerInterator::destroy() {
	this->trackerDevice->stopDevice();
}

void CybTrackerInterator::drawInterator() {
	drawTrackerCursor();
}

/**	Function responsible for drawing interator object when tracker is enable.
		@param void
		@return void
 */
void CybTrackerInterator::drawTrackerCursor()
{
	//cout << "drawTrackerCursor()" << endl;

	CybParameters *cybCore = CybParameters::getInstance();

	static const double kCursorRadius = 0.5;
	static const double kCursorHeight = 1.5;
	static const int kCursorTess = 15;
	float currentPosition[3];
	float initialPosition[3] = {0,0,0};
	GLfloat  matrix[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	static bool calcIsNeed = true;
	static GLuint gCursorDisplayList = 0;
	//int index = cybCore->activeInterator;	// Interator object actived
	int l;
	sVertex *v0, *v1, *v2;

	GLUquadricObj *qobj = 0;

	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
	glPushMatrix();

	if (!gCursorDisplayList || isActiveMeshChange())
	{
		gCursorDisplayList = glGenLists(1);
		glNewList(gCursorDisplayList, GL_COMPILE);
		qobj = gluNewQuadric();


		if(isEnabled()) // interator object from file
		{

			CybVector4D<float> color 	 = getColor();
			CybVector3D<float> startPosition = getStartPosition();
			CybVector3D<float> translation 	 = getTranslation();
			CybVector3D<float> rotation    	 = getRotation();
			CybVector3D<float> scale	 = getScale();
			CybVector3D<float> position	 = getPosition();

			cybMesh<cybTraits>* mesh = getMesh(getActiveMesh());

			ofCellsIterator<cybTraits> cellsIterator(mesh);
			glColor4f(color[0], color[1], color[2], color[3]);

			// transformations
			glScaled(scale[0], scale[1], scale[2]);
			glTranslated(position[0] + translation[0], position[1] + translation[1], position[2]+ translation[2]);

			glTranslated(-startPosition[0], -startPosition[1], -startPosition[3]);

			glRotated(rotation[0],1,0,0);
			glRotated(rotation[1],0,1,0);
			glRotated(rotation[2],0,0,1);
			glTranslated(startPosition[0], startPosition[1], startPosition[3]);

			for(cellsIterator.initialize(); cellsIterator.notFinish(); ++cellsIterator)
			{
				v0 = mesh->getVertex(cellsIterator->getVertexId(0));
				v1 = mesh->getVertex(cellsIterator->getVertexId(1));
				v2 = mesh->getVertex(cellsIterator->getVertexId(2));

				glBegin(GL_TRIANGLES);
				glNormal3f(v0->getVNormalCoord(0), v0->getVNormalCoord(1), v0->getVNormalCoord(2));
				glVertex3f(v0->getCoord(0), v0->getCoord(1), v0->getCoord(2));

				glNormal3f(v1->getVNormalCoord(0), v1->getVNormalCoord(1), v1->getVNormalCoord(2));
				glVertex3f(v1->getCoord(0), v1->getCoord(1), v1->getCoord(2));

				glNormal3f(v2->getVNormalCoord(0), v2->getVNormalCoord(1), v2->getVNormalCoord(2));
				glVertex3f(v2->getCoord(0), v2->getCoord(1), v2->getCoord(2));
				glEnd();
			}
		}
		gluDeleteQuadric(qobj);
		glEndList();
		setActiveMeshChange(false);
	}

	// Get the proxy transform in world coordinates.
	trackerDevice->getMatrix(matrix);
	trackerDevice->getInitialPosition(initialPosition);
	trackerDevice->getPosition(currentPosition);


	glTranslatef(initialPosition[0],initialPosition[1],initialPosition[2]-1);
	glMultMatrixf(matrix);

	// Apply the local cursor scale factor.
	/*glScaled(CybInterator::getInstance()->hapticDevice.getHapticScaleFactor(),
				CybInterator::getInstance()->hapticDevice.getHapticScaleFactor(),
				CybInterator::getInstance()->hapticDevice.getHapticScaleFactor());
	 */
	if(calcIsNeed )
	{
		setPosition(currentPosition[0] + initialPosition[0], currentPosition[1] + initialPosition[1], currentPosition[2] + initialPosition[2]);

		glGetFloatv(GL_MODELVIEW_MATRIX, cybCore->transforMatrix[0]);
		calcIsNeed = false;
	}
	else
		calcIsNeed = true;

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0, 0.5, 1.0);

	glCallList(gCursorDisplayList);

	glPopMatrix();
	glPopAttrib();
}


CybDevice* CybTrackerInterator::getDevice() {
	return this->trackerDevice;
}


CybTrackerInterator::~CybTrackerInterator() {
	// TODO Auto-generated destructor stub
}

CybInterator* CybTrackerInterator::getInterator(int interatorType){

    //A ser testado

    CybInterator* interator = new CybInterator();
    
    CybParameters *cybCore = CybParameters::getInstance();

    switch(interatorType){
    
    #ifdef CYBOPTICALTRACKER_H
		case TRACKER_HAAR_INTERATOR:
			interator = new CybTrackerInterator("haar");
			cybCore->addInterator(interator);
		break;

		case TRACKER_BLOB_INTERATOR:
			interator = new CybTrackerInterator("blob");
			cybCore->addInterator(interator);
		break;
    #endif //CYBOPTICALTRACKER_H

    #ifdef CYBMAGNETICTRACKER_H
		case TRACKER_MAGNETIC_INTERATOR:
			interator = new CybTrackerInterator("magnetic");
			cybCore->addInterator(interator);
		break;
    #endif //CYBMAGNETICTRACKER_H
        default:
            return NULL;
    
    }
    
    return interator;
}

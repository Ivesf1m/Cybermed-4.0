// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#ifndef CYBCOLLABORATION_H
#define CYBCOLLABORATION_H

#define MAX_INTEGRANTS 20
#define PORT_DEFAULT 3333

#include "cybCollaborationPerformance.h"
#include "cybCollaborationProperties.h"
#include <cybermed/cybInterator.h>
#include <cybermed/cybInteratorListener.h>
//#include <cybermed/cybInteratorFactory.h>
#include <cybermed/cybNode.h>
#include <cybermed/cybNodeAddress.h>
#include <cybermed/cybReceiverThread.h>
#include <cybermed/cybReceiverThreadListener.h>
#include <cybermed/cybParameters.h>
#include <cybermed/CybDataObtainer.h>
#include <cybermed/cybMouse.h>
#include <cybermed/cybMouseListener.h>

#include "cybModelCollaboration.h"

#include "cybRemoteModel.h"
#include "cybRemoteModelFactory.h"
#include "cybRemoteInterator.h"
#include "cybRemoteHapticInterator.h"
#include "cybRemoteGloveInterator.h"

#include "cybGloveProcessInterator.h"
#include "cybHapticProcessInterator.h"


#ifdef CYBCOLLISION_H
	#include <cybermed/cybSphereTriangle.h>
#endif

#ifdef CYBDEFORMATION_H
	#include <cybermed/cybMassSpring.h>
#endif

#include "cybCollaborationIntegrant.h"
#include <sstream>
#include <list>

typedef list<CybCollaborationIntegrant*> tIntegrantsList;
typedef CybDataObtainer<cybSurfaceTriTraits> cybDObtainer;


typedef enum tMessageType {
	JOIN_REQUEST 		  = 0,
	LEAVE_REQUEST 		  = 1,
	SCENE_CONFIGURATION 	  = 2,
	INTERATOR_POSITION_CHANGE = 3,
	INTERATOR_ROTATION_CHANGE = 4,
	LAYER_POSITION_CHANGE 	  = 5,
	LAYER_ROTATION_CHANGE 	  = 6,
	LAYER_COLOR_CHANGE	  = 7,
	ACCEPT			  = 8,
} tMessageType;

/**
@class		CybCollaboration
@file		cybCollaboration.h
@short
Collaboration class.

Provides operations that can be used by every collaboration types

@author		LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
@version	2.0
@date		2010, May
*/

/*using namespace std;
std::string s;
std::stringstream out;*/

class CybCollaboration : public CybReceiverThreadListener, public CybMouseListener, public CybInteratorListener, public CybLayerListener {
public:
	
	void setModelFactory(CybRemoteModelFactory *modelFactory) {
		pModelFactory = modelFactory;
	}
	
	/** Constructor
	 * 	@param int port
	 */
	CybCollaboration(int port = PORT_DEFAULT, int communicationType = MULTICAST, const char *multicastGroupIP = "244.0.0.1");

	/** Constructor
	 *	@param int port
	 *	@param int objectManagerType the object manager type of the collaboration.
	 */
	CybCollaboration(int port, int objectManagerType, int communicationType, const char *multicastGroupIP = "244.0.0.1");

	/** Constructor
	 * 	@param int port
	 * 	@param CybCollaborationProperties* properties a pointer to the collaboration properties object.
	 */
	CybCollaboration(int port, CybCollaborationProperties* properties, int communicationType, const char *multicastGroupIP = "244.0.0.1");

	/**
	 * Adds an integrant to the collaboration.
	 * @param CybCollaborationIntegrant* pointer to the integrant to be added.
	 * @param int interatorType interator type of the new integrant.
	 */
	void addIntegrant(CybCollaborationIntegrant* integrant, int interatorType);

	/**
	 * Adds an integrant to the collaboration.
	 * @param const char* integrant's address.
	 * @param const short port number.
	 */
	bool addIntegrant(const char* ip, const short port = PORT_DEFAULT);

	/**
	 * Adds an integrant to the collaboration.
	 * @param const char* integrant's name.
	 * @param const char* integrant's address.
	 * @param const short port number.
	*/
	bool addIntegrant(const char* name, const char* ip, const short port = PORT_DEFAULT);

	/**
	 * Adds an integrant to the collaboration
	 */
	//virtual void addIntegrant(CybCollaborationIntegrant* integrant);

	/**
	 * Remove an integrant from the collaboration.
	 * @param char* integrant's address.
	 */
	bool removeIntegrant(char* ip);

	/**
	 * Remove an integrant from the collaboration.
	 * @param int integrant's index.
	*/
	bool removeIntegrant(int index);

	/**
	 * Remove an integrant from the collaboration.
	 * param CybCollaborationIntegrant* integrant
	 */
	bool removeIntegrant(CybCollaborationIntegrant* integrant);

	/**
	 * Create a collaboration and wait for participants.
	 */
	virtual bool createCollaboration(int serverInteratorModel);

	/**
	 * This method must to be implemented by the subclasses to return the main interator of the collaboration.
	 */
	virtual CybInterator* getMainInterator() = 0;

	/**
	 * Creates a remoteInterator of a specific type.
	 * @param int interatorType the type of the remoteInterator.
	 */
	virtual CybRemoteInterator* getRemoteInterator(int interatorType);

	void activeCollision();

#ifdef CYBDEFORMATION_H
	void activeDeformation(EnumDefMode type);
#endif

	bool isCollisionActive();

	/**
	 * Join an existing collaboration.
	 * @return
	 */
	virtual bool joinCollab(string name, int clientInteratorModel, string serverIp, short int serverPort);

	/**
	 * Send data to all participanting users based on the communication type parameter passed 
	 * @return
	 * @param char* buffer to send data
	 * @param int bufferLen 
	 * @param int communicationType (UNICAST_UDP or MULTICAST)
	 */
	void sendDataToAll(char* buffer, int bufferLen, int communicationType);	

	/**
	 * Listen to network events.
	 * @param char* buffer pointer to arrived data.
	 * @param CybNodeAddress address address of the data sender.
	 */
	virtual void eventPerformed(char* buffer, CybNodeAddress address);

	/**
	 * Listen to mouse events.
	 * @param float x position x.
	 * @param float y position y.
	 */
	virtual void mouseEventPerformed(float x, float y);

	/**
	 * Listen to interator position events.
	 * @param float x position x.
	 * @param float y position y.
	 * @param float z position z.
	 */
	virtual void interatorPositionEventPerformed(float x, float y, float z);

	/**
	 * Listen to interator rotation events.
	 * @param float x rotation x.
	 * @param float y rotation y.
	 * @param float z rotation z.
	 */
	virtual void interatorRotationEventPerformed(float x, float y, float z);

	/**
	 * Listen to layer color events.
	 * @param int layer the layer changed.
	 * @param float r red.
	 * @param float g green.
	 * @param float b blue.
	 * @param float a transparency.
	 */
	virtual void layerColorEventPerformed(int layer, float r, float g, float b, float a);

	/**
	 *
	 */
	CybInterator* getInterator();

	/**
	 * Gets the collaboration integrants.
	 */
	tIntegrantsList getIntegrants();

	/**
	 * Gets the port number.
	 */
	int getPort();

	CybCollaborationPerformance* getCollaborationPerformance();

	/**
	 * Gets a pointer to the collaboration prperties object.
	 */
	CybCollaborationProperties* getCollaborationProperties();

	/**
	 * Sets the port number
	 */
	void setPort(int port);

	/** */
	void setDataObtainer(cybDObtainer* data);

	/** */
	void setMainInterator(CybInterator* mainInterator);

	/** */
	void setInteratorModel(char* file);	

	/** */
	void setCybNode(CybNode* node);	
	
	
	/** Destructor */
	virtual ~CybCollaboration();
		
protected:
	CybReceiverThread* receiver;
	CybNode* node;
	tIntegrantsList integrants;
	tIntegrantsList::iterator it;
	CybParameters* cybCore;
	CybMouse* mouse;
	CybInterator* mainInterator;
	cybDObtainer* data;
	CybCollaborationProperties* properties;
	CybCollaborationPerformance *performance; // instance for count network traffic

#ifdef CYBCOLLISION_H
	CybSphereTriangle* collision;
#endif

	virtual void processJoinRequestMsg(char* buffer, string ipStr, short int port);

	virtual void processSceneConfigMsg(char* buffer, string ipStr, short int port);

	virtual void processInteratorPositionChangeMsg(char* buffer, string ipStr, short int port);

	virtual void processInteratorRotationChangeMsg(char* buffer, string ipStr, short int port);

	virtual void processLayerPositionChangeMsg(char* buffer);

	virtual void processLayerRotationChangeMsg(char* buffer);

	virtual void processLayerColorChangeMsg(char* buffer);

	void localActiveDeformation(CybInterator* interator);

private:
	int port;

	char* interatorModel;
	int idInteratorModel; // ID of server's interator model
	bool collisionStatus;
	bool deformationStatus;
	bool isDebugOn; // flag to control debug	
	CybRemoteModelFactory *pModelFactory;	

#ifdef CYBDEFORMATION_H
	EnumDefMode defMode;
#endif
	/**
	 * Verifica se o ip passado como parâmetro corresponde ao formato correto.
	 * @ip ip a ser validado.
	 */
	bool validaIP(const char* ip);

};

#endif /* CYBCOLLABORATION_H */


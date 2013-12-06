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
#include "cybCollaboration.h"


CybCollaboration::CybCollaboration(int port, int communicationType, const char *multicastGroupIP) {
	this->port = port;
	this->performance = new CybCollaborationPerformance(); 

	this->cybCore = CybParameters::getInstance();
	this->mouse = CybMouse::getInstance();

	this->data = NULL;
	this->mainInterator = NULL;

	// Gets a socket based on type of comunication specified
	this->node = CybNodeFactory::getNode(communicationType, getPort(), multicastGroupIP);

	if (communicationType == MULTICAST) {
		CybMulticastPeer *serverNode = (CybMulticastPeer*) this->node;
		serverNode->setLoopbackOption(0); // Also receive sent packets
	}

	this->receiver = new CybReceiverThread(node);
	mouse->addMouseListener(this);

	collisionStatus = false;

	this->interatorModel = NULL; //"esfera.wrl";
	deformationStatus = false;

	// Set properties of collaboration (integrants, network communication and object management types)
	this->properties = new CybCollaborationProperties(BLOCK_OBJECT_MANAGER, this->node);
	properties->setCommunicationType(communicationType);
	properties->setIntegrants(&integrants);
	this->isDebugOn = true;
}

/** Constructor
 *
 */
CybCollaboration::CybCollaboration(int port, int objectManagerType, int communicationType, const char *multicastGroupIP) {
	this->port = port;

	this->cybCore = CybParameters::getInstance();
	this->mouse = CybMouse::getInstance();

	// Gets a socket based on type of comunication 	
	this->node = CybNodeFactory::getNode(communicationType, getPort(), multicastGroupIP);

	// Sets the option of receiving all data from group
	if (communicationType == MULTICAST) {
		CybMulticastPeer *serverNode = (CybMulticastPeer*) this->node;
		serverNode->setLoopbackOption(0); // Also receive sent packets
	}

	this->receiver = new CybReceiverThread(node);

	mouse->addMouseListener(this);

	collisionStatus = false;

	this->interatorModel = NULL; //"esfera.wrl";
	deformationStatus = false;

	// Set properties of collaboration (integrants, network communication and object management types)
	this->properties = new CybCollaborationProperties(objectManagerType, this->node);
	properties->setIntegrants(&integrants);
	properties->setCommunicationType(communicationType);
	this->isDebugOn = true;
}

/** Constructor
 *
 */
CybCollaboration::CybCollaboration(int port, CybCollaborationProperties* properties, int communicationType, const char *multicastGroupIP) {
	this->port = port;

	this->cybCore = CybParameters::getInstance();
	this->mouse = CybMouse::getInstance();


	this->node = CybNodeFactory::getNode(communicationType, getPort(), multicastGroupIP);

	if (communicationType == MULTICAST) {
		CybMulticastPeer *serverNode = (CybMulticastPeer*) this->node;
		serverNode->setLoopbackOption(0);
	}

	this->receiver = new CybReceiverThread(node);

	mouse->addMouseListener(this);

	collisionStatus = false;

	this->interatorModel = NULL; //"esfera.wrl";
	deformationStatus = false;

	properties->setIntegrants(&integrants);
	properties->setCommunicationType(communicationType);
	this->properties = properties;
	this->isDebugOn = true;
}


bool CybCollaboration::createCollaboration(int serverInteratorModel) {

	this->idInteratorModel = serverInteratorModel;
	this->properties->setObjectFree(true);
	this->mainInterator = getMainInterator();

	mainInterator->setColor(1, 0, 0, 1);
	mainInterator->addListener(this);

	cybCore->addLayerListener(this);

	receiver->setBufferSize(200);
	receiver->addListener(this);
	receiver->addListener(properties);
	receiver->init();
}

//******** Receive an integrant and his interator type for locally create and start it **********

void CybCollaboration::addIntegrant(CybCollaborationIntegrant* integrant, int interatorType) {
	
	CybRemoteInterator* interator = getRemoteInterator(interatorType);
	CybRemoteModel *pCollabModel = pModelFactory->getModel(integrant->getIdInteratorModel());

	if (CybRemoteModel::CYBMODEL == pCollabModel->getTypeModel()) {
		data->loadInteratorModel(interator->getId(), pCollabModel->getCybModel());
	}
	else {
		data->loadInteratorModel(interator->getId(), 0, const_cast<char *>(pCollabModel->getModel().c_str()));
		data->startInterator(interator->getId(), 0);	
		interator->setColor(0, 1, 0, 1);	
	}
	integrant->setInterator(interator);
	this->integrants.push_back(integrant);

#ifdef CYBCOLLISION_H
	if (collisionStatus) {
		localActiveCollision(true, 0, interator);
	}
#endif
}

CybRemoteInterator* CybCollaboration::getRemoteInterator(int interatorType) {

    // falta testar!!!
	CybRemoteInterator* remoteInterator;

	switch (interatorType) {
		case MOUSE_INTERATOR: case REMOTE_INTERATOR:
			remoteInterator = CybRemoteInterator::getInterator();
			remoteInterator->create(cybCore->getNumInterators() - 1);
		break;

		case HAPTIC_INTERATOR: case REMOTE_HAPTIC_INTERATOR:
			remoteInterator = CybRemoteHapticInterator::getInterator();
			remoteInterator->create(cybCore->getNumInterators() - 1);
		break;

		case TRACKER_INTERATOR:
		break;
		
		case REMOTE_GLOVE_INTERATOR: case GLOVE_5DT_INTERATOR:
			remoteInterator = CybRemoteGloveInterator::getInterator(); 
			remoteInterator->create(cybCore->getNumInterators() - 1);
		break;
	
	}
	return remoteInterator;
}

bool CybCollaboration::removeIntegrant(char* ip) {

}

bool CybCollaboration::removeIntegrant(int index) {
	/*
	 if (index < MAX_INTEGRANTS) {
		integrants[index] = NULL;
		for (int i = index; i <= lastIntegrant; i++) {
			integrants[i] = integrants[i+1];
		}
		lastIntegrant--;
	}
	*/
}


bool CybCollaboration::removeIntegrant(CybCollaborationIntegrant* integrant) {

}

void CybCollaboration::sendDataToAll(char *buffer, int bufferLen, int netCommunicationType) {

	char type = buffer[0];

	if (netCommunicationType == MULTICAST) {
		CybMulticastPeer *serverNode = (CybMulticastPeer*) node;
		serverNode->sendMulticastData(buffer, bufferLen);
   		performance->countTrafficSent(type, bufferLen);

	} else if (netCommunicationType == UNICAST_UDP) {

		CybUDPServer *serverNode = (CybUDPServer*) node;

		for (it = integrants.begin(); it != integrants.end(); ++it) {
			CybNodeAddress* addr = (*it)->getAddress();
			try {
		  	     serverNode->sendData(buffer, bufferLen, addr);			    
			} catch (CybCommunicationException e) {
			     e.showErrorMessage();
			}			     	
		     performance->countTrafficSent(type, bufferLen);	
		}
	}
}

bool CybCollaboration::joinCollab(string name, int clientInteratorModel, string serverIp, short int serverPort) {
	
	int nameLen = name.length();

	// Instanciate and configure the mainInterator to be used
	this->mainInterator = getMainInterator();
	mainInterator->addListener(this);
	mainInterator->setColor(1, 0, 0, 1);

	CybNodeAddress* address = new CybNodeAddress(serverPort, serverIp.c_str(), AF_INET);

	/*********** Mouting the JOIN_REQUEST packet for require participation ***************/
	
	char buffer[100]; // buffer to storage the data
	memset(buffer, 0, 100);

	int pos = 0; // flag for access the packet fields
	buffer[pos++] = JOIN_REQUEST; // packet type flag

	int type = mainInterator->getInteratorType();

	memcpy(buffer + pos, &type, sizeof(int)); //name length
	pos += sizeof(int);

	memcpy(buffer + pos, &nameLen, sizeof(int)); //name length
	pos += sizeof(int);
	
	memcpy(buffer + pos, &clientInteratorModel, sizeof(int)); //type of interator model
	pos += sizeof(int);

	memcpy(buffer + pos, name.c_str(), nameLen); //integrant name
	pos += nameLen;
	
	/***************************************************************************************/

	/* Inits the receiver thread */
	this->receiver = new CybReceiverThread(node);
	receiver->setBufferSize(200);
	receiver->addListener(this);
	receiver->addListener(properties);
	receiver->init();

	CybUDPServer *serverNode = (CybUDPServer*) node;		

	try {
		serverNode->sendData(buffer, pos, address);
	} catch (CybCommunicationException e) {
			e.showErrorMessage();
	}	
		
	if(isDebugOn){
		cout << "JOIN_REQUEST message sent" << endl;
		cout << "--interator type:	" << type << endl;
		cout << "--name lenght:	" << nameLen << endl;
		cout << "--client's interator model" << clientInteratorModel << endl;
		cout << "--client's name" << name.c_str() << endl;			
	}
}

void CybCollaboration::eventPerformed(char* buffer, CybNodeAddress address) {


	short int port = address.getPort();
	string ipStr(address.getIP());

	char type = buffer[0];

	int serverInteratorType;
	int serverInteratorModel = 0;	

	switch(type) {

		// processed by new participants
		case ACCEPT: {
			int pos = 1;	
			memcpy(&serverInteratorType, buffer + pos, sizeof(int));
			pos += sizeof(int);
			memcpy(&serverInteratorModel, buffer + pos, sizeof(int));
			pos += sizeof(int);
				
			if(isDebugOn){	
				cout << "ACCEPT received" << endl;
				cout << "--serverInteratorType: " << serverInteratorType << endl;
				cout << "--serverInteratorModel: " << serverInteratorModel << endl;				
			}
			
			CybCollaborationIntegrant *server = new CybCollaborationIntegrant(ipStr.c_str(), port);						
			server->setInteratorModel(serverInteratorModel);			
 			addIntegrant(server, serverInteratorType);
		}
		break;

		// processed by server
		case JOIN_REQUEST: // Join collaboration request
			processJoinRequestMsg(buffer, ipStr, port);

		break;

		// processed by server
		case LEAVE_REQUEST: // Leave collaboration request
			;
		break;

		// processed by new participants
		case SCENE_CONFIGURATION: // Receive collaboration configuration data
			processSceneConfigMsg(buffer, ipStr, port);
		break;

		case INTERATOR_POSITION_CHANGE: // Interator position change
			processInteratorPositionChangeMsg(buffer, ipStr, port);
		break;

		case INTERATOR_ROTATION_CHANGE: // Interator rotation change
			processInteratorRotationChangeMsg(buffer, ipStr, port);
		break;

		case LAYER_POSITION_CHANGE: // Layer position change
			processLayerPositionChangeMsg(buffer);
		break;

		case LAYER_ROTATION_CHANGE: // Layer rotation change
			processLayerRotationChangeMsg(buffer);
		break;

		case LAYER_COLOR_CHANGE: //Layer rotation change
			processLayerColorChangeMsg(buffer);
		break;
	}
}

void CybCollaboration::mouseEventPerformed(float x, float y) {


	CybUDPServer* serverNode = (CybUDPServer*) this->node;
	char buffer[100];
	int layerID = 0;
	float xAngle, yAngle, zAngle;
	float xSpeed = 0.4166;
	float ySpeed = 0.4166;

	memset(buffer, 0, 100);
	int pos = 0;

	buffer[pos++] = LAYER_ROTATION_CHANGE;

	xAngle = cybCore->getXAngle() + ((double)(y - cybCore->initialY)*ySpeed);
	yAngle = cybCore->getYAngle() + ((double)(x - cybCore->initialX)*xSpeed);
	zAngle = 0;

	memcpy(buffer + pos, &layerID, sizeof(int));
	pos += sizeof(int);
	memcpy(buffer + pos, &xAngle, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &yAngle, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &zAngle, sizeof(float));
	pos += sizeof(float);
	
	//cout << "LAYER-ROT-size: " << pos;

	if (properties->isObjectFree()) 
		sendDataToAll(buffer, pos, properties->getCommunicationType());
}


void CybCollaboration::interatorPositionEventPerformed(float x, float y, float z) {

	char buffer[100];

	memset(buffer, 0, 100);

	int pos = 0;
	buffer[pos++] = INTERATOR_POSITION_CHANGE;
	memcpy(buffer + pos, &x, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &y, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &z, sizeof(float));
	pos += sizeof(float);

	sendDataToAll(buffer, pos, properties->getCommunicationType());
	//cout << "INT-POS-size: " << pos;
}

void CybCollaboration::interatorRotationEventPerformed(float x, float y, float z) {

	char buffer[100];

	memset(buffer, 0, 100);

	int pos = 0;
	buffer[pos++] = INTERATOR_ROTATION_CHANGE;
	memcpy(buffer + pos, &x, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &y, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &z, sizeof(float));
	pos += sizeof(float);

	sendDataToAll(buffer, pos, properties->getCommunicationType());
}

void CybCollaboration::layerColorEventPerformed(int layer, float r, float g, float b, float a) {
	
	char buffer[100];

	memset(buffer, 0, 100);

	int pos = 0;
	buffer[pos++] = LAYER_COLOR_CHANGE;

	memcpy(buffer + pos, &layer, sizeof(int));
	pos += sizeof(int);

	memcpy(buffer + pos, &r, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &g, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &b, sizeof(float));
	pos += sizeof(float);
	memcpy(buffer + pos, &a, sizeof(float));
	pos += sizeof(float);

	sendDataToAll(buffer, pos, properties->getCommunicationType());
	//cout << "COLOR-size: " << pos << endl;
}


void CybCollaboration::processJoinRequestMsg(char* buffer, string ipStr, short int port) {	

	int ipAddrLen = ipStr.length();
	int pos = 1;
	int nameLen = 0;
	int interatorType;

	/************** Mouting the ACCEPT packet for answering the new user **************/
	int tam = 0;
	int serverInteratorType = mainInterator->getInteratorType();
	
	//int serverInteratorModel = 1; // server-esfera
	int serverInteratorModel = this->idInteratorModel;
	int clientInteratorModel = NULL;
	
	char serverAnswer[10]; 
	memset(serverAnswer, 0, 10);

	serverAnswer[tam++] = ACCEPT;
	memcpy(serverAnswer + tam, &serverInteratorType, sizeof(int));
	tam += sizeof(int);
	memcpy(serverAnswer + tam, &serverInteratorModel, sizeof(int));
	tam += sizeof(int);
	
	//*********************************************************************************
	
	CybUDPServer *serverNode = (CybUDPServer*) node;

	try {    	     	
	     serverNode->sendData(serverAnswer, tam, new CybNodeAddress(port, ipStr.c_str(), AF_INET));
	     
	} catch (CybCommunicationException e) {
		e.showErrorMessage();
	}
	/*********************/	
	
	/****** ADDS AN INTEGRANT IN THE SCENE ******/
		
	memcpy(&interatorType, buffer + pos, sizeof(int));
	pos += sizeof(int);

	memcpy(&nameLen, buffer + pos, sizeof(int));
	pos += sizeof(int);
	
	memcpy(&clientInteratorModel, buffer + pos, sizeof(int));
	pos += sizeof(int);

	// Name
	char* name = new char[nameLen + 1];
	memset(name, 0, nameLen + 1);
	memcpy(name, buffer + pos, nameLen);
	pos += nameLen;
		
	if(isDebugOn){	
		cout << "JOIN_REQUEST message received" << endl;
		cout << "--interator type: " << interatorType << endl;
		cout << "--name lenght: " << nameLen << endl;
		cout << "--name: " << name << endl;	
		cout << "--client's interator model: " << clientInteratorModel << endl;

		cout << "ACCEPT message sent" << endl;
		cout << "--server's interator type = " << serverInteratorType << endl;
		cout << "--server's interator model = " << serverInteratorModel << endl;
	}

	// Mounting send message
	char sendMessage[100];
	int numIntegrants = 1;
	pos = 0;

	memset(sendMessage, 0, 100);
	sendMessage[pos++] = 2;

	memcpy(sendMessage + pos, &numIntegrants, sizeof(int));
	pos += sizeof(int);

	memcpy(sendMessage + pos, &interatorType, sizeof(int));
	pos += sizeof(int);
	
	memcpy(sendMessage + pos, &clientInteratorModel, sizeof(int));
	pos += sizeof(int);

	memcpy(sendMessage + pos, &nameLen, sizeof(int));
	pos += sizeof(int);

	memcpy(sendMessage + pos, name, nameLen);
	pos += nameLen;

	memcpy(sendMessage + pos, &ipAddrLen, sizeof(int));
	pos += sizeof(int);

	memcpy(sendMessage + pos, ipStr.c_str(), ipAddrLen);
	pos += ipAddrLen;

	memcpy(sendMessage + pos, &port, sizeof(short int));
	pos += sizeof(short int);

	int sendMessageLen = pos;

	

	/*************************************************/
	
	properties->sendCollaborationProperties(new CybNodeAddress(port, ipStr.c_str(), AF_INET));

	/***** SENDS SCENE CONFIGURATIONS *****/
	int numberOfIntegrants = integrants.size();
	
	int j = 0;
	
	for(it = integrants.begin(); it != integrants.end(); ++it) {

		j++;

		//Sends information of the new integrant to old integrants.
		try {
			CybUDPServer *serverNode = (CybUDPServer*) node;
			serverNode->sendData(sendMessage, sendMessageLen, (*it)->getAddress());
			
			if(isDebugOn){
				cout << "SCENE_CONFIG message sent (new user -> user[" << j << "]" << endl;
				cout << "--number of integrants: " << numIntegrants << endl;			 
				cout << "--interator type: " << interatorType << endl;
				cout << "--interator model: " << clientInteratorModel << endl;
				cout << "--name lenght: " << nameLen << endl;
				cout << "--name: " << name << endl;
				cout << "--ipAddrLen: " << ipAddrLen << endl;
				cout << "--IP address: " << ipStr.c_str() << endl;
				cout << "--port: " << port << endl;
			}
			
		} catch (CybCommunicationException e) {
			e.showErrorMessage();
		}

		char bufferNew[100];
		int integrantInteratorType = (*it)->getInterator()->getInteratorType();
		int integrantInteratorModel = (*it)->getIdInteratorModel();
		
		memset(bufferNew, 0, 100);

		pos = 0;
		bufferNew[pos++] = SCENE_CONFIGURATION;

		string nameStr((*it)->getName());
		int nameLenNew = nameStr.length();

		CybNodeAddress* addr = (*it)->getAddress();
		string ipNew(addr->getIP());

		short int portNew = addr->getPort();
		int ipLen = ipNew.length();

		memcpy(bufferNew + pos, &numberOfIntegrants, sizeof(int));
		pos += sizeof(int);

		memcpy(bufferNew + pos, &integrantInteratorType, sizeof(int));
		pos += sizeof(int);
		
		memcpy(sendMessage + pos, &integrantInteratorModel, sizeof(int));
		pos += sizeof(int);

		memcpy(bufferNew + pos, &nameLenNew, sizeof(int));
		pos += sizeof(int);

		memcpy(bufferNew + pos, nameStr.c_str(), nameLenNew);
		pos += nameLenNew;

		memcpy(bufferNew + pos, &ipLen, sizeof(int));
		pos += sizeof(int);

		memcpy(bufferNew + pos, ipNew.c_str(), ipLen);
		pos += ipLen;

		memcpy(bufferNew + pos, &portNew, sizeof(short int));
		pos += sizeof(short int);

		try {
			CybUDPServer *serverNode = (CybUDPServer*) node;
			serverNode->sendData(bufferNew, pos, new CybNodeAddress(port, ipStr.c_str(), AF_INET));
			
			if(isDebugOn){
				cout << "SCENE_CONFIG message sent (user[" << j << "] -> new user)" << endl;
				cout << "--number of integrants: " << numberOfIntegrants << endl;			 
				cout << "--interator type: " << integrantInteratorType << endl;
				cout << "--interator model: " << integrantInteratorModel << endl;
				cout << "--name lenght: " << nameLenNew << endl;
				cout << "--name: " << nameStr.c_str() << endl;
				cout << "--ipAddrLen: " << ipLen << endl;
				cout << "--IP address: " << ipNew.c_str() << endl;
				cout << "--port: " << portNew << endl;			
			}
			
		} catch (CybCommunicationException e) {
			e.showErrorMessage();

		}
	}
	CybCollaborationIntegrant* newIntegrant = new CybCollaborationIntegrant(name, ipStr, port);
	newIntegrant->setInteratorModel(clientInteratorModel);
	addIntegrant(newIntegrant, interatorType);
}

void CybCollaboration::processSceneConfigMsg(char* buffer, string ipStr, short int port) {
	int pos = 1;
	int numberOfIntegrants = 0;
	int nameLen = 0;
	int ipLen   = 0;
	int interatorType;
	int newInteratorModel;
	char* name;
	char ip[30];
	short int newIntegrantPort;

	memset(ip, 0, 30);

	CybCollaborationIntegrant* newIntegrant;

	memcpy(&numberOfIntegrants, buffer + pos, sizeof(int));
	pos += sizeof(int);
	
	int j=0;
	
	for (int i=0; i<numberOfIntegrants; i++) {

		j++;		
		
		memcpy(&interatorType, buffer + pos, sizeof(int));
		pos += sizeof(int);
		
		memcpy(&newInteratorModel, buffer + pos, sizeof(int));
		pos += sizeof(int);

		memcpy(&nameLen, buffer + pos, sizeof(int));
		pos += sizeof(int);

		name = new char[nameLen + 1];
		memcpy(name, buffer + pos, nameLen);
		name[nameLen] = '\0';
		pos += nameLen;

		memcpy(&ipLen, buffer + pos, sizeof(int));
		pos += sizeof(int);

		memcpy(ip, buffer + pos, ipLen);
		pos += ipLen;

		memcpy(&newIntegrantPort, buffer + pos, sizeof(short int));
		pos += sizeof(short int);
		
		if(isDebugOn){
			cout << "processing SCENE_CONFIG message received [" << j << "]" << endl;
			cout << "--number of integrants: " << numberOfIntegrants << endl;			 
			cout << "--interator type: " << interatorType << endl;
			cout << "--interator model: " << newInteratorModel << endl;
			cout << "--name lenght: " << nameLen << endl;
			cout << "--name: " << name << endl;
			cout << "--ipAddrLen: " << ipLen << endl;
			cout << "--IP address: " << ipStr.c_str() << endl;
			cout << "--port: " << newIntegrantPort << endl;
		}

		newIntegrant = new CybCollaborationIntegrant(name, ip, newIntegrantPort);
		newIntegrant->setInteratorModel(newInteratorModel);
		this->addIntegrant(newIntegrant, interatorType);
	}
}


void CybCollaboration::processInteratorPositionChangeMsg(char* buffer, string ipStr, short int port) {	
	int ipLen = ipStr.length();
	for (it = integrants.begin(); it != integrants.end(); ++it) {
		CybNodeAddress *addr = (*it)->getAddress();
		int n = memcmp(addr->getIP(), ipStr.c_str(), ipLen);

		//--------------------ta ok-------------------------------
		if (n == 0) {
			CybRemoteInterator* interator = (*it)->getInterator();

			switch(interator->getInteratorType()) {
				
				case REMOTE_GLOVE_INTERATOR: 
					CybGloveProcessInterator::processPosition(buffer, ipStr, port, interator);
					break;
				
				case REMOTE_INTERATOR:
					interator->setInteratorChange(buffer);
					performance->countTrafficReceived(INTERATOR_POSITION_CHANGE, 13);
					break;
	
				case HAPTIC_INTERATOR: case REMOTE_HAPTIC_INTERATOR:	
					CybHapticProcessInterator::processPosition(buffer, ipStr, port, interator);
				break;						


			}
		}
	}
}

void CybCollaboration::processInteratorRotationChangeMsg(char* buffer, string ipStr, short int port) {

	int ipLen = ipStr.length();
	int pos = 1;
	float x, y, z;
	memcpy(&x, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&y, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&z, buffer + pos, sizeof(float));


	for (it = integrants.begin(); it != integrants.end(); ++it) {
		CybNodeAddress *addr = (*it)->getAddress();
		int n = memcmp(addr->getIP(), ipStr.c_str(), ipLen);

		if (n == 0) {
			CybRemoteInterator* interator = (*it)->getInterator();
			interator->setRotation(x, y, z);
		}
	}
}

void CybCollaboration::processLayerPositionChangeMsg(char* buffer) {
	int layerID = 0;
	int pos = 1;
	float x, y, z;

	memcpy(&layerID, buffer + pos, sizeof(int));
	pos += sizeof(int);
	memcpy(&x, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&y, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&z, buffer + pos, sizeof(float));

	cybCore->setLayerTranslation(layerID, x, y, z);

}

void CybCollaboration::processLayerRotationChangeMsg(char* buffer) {

	int layerID = 0;
	int pos = 1;
	float x, y, z;

	memcpy(&layerID, buffer + pos, sizeof(int));
	pos += sizeof(int);
	memcpy(&x, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&y, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&z, buffer + pos, sizeof(float));

	bool sceneEditable = cybCore->isSceneEditable();
	cybCore->setSceneEditable(true);
	cybCore->setAngle(x, y, z);

	cybCore->setSceneEditable(sceneEditable);

	performance->countTrafficReceived(LAYER_ROTATION_CHANGE, pos + sizeof(int));
}

void CybCollaboration::processLayerColorChangeMsg(char* buffer) {

	int layerID = 0;
	int pos = 1;
	float r, g, b, a;

	memcpy(&layerID, buffer + pos, sizeof(int));
	pos += sizeof(int);

	memcpy(&r, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&g, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&b, buffer + pos, sizeof(float));
	pos += sizeof(float);
	memcpy(&a, buffer + pos, sizeof(float));

	bool sceneEditable = cybCore->isSceneEditable();
	cybCore->setSceneEditable(true);

	cybCore->setColor(layerID, r, g, b, a);
	cybCore->setSceneEditable(sceneEditable);

	performance->countTrafficReceived(LAYER_COLOR_CHANGE, pos + sizeof(int));

}

CybInterator* CybCollaboration::getInterator() {
	return this->mainInterator;
}

tIntegrantsList CybCollaboration::getIntegrants() {
	return this->integrants;
}

int CybCollaboration::getPort() {
	return this->port;
}

CybCollaborationPerformance* CybCollaboration::getCollaborationPerformance() {
	return this->performance;
}

CybCollaborationProperties* CybCollaboration::getCollaborationProperties() {
	return this->properties;
}

void CybCollaboration::setDataObtainer(cybDObtainer* data) {
	this->data = data;
}

void CybCollaboration::setMainInterator(CybInterator* mainInterator) {
	this->mainInterator = mainInterator;
}


void CybCollaboration::setInteratorModel(char* file) {
	this->interatorModel = file;	
}

void CybCollaboration::setCybNode(CybNode* node) {
	this->node = node;
}

#ifdef CYBCOLLISION_H
void CybCollaboration::activeCollision() {
	collisionStatus = status;
	localActiveCollision(status, layer, mainInterator);
}
#endif

#ifdef CYBDEFORMATION_H
void CybCollaboration::activeDeformation() {

}
#endif

#ifdef CYBCOLLISION_H
void CybCollaboration::localActiveCollision(bool status, int layer, CybInterator* interator) {
	CybSphereTriangle* collision = new CybSphereTriangle(layer, interator);
	//collision->init();

	CybMassSpring *deformationObj = new CybMassSpring(collision, DEF_GO_AND_BACK);

	//Update the deformation properties
	deformationObj->update();
	deformationObj->init();
	//collision->setIsHablitated(status);
}
#endif

CybCollaboration::~CybCollaboration() {
	delete receiver;
	delete node;
	delete mainInterator;
}

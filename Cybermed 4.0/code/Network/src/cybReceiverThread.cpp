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

#include "cybReceiverThread.h"

	CybReceiverThread::CybReceiverThread(CybNode* node, int receiverSock)
	{

		this->node = node;
		this->remoteNode = NULL;
		this->receiverSock = receiverSock;
		bufferSize = 1;
		buffer = new char[bufferSize];
	}

	CybReceiverThread::CybReceiverThread(CybNode* node)
	{
		this->node = node;
		this->remoteNode = NULL;
		this->receiverSock = 0;
		bufferSize = 1;
		buffer = new char[bufferSize];
	}

	int CybReceiverThread::getBufferSize(void)
	{
		return bufferSize;
	}

	void CybReceiverThread::setBufferSize(int n)
	{
		bufferSize = n;
		delete buffer;
		buffer = new char[bufferSize];
	}

	char* CybReceiverThread::getBuffer(void)
	{
		return this->buffer;
	}

	void CybReceiverThread::addListener(CybReceiverThreadListener* listener) {
		listenerList.push_back(listener);
	}

	void CybReceiverThread::run(void)
	{
		//cout << "ReceiverThread" << endl;
		//CybThread::lock();
			try
			{	
				//cout << "waiting data... " << endl;

				CybUDPServer* server = (CybUDPServer*)node;				
				CybNodeAddress remoteAddress;

				int result = server->receiveDataFrom(buffer, bufferSize, &remoteAddress);
				
				for(it = listenerList.begin(); it != listenerList.end(); it++) {
					(*it)->eventPerformed(buffer, remoteAddress);
				}
				//cout << "received: " << buffer << endl;
						
			}
			catch(CybCommunicationException e)
			{
				e.showErrorMessage();
			}
		//CybThread::unlock();
		//CybThread::sleep(0);
	}

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

#ifndef _CYBRECEIVERTHREAD_H
#define	_CYBRECEIVERTHREAD_H

#include "cybThread.h"
#include "cybNode.h"
#include "cybCommunicationException.h"
#include "cybReceiverThreadListener.h"
#include "cybMulticastPeer.h"
#include <list>

typedef list<CybReceiverThreadListener*> tListenerList;

class CybReceiverThread: public CybThread
{
protected:
    CybNode* node;
    CybNode* remoteNode;
    char* buffer;
    int bufferSize;
    int receiverSock;

    tListenerList listenerList;
    tListenerList::iterator it;
    
public:
    /** Constructor
     *@node
     *@receiverSock
     */
    CybReceiverThread(CybNode* node, int receiverSock);

    /** Constructor
     *@node
     */
    CybReceiverThread(CybNode* node);


    void addListener(CybReceiverThreadListener* listener);

    /** */
    int getBufferSize(void);

    /** */
    void setBufferSize(int n);

    /** */
    char* getBuffer(void);

    /** */
    virtual void run(void);

};
#endif	/* _CYBRECEIVERTHREAD_H */

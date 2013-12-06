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

#include "cybThread.h"

	pthread_mutex_t CybThread::mutex = PTHREAD_MUTEX_INITIALIZER;  	//initializes the mutex	
	bool CybThread::is_locked = false;
	
	CybThread::CybThread()
	{
		this->thread_is_active = false;  // all the atributes seted as false.
		this->exit = false;
		this->thread_is_habilitated = false;
		this->setTime(10);	// It sets the thread time (the frequency is (1000/time) Hz)		
	}	
	
	/** Destructor */	
	CybThread::~CybThread()
	{
		this->destroy();	//destroy the thread
	}
	
	void CybThread::destroy()
	{
		if(this->thread_is_active)
		{		
			this->exit = true;			//end the loop of the thread function
			cout << "The thread was finished normaly!" << endl;
		} else cout << "The thread is not active!" << endl;	
	} 	  	    
	
	int CybThread::getFrequency()
	{
		return this->frequency;
	}
	
	bool CybThread::isActive()
	{
		return this->thread_is_active;
	}  	
	
	bool CybThread::isHabilitated()
	{
		return this->thread_is_habilitated;
	}
	
	int CybThread::getTime()
	{
		return this->time;
	} 	
	
	void CybThread::init()
	{		
		if(!this->thread_is_active)
		{
			this->retval = pthread_create(&(this->thread), NULL, CybThread::threadFunction, (void*) this); // create the thread
			// criates the thread
			if(this->retval)
				cout << "The thread cannot to be created!" << endl;
			else
			{
				this->thread_is_active = true;			// habilites the thread
				this->thread_is_habilitated = true;
				cout << "The thread was created!" << endl;
			}
		} 
		else cout << "The thread already was created!" << endl;
	}
	
	void CybThread::join()
	{
		pthread_join(this->thread, NULL);
	}
	
	void CybThread::lock()
	{
		pthread_mutex_lock(&CybThread::mutex);
		CybThread::is_locked = true;		
	}	
	
	void CybThread::setIsHablitated(bool flag)
	{
		this->thread_is_habilitated = flag;
	}
	
	void CybThread::setFrequency(int frequency)
	{
		if(frequency > 0)
		{
			this->frequency = frequency;
			this->time = 1000/frequency; //changes the time too
		}
	}
	
	void CybThread::setTime(int time)
	{
		if(time > 0)
		{
			this->time = time;
			this->frequency = 1000/time; //changes the frequency too
		}   	
	}
	
	void CybThread::sleep(int time)
	{
		if(time > 0)  		
			usleep(time*1000);	//do the thread sleep a time
	}
	
	void CybThread::start()
	{
		this->thread_is_habilitated = true;			// habilites the thread executation.			
	}	 
	
	void CybThread::stop()
	{
		this->thread_is_habilitated = false;		//desabilites the thread executation.
	}
	
	void* CybThread::threadFunction(void* objectReference)
	{
		CybThread* object = (CybThread*) objectReference;	//A refernce to this object
	
		while(true)
		{	
			object->update();
			
			if(object->isHabilitated()) 
			{	                                
				object->run();		//calls the run method defined in son class 	
			} else
				pthread_yield();
			
			CybThread::sleep(object->time);		//wait a moment		
	
			if(object->exit) return NULL;
		}			  
	}	
	
	void CybThread::unlock()
	{
		pthread_mutex_unlock(&CybThread::mutex);		//unlocks the thread
		CybThread::is_locked = false;
	
	}
	
	inline void CybThread::update()
	{		
		// do nothing, but the sons do not need implement its but it can to do its. 
	}

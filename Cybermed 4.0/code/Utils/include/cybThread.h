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

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

#ifndef _CYB_THREAD_H_
#define _CYB_THREAD_H_

/**
 * @class CybThread
 * @file cybThread.h 
 * @short thread manipulation SUPER class
 * 
 * This class implements the methods that create, manipulate and terminates a thread executation.
 * His son's must to implement the run() virtual method that will be called in thread executation.
 * Inside the run() method must to be called the code that will be executed. 
 * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 1.0
 * @date 2007, July
 * 
 */
class CybThread
{
	
protected:
   pthread_t thread;			/**< The object that manipulates the collision detection thread. */
   int retval;			 		/**< The identification of the thread executation status last his creation. */   
   
private: 
   bool thread_is_habilitated;		/**< Indicates if the thread executation is habilitated. */	
   bool thread_is_active;		/**<  Indicates if the collision thread is active. */
   bool exit;					/**< Indicates if the collision thread must to be terminated. */
   int time;					/**< Stores the time of thread execution. (miliseconds)*/
   int frequency;				/**< Stores the frequency of thread executation. (miliseconds) */
   // time * frequency = 1000; 
   static pthread_mutex_t mutex;  	/**< It controls the concorrent acess (it gives exclusivity in thread executation). */
   static bool is_locked;		/**< Indicates if this thread is exclusivity or no. */

public:

	/** Constructor */
	CybThread();
	
	/** Destructor */	
	~CybThread();
	
	 /**
	 * This method destroys the thread executation.
	 * 
	 * @param void
	 * @return void
	 * 
	 */  	
  	virtual void destroy();  	
  	    
	/**
	 * It returns the frequency of thread executation.
	 * 
	 * @param void
	 * @return int The the frequency of thread executation in miliseconds.
	 * 
	 */		
 	inline int getFrequency(); 
 	
 	 /**
 	 * This method returns the executation thread status. It returns true if the thread is active
 	 * and false else.
 	 * 
 	 * @param void
 	 * @return bool The thread status.
 	 * 
 	 */
 	inline bool isActive();

	/**
	* This method returns if the run method is habilitated for to be executed.
	*
	* @param void
	* @return bool The run method habilitation.
	*
	*/
	inline bool isHabilitated();
  	
  	/**
	 * This method returns the time of the thread executation.
	 * 
	 * @param void
	 * @return int The time of recalling the thread in miliseconds.
	 * 
	 */	
  	inline int getTime(); 
	
	/**
	 * This method creates this object thread. 
	 * It habilitates the thread to the call the run() method declarated in any son of this class.
	 * The template indicates the Son that implements the run() method.
	 * 
	 * @param void
	 * @return void
	 * 
	 */
	 virtual void init();

	/**
	* This method do the thread wait for the other threads.
	*
	* @param void
	* @return void
	*
	*/
	void join();

	/**
	* This method gives the priority to the thread until the unlock() method to be called.
	*
	* @param void
	* @return void
	*
	*/
	static void lock();
	
	/**
	 * This method is abstract and must to be implemented in derived class.
	 * It implements the code that will be called in thread executation.
	 *
	 * @param void
	 * @return void
	 * 
	 */
  	virtual void run() = 0; 

	/**
	 * This method changes the value of frequency that thread is  recalled.
	 *
	 * @param int frequency the new frequency of thread executation in miliseconds.
	 * @return void
	 * 
	 */
  	void setFrequency(int frequency);

	/** This methos sets the thread's habilitation to execute the run() method.
	*
	* @param bool flag The status of the run() method exectation.
	* @return void
	*
	*/
	void setIsHablitated(bool flag);
	
	/**
	* This method changes the value of time thread executation is  recalled.
	*
	* @param int time the new time in miliseconds.
	* @return void
	* 
	*/
	void setTime(int time);   
        

  	/** 
  	 * This method specifies a time to thread wait to recall his
  	 * executation.
  	 * 
  	 * @param int time The time that the thread must to wait.
  	 * @void
  	 * 
  	 */  	
  	static void sleep(int time);
		
	/**
	 * This method habilites the thread executation.
	 * 
	 * @param void
	 * @return void
	 * 
	 */
	 void start();	 
      
	/**
	 * This method desabilites the thread executation.
	 *  
	 * @param void
	 * @return void
	 * 
	 */	 
  	void stop();
  
 	/**
 	 * This method implements the thread of this object, but the method run() 
 	 * of a son class is called in this method.
	 *
	 * @param void* objectReference a reference to this object.
	 * @return void*
	 * 
	 */
  	static void* threadFunction(void* objectReference);

	/**
	* This method removes the thread priority that was giving by the lock() method.
	*
	* @param void
	* @return void
	*
	*/
	static void unlock();
  	
	/**
	 * This method updates the data before the run() in thread specification.
	 * 
	 * @param void
	 * @return void
	 * 
	 */
	virtual void update(); 
	//indicates if the run method can or can't be executed modifing the thread_is_habilitated attribute (in class son)

};

#endif /*_CYB_THREAD_H_*/

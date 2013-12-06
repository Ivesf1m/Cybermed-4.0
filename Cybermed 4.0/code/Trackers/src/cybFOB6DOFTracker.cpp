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


#include "cybFOB6DOFTracker.h"

	
	CybFOB6DOFTracker::CybFOB6DOFTracker()
	{

		for(int i = 0; i < 16; i++){ matrixIn[i] = 0;}
		birdsOn = 0;			// number of birds
		scale = 1;

	}
	
	
	CybFOB6DOFTracker::~CybFOB6DOFTracker()
	{
		flockGlobal.close();
	 	sleep(5);
	}


	void CybFOB6DOFTracker::setTrackerPort(char *device_port)
	{
		port = device_port;
	}


	void CybFOB6DOFTracker::setTrackerHemisphere(fob::hemisphere h)
	{
		hemisphere = h;
	}

	void CybFOB6DOFTracker::setScale(float newScale)
	{
		scale = newScale;	
	}


	void CybFOB6DOFTracker::initDevice()
	{

		if(!flockON){
			printf("\n\rStarting Flocks of Birds\n\n");
			flockGlobal.open( "/dev/ttyS0", fob::UP, fob::FAST );
			if( !flockGlobal ) {
			  std::cerr << "fatal: " << flockGlobal.get_error( ) << std::endl;
			  exit(0);
			}
			printf("\n\rFlocks of Birds started\n\n");
			
			flockON = true;
		}

	}

	void CybFOB6DOFTracker::createTracker(void *userData){

			createTracker();
	}

	void CybFOB6DOFTracker::createTracker(void)
	{
		if(!flockON)
		{
			CybFOB6DOFTracker::initDevice();
		}

		// get 'birds' list
		fob::bird_list& birds = flockGlobal.get_birds( );
		birdsOn = birds.size();

		// set get mode to Position and Orientation
		for( unsigned int i = 0; i < birds.size( ); ++i ) {
		  if( !birds[ i ]->set_mode( fob::POSITION | fob::ORIENTATION ) ) {
		    std::cerr << "fatal: " << flockGlobal.get_error( ) << std::endl;
		    exit(0);
		  }
		}
		// start 'birds'
		flockGlobal.fly( );
	
		// sleep time to get initial position
		sleep( 1 );
	
		// store initial orientation matrix
		// '0' is FOB master address
		birds[ 0 ]->get_matrix( matrixIn );
		transposeMatrix(matrixIn);

		// set initial position to (0,0,0)
		// need use glTranslatef(posx,posy,posz)
		posx = -matrixIn[12];
		posy = -matrixIn[13];
		posz = -matrixIn[14];

	}


	bool CybFOB6DOFTracker::isTrackerEnable(void)
	{
		return flockON;
	}

	
	void CybFOB6DOFTracker::stopDevice(void)
	{
		flockGlobal.close();
	 	sleep(5);
	}


	void CybFOB6DOFTracker::getInitialPosition(float *position)
	{
		position[0] = posx;
		position[1] = posy;
		position[2] = posz;
	}


	void CybFOB6DOFTracker::resetInitialPosition(void)
	{
		float position[3];
		
		fob::bird_list& birds = flockGlobal.get_birds();
		birds[ 0 ]->get_position( position );
		
		posx = (-position[0] * scale);
		posy = (-position[1] * scale);
		posz = (-position[2] * scale);

	}


	void CybFOB6DOFTracker::getPosition(float *position)
	{
		fob::bird_list& birds = flockGlobal.get_birds();
		birds[ 0 ]->get_position( position );
		
		position[0]*=scale;
		position[1]*=scale;
		position[2]*=scale;

	}


	void CybFOB6DOFTracker::getMatrix(float *matrix)
	{
		fob::bird_list& birds = flockGlobal.get_birds();
		birds[ 0 ]->get_matrix( matrix );
		transposeMatrix(matrix);

		// obs.: devera ser utilizado glTranslatef(posx,posy,posz)
		// a cada visualizacao, utilizando o metodo getInicialPosition()
	}


	void CybFOB6DOFTracker::transposeMatrix(float *matrix){
			
		float copia; 
	
		copia = matrix[1];
		matrix[1] =  matrix[4];
		matrix[4] = copia;
	
		copia = matrix[2];
		matrix[2] = matrix[8];
		matrix[8] = copia;
	
		copia = matrix[3];
		matrix[3] = matrix[12];
		matrix[12] = (copia * scale);
		
		copia = matrix[6];
		matrix[6] = matrix[9];
		matrix[9] = copia;
	
		copia = matrix[7];
		matrix[7] = matrix[13];
		matrix[13] = (copia * scale);
	
		copia = matrix[11];
		matrix[11] = matrix[14];
		matrix[14] = (copia * scale);
	
	}

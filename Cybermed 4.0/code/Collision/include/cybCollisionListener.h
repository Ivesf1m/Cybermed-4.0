// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2011 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba.
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

#ifndef _CYB_COLLISIONLISTENER_H_
#define _CYB_COLLISIONLISTENER_H_

#include "cybCollisionInstance.h"

/**
 * @class CybCollisionListener
 * @file cybCollisionListener.h 
 * @short Collision Listener abstract class.
 *
 * This class must be extended to implement collision listeners. 
 *
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 2.2
 * @date 2011, November
 */

class CybCollisionListener
{
	public:
		/*
		* Pure virtual getter for the collision status.
		*
		* @param void
		* @return bool: the collision status (true if colliding, false otherwise).
		*/
		virtual bool getCollisionStatus() = 0;
		/*
		* Pure virtual notificator for listening objects. 
		*
		* @param CybCollisionInstance* instance: the instance to be notified.
		* @return void
		*/
		virtual void notification(CybCollisionInstance*) = 0;
};



#endif // _CYB_COLLISIONLISTENER_H_

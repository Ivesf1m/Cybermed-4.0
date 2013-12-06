// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2012 LabTEVE (http://www.de.ufpb.br/~labteve),
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

#ifndef _CYBBOXDRAWER_H_
#define _CYBBOXDRAWER_H_

/**
 * @class CybBoxDrawer
 * @file cybBoxDrawer.h 
 * @short This is an abstract class that must be extended to implement box drawers.
 *
 * This class defines the basic draw operator for box drawers and must be extended when implementing 
 * one of them. 
 * 
 * @author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
 * @version 3.0
 * @date 2012, March
 * 
 */

class CybBoxDrawer
{
	public:
		/*
		* Constructor
		*
		* @param void
		*/
		CybBoxDrawer();
		/*
		* Abstract draw method. Must be implemented in subclasses.
		*
		* @param void
		* @return void
		*/
		virtual void drawBox() = 0;
};

#endif //_CYBBOXDRAWER_H_

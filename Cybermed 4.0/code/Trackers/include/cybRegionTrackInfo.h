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

#ifndef REGIONTRACKINFO_H_
#define REGIONTRACKINFO_H_

#ifdef CYBOPTICALTRACKER_H

#include <opencv/Blob.h>
#include <opencv/BlobResult.h>

class CybRegionTrackInfo
{
public:

	/** Constructor */
	CybRegionTrackInfo();

	/** Constructor 
	*
	*@param int maxX 
	*@param int minX
	*@param int maxY
	*@param int minY
	*
	*/
	CybRegionTrackInfo(int maxX, int minX, int maxY, int minY);

	/** Constructor
	*
	*@param const CBlob *blob
	*
	*/
	CybRegionTrackInfo(const CBlob *blob);

	/** Destructor */
	virtual ~CybRegionTrackInfo();
	
	 /**
  	 * Get max X
  	 * 
  	 * @param void
  	 * @return int
  	 * 
  	 */ 	
	int getMaxX();

	 /**
  	 * Get min X
  	 * 
  	 * @param void
  	 * @return int
  	 * 
  	 */
	int getMaxY();

	 /**
  	 * Get min X
  	 * 
  	 * @param void
  	 * @return int
  	 * 
  	 */
	int getMinX();

	 /**
  	 * Get min Y
  	 * 
  	 * @param void
  	 * @return int
  	 * 
  	 */
	int getMinY();
	
	/**
  	 * Return the area of a rectangle calculated using maxX, minX, maxY, minY
  	 * 
  	 * @param void
  	 * @return double
  	 * 
  	 */
	double getArea();
	
	 /**
  	 * Set max X
  	 * 
  	 * @param int
  	 * @return void
  	 * 
  	 */
	void setMaxX(int maxX);

	 /**
  	 * Set min Y
  	 * 
  	 * @param int
  	 * @return void
  	 * 
  	 */

	void setMinX(int minX);

	 /**
  	 * Set max Y
  	 * 
  	 * @param int
  	 * @return void
  	 * 
  	 */

	void setMaxY(int maxY);

	 /**
  	 * Set min Y
  	 * 
  	 * @param int
  	 * @return void
  	 * 
  	 */
	void setMinY(int minY);
	
private:
	int maxX, maxY, minX, minY; /**< rectangle values*/
	
};

#endif //CYBOPTICALTRACKER_H

#endif /*REGIONTRACKINFO_H_*/

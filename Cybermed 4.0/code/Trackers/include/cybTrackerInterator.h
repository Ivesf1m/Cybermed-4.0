/*
 * CybTrackerInterator.h
 *
 *  Created on: Feb 4, 2010
 *      Author: brunorasales
 */

#ifndef CYBTRACKERINTERATOR_H_
#define CYBTRACKERINTERATOR_H_

#include <string>

#include "cybParameters.h"
#include "cybInterator.h"
#include "cybTracker.h"

#ifdef CYBOPTICALTRACKER_H
	#include "cybHaarTracker.h"
	#include "cybBlobTracker.h"
#endif

#ifdef CYBMAGNETICTRACKER_H
	#include "cybFOB6DOFTracker.h"
#endif


class CybTrackerInterator: public CybInterator {

public:
	CybTrackerInterator(std::string type);

	virtual void create(int id);

	virtual void destroy();

	virtual void drawInterator();

	CybDevice* getDevice();
	
	static CybInterator* getInterator(int interatorType);

	virtual ~CybTrackerInterator();

private:
	CybTracker* trackerDevice;

	void drawTrackerCursor();
};

#endif /* CYBTRACKERINTERATOR_H_ */

#ifndef INTERACTIONHANDLE_H_
#define INTERACTIONHANDLE_H_

#include <cybermed/cybThread.h>
#include <cybermed/cybCore.h>
#include <cybermed/cybOpticalTracker.h>
#include <cybermed/cybHaarTracker.h>

class InteractionHandle : public CybThread
{
public:
	InteractionHandle(CybHaarTracker *tracker, CybParameters *core);
	virtual ~InteractionHandle();
	virtual void initialize();
private:
	void run();
	
	CybHaarTracker *tracker;
	CybParameters *core;
};

#endif /*INTERACTIONHANDLE_H_*/

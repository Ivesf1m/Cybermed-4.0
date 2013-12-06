#include <cybermed/cybAABB.h>

class collisionCheck : public CybThread
{
	private:
	CybAABB *collisionObj;
	CybParameters *cybCore;
	int count;
	
	public:
	collisionCheck(int layerID, int interatorId, cybMesh<cybTraits>* mesh)
	{
		collisionObj = new CybAABB(layerID, interatorId, mesh);		
		count = 0;
		
		cybCore = CybParameters::getInstance();
		this->setTime(1000);
	}
	
	~collisionCheck(){	delete collisionObj; }
	
	void run()
	{	
		if(!count){ collisionObj->drawBox(); ++count; }
		CybThread::lock();
		if(collisionObj->getCollisionStatus()){
			cybCore->setColor(0,1,1,0,1);

			cout << "is Equal the last collision " << collisionObj->isEqualLastCollision() << endl;
		}
		else
			desenhaCaixa();
			cybCore->setColor(0,1,0,1,1);
		CybThread::unlock();
	}
	
	CybAABB *getCollisionInstance() {return collisionObj;}
	void desenhaCaixa() { if(collisionObj) collisionObj->drawBox();}
	
};

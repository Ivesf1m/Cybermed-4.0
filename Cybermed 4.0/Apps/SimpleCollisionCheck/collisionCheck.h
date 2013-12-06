class collisionCheck : public CybThread
{
	private:
	CybSphereTriangle *collisionObj;
	CybParameters *cybCore;
	int count;
	
	public:
	collisionCheck(int layerID, int interatorId)
	{
		collisionObj = new CybSphereTriangle(layerID, interatorId);
		count = 0;
		
		cybCore = CybParameters::getInstance();
		this->setTime(50);
	}
	
	~collisionCheck(){	delete collisionObj; }
	
	void run()
	{
		CybThread::lock();
		if(collisionObj->getCollisionStatus()){
			cybCore->setColor(0,1,1,0,1);

			cout << "is Equal the last collision " << collisionObj->isEqualLastCollision() << endl;
		}
		else
			cybCore->setColor(0,1,0,1,1);
		CybThread::unlock();
	}
	
	CybSphereTriangle *getCollisionInstance() {	return collisionObj; }
	
};


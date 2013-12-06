#include<cybermed/cybRemoteModelFactory.h> 

class InteratorModelFactory : public CybRemoteModelFactory {
	public:
		enum NameModel {SPHERE, MONKEY, NEDDLE};
		CybRemoteModel *getModel(int id) {			
			switch (id) {				
				case 0:
					return new CybRemoteModel("esfera.wrl");
					break;
				case 1:
					return new CybRemoteModel("monkey.wrl");
					break;
				
				case 2: return new CybRemoteModel("agulha_unida2.wrl");
					break;				
				
			}		
		}
};

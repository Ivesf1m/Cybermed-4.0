#include <cybermed/cybGlove.h> //adicionado, testar
#include "cybHandModel.h"
#include "fglove.h" //precisa por está usando enumerações da 5DT
#include "cybUpdate5dt14Model.h"


void CybUpdate5dt14Model::update(CybDevice *device, CybModel *models) {
	
	CybGlove *glove = dynamic_cast<CybGlove *>(device);
	CybHandModel *handModel = dynamic_cast<CybHandModel *>(models);
	
	int size = glove->getNumSensors();	
	float gloveA_scaled[size];
	float eixo[18];
	glove->getSensorScaledAll(gloveA_scaled);
	
	float angBase = 90;
	
	eixo[0] = gloveA_scaled[FD_THUMBNEAR] * 60; //35
   eixo[1] = gloveA_scaled[FD_THUMBFAR] * 118;
   eixo[2] =  gloveA_scaled[FD_THUMBINDEX] * -30 ; //ok
   eixo[3] = gloveA_scaled[FD_INDEXNEAR] * angBase;
	eixo[4] = eixo[5] = gloveA_scaled[FD_INDEXFAR] * 97;
	eixo[6] = (1 - gloveA_scaled[FD_INDEXMIDDLE]) * 25;
	eixo[7] = gloveA_scaled[FD_MIDDLENEAR] * angBase;
	eixo[8] = eixo[9] = gloveA_scaled[FD_MIDDLEFAR] * 97;
	eixo[10] = (1 - gloveA_scaled[FD_MIDDLERING]) * -23;
	eixo[11] = gloveA_scaled[FD_RINGNEAR] * angBase;
	eixo[12] = eixo[13] = gloveA_scaled[FD_RINGFAR] * 91;
	eixo[14] = (1 - gloveA_scaled[FD_RINGLITTLE]) * -30;
	eixo[15] = gloveA_scaled[FD_LITTLENEAR] * angBase;
	eixo[16] =  eixo[17] = gloveA_scaled[FD_LITTLEFAR] * 98;
	
	if (eixo[0] > 26) {
		eixo[0] = 26;		
		if (eixo[1] > 25)
			eixo[1] = 25;
	}	
	if (eixo[3] > 46) {
			eixo[3] = 46;
		if (eixo[4] > 20)
			eixo[4] = eixo[5] = 20;
	}
	
	if (eixo[7] > 47) {
		eixo[7] = 47;
		if (eixo[8] > 14)
			eixo[8] = eixo[9] = 14;
	}
	
	if (eixo[11] > 45) {
		eixo[11] = 45;
		if (eixo[12] > 12)
			eixo[12] =  eixo[13] = 12;
	}
		
	if (eixo[15] > 49) {
		eixo[15] = 49;
		if (eixo[16] > 3)
			eixo[16] = eixo[17] = 3;
	}
	
	/*printf("[0]: %f, [1]: %f, [2]: %f, [3]: %f, [4]: %f, [5]: %f, [6]: %f\n"
			 "[7]: %f, [8]: %f, [9]: %f, [10]: %f, [11]: %f, [12]: %f, [13]: %f\n"
			 "[14]: %f, [15]: %f, [16]: %f, [17]: %f\n",
			 eixo[0], eixo[1], eixo[2], eixo[3], eixo[4], eixo[5], eixo[6], eixo[7], eixo[8], eixo[9],
			 eixo[10], eixo[11], eixo[12], eixo[13], eixo[14], eixo[15], eixo[16], eixo[17]);*/
	
	handModel->setEixos(eixo);

}

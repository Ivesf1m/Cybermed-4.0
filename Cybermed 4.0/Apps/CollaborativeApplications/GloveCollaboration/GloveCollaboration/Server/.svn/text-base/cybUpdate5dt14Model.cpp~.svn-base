#include <cybermed/cybGlove.h> //adicionado, testar
#include "cybHandModel.h"
#include "fglove.h" //precisa por está usando enumerações da 5DT
#include "cybUpdate5dt14Model.h"


void CybUpdate5dt14Model::update(CybDevice *device, CybModel *models) {
	
	CybGlove *glove = dynamic_cast<CybGlove *>(device);
	CybHandModel *handModel = dynamic_cast<CybHandModel *>(models);
	
	int size = glove->getNumSensors();	
	float gloveA_scaled[size];
	float *eixo = new float[18];
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

	
	handModel->setEixos(eixo);

}

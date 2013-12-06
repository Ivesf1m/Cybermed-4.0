#include <GL/glut.h>
#include <string>
#include "cybHandModel.h"
#include "cybUpdate5dt14Model.h"
#include "cybUpdate5dt5Model.h"
using namespace std;

CybHandModel::CybHandModel() {
	string model[] = {"modelos/palma2.wrl", "modelos/baseD1.wrl", "modelos/meioD1.wrl",
	"modelos/pontaD1.wrl", "modelos/baseD2_4.wrl", "modelos/meioD2_2.wrl", "modelos/pontaD1.wrl",
	"modelos/baseD4.wrl", "modelos/meioD4_8.wrl", "modelos/pontaD4.wrl", "modelos/basededao.wrl",
	"modelos/pontaDedao_2.wrl"};
	//Reference to an object CybMultiModel
	bool teste = loadModels(model, 12);

	if (!teste) {
		exit(1);
	}
	else {
		cout << "Loaded models!" << endl;
	}
	
	eixo = new float[18];
	sendMatrix = new float[16];
	for (int i = 0; i < 18; i++) {
		eixo[i] = 0;
	}
	for (int i = 0; i < 16; i++) {
		sendMatrix[i] = 0;
	}
}//CybHandModel

void CybHandModel::draw() {
	CybMultiModel *model = getModels();

	glEnable(GL_NORMALIZE);
	
	glPushMatrix();
		
		glScalef(0.5, 0.5, 0.5);
		glColor3f(0.8f, 0.66f, 0.52f);
		glTranslated(0, -30, 0);
		
		glGetFloatv(GL_MODELVIEW_MATRIX, position);
		
		//Base D1
		glPushMatrix();//1

			glPushMatrix();//2

				glTranslated(0, 50, 0);
				glScaled(100, 100, 100);
				drawModel(0);
			glPopMatrix();//2
			//---baseD1------------


			glTranslatef(9.5, 27 , 3.5 );
			glRotatef(eixo[3], 1, 0, 0); //rotação da dobra
			glRotatef(eixo[6] - 6, 0, 0, 1); //rotação da base em z
			glPushMatrix();
				glTranslatef(0, -7, 0.5);
				glScaled(100, 100, 100);
				drawModel(1);
			glPopMatrix();
			//---meioD1
			glTranslatef(-9.5, -27, -3.5);

			glTranslatef(9.5, 14, 3.8);
			glRotatef(eixo[4], 1, 0, 0);
			glPushMatrix();
				glTranslatef(0, -7 , 0);
				glScaled(100, 100, 100);
				drawModel(2);
			glPopMatrix();

			//---pontaD1
			glTranslatef(-9.5, -14 , -3.8 );

			glTranslatef(9.7 , 2.3, 4.2);
			glRotatef(eixo[5] , 1, 0, 0);
			glPushMatrix();
				glTranslatef(0, -5.8, -0.9);
				glScaled(100, 100, 100);
				drawModel(3);
			glPopMatrix();

		glPopMatrix();//1


	//dedo2
		glPushMatrix();//2
			//--baseD2
			glTranslatef(-0.1, 25.8, 4.2);
			glRotatef(eixo[7], 1, 0, 0);
			glPushMatrix();
				glTranslatef(0, -8.4, 0.5);
				glScaled(100, 100, 100);
				drawModel(4);
			glPopMatrix();

			//--meioD2

				glTranslatef(0.1, -25.8, -4.2);

				glTranslatef(0, 11.5, 4.4);
				glRotatef(eixo[8], 1, 0, 0);
				glPushMatrix();
					glTranslatef(0, -7.3, 0.1);
					glScaled(100, 100, 100);
					drawModel(5);
				glPopMatrix();

				//--pontaD2
				glTranslatef(0, -11.5, -4.4);

				glTranslatef(0, -0.2, 3.4);
				glRotatef(eixo[9], 1, 0, 0);
				glPushMatrix();
					glTranslatef(0, -5.8, 0);
					glScaled(100, 100, 100);
					drawModel(6);
				glPopMatrix();
		glPopMatrix();//2

	//Dedo3
		glPushMatrix();//3
			//---baseD3------------
			glTranslatef(-18.7, 0.1, 0);

			glTranslatef(9.5, 27 , 3.5 );
			glRotatef(eixo[11], 1, 0, 0); //Rotação de dobra
			glRotatef(eixo[10] + 4, 0, 0, 1);// /rotação da base em z
			glPushMatrix();
				glTranslatef(0, -7, 0.5);
				glScaled(100, 100, 100);
				drawModel(1);
			glPopMatrix();
			//---meioD3
			glTranslatef(-9.5, -27, -3.5);

			glTranslatef(9.5, 14, 3.8);
			glRotatef(eixo[12], 1, 0, 0);
			glPushMatrix();
				glTranslatef(0, -7 , 0);
				glScaled(100, 100, 100);
				drawModel(2);
			glPopMatrix();

			//---pontaD3
			glTranslatef(-9.5, -14 , -3.8 );

			glTranslatef(9.7 , 2.3, 4.2);
			glRotatef(eixo[13], 1, 0, 0);
			glPushMatrix();
				glTranslatef(0, -5.8, -0.9);
				glScaled(100, 100, 100);
				drawModel(3);
			glPopMatrix();

		glPopMatrix();//3

//Dedo4

		glPushMatrix();//4
			//--baseD4
			glTranslatef(-16.6, 30.8, 1.8);
			glRotatef(eixo[15], 1, 0, 0); // rotação da dobra
			glRotatef(eixo[14] + 6, 0, 0, 1);// rotação da base em z
			glPushMatrix();
				glTranslatef(0, -6.6, 0);
				glScaled(100, 100, 100);
				drawModel(7);
			glPopMatrix();

			//--meioD4
			glTranslatef(16.6, -30.8, -1.8);
			glTranslatef(-16.4, 19.5, 1.3);
			glRotatef(eixo[16], 1, 0, 0);
			glPushMatrix();
				glTranslatef(0, -5.5, 0);
				glScaled(100, 100, 100);
				drawModel(8);
			glPopMatrix();

			//--pontaD4
			glTranslatef(16.4, -19.5, -1.3);
			glTranslatef(-16.1, 10.5, 1.1);
			glRotatef(eixo[17], 1, 0, 0);
			glPushMatrix();
				glTranslatef(0, -4.4, 0);
				glScaled(100, 100, 100);
				drawModel(9);
			glPopMatrix();

		glPopMatrix();//4

	//Dedao

		glPushMatrix();
			//--Base
			glRotated(-45, 1, 0, 0);
			glTranslatef(12.7, 38.1, 34.5);
			glRotated(-353, 1, 0, 0);
			glRotated(50, 0, 1, 0);
			glRotated(eixo[0], 0, 1, 0);//rotação de dobra
			glRotated(-15, 0, 1, 0);
			glRotated(eixo[2] + 7, 0, 0, 1);// rotação de aproximação
			glPushMatrix();
				glTranslatef(12.3, 0, -3.8);
				glScaled(100, 100, 100);
				drawModel(10);
			glPopMatrix();

			glTranslatef(-12.7, -38.1, -34.5);
			//--ponta
			glRotated(45, 1, 0, 0);

			glTranslatef(30.3, 48, -7.5);
			glRotated(-3, 0, 0, 1);

			glRotated(-65, 1, 0, 0);
			glRotated(eixo[1], 0, 1, 0);
			glPushMatrix();
				glTranslatef(5.6, 0, -0.1);
				glScaled(100, 100, 100);
				drawModel(11);
			glPopMatrix();
			//*/
		glPopMatrix();
	glPopMatrix();


}//draw


void CybHandModel::setEixos(float eixos[]) {
	eixo = eixos;
}

void CybHandModel::setMatrix(float ar[]) {
	for (int i = 0; i < 18; ++i) {
		eixo[i] = ar[i];
	}
	
	for (int i = 18; i < 34; ++i) {
		position[i] = ar[i];
	}
}


float *CybHandModel::getMatrix() {
	
	for (int i = 0; i < 18; ++i) {
		sendMatrix[i] = eixo[i];
	}
	int k = 0;
	for (int i = 18; i < 34; ++i) {
		sendMatrix[i] = position[k];
		++k;
	}
	
	return sendMatrix;	
}

void CybHandModel::setUpdateModel(string type) {
	if(type.compare("DG14 Ultra USB") == 0) {
		setUpdate(new CybUpdate5dt14Model());
		}
	if(type.compare("Data Glove 5 Ultra USB") == 0 || type.compare("Data Glove 5 Ultra") == 0 || type.compare("Data Glove 5") == 0) {
		setUpdate(new CybUpdate5dt5Model());
	}
}

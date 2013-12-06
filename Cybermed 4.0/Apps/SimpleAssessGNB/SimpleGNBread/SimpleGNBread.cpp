#include <cybermed/cybGaussianNaiveBayes.h>
#include <cybermed/cybGaussianNaiveBayesIO.h>
#include <iostream>

int main() {

		CybGaussianNaiveBayes* gnb = new CybGaussianNaiveBayes(3);
		CybGaussianNaiveBayesIO* gnbIO = new CybGaussianNaiveBayesIO("/root/gnbTest");
		CybGaussianNaiveBayesIO* gnbIO_2 = new CybGaussianNaiveBayesIO("/root/gnbTest2");

		printf("%s", gnbIO->getFile());

		//We dont need to read the parameters, we can call training() see more below
		//gnb = (CybFuzzyGaussianNaiveBayes*) gnbIO->read()

		for (int i=0; i<gnbIO->readData()->size(); i++)
		{
			gnb->addData(gnbIO->readData()->pos(i)); //adding data to list
		}	

		gnb->training(); //calling training() to get parameters
		gnbIO_2->write(gnb); //writing parameters
		gnbIO_2->writeData(gnb); //writing data

		delete gnb;
		delete gnbIO;
		delete gnbIO_2;
		return 0;
}

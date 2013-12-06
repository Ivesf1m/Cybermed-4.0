#include <cybermed/cybFuzzyGaussianNaiveBayes.h>
#include <cybermed/cybFuzzyGaussianNaiveBayesIO.h>
#include <iostream>

int main() {

		CybFuzzyGaussianNaiveBayes* fgnb = new CybFuzzyGaussianNaiveBayes(3);
		CybFuzzyGaussianNaiveBayesIO* fgnbIO = new CybFuzzyGaussianNaiveBayesIO("/root/fgnbTest");
		CybFuzzyGaussianNaiveBayesIO* fgnbIO_2 = new CybFuzzyGaussianNaiveBayesIO("/root/fgnbTest2");

		printf("%s", fgnbIO->getFile());

		//We dont need to read the parameters, we can call training() see more below
		//fgnb = (CybFuzzyGaussianNaiveBayes*) fgnbIO->read()

		for (int i=0; i<fgnbIO->readData()->size(); i++)
		{
			fgnb->addData(fgnbIO->readData()->pos(i)); //adding data to list
		}	

		fgnb->training(); //calling training() to get parameters
		fgnbIO_2->write(fgnb); //writing parameters
		fgnbIO_2->writeData(fgnb); //writing data

		delete fgnb;
		delete fgnbIO;
		delete fgnbIO_2;
		return 0;
}

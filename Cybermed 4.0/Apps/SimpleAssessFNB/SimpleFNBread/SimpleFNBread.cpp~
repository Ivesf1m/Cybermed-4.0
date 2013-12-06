#include <cybermed/cybNaiveBayes.h>
#include <cybermed/cybNaiveBayesIO.h>
#include <iostream>

int main() {

		CybNaiveBayes* nb = new CybNaiveBayes(3);
		CybNaiveBayesIO* nbIO = new CybNaiveBayesIO("/root/nbTest");
		CybNaiveBayesIO* nbIO_2 = new CybNaiveBayesIO("/root/nbTest2");

		printf("%s", nbIO->getFile());

		//We dont need to read the parameters, we can call training() see more below
		//nb = (CybNaiveBayes*) nbIO->read()

		for (int i=0; i<nbIO->readData()->size(); i++)
		{
			nb->addData(nbIO->readData()->pos(i)); //adding data to list
		}	

		nb->training(); //calling training() to get parameters
		nbIO_2->write(nb); //writing parameters
		nbIO_2->writeData(nb); //writing data

		delete nb;
		delete nbIO;
		delete nbIO_2;
		return 0;
}

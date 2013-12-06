#include <cybermed/cybFuzzyNaiveBayes.h>
#include <cybermed/cybFuzzyNaiveBayesIO.h>
#include <iostream>

int main() {

		CybFuzzyNaiveBayes* fnb = new CybFuzzyNaiveBayes(3);
		CybFuzzyNaiveBayesIO* fnbIO = new CybFuzzyNaiveBayesIO("/root/fnbTest");
		CybFuzzyNaiveBayesIO* fnbIO_2 = new CybFuzzyNaiveBayesIO("/root/fnbTest2");

		printf("%s", fnbIO->getFile());

		//We dont need to read the parameters, we can call training() see more below
		//fnb = (CybFuzzyNaiveBayes*) fnbIO->read()

		for (int i=0; i<fnbIO->readData()->size(); i++)
		{
			fnb->addData(fnbIO->readData()->pos(i)); //adding data to list
		}	

		fnb->training(); //calling training() to get parameters
		fnbIO_2->write(fnb); //writing parameters
		fnbIO_2->writeData(fnb); //writing data

		delete fnb;
		delete fnbIO;
		delete fnbIO_2;
		return 0;
}

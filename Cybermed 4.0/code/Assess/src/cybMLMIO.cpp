#include "cybMLMIO.h"

CybMLMIO::CybMLMIO(char* file_name) : CybAssessIO(file_name, ".cyba_MLM")
{
	
}
		
void CybMLMIO::write(void* mlmObject)
{
	CybMLM* mlm = (CybMLM*) mlmObject;
	
	ofstream fout(this->getFile()); 
	
		if(fout.fail())
		{
			cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
			cout << flush;
			exit(0);
		}
		
	fout << "##" << mlm->getVariablesNumber(); 
	
	fout << "\n\nPrior Probability [ " << mlm->getPrioriProbability() << " ]";
		
	fout << "\n\nMean" << "\n[\n";
	

	for(int i=0; i < mlm->getVariablesNumber(); i++)
	{
		fout << mlm->getMean(i); 
	
			if(i < mlm->getVariablesNumber()-1)
				fout << ",\n";
	}
		fout << "\n]\n\n";
		
			fout << "Precision Matrix\n[\n";
		
			for(int i=0; i < mlm->getVariablesNumber(); i++)
			{
				for(int j=0; j < mlm->getVariablesNumber(); j++)
					fout << mlm->getCovariance()[i* mlm->getVariablesNumber() + j] << " ";
				fout << "\n";
			}
		fout << "]";	
	fout.close();
}
	
void* CybMLMIO::read()
{
	//cout << "entrou" << endl;
	ifstream fin(this->getFile());
	//cout << "passou" << endl;
	
	if(fin.fail())
	{
		cout << "Problemas na abertura do arquivo " << this->getFile() << endl;
		exit(0);
	}
	
	char c = 'a';
	int number = 0;
	float mean;
	int count = 0;
	float prob = 1.0;
	
	fin >> c;
	fin >> c;
	fin >> number;
	
	
	while(c != '[')
		fin >> c;
	
	fin >> prob;
	
	fin >> c;

	CybMLM* mlm = new CybMLM(number, prob);
	
	while(c != '[')
		fin >> c;
	
	while(c != ']')
	{
		fin >> mean;
		fin >> c;
	
		mlm->setMean(mean, count++);	
	}	

	while(c != '[')
		fin >> c;	
	
	float* matrix = new float[mlm->getVariablesNumber()*mlm->getVariablesNumber()];
	
	for(int i=0; i < mlm->getVariablesNumber()*mlm->getVariablesNumber(); i++)
		fin >> matrix[i];
	
	mlm->setCovariance(matrix);
	
	mlm->checkVariables();
	
	fin.close();
	
	return (void*) mlm;
}		

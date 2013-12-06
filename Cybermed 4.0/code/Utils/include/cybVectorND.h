#include "cybVector.h"

#ifndef _CYB_VECTORND_H_
#define _CYB_VECTORND_H_

template <class _TYPE = float> class CybVectorND : public CybVector<CybVectorND<_TYPE>,_TYPE>
{
private:
	int dimension;
	
public:
	
	CybVectorND(int dimension)
	{
		this->dimension = dimension;
		this->ELEMENTS = new _TYPE[dimension];
	}
	
	~CybVectorND() 
	{ 
		delete[] this->ELEMENTS;
	};
	
	int getDimension()
	{
		return this->dimension;
	}
	
	 _TYPE operator^(CybVectorND<_TYPE> vector)
	 {
		 _TYPE temp = 0;
		 
		 for(int i=0; i < this->dimension; i++)		
			 temp += this->ELEMENTS[i]*vector[i];		 
		 
	 	return temp;
	 }
	 
	CybVectorND<_TYPE> operator=(CybVectorND<_TYPE> vector)
 	{
		 for(int i=0; i < this->dimension; i++)		 
			 this->ELEMENTS[i] = vector[i];		 
 		
 		return *this;
 	}		
	
	bool operator==(CybVectorND<_TYPE> vector)
 	{
		 for(int i=0; i < this->dimension; i++)		
			 if(this->ELEMENTS[i] != vector[i])
				 return false;		 
 		
 		return true;
 	}	
	
	CybVectorND<_TYPE> operator+(CybVectorND<_TYPE> vector)
 	{
		CybVectorND<_TYPE> temp(this->dimension);
		
		 for(int i=0; i < this->dimension; i++)		 
			 temp[i] = this->ELEMENTS[i] + vector[i];		 
 		
 		return temp;
 	}
	
	CybVectorND<_TYPE> operator-(CybVectorND<_TYPE> vector)
 	{
		CybVectorND<_TYPE> temp(this->dimension);
		
		 for(int i=0; i < this->dimension; i++)		 
			 temp[i] = this->ELEMENTS[i] - vector[i];		 
 		
 		return temp;
 	}
	
	 CybVectorND<_TYPE> operator*(_TYPE k)
	 {
		 CybVectorND<_TYPE> temp(this->dimension);
		 
		 for(int i=0; i < this->dimension; i++)		 
			 temp[i] = this->ELEMENTS[i] * k;	
	 	
	 	return temp;	 	
	 } 
	
	 CybVectorND<_TYPE> operator/(_TYPE k)
	 {
		 CybVectorND<_TYPE> temp(this->dimension);
		 
		 for(int i=0; i < this->dimension; i++)		 
			 temp[i] = this->ELEMENTS[i] / k;	
	 	
	 	return temp;	 	
	 } 
	 
	/**
	* This method shows the vector
	*
	* @param void.
	* @return void.
	*
	*/	 
	 void show()
	 {
		 for(int i=0; i < this->dimension; i++)		 
					cout << this->ELEMENTS[i] << " ";
	 }

};

#endif /*_CYB_VECTORND_H_*/

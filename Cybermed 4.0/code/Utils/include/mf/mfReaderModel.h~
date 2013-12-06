#ifndef MFREADERMODEL_H
#define MFREADERMODEL_H

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfReader.h"
#include "mfWrlReader.h"
#include "mfX3dReader.h"
#include "mfVtkReader.h"
#include "mfReaderFactory.h"
#include <string>

using namespace std;

namespace mf
{
/**
	@class mfReaderModel
	@file mfReaderModel.h 
	@short
			
		This class can read models of the following types: vtk, wrl/vrml, x3d
	
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2012, May
*/



template <class _Traits> class mfReaderModel
{
	public:
		typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */
		
		/** Constructor */
		mfReaderModel();

		/** Destrutor */
		virtual ~mfReaderModel();
	
		/** Read the model indicate by parameter fileName
		@param sMesh* 
		@param const char*
		@return bool
		*/
		bool read(sMesh* malha, const char *filename);
		
		/** Read the model indicate by parameter fileName
		@param sMesh* 
		@param string
		@return bool
		*/
		bool read(sMesh* malha, string filename);
		
		/** Read the color model
		@param float[] 
		@param const char*
		@return bool
		*/
		bool readColor(float rgba[], const char *filename);
		
		/** Read the color model
		@param float[] 
		@param string
		@return bool
		*/		
		bool readColor(float rgba[], string filename);
	
	private:
		mfReader<_Traits> *reader;
};

//Constructor
template <class _Traits> mfReaderModel<_Traits>::mfReaderModel()
{
	reader = 0;
}

//Destructor
template <class _Traits> mfReaderModel<_Traits>::~mfReaderModel()
{

}


//read
template <class _Traits> bool mfReaderModel<_Traits>::read(sMesh* malha, const char *filename)
{
	reader = mfReaderFactory<_Traits>::getReader(filename);
	bool res = reader->read(malha, filename);
	
	delete reader;
	reader = 0;
	
	return res;
}

template <class _Traits> bool mfReaderModel<_Traits>::read(sMesh* malha, string filename)
{
	reader = mfReaderFactory<_Traits>::getReader(filename.c_str());
	bool res = reader->read(malha, filename.c_str());
	
	delete reader;
	reader = 0;
	
	return res;
}

//readColor
template <class _Traits> bool mfReaderModel<_Traits>::readColor(float rgba[], const char *filename)
{
	reader = mfReaderFactory<_Traits>::getReader(filename);
	bool res = reader->readColor(rgba, filename);
	
	delete reader;
	reader = 0;
	
	return res;
}


template <class _Traits> bool mfReaderModel<_Traits>::readColor(float rgba[], string filename)
{
	reader = mfReaderFactory<_Traits>::getReader(filename.c_str());
	bool res = reader->readColor(rgba, filename.c_str());
	
	delete reader;
	reader = 0;
	
	return res;
	
}


}

#endif

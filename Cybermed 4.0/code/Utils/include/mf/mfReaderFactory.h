#ifndef MFREADERFACTORY_H
#define MFREADERFACTORY_H

#include "mfWrlReader.h"
#include "mfX3dReader.h"
#include "mfVtkReader.h"
#include <cstring>
#include <string>
#include <cctype>

namespace mf
{

/**
	@class mfReaderFactory.h
	@file mfReaderFactory.h 
	@short
			
		This class returns the appropriate reader for the file.
	
	@author LabTEVE (http://www.de.ufpb.br/~labteve), Federal University of Paraiba
	@version 1.0
	@date 2012, May
*/

template <class _Traits> class mfReaderFactory 
{
	public:
		/** Factory that returns the appropriate reader for the file.
		@param const char*
		@return mfReader<_Traits> *
		*/
		static mfReader<_Traits> *getReader(const char *file) {
		char type[4];
		size_t size = strlen(file);
		//Isolate the file's extension
		type[0] = tolower(file[size - 3]);
		type[1] = tolower(file[size - 2]);
		type[2] = tolower(file[size - 1]);
		type[3] = '\0';
		string fileExt(type);
		
		//return the reader
		if (fileExt.compare("wrl") == 0) 
			return new mfWrlReader<_Traits>;
		
		if (fileExt.compare("x3d") == 0)
			return new mfX3dReader<_Traits>;	
			
		if (fileExt.compare("vtk") == 0)
			return new mfVtkReader<_Traits>;				
		
		
		return 0;	
			
		}

};

}

#endif

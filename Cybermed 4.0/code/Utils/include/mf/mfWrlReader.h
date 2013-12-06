#ifndef MFWRLREADER_H
#define MFWRLREADER_H

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfReader.h"

using namespace std;

namespace mf
{

template <class _Traits> class mfWrlReader : public mfReader<_Traits>
{
public:
	typedef typename _Traits::space space;		/**< Space typename definition */
	typedef typename _Traits::ids ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */

	/** Constructor */
	mfWrlReader();

	/** Destructor */
	~mfWrlReader();

	virtual bool read(sMesh* malha, const char* filename);

	virtual bool read(sMesh* malha, const char* filename, int cellDimension);
	
	virtual bool readColor(float rgba[], const char *filename);

private:
	bool reader(ifstream &pf, sMesh* malha);

	bool reader(ifstream &pf, sMesh* malha, int cellDimension);
};

template <class _Traits> mfWrlReader<_Traits>::mfWrlReader()
{
}

template <class _Traits> mfWrlReader<_Traits>::~mfWrlReader()
{
}

template <class _Traits> bool mfWrlReader<_Traits>::read(sMesh* malha, const char *filename)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);

	ifstream pf(filename);

	if( pf.is_open())
	{
		if(! reader(pf, malha))
			return false;

		pf.close();
	}
	else
		return false;

	return true;
}

template <class _Traits> bool mfWrlReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	char auxstr[255];
	space coords[3];
	int auxvtx[3];
	char c;

	MF_ASSERT(auxstr);
	
	pf >> auxstr;

	/* try to find 'point' tag */
	while( (! pf.eof()) && (strcmp(auxstr,"point") != 0) )
	{
		pf >> auxstr;
	}	
	if(pf.eof())
		return false;

	pf >> c;

	/* start to add 'space coords' to 'sMesh* malha' with 'addVertex' method */
	if( c == '[')
	{	
		pf >> c;	
		if(c == ']')
			return false;
			
		do{
			pf.putback(c);
			pf >> auxstr;
			coords[0] = atof(auxstr);
			pf >> auxstr;
			coords[1] = atof(auxstr);
			pf >> coords[2];
			malha->addVertex(coords);
			pf >> c;
			if(c ==',')
				pf >> c;
		}while(c == '-' || isdigit(c)); // verify if the next character is a number (negative or not)
			
		if(c != ']')
			return false;
	}
	else
		return false;

	/* try to find 'coordIndex' tag */
	while( (! pf.eof())&&(strcmp(auxstr,"coordIndex") != 0) )
	{
		pf >> auxstr;
	}
	if(pf.eof())
		return false;
	pf >> c;

	/* start to add 3d vector to 'sMesh* malhar' with 'addCell' method */
	if( c == '[' )
	{	
		pf >> c;
		if(c == ']')
			return false;
		
		do{
			pf.putback(c);
			pf >> auxstr;
			auxvtx[0] = atoi(auxstr);
			pf >> auxstr;
			auxvtx[1] = atoi(auxstr);
			pf >> auxvtx[2];
			malha->addCell(auxvtx);
				
			// if there isnt '-1' after, there isnt another cell to add
			pf >> c;
			if(c == ',')
				pf >> c;
			if(c != '-') // verify if there is another cell to add
				break;
			pf >> c;
			pf >> c;
			if(c == ',')
				pf >> c;
				
		}while(c == '-' || isdigit(c));
			
		if(c != ']')
			return false;
	}
	else
		return false;

	return true;
}


template <class _Traits> bool mfWrlReader<_Traits>::read(sMesh* malha, const char *filename, int cellDimension)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);

	ifstream pf(filename);

	if( pf.is_open())
	{
			if(! reader(pf, malha, cellDimension))
				return false;
		
			pf.close();
	}
	else
		return false;

	return true;
}

template <class _Traits> bool mfWrlReader<_Traits>::reader(ifstream &pf, sMesh* malha, int cellDimension)
{
	char auxstr[255];
	space coords[3];
	int j;
	int auxvtx[cellDimension];
	char c;

	MF_ASSERT(auxstr);

	pf >> auxstr;

	/* try to find 'point' tag */
	while( (! pf.eof()) && (strcmp(auxstr,"point") != 0) )
	{
		pf >> auxstr;
	}	
	if(pf.eof())
		return false;

	pf >> c;

	/* start to add 'space coords' to 'sMesh* malha' with 'addVertex' method */
	if( c == '[')
	{	
		pf >> c;	
		if(c == ']')
			return false;
			
		do{
			pf.putback(c);
			pf >> auxstr;
			coords[0] = atof(auxstr);
			pf >> auxstr;
			coords[1] = atof(auxstr);
			pf >> coords[2];
			malha->addVertex(coords);
			pf >> c;
			if(c ==',')
				pf >> c;
		}while(c == '-' || isdigit(c)); // verify if the next character is a number (negative or not)
			
		if(c != ']')
			return false;
	}
	else
		return false;

	/* try to find 'coordIndex' tag */
	while( (! pf.eof())&&(strcmp(auxstr,"coordIndex") != 0) )
	{
		pf >> auxstr;
	}
	if(pf.eof())
		return false;
	pf >> c;

	/* start to add 3d vector do 'sMesh* malhar' with 'addCell' method */
	if( c == '[' )
	{	
		pf >> c;
		if(c == ']')
			return false;
			
		do{
			pf.putback(c);
			for(j = 0;  j < cellDimension-1; j++)
			{
				pf >> auxstr;
				auxvtx[j] = atoi(auxstr);
			}
			pf >> auxvtx[j];
			
			malha->addCell(auxvtx);
		
			// if there isnt '-1' after, there isn't another cell to add
			pf >> c;
			if(c == ',')
				pf >> c;
			if(c != '-') // verify if there is another cell to add
				break;
			pf >> c;
			pf >> c;
			if(c == ',')
				pf >> c;
		}while(c == '-' || isdigit(c));
			
		if(c != ']')
			return false;
	}
	else
		return false;

	return true;
}

template <class _Traits> bool mfWrlReader<_Traits>::readColor(float rgba[], const char *filename) {
	ifstream inputFile;
	string word;
	char wordAux[10];
	int value;
	bool foundColor = false;

	inputFile.open( filename, ios::in );

	while(1)
	{
		inputFile >> word;

		if( word == "diffuseColor" )
		{
			inputFile >> word;
			value = word.copy(wordAux, 8, 0);
			wordAux[value] = '\0';
			rgba[0] = atof(wordAux);

			inputFile >> word;
			value = word.copy(wordAux, 8, 0);
			wordAux[value] = '\0';
			rgba[1] = atof(wordAux);

			inputFile >> word;
			value = word.copy(wordAux, 8, 0);
			wordAux[value] = '\0';
			rgba[2] = atof(wordAux);
			
			rgba[3] = 1;

			foundColor = true;
		}

		// protection for wrl files that don't have the models color.
		if( word == "IndexedFaceSet" )
		{
			if(foundColor == false)
			{
				/*Set default color*/
				
				rgba[0] = 1;
				rgba[1] = 1;
				rgba[2] = 1;
				rgba[3] = 1;
			} //if
			break;
		} //if
	} // while
	
	inputFile.close();
	return true;
} //end readColor

}

#endif

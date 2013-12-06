#ifndef MFOBJREADER_H
#define MFOBJREADER_H

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <vector>

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfReader.h"

using namespace std;

namespace mf
{

template <class _Traits> class mfObjReader : public mfReader<_Traits>
{
	public:
		typedef typename _Traits::space space;		/**< Space typename definition */
		typedef typename _Traits::ids ids;		/**< Id typename definition */
		typedef typename _Traits::sVertex sVertex;	/**< Vertex typename definition */
		typedef typename _Traits::sCell sCell;		/**< Cell typename definition */
		typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */

		/** Constructor */
		mfObjReader();

		/** Destructor */
		~mfObjReader();

		virtual bool read(sMesh* malha, const char* filename);
	
		virtual bool readColor(float rgba[], const char *filename);

	private:
		bool reader(ifstream &pf, sMesh* malha);

};

template <class _Traits> mfObjReader<_Traits>::mfObjReader()
{
}

template <class _Traits> mfObjReader<_Traits>::~mfObjReader()
{
}

template <class _Traits> bool mfObjReader<_Traits>::read(sMesh* malha, const char *filename)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);

	ifstream pf(filename, ios::in);

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

template <class _Traits> bool mfObjReader<_Traits>::reader(ifstream& pf, sMesh* malha)
{
	space coords[3];
	int auxvtx[3];
	int test;
	bool isFaceSet = false;

	string aux;
	string v("v");
	string f("f");
	
	while(!pf.eof()){
		pf >> aux;
		if(aux.compare(v) == 0){
			pf >> coords[0] >> coords[1] >> coords[2];
			malha->addVertex(coords);
		}
		if(aux.compare(f) == 0){
			int fn;
			char slash;
			pf >> auxvtx[0] >> slash >> slash >> fn;
			pf >> auxvtx[1] >> slash >> slash >> fn;
			pf >> auxvtx[2] >> slash >> slash >> fn;
			malha->addCell(auxvtx);
		}
		if(!pf.good()) return false;
	}

	int numVerts = malha->getNumberOfVertices();
	for(int i = 0; i < numVerts; ++i){
		malha->updateVertexNormalVector(i);
	}

	return true;
	
}

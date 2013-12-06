#ifndef MFX3DREADER_H
#define MFX3DREADER_H

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

template <class _Traits> class mfX3dReader : public mfReader<_Traits>
{
public:
	typedef typename _Traits::space space;		/**< Space typename definition */
	typedef typename _Traits::ids ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */

	/** Constructor */
	mfX3dReader();

	/** Destructor */
	~mfX3dReader();

	virtual bool read(sMesh* malha, const char* filename);
	
	virtual bool readColor(float rgba[], const char *filename);

private:
	bool reader(ifstream &pf, sMesh* malha);

};

template <class _Traits> mfX3dReader<_Traits>::mfX3dReader()
{
}

template <class _Traits> mfX3dReader<_Traits>::~mfX3dReader()
{
}

template <class _Traits> bool mfX3dReader<_Traits>::read(sMesh* malha, const char *filename)
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

template <class _Traits> bool mfX3dReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	space coords[3];
	int auxvtx[3];
	int test;
	bool isFaceSet = false;
	
	string auxstr;
	string triangleSet("<IndexedTriangleSet");
	string faceSet("<IndexedFaceSet");
	string index("index=");
	string coordIndex("coordIndex");
	string point("point");
	string stop;
	
	char c;
	
	pf >> auxstr;

	// try to find 'point' tag 
	while( (!pf.eof()) && auxstr.find(triangleSet) == string::npos && auxstr.find(faceSet) == string::npos) {
		pf >> auxstr;
		//cout << auxstr << endl;
	}	
	if(pf.eof()) {
		cout << "end of file while read the model" << endl;
		exit(1);
	}	
	//verifica se é faceset ou triangleset
	if (auxstr.compare(faceSet) == 0) {
		isFaceSet = true;
		stop = coordIndex;
	}
	else {
		stop = index;
	}
		
		
	while( (!pf.eof()) && (auxstr.find(stop) == string::npos) ) {
		pf >> auxstr;
	}
	if(pf.eof()) {
		cout << "end of file while read the model" << endl;
		exit(1);		
	}	
		
	size_t numPos = auxstr.find("\"");		
	
	string num = auxstr.substr(numPos + 1, auxstr.size() - 1);
		
	auxvtx[0] = atoi(num.c_str());
	pf >> auxvtx[1];
	pf >> auxvtx[2];
	if (isFaceSet) {
		pf >> test;		
		if (test != -1) {
			cout << "The model must have triangles!" << endl;
			exit(1);
		}
	}
	malha->addCell(auxvtx);
	pf >> c;
	
	while (isdigit(c)) {		
		pf.putback(c);		
		pf >> auxvtx[0];		
		pf >> auxvtx[1];		
		pf >> auxvtx[2];		
			
		if (isFaceSet) {
		
			pf >> test;		
			
			if (test != -1) {			
				cout << "The model must have triangles!" << endl;					
				exit(1);
			}
		}	
		malha->addCell(auxvtx);			
		pf >> c;			
	}		
	
	//pega os pontos
	while( (!pf.eof()) && (auxstr.find(point) == string::npos)) {
		pf >> auxstr;
		//cout << auxstr << endl;
	}	
	if(pf.eof()) {
		cout << "end of file while read the model" << endl;
		exit(1);		
	}	
		
	numPos = auxstr.find("\"");		
		
	num = auxstr.substr(numPos + 1, auxstr.size() - 1);
	
		
	coords[0] = strtod(num.c_str(), NULL);
	pf >> coords[1];
	pf >> coords[2];
	
	malha->addVertex(coords);
		
	pf >> c;	
	
	while (isdigit(c) || c == '-') {
		pf.putback(c);
		pf >> coords[0];
		pf >> coords[1];
		pf >> coords[2];
		malha->addVertex(coords);

		pf >> c;		
	}
	return true;
}

template <class _Traits> bool mfX3dReader<_Traits>::readColor(float rgba[], const char *filename) {

	rgba[0] = 1;
	rgba[1] = 0;
	rgba[2] = 0;
	rgba[3] = 1;
	
	return true;
} //end readColor

}

#endif

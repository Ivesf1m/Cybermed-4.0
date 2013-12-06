#ifndef MFPLYREADER_H
#define MFPLYREADER_H

#include <fstream>

#include "mfMacros.h"
#include "mfMesh.h"
#include "mfReader.h"

using namespace std;

namespace mf
{

template <class _Traits> class mfPlyReader : public mfReader<_Traits>
{
public:
	typedef typename _Traits::space		space;		/**< Space typename definition */
	typedef typename _Traits::ids		ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex	sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell		sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition */

	/** Constructor */
	mfPlyReader();
	
	/** Destructor */
	~mfPlyReader();

	virtual bool read(sMesh* malha, const char* filename);

	virtual bool read(sMesh* malha, const char* filename, int cellDimension);

private:

	bool reader(ifstream &pf, sMesh* malha);

	bool reader(ifstream &pf, sMesh* malha, int cellDimension);
};

template <class _Traits> mfPlyReader<_Traits>::mfPlyReader()
{
}

template <class _Traits> mfPlyReader<_Traits>::~mfPlyReader()
{
}

template <class _Traits> bool mfPlyReader<_Traits>::read(sMesh* malha, const char *filename)
{
	MF_ASSERT(filename);
	MF_ASSERT(malha);

	ifstream pf(filename);

	if(pf.is_open())
	{
		if(! reader(pf, malha))
			return false;

		pf.close();
	}
	else
		return false;

	return true;
}

template <class _Traits> bool mfPlyReader<_Traits>::reader(ifstream &pf, sMesh* malha)
{
	char auxstr[255];
	space coords[3], bin;
	sCell cell;
	int i, j;
	int numVertex, numFace;
	int auxvtx[4]; //cell.getNumberVerticesInCell()
	int vPropertyJump = -3, idnv;
	char c;
	
	//cout << cell.getDimension()+1 << endl;

	MF_ASSERT(auxstr);

	// Num of vertices
	while((! pf.eof())&&(strcmp(auxstr,"vertex") != 0))
	{
		pf >> auxstr;
	}

	pf >> numVertex;

	while((! pf.eof())&&(strcmp(auxstr,"property") != 0))
	{
		pf >> auxstr;
	}

	while((! pf.eof())&&(strcmp(auxstr,"property") == 0))
	{
		vPropertyJump++;
		pf >> auxstr; //float...
		pf >> auxstr; //id
		pf >> auxstr; //property
	}

	// Num of faces
	while((! pf.eof())&&(strcmp(auxstr,"face") != 0))
	{
		pf >> auxstr;
	}

	pf >> numFace;

	while((! pf.eof()) && (strcmp(auxstr,"end_header") != 0))
	{
		pf >> auxstr;
	}

	if(! pf.eof())
	{
		//coords
		for(i = 0; i<numVertex; i++)
		{
			for(j = 0; j < 3; j++)
			{
				pf >> coords[j];
				//cout << j << ": " << coords[j] << endl;
			}

			for(j = 0; j < vPropertyJump; j++)
			{
				pf >> bin;
			}

			malha->addVertex(coords);
		}

		//faces
		for(i = 0; i<numFace; i++)
		{
			pf >> idnv;
			
			MF_ASSERT(idnv <= 4); //cell.getNumberVerticesInCell()
			//cout << cell.getDimension() << endl;
			
			for(j = 0; j < idnv; j++)
			{
				pf >> auxvtx[j];
			}
			for(j=idnv; j < 4; j++) //cell.getNumberVerticesInCell()
			{
				auxvtx[j] = -1;
			}

// 			if(idnv == 3)
// 			{
// 				auxvtx[3] = -1;
// 			}

			malha->addCell(auxvtx);
		}
	}
	else
		return false;

	return true;
}


template <class _Traits> bool mfPlyReader<_Traits>::read(sMesh* malha, const char *filename, int cellDimension)
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

template <class _Traits> bool mfPlyReader<_Traits>::reader(ifstream &pf, sMesh* malha, int cellDimension)
{
	char auxstr[255];
	space coords[3], bin;
	int i, j;
	int numVertex, numFace;
	int auxvtx[cellDimension];
	int vPropertyJump = -3, faceType;
	char c;

	MF_ASSERT(auxstr);

	// Num of vertices
	while((! pf.eof())&&(strcmp(auxstr,"vertex") != 0))
	{
		pf >> auxstr;
		//cout << "\nValor: " << auxstr;
	}

	pf >> numVertex;
	//cout << "Num Vertices " << numVertex << endl;

	while((! pf.eof())&&(strcmp(auxstr,"property") != 0))
	{
		pf >> auxstr;
		//cout << "\nValor: " << auxstr;
	}

	while((! pf.eof())&&(strcmp(auxstr,"property") == 0))
	{
		vPropertyJump++;
		pf >> auxstr; //float...
		pf >> auxstr; //id
		pf >> auxstr; //property
	}

	// Num of faces
	while((! pf.eof())&&(strcmp(auxstr,"face") != 0))
	{
		pf >> auxstr;
		//cout << "\nValor: " << auxstr;
	}

	pf >> numFace;
	//cout << "Num Faces " << numFace << endl;

	while((! pf.eof()) && (strcmp(auxstr,"end_header") != 0))
	{
		pf >> auxstr;
		//cout << "\nValor: " << auxstr;
	}

	//start reading data
	if(! pf.eof())
	{
		//coords
		for(i = 0; i<numVertex; i++)
		{
			for(j = 0; j < 3; j++)
			{
				pf >> coords[j];
				//cout << j << ": " << coords[j] << endl;
			}

			for(j = 0; j < vPropertyJump; j++)
			{
				pf >> bin;
			}

			malha->addVertex(coords);
		}
		//faces
		for(i = 0; i<numFace; i++)
		{
			pf >> faceType;
			for(j = 0; j < faceType; j++)
			{
				pf >> auxvtx[j];
			}

			if(faceType == 3)
			{
				auxvtx[3] = -1;
			}

			malha->addCell(auxvtx);
		}
	}
	else
		return false;


	return true;
}

}

#endif

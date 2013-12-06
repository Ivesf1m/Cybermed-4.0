#ifdef MF_THREADS

#ifndef MFTREADER_H
#define MFTREADER_H

#include "mfMacros.h"
#include "mfMesh.h"

namespace mf
{
	
//! Modelo dos leitores de arquivos
/*!
*/
template <class sTraits> class mfTReader
{
public:
	typedef typename sTraits::ids ids;
	
	typedef typename _Traits::sMesh		sMesh;

	/** Construtor 
	*
	* \param
	*/
	mfTReader(int threads_vertices, int threads_cells);

	/** Destructor */
	virtual ~mfTReader();

	void setNumberOfThreads(int threads_vertices, int threads_cells);
	
	//! Executa a leitura de um arquivo
	/*!
	Parametros de entrada:
	malha : endereco de memoria de destino da malha a ser carregada. Ja deve estar alocado.
	filename : nome do arquivo da malha.
	*/
	virtual bool read(sMesh* malha, char* xml) = 0;

protected:

	struct mfTReaderData
	{
		char *str;
	
		ids id;
		ids start;
		ids end;
		sMesh *malha;
		mfXmlParser *config;
		
	};

	int nthreadsv, nthreadsc;
};

template <class sTraits> mfTReader<sTraits>::mfTReader(int threads_vertices, int threads_cells)
{
	setNumberOfThreads(threads_vertices, threads_cells);
}

template <class sTraits> mfTReader<sTraits>::~mfTReader()
{
}

template <class sTraits> void mfTReader<sTraits>::setNumberOfThreads(int threads_vertices, int threads_cells)
{
	MF_ASSERT(threads_vertices > 0);
	MF_ASSERT(threads_cells > 0);

	nthreadsv = threads_vertices;
	nthreadsc = threads_cells;
}

}

#endif
#endif

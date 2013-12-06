#ifndef MFWRITER_H
#define MFWRITER_H

#include "mfMacros.h"
#include "mfMesh.h"

namespace mf
{

//! Modelo dos escritores de arquivos
/*!
Esta classe eh abstrata, devendo servir apenas de molde para novas implementacoes de escritores de arquivos.
*/
template <class _Traits>  class mfWriter
{
public:

	typedef typename _Traits::sMesh		sMesh;

	/** Construtor */
	mfWriter();

	/** Destrutor */
	virtual ~mfWriter();
	
	//! Executa a escrita de um arquivo (salva uma malha)
	/*!
	Paraetros de entrada:
	malha : endereco de memoria da malha a ser salva.
	filename : nome do arquivo da malha. (destino)
	*/
	virtual bool write(sMesh* malha, const char* filename) = 0;
};

template <class _Traits>  mfWriter<_Traits>::mfWriter()
{
}

template <class _Traits>  mfWriter<_Traits>::~mfWriter()
{
}

}

#endif

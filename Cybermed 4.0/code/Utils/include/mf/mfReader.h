#ifndef MFREADER_H
#define MFREADER_H

#include "mfMacros.h"
#include "mfMesh.h"

namespace mf
{

//! Modelo dos leitores de arquivos
/*!
Esta classe eh abstrata, devendo servir apenas de molde para novas implementacoes de leitores de arquivos.
*/
template <class _Traits> class mfReader
{
public:
	typedef typename _Traits::space space;		/**< Space typename definition */
	typedef typename _Traits::ids ids;		/**< Id typename definition */
	typedef typename _Traits::sVertex sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell sCell;		/**< Cell typename definition */
	typedef typename _Traits::sMesh sMesh;		/**< Mesh typename definition */

	/** Construtor */
	mfReader();

	/** Destrutor */
	virtual ~mfReader();
	
	//! Executa a leitura de um arquivo
	/*!
	Paraetros de entrada:
	malha : endereco de memoria de destino da malha a ser carregada. Ja deve estar alocado.
	filename : nome do arquivo da malha.
	*/
	virtual bool read(sMesh* malha, const char* filename) = 0;
	
	virtual bool readColor(float rgba[], const char *filename) = 0;
};

template <class _Traits> mfReader<_Traits>::mfReader()
{
}

template <class _Traits> mfReader<_Traits>::~mfReader()
{
}

}

#endif

#ifndef	MFSEARCHDIDO_H
#define	MFSEARCHDIDO_H

#include "mfMacros.h"
#include "mfBase.h"

namespace mf
{

template <class _Traits> class mfSearchDIDO 
{
public:	
	typedef typename _Traits::sVertex 	sVertex;	/**< Vertex typename definition */
	typedef typename _Traits::sCell 	sCell;		/**< Cell typename definition */
	typedef typename _Traits::ids 		ids;		/**< Id typename definition */
	typedef typename _Traits::space		space;		/**< Space typename definition */
	typedef typename _Traits::sGeometric sGeometric;	/**< Geometric typename definition */
	typedef typename _Traits::sMesh		sMesh;		/**< Mesh typename definition */

	/** Construtor 
	 *
	 * \param _mesh: the mesh address that this class will manipulate
	 */
	mfSearchDIDO(sMesh *_mesh);

	/** Destrutor */
	~mfSearchDIDO();

	int dido(sVertex *_v, space *coords, ids &idcelula, int &lado);

	/** Set the mesh instance to which this class will manipulate.
	 *
	 * \param _mesh: the mesh address that this class will manipulate
	 */
	void setMesh(sMesh *_mesh);

private:
	sMesh *mesh;		/**< The mesh that this class will manipulate */
	sGeometric geom;	/**< Geometric operator instance */
};

template <class _Traits> mfSearchDIDO<_Traits>::mfSearchDIDO(sMesh *_mesh)
{
	
	mesh = _mesh;
	geom.setMesh(mesh);
}

template <class _Traits> mfSearchDIDO<_Traits>::~mfSearchDIDO() 
{
}

template <class _Traits> void mfSearchDIDO<_Traits>::setMesh(sMesh *_mesh)
{
	MF_ASSERT(_mesh);
	mesh = _mesh;
}

template<class _Traits> int mfSearchDIDO<_Traits>::dido(sVertex *_v, space *coords, ids &idcelula, int &lado)
{
	//Retorna 0 caso esteja dentro
	//Retorna 1 caso esteja fora
	//Retorna 2 caso esteja sobre a aresta lado
	//Retorna 3 caso seja um vertice repetido

	MF_ASSERT(mesh);
	
	sCell* auxc = NULL;
	sVertex *v[3];
	ids icell, iauxc = 0;
	int sobre, left, retorno = -1;
		
	MF_ASSERT(_v->getNumberOfSings() == 1); // nao permite vertice singular ou isolado
	
	iauxc = _v->getSingCell(0);
	auxc = mesh->getCell(iauxc MF_MUTEXV);
	
	lado = 0;
	
	while(retorno < 0)
	{
		v[0] = mesh->getVertex(auxc->getVertexId(lado MF_MUTEXFALSEV) MF_MUTEXV);
		v[1] = mesh->getVertex(auxc->getVertexId((lado+1)%3 MF_MUTEXFALSEV) MF_MUTEXV);
		v[2] = mesh->getVertex(auxc->getVertexId((lado+2)%3 MF_MUTEXFALSEV) MF_MUTEXV);
		sobre = -1;
		
		left = geom.inLeft(v[0],v[1],coords[0], coords[1] MF_MUTEXFALSEV);
		
		if(left == 0)
		{
			if (auxc->getMateId((lado+2)%3 MF_MUTEXFALSEV) >= 0)
			{
				icell = iauxc;
				iauxc = auxc->getMateId((lado+2)%3 MF_MUTEXFALSEV);
				auxc = mesh->getCell(iauxc MF_MUTEXV);
				lado = (auxc->getMateIndex(icell MF_MUTEXFALSEV) + 2)%3;
			}
			else
			{
				lado = (lado+2)%3;
				idcelula = iauxc;
				retorno = 1;
			}
		}
		else
		{
			if(left == 2)
				sobre = (lado+2)%3;
							
			left = geom.inLeft(v[1],v[2],coords[0], coords[1] MF_MUTEXFALSEV);
			if(left == 0)
			{
				if (auxc->getMateId(lado MF_MUTEXFALSEV) >= 0)
				{
					icell = iauxc;
					iauxc = auxc->getMateId(lado MF_MUTEXFALSEV);
					auxc = mesh->getCell(iauxc MF_MUTEXV);
					lado = (auxc->getMateIndex(icell MF_MUTEXFALSEV) + 2)%3;
				}	
				else
				{
					//lado = lado;
					idcelula = iauxc;
					retorno = 1;
				}
			}
			else
			{
				if (left == 2)
				{
					if(sobre >= 0)
					{
						lado = (lado+1)%3;
						idcelula = iauxc;
						retorno = 3;
					}
					else
						sobre = lado;
				}
				
				if(retorno < 0)
				{
					left = geom.inLeft(v[2],v[0],coords[0], coords[1] MF_MUTEXFALSEV);
					
					if(left == 0)
					{
						if (auxc->getMateId((lado+1)%3 MF_MUTEXFALSEV) >= 0)
						{
							icell = iauxc;
							iauxc = auxc->getMateId((lado+1)%3 MF_MUTEXFALSEV);
							auxc = mesh->getCell(iauxc MF_MUTEXV);
							lado = (auxc->getMateIndex(icell MF_MUTEXFALSEV) + 2)%3;
						}
						else
						{
							lado = (lado+1)%3;
							idcelula = iauxc;
							retorno = 1;
						}						
					}
					else
					{
						if(left == 2)
						{
							if(sobre >= 0)
							{
								idcelula = iauxc;
								
								if(sobre == lado)								
									lado = (lado+2)%3;
									
								retorno = 3;
							}
							else
							{
								idcelula = iauxc;
								lado = (lado+1)%3;
								retorno = 2;
							}
						}
						else
						{			
							if(sobre >= 0)
							{
								idcelula = iauxc;
								lado = sobre;
								retorno = 2;
							}	
							else
							{
								idcelula = iauxc;
								lado = -1;
								retorno = 0;
							}
						}
					}
				}
			}
		}
	}

	return retorno;	
}

}
#endif

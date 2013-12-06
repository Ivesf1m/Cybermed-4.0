#ifndef MFVECTOR_H
#define MFVECTOR_H

#include "mfMacros.h"

namespace mf
{

/**
 *	@class		mfVector
 *	@file		mfVector.h
 *	@short
 *	Base vector class
 *	This is a block allocation version of vector with free space management.
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template <class T, class ids> class mfVector
{
public:

	/**	Constructor
	 *
	 *	\param block_size: the size of each block (The maximum capacity of vector if : block_size * block_size)
	 */
	mfVector(ids block_size);

	/**	Destructor
	 */
	~mfVector();

	/** Return the specified element
	 *
	 * \param index: position of element
	 */
	T& operator[](ids index);

	/**	Return a free position in vector
	 */
	ids getFree();

	/**	Define the number of elements in vector
	 *
	 * 	(DONT USE)
	 */
	void setSize(ids size);

	/**	Return the number of elements in vector
	 */
	ids getSize();

	/**	Return the maximum position in vector
	 */
	ids getMaxId();

	/**	Delete a position in vector
	 *
	 * 	\return true if this position was deleted
	 */
	bool free(ids index);

private:

	T** vetor;		/**< Vector definition */
	int block;		/**< Block size of the vector */

	ids  nt;		/**< Number of elements in the vector */
    ids ntmax;		/**< Number of maximum possible elements in the vector */
    ids first;		/**< First elemente in the vector */
    ids last;		/**< Last elemente in the vector */
	bool hasfree;	/**< Indicates if vector has free space */
};

template <class T, class ids> mfVector<T,ids>::mfVector(ids block_size)
{
	MF_ASSERT(block_size > 0);
	block = block_size;

	vetor = new T*[block];

	MF_ASSERT(vetor);

	for(ids index=0; index < block; index++)
		vetor[index] = NULL;

	nt = ntmax = 0;
	hasfree = false;
}

template <class T, class ids> mfVector<T,ids>::~mfVector()
{
	for(ids index=0; index < block; index++)
		if(vetor[index])
			delete [] vetor[index];

		delete [] vetor;
}

template <class T, class ids> T& mfVector<T,ids>::operator [](ids index)
{
	MF_ASSERT(index >= 0);

	if(vetor[index / block])
		return vetor[index / block][index % block];
	else
	{
		vetor[index / block] = new T[block];
		MF_ASSERT(vetor[index / block]);
		return vetor[index / block][index % block];
	}
}

template <class T, class ids> ids mfVector<T,ids>::getFree()
{
	ids i;

	if (!hasfree)
	{
		i = ntmax;
		ntmax++;
	}
	else
	{
		i = first;

		if(last == first)
			hasfree = false;
		else
#ifdef MF_THREADS
			first = (*this)[i].getPosition(false);
#else
			first = (*this)[i].getPosition();
#endif
	}

#ifdef MF_THREADS
	(*this)[i].setInMesh(true, false);
#else
	(*this)[i].setInMesh(true);
#endif
	nt++;

	return i;
}
	
template <class T, class ids> void mfVector<T,ids>::setSize(ids size)
{
	if(ntmax < size)
		ntmax = size; 

	nt = size;
}

template <class T, class ids> ids mfVector<T,ids>::getSize()
{
	return nt;
}

template <class T, class ids> ids mfVector<T,ids>::getMaxId()
{
	return ntmax;
}

template <class T, class ids> bool mfVector<T,ids>::free(ids index)
{
	MF_ASSERT(index >= 0);

	T* v = &(*this)[index];

	MF_ASSERT(v->inMesh());
	if(hasfree)
	{
#ifdef MF_THREADS
		v->setPosition(first, false);
#else
		v->setPosition(first);
#endif
		first = index;
	}
	else
	{
#ifdef MF_THREADS
	v->setInMesh(false, false);
#else
	v->setInMesh(false);
#endif
		hasfree = true;
		first = index;
		last = first;
	}
	nt--;

	return true;
}

}

#endif

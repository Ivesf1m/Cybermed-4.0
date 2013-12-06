#ifndef MFLIST_H
#define MFLIST_H

#include "mfMacros.h"

namespace mf
{

/**
 *	@class		mfListNode
 *	@file		mfList.h
 *	@short
 *	Node Class
 *	Node of mfList. T is a type of element to be listed.
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template<class T> class mfListNode
{
public:

	/** Constructor */
	mfListNode();

	/** Destructor */
	~mfListNode();

	/** Define the element in list node 
     *
     * 	\param info: node element of type T
     */
	void	setInfo(T info) {atu=info;};

	/** Return the element in list node */
	T getInfo() {return atu;};

	/** Define the next node 
	 *
     * 	\param prox: next element on the list
     */
	void	setNext(mfListNode<T> *prox){next=prox;};
	
	/** Return the next node */
	mfListNode<T>*	getNext(){return next;};

protected:
	T	atu;				/**< Node element of type T */
	mfListNode<T>*	next;	/**< Reference to the next element of the list */
};

template<class T> mfListNode<T>::mfListNode()
{
	next = NULL;
};

template<class T> mfListNode<T>::~mfListNode()
{
};

/**
 *	@class		mfList
 *	@file		mfList.h
 *	@short
 *	List Class
 *	Dynamic single linked list. T is a type of element to be listed.
 *
 *	@author		Mario Lizier
 *	@version	1.0
 *	@date		2007, july
 */
template<class T> class mfList
{
public:

	/** Constructor */
	mfList();

	/** Destructor */
	~mfList();

	/** Return a element of the specified position
	 * 
	 * 	\param pos: position of the element
	 */
	T	pos(int pos);

	/**	Return the first element */
	T	first();

	/**  Return the last element (faster than pos(size() - 1) )
	 */
	T	last();

	/**	Return the number of elements in list */
	int size();

	/** Insert a element in list (in last position)
	 * 
	 * 	\param novo: element will be inserted
	 */
	void insert(T novo);

	/** Insert a element in list, only if this element isnt in list. (in last position)
	 * 
	 * 	\param novo: element
	 */
	bool insertOnlyOne(T novo);

	/** Insert a element in first position of list
	 * 
	 * 	\param novo: element
	 */
	void insertFirst(T novo);

	/** Insert a element in the specified position of list
	 * 
	 * 	\param novo: element
	 * 	\param pos: position
	 */
	void insert(T novo, int pos);

	/** Delete a element
	 * 
	 * 	\param pos: position of element
	 */
	bool  erase(int pos);

	/** Return true if the element is inlist */
	bool	inList(T info);

	/**	Return the position of a element, -1 if isnt in list
	 */
	int 	search(T info);

	/** Delete all element of list
	 */
	void  clear();

	/** Return true if list dont have any element
	 *
	 */
	bool  empty();

protected:
	int lsize;			/**< List size */
	mfListNode<T>*	lfirst;		/**< First node on list */
	mfListNode<T>*  llast;		/**< Last node on list */
};

template<class T> mfList<T>::mfList() //construtor
{
	lfirst = NULL;
	llast = NULL;
	lsize = 0;
};

template<class T> mfList<T>::~mfList()
{
	clear();
};

template<class T> T mfList<T>::pos(int pos)
{
	MF_ASSERT((pos >=0)&&(pos < lsize));
	
	mfListNode<T> *p = lfirst;
	
	for(int i=0; i<pos; i++)
	{
		MF_ASSERT(p);
		p = p->getNext();
	}
	
	return p->getInfo();
};

template<class T> T mfList<T>::first()
{
	MF_ASSERT(lfirst);
	return lfirst->getInfo();
};

template<class T> T mfList<T>::last()
{
	MF_ASSERT(llast);
	return llast->getInfo();
};

template<class T> int mfList<T>::size()
{
	return lsize;
}

template<class T> void mfList<T>::insert(T novo)
{
	mfListNode<T> *t = new mfListNode<T>();

	MF_ASSERT(t);

	t->setInfo(novo);
	if (lsize==0)
		lfirst = t;
	else
	{
		MF_ASSERT(llast);
		llast->setNext(t);
	}
	llast = t;
	lsize++;
};

template<class T> bool mfList<T>::insertOnlyOne(T novo)
{
	if (lsize==0)
	{
		mfListNode<T> *t = new mfListNode<T>();
		MF_ASSERT(t);

		t->setInfo(novo);
		t->setNext(NULL);
		lfirst = t;
		llast = t;
	}
	else
	{
		mfListNode<T> *point = lfirst;
		MF_ASSERT(point);

		while((point->getNext()!=NULL)&&(point->getInfo() != novo))
		{
			point = point->getNext();
			MF_ASSERT(point);
		}

		if(point->getInfo() != novo)
		{
			mfListNode<T> *t = new mfListNode<T>();

			MF_ASSERT(t);

			t->setInfo(novo);
			t->setNext(NULL);
			point->setNext(t);
			llast = t;
		}
		else
			return false;
	};
	lsize++;

	return true;
};

template<class T> void mfList<T>::insertFirst(T novo)
{
	mfListNode<T> *t = new mfListNode<T>();

	MF_ASSERT(t);

	t->setInfo(novo);
	t->setNext(lfirst);
	lfirst = t;
	if(lsize==0) llast = lfirst;
	lsize++;
};

template<class T> void mfList<T>::insert(T novo, int pos)
{
	MF_ASSERT((pos >=0)&&(pos <= lsize));

	mfListNode<T> *t = new mfListNode<T>();

	MF_ASSERT(t);

	t->setInfo(novo);
	if ((pos==0)||(lsize==0))
	{
		t->setNext(lfirst);
		lfirst = t;
		if (lsize==0) llast = t;
	}
	else
	{
		mfListNode<T> *point=lfirst;
		MF_ASSERT(point);
		int i;
		for(i=1; (i<pos)&&(point->getNext()!=NULL); i++)
		{
			point = point->getNext();
			MF_ASSERT(point);
		}
		t->setNext(point->getNext());
		point->setNext(t);
		if (pos>=lsize) llast = t;
	};
	lsize++;
};

template<class T> bool mfList<T>::erase(int pos)
{
	MF_ASSERT((pos >=0)&&(pos < lsize));

	mfListNode<T> *p,*a;

	if (pos ==0)
	{
		p = lfirst;
		MF_ASSERT(lfirst);
		lfirst = lfirst->getNext();
		if (lsize==1) llast = NULL;
		delete p;
	}
	else
	{
		a = lfirst;
		MF_ASSERT(lfirst);
		p = lfirst->getNext();
		for(int i=1; i<pos; i++)
		{
			a = p;
			MF_ASSERT(p);
			p = p->getNext();
		};

		a->setNext(p->getNext());
		if(pos==(lsize-1)) llast = a;
		delete p;
	};
	lsize--;
	return true;
};

template<class T> bool mfList<T>::inList(T info)
{
	if (lsize==0) return false;

	mfListNode<T> *p=lfirst;

	MF_ASSERT(p);

	for(int i=0; (p->getInfo()!=info)&&(i<lsize);i++)
	{
		if (p->getNext() != NULL) p=p->getNext();
		MF_ASSERT(p);
	}
	return (p->getInfo()==info);
};

template<class T> int mfList<T>::search(T info)
{
	int i;

	if (lsize==0) return -1;

	mfListNode<T> *p=lfirst;

	MF_ASSERT(p);

	for(i=0; (p->getInfo()!=info)&&(i<lsize);i++)
	{
		if (p->getNext() != NULL) p=p->getNext();
		MF_ASSERT(p);
	}
	if(p->getInfo()==info)
		return i;
	else
		return -1;
};

template<class T> void mfList<T>::clear()
{
	while(lsize > 0)
		erase(0);

	lsize = 0;
	lfirst=NULL;
	llast=NULL;
};

template<class T> bool mfList<T>::empty()
{
	return (lsize == 0);
};

}

#endif

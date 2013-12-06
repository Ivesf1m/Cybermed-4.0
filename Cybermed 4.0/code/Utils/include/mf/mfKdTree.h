#ifndef	MFKDTREE_H
#define	MFKDTREE_H

#include "mfMacros.h"
#include "mfList.h"

namespace mf
{

template<class sObject> struct mfKdTreeNode
{
    sObject	ptr;
    mfKdTreeNode *p[2];
};


template <class sObject, class sObjectCompare> class mfKdTree
{
public:

	/** Constructor */
	mfKdTree(int dim);

	/** Destructor */
	~mfKdTree();

	void insert(sObject obj);
	//bool erase(sObject obj);
	
	sObject nearest(sObject obj);
	sObject nearestAndInsert(sObject obj);

	int size();

private:

	mfKdTreeNode<sObject> *add(sObject obj);
	mfKdTreeNode<sObject> *nearestSearch(sObject obj);

	sObjectCompare comp;
	
	mfKdTreeNode<sObject> *root;	/**< KdTree root node */
	int n;		/**< Size of the KdTree */
	int ndim;
};

template <class sObject, class sObjectCompare> mfKdTree<sObject,sObjectCompare>::mfKdTree(int dim) 
{
	MF_ASSERT(dim);
	
	root = NULL;
	ndim = dim;
	n = 0;
}

template <class sObject, class sObjectCompare> mfKdTree<sObject,sObjectCompare>::~mfKdTree()
{
	mfList< mfKdTreeNode<sObject> * > lista;

	mfKdTreeNode<sObject> *node = root;

	while(node)
	{
		if(node->p[0])
			lista.insert(node->p[0]);
		if(node->p[1])
			lista.insert(node->p[1]);
			
		delete node;
		
		lista.erase(0);

		if(!lista.empty())
			node = lista.first();
		else
			node = NULL;
	}
}

template <class sObject, class sObjectCompare> void mfKdTree<sObject,sObjectCompare>::insert(sObject obj)
{
	add(obj);
}


template <class sObject, class sObjectCompare> sObject mfKdTree<sObject,sObjectCompare>::nearest(sObject obj)
{
	mfKdTreeNode<sObject> *node = nearestSearch(obj);
	
//	MF_ASSERT(node);
	if (node)
		return node->ptr;
	else
		return NULL;
}

template <class sObject, class sObjectCompare> sObject mfKdTree<sObject,sObjectCompare>::nearestAndInsert(sObject obj)
{
	mfKdTreeNode<sObject> *node = nearestSearch(obj);
	
	add(obj);
	
	MF_ASSERT(node);

	return node->ptr;
}

template <class sObject, class sObjectCompare> mfKdTreeNode<sObject>*mfKdTree<sObject,sObjectCompare>::add(sObject obj)
{
	mfKdTreeNode<sObject> *leaf = root, *ant = NULL;
	int ld = 0, dim = 0;
	
	while(leaf)
	{
		if(comp.greater(leaf->ptr, obj, dim))
		{
			ant = leaf;
			ld = 0;
		}
		else
		{
			ant = leaf;
			ld = 1;
		}

		leaf = ant->p[ld];

		if(++dim == ndim)
			dim = 0;
	}

	leaf = new mfKdTreeNode<sObject>;

	leaf->ptr = obj;
	leaf->p[0]  = NULL;
	leaf->p[1] = NULL;

	if(ant)
		ant->p[ld] = leaf;
	else
	{
		root = leaf;
		ant = root;
	}
		
	n++;

	return ant;
}

template <class sObject, class sObjectCompare> mfKdTreeNode<sObject>* mfKdTree<sObject,sObjectCompare>::nearestSearch(sObject obj)
{
	mfKdTreeNode<sObject> *leaf = root, *ant = NULL;
	int ld, dim = 0;
	
	while(leaf)
	{
		if(comp.greater(leaf->ptr, obj, dim))
		{
			ant = leaf;
			ld = 0;
		}
		else
		{
			ant = leaf;
			ld = 1;
		}

		leaf = ant->p[ld];
	
		if(++dim == ndim)
			dim = 0;
	}
	
	if(ant)
		return ant;
	else
		return NULL;
}

template <class sObject, class sObjectCompare> int mfKdTree<sObject,sObjectCompare>::size()
{
	return n;
}

}
#endif

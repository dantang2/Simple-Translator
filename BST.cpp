/*
 * BST.cpp
 * 
 * Description: Data collection Binary Search Tree ADT class.
 *              Link-based implementation.
 *
 *				dataFile.txt contains translations from English to
 *				the fictional language Dothraki from Game of Thrones
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Dan Tang
 * Date of last modification: July 18 2017
 * 
 */

#include "BST.h"
#include "ElementAlreadyExistsInBSTException.h"
#include "ElementDoesNotExistInBSTException.h"

//Default Constructor
template<class ElementType>
BST<ElementType>::BST()
{
	root = NULL;
	elementCount = 0;
}

//Parameterized Constructor
template<class ElementType>
BST<ElementType>::BST(ElementType& element)
{
	root->element = element;
	root->left = NULL;
	root->right = NULL;
	elementCount = 1;
}

//Destructor debugging purposes
template<class ElementType>
BST<ElementType>::~BST()
{
	cout<<"Deleted..."<<endl;
}

//Description: Returns ElementCount
template<class ElementType>
int BST<ElementType>::getElementCount() const
{
	return elementCount;
}

// Time efficiency: O(log2 n)
// Description: Inserts new element
template<class ElementType>
void BST<ElementType>::insert(const ElementType& newElement) throw(ElementAlreadyExistsInBSTException)
{
	BSTNode<ElementType> *p = new BSTNode<ElementType>();
	p->element = newElement;

	if(root==NULL)
	{
		root = p;
		elementCount++;
	}

	else
	{
		insertR(newElement, root);
	}

}

// Time efficiency: O(log2 n)
// Description: Retrieves element that matches with the targetElement
template<class ElementType>
ElementType& BST<ElementType>::retrieve(const ElementType& targetElement) const throw(ElementDoesNotExistInBSTException)
{
	BSTNode<ElementType> *p = new BSTNode<ElementType>();
	p->element = targetElement;

	
	if(p->element.getEnglish()==root->element.getEnglish())
	{
		p->element = root->element;
	}

	else
	{
		p->element = retrieveR(targetElement, root);
	}

	return p->element;

}

// Time efficiency: O(n)
// Description: Prints elements in alphabetical order of their english word
template<class ElementType>
void BST<ElementType>::traverseInOrder(void visit(ElementType&)) const
{
	if(root->isLeaf())
	{
		visit(root->element);
	}
	else
	{
		traverseInOrderR(visit,root);

	}
}

//Helper Method 
template<class ElementType>
bool BST<ElementType>::insertR(const ElementType& element, BSTNode<ElementType>* current)
{
	BSTNode<ElementType> *p = new BSTNode<ElementType>();
	p->element = element;
	

	if(current->isLeaf())
	{
		if(element.getEnglish()<=current->element.getEnglish())
		{
			current->left = p;
		}

		else if(element.getEnglish()>current->element.getEnglish())
		{
			current->right = p;
		}

		elementCount++;
		
	}

	else if(!current->hasRight()&&(element.getEnglish()>current->element.getEnglish()))
	{
		
		current->right = p;
		elementCount++;

	}

	else if(!current->hasLeft()&&(element.getEnglish()<current->element.getEnglish()))
	{
		current->left = p;
		
		elementCount++;
	}

	else if(element.getEnglish()<=current->element.getEnglish())
	{
		insertR(element, current->left);
	}

	else if(element.getEnglish()>current->element.getEnglish())
	{
		insertR(element, current->right);	
	}

	return current;
}

//Helper Method
template<class ElementType>
ElementType& BST<ElementType>::retrieveR(const ElementType& targetElement, BSTNode<ElementType>* current) const throw(ElementDoesNotExistInBSTException)
{
	BSTNode<ElementType> *p = new BSTNode<ElementType>();
	p->element = targetElement;
	

	if(targetElement.getEnglish()==current->element.getEnglish())
	{
		p = current;
		
		return p->element;
	}

	else if(targetElement.getEnglish()<=current->element.getEnglish()&&current->hasLeft())
	{
		
		p->element = retrieveR(targetElement, current->left);
		return p->element;
	}

	else if(targetElement.getEnglish()>current->element.getEnglish()&&current->hasRight())
	{

		p->element = retrieveR(targetElement, current->right);
		return p->element;
	}

	else
	{
		throw ElementDoesNotExistInBSTException();
	}


}

//Helper Method
template<class ElementType>
void BST<ElementType>::traverseInOrderR(void visit(ElementType&), BSTNode<ElementType>* current) const
{
	if(current->isLeaf())
	{
		visit(current->element);
		
	}
	else if(current->hasLeft())
	{
		traverseInOrderR(visit, current->left);
		visit(current->element);
		if(current->hasRight())
			traverseInOrderR(visit, current->right);

	}
	else if(current->hasRight())
	{
		visit(current->element);
		traverseInOrderR(visit, current->right);
	}
	
}









































// To be completed!
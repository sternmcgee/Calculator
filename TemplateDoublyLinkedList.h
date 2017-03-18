//programming assignment 3
#ifndef LIST_H
#define LIST_H

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : range_error {
	explicit EmptyDLinkedListException(char const* msg = NULL) : range_error(msg) {}
};

template <class T> class DListNode;
template <class T> class DoublyLinkedList;

// templated list node
template <class T> class DListNode {
private:
	T obj;
	DListNode *prev, *next;
	friend class DoublyLinkedList<T>;
public:
	DListNode(T e = T(), DListNode *p = nullptr, DListNode *n = nullptr)
		: obj(e), prev(p), next(n) {}
	T getElem() const { return obj; }
	DListNode * getNext() const { return next; }
	DListNode * getPrev() const { return prev; }
};

//templated doubly linked list
template <class T>  class DoublyLinkedList {
protected:
	DListNode<T> header, trailer;
public:
	DoublyLinkedList() : // constructor
		header(T()), trailer(T())
	{
		header.next = &trailer; trailer.prev = &header;
	}
	DoublyLinkedList(const DoublyLinkedList& dll); // copy constructor
	~DoublyLinkedList(); // destructor
	DoublyLinkedList& operator=(const DoublyLinkedList& dll); // assignment operator
															  // return the pointer to the first node
	DListNode<T> *getFirst() const { return header.next; }
	// return the pointer to the trailer
	const DListNode<T> *getAfterLast() const { return &trailer; }
	// check if the list is empty
	bool isEmpty() const { return header.next == &trailer; }
	T first() const; // return the first object
	T last() const; // return the last object
	void insertFirst(T newobj); // insert to the first of the list
	T removeFirst(); // remove the first node
	void insertLast(T newobj); // insert to the last of the list
	T removeLast(); // remove the last node
};

template<class T> ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll);

// copy constructor
template <class T> DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& dll)
{
	// Initialize the list
	header.next = &trailer;
	trailer.prev = &header;

	// Copy from dll
	DListNode<T>* itrNode = dll.getFirst();
	while (itrNode != dll.getAfterLast())		// f(n) = O(n)
	{
		DListNode<T>* newNode = new DListNode<T>(itrNode->getElem(), trailer.prev, &trailer);
		trailer.prev->next = newNode;
		trailer.prev = newNode;
		itrNode = itrNode->next;
	}
}

// assignment operator
template <class T> DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& dll)
{
	if (header.next != &trailer) delete this;
	//Initializing list
	header.next = &trailer;
	trailer.prev = &header;

	//copy from dll
	DListNode<T>* itrNode = dll.getFirst();
	while (itrNode != dll.getAfterLast())		// f(n) = O(n)
	{
		DListNode<T>* newNode = new DListNode<T>(itrNode->obj, trailer.prev, &trailer);
		trailer.prev->next = newNode;
		trailer.prev = newNode;
		itrNode = itrNode->next;
	}
	return *this;
}

// insert the object to the first of the linked list
template <class T> void DoublyLinkedList<T>::insertFirst(T newobj)		//f(n)=O(6)  3 assignments, 1 operation for each DListNode paramater initialization (obj and 2 pointers)
{
	DListNode<T> *newNode = new DListNode<T>(newobj, &header, header.next);
	header.next->prev = newNode;
	header.next = newNode;
}

// insert the object to the last of the linked list
template <class T> void DoublyLinkedList<T>::insertLast(T newobj)
{
	DListNode<T> *newNode = new DListNode<T>(newobj, trailer.prev, &trailer);
	trailer.prev->next = newNode;
	trailer.prev = newNode;
}

// remove the first object of the list
template <class T> T DoublyLinkedList<T>::removeFirst()		//f(n)=O(4)  4 assignments
{
	if (isEmpty())
		throw EmptyDLinkedListException("Empty Doubly Linked List");

	DListNode<T>* node = header.next;		
	node->next->prev = &header;
	header.next = node->next;
	T obj = node->obj;

	return obj;
}

// remove the last object of the list
template <class T> T DoublyLinkedList<T>::removeLast()
{
	if (isEmpty())
		throw EmptyDLinkedListException("Empty Doubly Linked List");

	DListNode<T> *node = trailer.prev;
	node->prev->next = &trailer;
	trailer.prev = node->prev;
	T obj = node->obj;

	return obj;
}

// destructor
template <class T> DoublyLinkedList<T>::~DoublyLinkedList()
{
	DListNode<T> *prev_node, *node = header.next;
	while (node != &trailer) {
		prev_node = node;
		node = node->next;
		delete prev_node;
	}
	header.next = &trailer;
	trailer.prev = &header;
}

// return the first object
template <class T> T DoublyLinkedList<T>::first() const		//f(n)=O(0)		no operations (excluding return and throw)
{
	if (isEmpty())
		throw EmptyDLinkedListException("Empty Doubly Linked List");

	return header.next->obj;
}

// return the last object
template <class T> T DoublyLinkedList<T>::last() const
{
	if (isEmpty())
		throw EmptyDLinkedListException("Empty Doubly Linked List");

	return trailer.prev->obj;
}

// output operator
template<class T> ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
	DListNode<T>* itrNode = dll.getFirst();
	while (itrNode != dll.getAfterLast())		//f(n)=O(n)
	{
		out << itrNode->getElem() << " ";
		itrNode = itrNode->getNext();
	}
	return out;
}
#endif

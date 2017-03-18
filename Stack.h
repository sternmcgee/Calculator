/*
Stern McGee
Linked List Stack Header File
03/16/17
*/
#ifndef STACK_H
#define STACK_H

#include "TemplateDoublyLinkedList.h"
#include <stdexcept>
using namespace std;

template <class T> class LinkedStack
{
private:
	DoublyLinkedList<T> list;
public:
	//empty stack exception class
	class StackEmptyException : public runtime_error {
	public: StackEmptyException(const string& err) : runtime_error(err) {}
	};
	//default constructor
	LinkedStack(): list() {}			
	//destructor
	~LinkedStack() { list.~DoublyLinkedList(); }
	//checks if stack is empty
	bool isEmpty() const { return list.isEmpty(); }
	//returns the top value of the stack
	T top() const;
	//pushes element to top of the stack
	void push(const T elem) { return list.insertFirst(elem); }
	//pops element from the top of the stack and returns the value
	T pop();


};

template<class T> T LinkedStack<T>::top() const
{
	if (list.isEmpty())
		throw StackEmptyException("Attempt to access empty stack");
	return list.first();
}
template<class T> T LinkedStack<T>::pop()
{
	if (list.isEmpty())
		throw StackEmptyException("Attempt to access empty stack");
	return list.removeFirst();
}
#endif 
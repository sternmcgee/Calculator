/*
Stern McGee
Linked List Queue Header File
03/16/17
*/
#ifndef QUEUE_H
#define QUEUE_H

#include "TemplateDoublyLinkedList.h"
#include <stdexcept>
using namespace std;

template <class T> class LinkedQueue
{
private:
	DoublyLinkedList<T> list;
public:
	//empty queue exception class
	class QueueEmptyException : public runtime_error {
	public: QueueEmptyException(const string& err) : runtime_error(err) {}
	};
	//constructor
	LinkedQueue(): list() {}
	//destructor
	~LinkedQueue() { list.~DoublyLinkedList(); }
	//checks whether the queue is empty
	bool isEmpty() const { return list.isEmpty(); }
	//returns the first element in the queue
	T first() const;
	//enqueues the element at the back of the queue
	void enqueue(const T elem) { return list.insertLast(elem); }
	//dequeues the element at the front of the queue 
	T dequeue();

};

template<class T> T LinkedQueue<T>::first() const
{
	if (list.isEmpty())
		throw QueueEmptyException("Attempt to access empty queue");
	return list.first();
}

template<class T> T LinkedQueue<T>::dequeue()
{
	if (list.isEmpty())
		throw QueueEmptyException("Attempt to access empty queue");
	return list.removeFirst();
}
#endif 
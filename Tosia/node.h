#pragma once

template<class T>
class Node
{
public:
	T val;

	Node* previous;
	Node* next;

	Node()
	{
		previous = nullptr;
		next = nullptr;
	}

	~Node()
	{
		// Connect chain
		if(previous != nullptr)
			previous->next = next;

		if (next != nullptr)
			next->previous = previous;
	}

	Node<T> & operator ++(int) {
		return next;
	}

	Node<T> & operator --(int) {
		return previous;
	}
};
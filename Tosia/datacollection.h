#pragma once

#include "Node.h"

template<class T>
class DataCollection
{
protected:
	Node<T>* first;
	Node<T>* last;

	int length;

public:
	DataCollection()
	{
		first = nullptr;
		last = nullptr;
		length = 0;
	}

	virtual ~DataCollection()
	{
		if (length > 0) {
			Node<T>* tmp = first;
			for (int i = 0; i < length; i++) {
				if (tmp != nullptr) {
					tmp = tmp->next;

					if (tmp != nullptr)
						delete tmp->previous;
				}
			}
			delete tmp;
		}
	}

	int GetLength() const
	{
		return length;
	}

	virtual void Push(T val) = 0;
	virtual T & Pop() = 0;
	virtual T & PopAndLeave() = 0;
	virtual T & Get(int index) const = 0;
};
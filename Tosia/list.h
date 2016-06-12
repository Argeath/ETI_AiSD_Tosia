#pragma once

#include "DataCollection.h"
#include <exception>

template<class T>
class List : public DataCollection<T>
{
public:
	List() : DataCollection() {}

	List(int amount, T defaultValue) : DataCollection()
	{
		for (int i = 0; i < amount; i++)
			Push(defaultValue);
	}

	void reset(T value)
	{
		if (length == 0) return;

		Node<T>* tmp = first;
		for (int i = 0; i < length; i++) {
			tmp->val = value;
			tmp = tmp->next;
		}
	}

	void Push(T val) override
	{
		Node<T>* node = new Node<T>;
		node->val = val;

		if (last != nullptr) {
			node->previous = last;
			last->next = node;
		}

		if (first == nullptr)
			first = node;

		last = node;
		length++;
	}

	T & Pop() override
	{
		if (first == nullptr)
			throw std::exception("Out of range");

		T str = first->val;

		Node<T>* next = first->next;

		if (first == last)
			last = nullptr;

		delete first;
		first = next;

		length--;

		return str;
	}

	T & PopAndLeave() override
	{
		if (first == nullptr)
			throw std::exception("Out of range");

		return first->val;
	}

	T & Get(int index) const override
	{
		if (index >= length)
			throw std::exception("Out of range");
		if (first == nullptr)
			throw std::exception("Out of range");

		Node<T>* tmp = first;
		for (int i = 0; i < index; i++)
			tmp = tmp->next;

		return tmp->val;
	}

	Node<T>* Begin()
	{
		return first;
	}

	Node<T>* End()
	{
		return last->next;
	}

	T operator [](int i) const
	{
		if (i >= length)
			throw std::exception("Out of range");
		return *Get(i);
	}
	T & operator [](int i)
	{
		if (i >= length)
			throw std::exception("Out of range");
		return Get(i);
	}
};
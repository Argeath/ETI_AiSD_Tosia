#pragma once

#include "DataCollection.h"
#include <exception>

template<class T>
class List : public DataCollection<T>
{
	Node<T>** table;
	bool tableInitated;
public:
	List() : DataCollection(), tableInitated(false) {}

	List(int amount, T defaultValue) : DataCollection(), tableInitated(true)
	{
		table = new Node<T>*[amount];
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

		if (tableInitated)
			table[length] = node;

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

	bool Has(T obj)
	{
		for (Node<T>* it = Begin(); it != End(); it = it->next)
		{
			if (it->val == obj)
				return true;
		}
		return false;
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
		if (tableInitated)
			return table[i]->val;
		return *Get(i);
	}
	T & operator [](int i)
	{
		if (i >= length)
			throw std::exception("Out of range");
		if (tableInitated)
			return table[i]->val;
		return Get(i);
	}
};
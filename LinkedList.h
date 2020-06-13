#pragma once
#include <iostream>

constexpr auto IndexOutOfRange = "ERROR! INDEX OUT OF RANGE";

template < class T>
class LinkedList
{
private:
	struct Node
	{
		T values = 0;
		Node* next = nullptr;
	};
	Node* head = nullptr;
	int size = 0;

public:

	LinkedList() : size(0), head(nullptr) {};

	LinkedList(T* values, int size)
	{
		if (size <= 0) throw std::out_of_range(IndexOutOfRange);

		head = new Node{ *values, nullptr };

		for (size_t i = 1; i < size; i++)
		{
			head = new Node{ *(values + i), head };
		}
		this->size = size;
	}

	LinkedList(LinkedList <T> const& list)
	{
		Node* body{ head };
		Node* copyList{ body };

		for (size_t i = 1; i < size; ++i, body = body->next)
		{
			copyList = new Node{ body->values, copyList };
		}
		this->size = size;
	}

	LinkedList(LinkedList<T>* list)
	{
		this->list = list;
		this->size = list->GetLength();
	}

	~LinkedList()
	{
		while (this->head != nullptr)
		{
			Node* buffer{ head->next };
			delete[] head;
			this->head = buffer;
		}
		delete[] this->head;
		this->head = nullptr;
	}

	T GetFirst()
	{
		if (size == 0) throw std::out_of_range(IndexOutOfRange);

		std::cout << head->values;
		return head->values;
	}

	T GetLast()
	{
		if (size == 0) throw std::out_of_range(IndexOutOfRange);
		Node* it{ head };

		for (size_t i = 0; i < size - 1; ++i, it = it->next);
		std::cout << it->values;
		return it->values;

	}

	T Get(int index)
	{
		if (index < 0 || index >= size) throw std::out_of_range(IndexOutOfRange);

		Node* body{ head };
		for (size_t i = 0; i < index; ++i, body = body->next);
		return body->values;
	}


	LinkedList<T>* GetSubList(int startIndex, int endIndex)
	{
		if (startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size || startIndex > endIndex) throw std::out_of_range(IndexOutOfRange);
		Node* it{ head };
		for (size_t i = 0; i < startIndex - 1; ++i, it = it->next);
		LinkedList<T>* newNode = new LinkedList<T>;

		for (ptrdiff_t i(startIndex); i < endIndex + 1; ++i)
		{
			newNode->Prepend(it->values);
			it = it->next;
		}
		newNode->size = endIndex - startIndex + 1;

		return newNode;
	}

	int GetLength()
	{
		return size;
	}

	void Append(T data)
	{
		if (head != nullptr)
			head = new Node{ data, head };

		if (head == nullptr)
			head = new Node{ data, head };
		++this->size;

	}

	void Prepend(T data)
	{
		if (head != nullptr)
		{
			Node* body{ head };
			for (int i = 1; i < size; ++i, body = body->next);
			body->next = new Node{ data, nullptr };
		}

		if (head == nullptr)
			head = new Node{ data, head };

		++size;
	}

	void InsertAt(T data, int index)
	{
		if (index < 0 || index >= size) throw std::out_of_range(IndexOutOfRange);

		Node* body{ head };
		for (size_t i = 0; i < index - 1; ++i) { body = body->next; }

		Node* newNode = new Node{ data, body->next };
		body->next = newNode;

		this->size += 1;
	}


	LinkedList<T>* Concat(LinkedList<T>* list)
	{
		Node* body1{ this->head };
		LinkedList<T>* newList = new LinkedList<T>();

		for (int i = 0; i < this->size; ++i)
		{
			newList->Prepend(body1->values);
			body1 = body1->next;
		}

		Node* body2{ list->head };
		for (int i = 0; i < list->size; ++i)
		{
			newList->Prepend(body2->values);
			body2 = body2->next;
		}
		newList->size = this->size + list->size;

		LinkedList<T>* t = newList;
		for (int i = 0; i < newList->size; ++i)
		{
			std::cout << t->Get(i) << " ";
		}

		return newList;
	};
};
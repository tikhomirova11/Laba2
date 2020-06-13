#pragma once
#include "Dynamic_Array.h"
#include "Sequence.h"

template <class T>
class ArraySequence : public Sequence<T>
{
protected:
	DynamicArray<T>* mas{ nullptr };
	int size{ 0 };
public:
	ArraySequence() : Sequence<T>()
	{
		mas = new DynamicArray<T>();
		this->size = 0;
	}

	ArraySequence(int size) : Sequence<T>()
	{
		mas = new DynamicArray<T>(size);
		this->size = size;
	}

	ArraySequence(T* items, int size) : Sequence<T>()
	{
		mas = new DynamicArray<T>(items, size);
		this->size = size;
	}

	virtual ~ArraySequence()
	{
		delete this->mas;
		this->mas = nullptr;
	}

	ArraySequence(Sequence<T>* seq)
	{
		this->mas = new DynamicArray(seq->GetLength());
		for (size_t i(0); i < this->mas->GetSize(); ++i)
			this->mas->Set(i, seq->Get(i));
	}

	virtual T GetFirst() const override
	{
		if (this->size == 0) throw std::out_of_range(IndexOutOfRange);

		return mas->Get(0);
	}

	virtual T GetLast() const override
	{

		if (this->size == 0) throw std::out_of_range(IndexOutOfRange);

		return mas->Get(this->size - 1);
	}

	virtual T Get(int index) const override
	{
		if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRange);

		return mas->Get(index);
	}

	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override
	{
		if (startIndex < 0 || endIndex < 0 || startIndex >= this->size || endIndex >= this->size) throw std::out_of_range(IndexOutOfRange);

		int index(endIndex - startIndex + 1);
		Sequence<T>* getSub = new ArraySequence(0);
		for (int i = 0; i < index; ++i)
			getSub->Prepend(this->mas->Get(i + startIndex));

		return getSub;
	}

	virtual int GetLength() const override
	{
		return this->size;
	}

	virtual void Append(T item) override
	{
		this->mas->Resize(this->size + 1);
		T item1 = this->mas->Get(0);
		T item2 = 0;
		for (int i = 0; i < this->size; ++i)
		{
			item2 = item1;
			item1 = mas->Get(i + 1);
			this->mas->Set(i + 1, item2);
		}
		this->mas->Set(0, item);
	}

	virtual void Prepend(T item) override
	{
		this->mas->Resize(this->size + 1);
		this->size = this->size + 1;
		this->mas->Set(this->size - 1, item);
	}

	virtual void InsertAt(T item, int index) override
	{
		if (index < 0 || index == this->size || index > this->size) throw std::out_of_range(IndexOutOfRange);

		ArraySequence<T>* leftMas = new ArraySequence{ 0 };
		for (int i = 0; i < index; ++i)
			leftMas->Prepend(this->mas->Get(i));

		leftMas->Prepend(item);


		ArraySequence<T>* rightMas = new ArraySequence(0);
		for (int i = index; i < this->size; ++i)
			rightMas->Prepend(mas->Get(i));

		ArraySequence<T>* newMas = new ArraySequence(0);
		for (int i = 0; i < leftMas->size; ++i)
			newMas->Prepend(leftMas->Get(i));


		for (int i = 0; i < rightMas->size; ++i)
			newMas->Prepend(rightMas->Get(i));

		++this->size;
		this->mas = newMas->mas;
	}


	virtual ArraySequence <T>* Concat(Sequence<T>* mas1) const override
	{
		int masSize = mas1->GetLength();

		ArraySequence <T>* newMas = new ArraySequence(0);
		for (int i = 0; i < this->size; ++i)
			newMas->Prepend(this->mas->Get(i));

		for (int i = 0; i < masSize; ++i)
			newMas->Prepend(mas1->Get(i));

		return newMas;
	}

};
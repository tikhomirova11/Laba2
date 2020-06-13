#pragma once
#include <iostream>
#include <exception>
#include <cmath>
#include <stdlib.h>

constexpr auto NegativeSize = "ERROR! NEGATIVE SIZE";
constexpr auto IndexOutOfRange = "ERROR! INDEX OUT OF RANGE";

template <class T>
class DynamicArray
{
private:
	T* mas = nullptr;
	int size = 0;
public:

	DynamicArray() = default;

	DynamicArray(int size)
	{
		this->size = size;

		if (this->size < 0) throw std::length_error(NegativeSize);

		this->mas = new T[size];
	}

	DynamicArray(T* mas, int size) : DynamicArray(size)
	{
		std::memcpy(this->mas, mas, size * sizeof(T));
	}

	DynamicArray(DynamicArray<T> const& dynamicArray) : DynamicArray(dynamicArray->mas, dynamicArray->size) {}

	T Get(int index)
	{
		if (index < 0 || index >= size) throw std::out_of_range(IndexOutOfRange);
		return mas[index];
	}

	int GetSize() { return size; }

	void Set(int index, T& value)
	{

		if (index < 0 || index >= size) throw std::out_of_range(IndexOutOfRange);
		mas[index] = value;
	}

	void Resize(int newSize)
	{
		if (newSize < 0) throw std::length_error(NegativeSize);

		T* newMas = new T[newSize];
		memcpy(newMas, mas, newSize * sizeof(T));
		delete[] mas;
		mas = newMas;
		size = newSize;
	}

	void Write()
	{
		for (int i = 0; i < size; ++i)
			std::cout << mas[i];

	}

	~DynamicArray()
	{
		delete[] mas;
		size = 0;
	}
};
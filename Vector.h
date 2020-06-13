#pragma once
#include <cmath>
#include <stdlib.h>
#include <assert.h>
#include "Sequence.h"
#include "ArraySequence.h"

template <class T>
class Vector
{
private:
	Sequence<T>* vector{ nullptr };
public:
	Vector() = default;

	Vector(int size)
	{
		this->vector = new ArraySequence<T>(size);
	}

	Vector(T* items, int size)
	{
		this->vector = new ArraySequence<T>(items, size);
	}

	Vector(const Vector<T>* vector)
	{
		Vector<T> newVector = new Vector<T>{ 0, 0 };

		for (int i = 0; i < &(vector).GetLength(); ++i) newVector->vector->Prepend(&(vector).Get(i));
	}

	int GetLength()	{ return this->vector->GetLength();	}

	T Get(int i) { return this->vector->Get(i); }

	Vector<T>* Summa(Vector<T>& v)
	{
		if (this->vector->GetLength() != v.GetLength()) throw std::out_of_range(IndexOutOfRange);

		Vector<T>* addVec = new Vector<T>(0);

		for (int i = 0; i < this->vector->GetLength(); ++i)
			addVec->vector->Prepend(this->vector->Get(i) + v.Get(i));

		return addVec;
	}

	Vector<T>* SkalMultipy(T sklr)
	{
		Vector<T>* sklVec = new Vector<T>(0);
		for (int i = 0; i < this->vector->GetLength(); ++i)
			sklVec->vector->Prepend(this->vector->Get(i) * sklr);

		return sklVec;
	}

	double Rate()
	{
		double r = 0;

		for (int i = 0; i < this->vector->GetLength(); ++i)
			r = r + pow(this->vector->Get(i), 2);

		if (r != 0)
			return sqrt(r);
		else
			return r;
	}

	/*Vector<T>&operator=(const Vector& a)
	{
		size = a.size;
		for (int i = 0; i != a.size; ++i) {
			this->date[i] = a.data[i];
		}
		return *this;
	}*/

	/*Vector<T>& operator = (Vector<T>& v1) 
	{
		T* tmp = new T[this->vector->GetLength()];

		for (int i = 0; i < this->vector->GetLength(); ++i)
		{
			tmp[i] = v1.Get(i);
		}

		Vector<T>* vector = new Vector<T>(tmp, this->vector->GetLength());
		delete[] tmp;

		return vector;
	}*/
	   	 
	T Multipy(Vector<T>& v1)
	{
		if (this->vector->GetLength() != v1.GetLength()) throw std::out_of_range(IndexOutOfRange);

		T rez(0);

		for (int i = 0; i < this->vector->GetLength(); ++i)
			rez = rez + this->vector->Get(i) * v1.Get(i);

		return rez;
	}

	~Vector()
	{
		if (this->vector != nullptr)
		{
			delete this->vector;
			this->vector = nullptr;
		}
	}

	void Out()
	{
		for (int i = 0; i < this->vector->GetLength(); ++i)
			std::cout << this->vector->Get(i) << " ";
	}
};


//////////////TESTS///////////////


void TestVectorIntSumma()
{
	int items1[3]{ 11, 12,-36 };
	int s1 = 3;

	int items2[5]{ -97 , 1, 0, 1, 1 };
	int s2 = 5;

	int items3[5]{ 0, 0, 0, 0, 0 };
	int s3 = 5;

	int items4[3]{ -22,  0, -9 };
	int s4 = 3;


	Vector<int> v1{ items1, s1 };
	Vector<int> v2{ items2, s2 };
	Vector<int> v3{ items3, s3 };
	Vector<int> v4{ items4, s4 };

	assert(v1.GetLength() == s1);
	assert(v2.GetLength() == s2);
	assert(v3.GetLength() == s3);
	assert(v4.GetLength() == s4);

	assert(v1.Get(0) == 11);
	assert(v1.Get(1) == 12);
	assert(v1.Get(2) == -36);
	assert(v2.Get(0) == -97);
	assert(v2.Get(1) == 1);
	assert(v2.Get(2) == 0);
	assert(v2.Get(3) == 1);
	assert(v2.Get(4) == 1);
	assert(v3.Get(3) == 0);
	assert(v4.Get(0) == -22);
	assert(v4.Get(1) == 0);
	assert(v4.Get(2) == -9);

	Vector<int>* sm1{ v1.Summa(v4) };
	Vector<int>* sm2{ v1.Summa(v1) };
	Vector<int>* sm3{ v2.Summa(v3) };
	Vector<int>* sm4{ v3.Summa(v3) };

	assert(sm1->GetLength() == s1);
	assert(sm1->Get(0) == -11);
	assert(sm1->Get(1) == 12);
	assert(sm1->Get(2) == -45);

	assert(sm2->GetLength() == s1);
	assert(sm2->Get(0) == 22);
	assert(sm2->Get(1) == 24);
	assert(sm2->Get(2) == -72);

	assert(sm3->GetLength() == s3);
	assert(sm3->Get(0) == -97);
	assert(sm3->Get(1) == 1);
	assert(sm3->Get(2) == 0);
	assert(sm3->Get(3) == 1);
	assert(sm3->Get(4) == 1);

	assert(sm4->GetLength() == s3);
	assert(sm4->Get(0) == 0);
	assert(sm4->Get(1) == 0);
	assert(sm4->Get(2) == 0);
	assert(sm4->Get(3) == 0);
	assert(sm4->Get(4) == 0);

	std::cout << "Test Summa (int): success." << std::endl;
}

void TestVectorDoubleSumma()
{

	double items1D[5]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
	int s1D = 5;

	double items2D[4]{ 0 , 0, 0, 0 };
	int s2D = 4;

	double items3D[6]{ 6.11, 7.11, 8.11, 9.11, 10.11, 11.11 };
	int s3D = 6;

	double items4D[4]{ -15.5, 0, -99.9, -62.2 };
	int s4D = 4;

	double items5D[5]{ 3.1, 0, 99.1, 62.1, 1.1 };
	int s5D = 5;

	double items6D[4]{ 3.3, 7.4, 99.58, 73.03 };
	int s6D = 4;


	Vector<double> v1D{ items1D, s1D };
	Vector<double> v2D{ items2D, s2D };
	Vector<double> v3D{ items3D, s3D };
	Vector<double> v4D{ items4D, s4D };
	Vector<double> v5D{ items5D, s5D };
	Vector<double> v6D{ items6D, s6D };

	assert(v1D.GetLength() == s1D);
	assert(v2D.GetLength() == s2D);
	assert(v3D.GetLength() == s3D);
	assert(v4D.GetLength() == s4D);
	assert(v5D.GetLength() == s5D);
	assert(v6D.GetLength() == s6D);

	assert(v1D.Get(0) == 1.1);
	assert(v1D.Get(1) == 2.2);
	assert(v1D.Get(2) == 3.3);
	assert(v1D.Get(3) == 4.4);
	assert(v1D.Get(4) == 5.5);
	assert(v2D.Get(0) == 0);
	assert(v4D.Get(0) == -15.5);
	assert(v4D.Get(1) == 0);
	assert(v4D.Get(2) == -99.9);
	assert(v4D.Get(3) == -62.2);

	Vector<double>* sm1D{ v1D.Summa(v5D) };
	Vector<double>* sm2D{ v4D.Summa(v6D) };
	Vector<double>* sm3D{ v4D.Summa(v4D) };
	Vector<double>* sm4D{ v2D.Summa(v6D) };
	Vector<double>* sm5D{ v2D.Summa(v4D) };
	Vector<double>* sm6D{ v2D.Summa(v2D) };

	assert(sm1D->GetLength() == s1D);
	assert((sm1D->Get(0) - 4.2) <= 0.001);
	assert((sm1D->Get(1) - 2.2) <= 0.001);
	assert((sm1D->Get(2) - 102.4) <= 0.001);
	assert((sm1D->Get(3) - 66.5) <= 0.001);
	assert((sm1D->Get(4) - 6.6) <= 0.001);

	assert(sm2D->GetLength() == s4D);
	assert((sm2D->Get(0) - (-12.2)) <= 0.001);
	assert((sm2D->Get(1) - 7.4) <= 0.001);
	assert((sm2D->Get(2) - (-0.32)) <= 0.001);
	assert((sm2D->Get(3) - 10.83) < 0.001);

	assert(sm3D->GetLength() == s4D);
	assert((sm3D->Get(0) - (-31)) <= 0.001);
	assert(sm3D->Get(1) == 0);
	assert((sm3D->Get(2) - (-199.8)) <= 0.001);
	assert((sm3D->Get(3) - (-124.4)) <= 0.001);

	assert(sm4D->GetLength() == s4D);
	assert((sm4D->Get(0) - 3.3) <= 0.001);
	assert((sm4D->Get(1) - 7.4) <= 0.001);
	assert((sm4D->Get(2) - 99.58) <= 0.001);
	assert((sm4D->Get(3) - 73.03) <= 0.001);

	assert(sm5D->GetLength() == s4D);
	assert((sm5D->Get(0) - (-15 / 5)) <= 0.001);
	assert(sm5D->Get(1) == 0);
	assert((sm5D->Get(2) - (-99.9)) <= 0.001);
	assert((sm5D->Get(3) - (-62.2)) <= 0.001);

	assert(sm6D->GetLength() == s2D);
	assert(sm6D->Get(0) == 0);
	assert(sm6D->Get(1) == 0);
	assert(sm6D->Get(2) == 0);
	assert(sm6D->Get(3) == 0);

	std::cout << "Test Summa (double): success." << std::endl;

}


void TestVectorSkalMultyplyInt()
{
	int items1[5]{ 1, 2, 3, 4, 5 };
	int s1(5);

	int items2[4]{ 0 , 0, 0, 0 };
	int s2(4);

	int items3[4]{ -15, 0, -99, -62 };
	int s3(4);

	Vector<int> v1{ items1, s1 };
	Vector<int> v2{ items2, s2 };
	Vector<int> v3{ items3, s3 };

	int skal1(5);
	int skal2(-5);
	int skal3(0);

	Vector<int>* skalMul1{ v1.SkalMultipy(skal1) };
	Vector<int>* skalMul2{ v1.SkalMultipy(skal2) };
	Vector<int>* skalMul3{ v1.SkalMultipy(skal3) };

	Vector<int>* skalMul4{ v3.SkalMultipy(skal1) };
	Vector<int>* skalMul5{ v3.SkalMultipy(skal2) };
	Vector<int>* skalMul6{ v3.SkalMultipy(skal3) };
	Vector<int>* skalMul7{ v2.SkalMultipy(skal3) };

	assert(skalMul1->Get(0) == 5);
	assert(skalMul1->Get(1) == 10);
	assert(skalMul1->Get(2) == 15);
	assert(skalMul1->Get(3) == 20);
	assert(skalMul1->Get(4) == 25);

	assert(skalMul2->Get(0) == -5);
	assert(skalMul2->Get(1) == -10);
	assert(skalMul2->Get(2) == -15);
	assert(skalMul2->Get(3) == -20);
	assert(skalMul2->Get(4) == -25);

	assert(skalMul3->Get(0) == 0);
	assert(skalMul3->Get(1) == 0);
	assert(skalMul3->Get(2) == 0);
	assert(skalMul3->Get(3) == 0);
	assert(skalMul3->Get(4) == 0);

	assert(skalMul4->Get(0) == -75);
	assert(skalMul4->Get(1) == 0);
	assert(skalMul4->Get(2) == -495);
	assert(skalMul4->Get(3) == -310);

	assert(skalMul5->Get(0) == 75);
	assert(skalMul5->Get(1) == 0);
	assert(skalMul5->Get(2) == 495);
	assert(skalMul5->Get(3) == 310);

	assert(skalMul6->Get(0) == 0);
	assert(skalMul6->Get(1) == 0);
	assert(skalMul6->Get(2) == 0);
	assert(skalMul6->Get(3) == 0);

	assert(skalMul7->Get(0) == 0);
	assert(skalMul7->Get(1) == 0);
	assert(skalMul7->Get(2) == 0);
	assert(skalMul7->Get(3) == 0);

	std::cout << "Test skalar (int) : success." << std::endl;
}

void TestVectorSkalMultyplyDouble()
{
	double items1D[5]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
	int s1D(5);

	double items2D[4]{ 0 , 0, 0, 0 };
	int s2D(4);

	double items3D[4]{ -15.5, 0, -99.9, -62.2 };
	int s3D(4);

	Vector<double> v1D{ items1D, s1D };
	Vector<double> v2D{ items2D, s2D };
	Vector<double> v3D{ items3D, s3D };

	double skal1D(5.1);
	double skal2D(-5.1);
	double skal3D(0);

	Vector<double>* skalMul1D{ v1D.SkalMultipy(skal1D) };
	Vector<double>* skalMul2D{ v1D.SkalMultipy(skal2D) };
	Vector<double>* skalMul3D{ v1D.SkalMultipy(skal3D) };

	Vector<double >* skalMul4D{ v3D.SkalMultipy(skal1D) };
	Vector<double>* skalMul5D{ v3D.SkalMultipy(skal2D) };
	Vector<double>* skalMul6D{ v3D.SkalMultipy(skal3D) };
	Vector<double>* skalMul7D{ v2D.SkalMultipy(skal3D) };

	assert((skalMul1D->Get(0) - 5.61) <= 0.001);
	assert((skalMul1D->Get(1) - 11.22) <= 0.001);
	assert((skalMul1D->Get(2) - 16.86) <= 0.001);
	assert((skalMul1D->Get(3) - 22.44) <= 0.001);
	assert((skalMul1D->Get(4) - 28.05) <= 0.001);

	assert((skalMul2D->Get(0) - (-5.61)) <= 0.001);
	assert((skalMul2D->Get(1) - (-11.21)) <= 0.001);
	assert((skalMul2D->Get(2) - (-16.83)) <= 0.001);
	assert((skalMul2D->Get(3) - (-22.44)) <= 0.001);
	assert((skalMul2D->Get(4) - (-28.05)) <= 0.001);

	assert(skalMul3D->Get(0) == 0);
	assert(skalMul3D->Get(1) == 0);
	assert(skalMul3D->Get(2) == 0);
	assert(skalMul3D->Get(3) == 0);
	assert(skalMul3D->Get(4) == 0);

	assert((skalMul4D->Get(0) - (-79.05)) <= 0.001);
	assert(skalMul4D->Get(1) == 0);
	assert((skalMul4D->Get(2) - (-509.49)) <= 0.001);
	assert((skalMul4D->Get(3) - (-317.22)) <= 0.001);

	assert((skalMul5D->Get(0) - 79.05) <= 0.001);
	assert(skalMul5D->Get(1) == 0);
	assert((skalMul5D->Get(2) - 509.49) <= 0.001);
	assert((skalMul5D->Get(3) - 317.22) <= 0.001);

	assert(skalMul6D->Get(0) == 0);
	assert(skalMul6D->Get(1) == 0);
	assert(skalMul6D->Get(2) == 0);
	assert(skalMul6D->Get(3) == 0);

	assert(skalMul7D->Get(0) == 0);
	assert(skalMul7D->Get(1) == 0);
	assert(skalMul7D->Get(2) == 0);
	assert(skalMul7D->Get(3) == 0);

	std::cout << "Test skalar (double) : success." << std::endl;

}

void TestVectorNormaInt()
{

	int items1[5]{ 1, 2, 3, 4, 5 };
	int s1(5);

	int items2[4]{ 0 , 0, 0, 0 };
	int s2(4);

	int items3[4]{ -15, 0, -99, -62 };
	int s3(4);

	int items4[1]{ 6 };
	int s4(1);

	Vector<int> v1{ items1, s1 };
	Vector<int> v2{ items2, s2 };
	Vector<int> v3{ items3, s3 };
	Vector<int> v4{ items4, s4 };

	double r1{ v1.Rate() };
	double r2{ v2.Rate() };
	double r3{ v3.Rate() };
	double r4{ v4.Rate() };

	assert((r1 - 7.4162) <= 0.0001);
	assert(r2 == 0);
	assert((r3 - 117.7709) <= 0.0001);
	assert(r4 == 6);

	std::cout << "Test rate (int) : success." << std::endl;
}

void TestVectorNormaDouble()
{
	double items1D[5]{ 1.1, 2.2, 3.3, 4.4, 5.5 };
	int s1D(5);

	double items2D[4]{ 0 , 0, 0, 0 };
	int s2D(4);

	double items3D[4]{ -15.5, 0, -99.1, -62.2 };
	int s3D(4);

	double items4D[1]{ 6.1 };
	int s4D(1);

	Vector<double> v1D{ items1D, s1D };
	Vector<double> v2D{ items2D, s2D };
	Vector<double> v3D{ items3D, s3D };
	Vector<double> v4D{ items4D, s4D };

	double r1D{ v1D.Rate() };
	double r2D{ v2D.Rate() };
	double r3D{ v3D.Rate() };
	double r4D{ v4D.Rate() };

	assert((r1D - 8.157) <= 0.001);
	assert(r2D == 0);
	assert((r3D - 118.697) <= 0.001);
	assert(r4D == 6.1);

	std::cout << "Test rate (double) : success." << std::endl;
}

void TestVectorMultipyInt()
{
	int items1[4]{ 1, 2, 3, 4 };
	int s1(4);

	int items2[4]{ 0 , 0, 0, 0 };
	int s2(4);

	int items3[4]{ -15, 0, -99, -62 };
	int s3(4);

	int items4[1]{ 6 };
	int s4(1);

	Vector<int> v1{ items1, s1 };
	Vector<int> v2{ items2, s2 };
	Vector<int> v3{ items3, s3 };
	Vector<int> v4{ items4, s4 };

	int mulV1{ v1.Multipy(v1) };// ïîëîæèò íà ïîëîæèò
	int mulV2{ v1.Multipy(v3) };// ïîëîæèò íà îòðèö
	int mulV3{ v3.Multipy(v3) };// îòðèö íà îòðèö
	int mulV4{ v4.Multipy(v4) };// åäèíè÷íûé âåêòîð
	int mulV5{ v3.Multipy(v2) };// íà íóëåâîé âåêòîð 
	int mulV6{ v2.Multipy(v2) };// íóëåâîé íà íóëåâîé 

	assert(mulV1 == 30);
	assert(mulV2 == -560);
	assert(mulV3 == 13870);
	assert(mulV4 == 36);
	assert(mulV5 == 0);
	assert(mulV6 == 0);

	std::cout << "Test multipy (int) : success." << std::endl;
}
void TestVectorMultipyDouble()
{
	double items1D[4]{ 1.1, 2.2, 3.3, 4.4 };
	int s1D(4);

	double items2D[4]{ 0 , 0, 0, 0 };
	int s2D(4);

	double items3D[4]{ -15.5, 0, -99.9, -62.2 };
	int s3D(4);

	double items4D[1]{ 6.1 };
	int s4D(1);

	Vector<double> v1D{ items1D, s1D };
	Vector<double> v2D{ items2D, s2D };
	Vector<double> v3D{ items3D, s3D };
	Vector<double> v4D{ items4D, s4D };

	double mulV1D{ v1D.Multipy(v1D) };
	double mulV2D{ v1D.Multipy(v3D) };
	double mulV3D{ v3D.Multipy(v3D) };
	double mulV4D{ v4D.Multipy(v4D) };
	double mulV5D{ v3D.Multipy(v2D) };
	double mulV6D{ v2D.Multipy(v2D) };

	assert((mulV1D - 36.3) <= 0.0001);
	assert((mulV2D - (-620.4)) <= 0.0001);
	assert((mulV3D - 14089.1) <= 0.0001);
	assert((mulV4D - 37.21) <= 0.0001);
	assert(mulV5D == 0);
	assert(mulV6D == 0);

	std::cout << "Test multipy (double) : success." << std::endl;
}

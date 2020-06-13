#include <iostream>
#include "Vector.h"

template <class T>
Vector<T>* Entering()
{
	T* tmp(0);
	int length = 0;

	std::cout << "Enter length: ";
	std::cin >> length;

	if (length <= 0)
	{
		while (length <= 0)
		{
			std::cout << "ERROR! LENGTH MUST BE POSITIVE! \n Please, try again \n";
			std::cin >> length;
		}
	}

	tmp = new T[length];
	std::cout << "\nEnter elements: \n";
	for (int i = 0; i < length; ++i) std::cin >> tmp[i];
	
	Vector<T>* vector = new Vector<T>(tmp, length);
	delete[] tmp;

	return vector;
}

template<class T>
void Program()
{
	T scalar = 0;
	int choice = 0 ;
	int k = 0;

	Vector<T>* v1 = new Vector<T>(0);
	Vector<T>* v2 = new Vector<T>(0);

	do 
	{
		std::cout << "\nDo you want to choose some operations with vectors? \n Yes - enter 1 \n No - enter 0\n";
		std::cin >> k;

		if (k == 1)
		{
			std::cout << "\n Choose the operation: \n  1.Addition \n  2.Multiplication on scalar \n  3.Rate calculation \n  4.Multiplication \n  5.Test result\n" << std::endl;
			std::cout << "Your coice : ";
			std::cin >> choice;

			if ((choice > 5) || (choice < 1))
			{
				while ((choice > 5) || (choice < 1))
				{
					std::cout << "ERROR NUMBER!\nPlease, try again:";
					std::cin >> choice;
				}
			}

			switch (choice)
			{
			case 1:

				std::cout << "Remember, the length must be the same\n The first vector: " << std::endl;
				v1 = Entering<T>();
				std::cout << "The second vector: " << std::endl;
				v2 = Entering<T>();

				std::cout << "Rezult: ";
				v1->Summa(*(v2))->Out();
				break;

			case 2:

				std::cout << "The first vector: " << std::endl;
				v1 = Entering<T>();

				std::cout << "Write the scalar: ";
				std::cin >> scalar;

				std::cout << "Rezult : ";
				v1->SkalMultipy(scalar)->Out();
				break;

			case 3:

				std::cout << "The first vector: " << std::endl;
				v1 = Entering<T>();

				std::cout << "Rezult : ";
				std::cout << v1->Rate();
				break;

			case 4:
				
				std::cout << "Remember, the length must be the same\n The first vector: " << std::endl;
				v1 = Entering<T>();
				std::cout << "The second vector: " << std::endl;
				v2 = Entering<T>();

				std::cout << "Rezult : ";
				std::cout << v1->Multipy(*(v2));
				break;
				
			case 5:

				TestVectorIntSumma();
				TestVectorDoubleSumma();
				TestVectorMultipyInt();
				TestVectorMultipyDouble();
				TestVectorNormaInt();
				TestVectorNormaDouble();
				TestVectorMultipyInt();
				TestVectorMultipyDouble();
				break;

			default:

				std::cout << "Wrong number" << std::endl;
			}

		}
		else if (k == 0)
		{
			std::cout << "Thanks fot using this program" << std::endl;
		}
		else
		{
			while (k > 1 || k < 0)
			{
				std::cout << "ERROR NUMBER!\n Please? try again" << std::endl;
				std::cin >> k;
			}
		}
	} while (k == 1);
	
	
}


int main()
{

	std::cout << "Hi! Please, choose the type of vector: \n1. int\n2. double\n " << std::endl;

	int choice(0);
	std::cin >> choice;

	if ((choice > 2) || (choice < 1))
	{
		while ((choice > 2) || (choice < 1))
		{
			std::cout << "ERROR! WRONG NUMBER!\n Please, try again." << std::endl;
			std::cin >> choice;
		}
	}

	if (choice == 1) Program<int>();
	if (choice == 2) Program<double>();

	return 0;
}
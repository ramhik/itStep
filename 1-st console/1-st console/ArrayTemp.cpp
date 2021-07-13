#include "ArrayTemp.h"

template<typename T>
ArrayTemp<T>::ArrayTemp(int size)
{
	try
	{
		if (size < 0 || size>1000000000)
			throw invalid_argument("bad argument size!");
		this->mass = new T[size];
		this->size = size;
	}
	catch (exception& exp)
	{
		cout << exp.what() << endl;
	}
}

template<typename T>
void ArrayTemp<T>::Insert(T value, int index)
{
	try
	{
		if (index < 0 || index >= this->size)
			throw out_of_range("Index < 0 or size of mass");

		T* helpMass = new T[this->size + 1];

		int i = 0;
		for (;i<index;i++)
		{
			helpMass[i] = this->mass[i];
		}

		helpMass[i++] = value;

		for (; i<this->size;i++)
		{
			helpMass[i] = this->mass[i];
		}
		delete[] this->mass;
		this->mass = helpMass;
		this->size++;
	}
	catch (exception& exp)
	{
		cout << "error: " << exp.what() << endl;
	}
}
template<typename T>
T ArrayTemp<T>::Remove(int index)
{
	try
	{
		if (index < 0 || index >= this->size)
			throw out_of_range("index 0 or size > index");

		T* helpMass = new T[this->size + 1];

		int i = 0;
		for (; i < index; i++)
		{
			helpMass[i] = this->mass[i];
		}
		for ( ; i < this->size; i++)
		{
			helpMass[i] = this->mass[i + 1];
		}
		T help = this->mass[index];

		delete[]this->mass;
		this->mass = helpMass;
		this->size--;

		return size;
	}
	catch (const std::exception&)
	{

	}
}

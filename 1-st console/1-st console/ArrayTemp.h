#pragma once
#include<iostream>
using namespace std;

template<typename T>
class ArrayTemp
{
private:
	T* mass = NULL;
	int size = 0;
public:
	ArrayTemp(int = 0);

	friend ostream& operator<<(ostream& out, ArrayTemp<T>& arr) {
		{
			try
			{
				if (arr.mass == NULL) {
					throw NULL;
				}
				for (int i = 0; i < arr.size; i++)
				{
					cout << arr.mass[i] << "\t";
				}
				out << endl;
				return out;
			}
			catch (exception& exp)
			{
				cout << "input error!" << exp.what() << endl;
			}
		}
	}

	void Insert(T value, int index=0);

	T Remove(int index);
};
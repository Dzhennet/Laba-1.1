// 6 лаба!.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

class Nogaeva

{

public:

	int i1;

	Nogaeva() { i1 = 2; }

	virtual ~Nogaeva() {}

	virtual void Get() { cout << i1; }

	virtual Nogaeva* copy() { return new Nogaeva(*this); }

	Nogaeva(const Nogaeva& o) { i1 = o.i1; }

};

class Dzhennet :public Nogaeva

{

public:

	int i2;

	Dzhennet() { i2 = 1; }

	~Dzhennet() {}

	void Get() { cout << i2; }

	Dzhennet* copy() { return new Dzhennet(*this); }

	Dzhennet(const Dzhennet& o) { i2 = o.i2; }

};

Nogaeva** g_Array = new Nogaeva * [5]{ 0 };

void append(Nogaeva* o, int size)

{

	Nogaeva** Array_new;

	int t;

	if (size > 4)

	{

		Array_new = new Nogaeva * [size];

		for (int i = 0; i < size; i++)

		{

			Array_new[i] = g_Array[i]->copy();

		}

		for (int i = 0; i < size; i++)

		{

			delete g_Array[i];

		}

		delete[](g_Array);

		g_Array = new Nogaeva * [size + 1];

		for (int i = 0; i < size; i++)

		{

			g_Array[i] = Array_new[i]->copy();

		}

		g_Array[size] = o;

		for (int i = 0; i < size; i++)

		{

			delete Array_new[i];

		}

		delete[](Array_new);

	}

	else

	{

		t = 0;

		while (g_Array[t] != NULL)

			t++;

		g_Array[t] = o;

	}

}

int main()

{

	{

		for (int i = 0; i < 10; i++)

		{

			if (i % 2 == 0)

				append(new Nogaeva(), i);

			else

				append(new Dzhennet(), i);

		}

		for (int i = 0; i < 10; i++)

		{

			g_Array[i]->Get();

		}

		for (int i = 0; i < 10; i++)

		{

			delete g_Array[i];

		}

		delete g_Array;

	}

	_CrtDumpMemoryLeaks();

}
#include <iostream>
#include "Generator.h"

using namespace std;
using namespace coroutine;

class MyGenerator : public Generator<int>
{
protected:
	virtual void run()
	{
		cout << "10" << endl;
		yield();
		cout << "20" << endl;
		yield();
	}
};

class ThreeTimesGenerator : public Generator<int>
{
protected:
	virtual void run()
	{
		yield(1);
		yield(2);
		yield(3);
	}
};


///////////////////////////////////////////////////////////
// Sick of typing constructors and members ?
///////////////////////////////////////////////////////////
#define STRUCT_BODY_1(Class, type1, attr1) \
	public: \
		Class(type1 attr1): m_##attr1(attr1) {} \
		virtual ~Class() {} \
	private: \
		type1 m_##attr1;
///////////////////////////////////////////////////////////
#define STRUCT_BODY_2(Class, type1, attr1, type2, attr2) \
	public: \
		Class(type1 attr1, type2 attr2): m_##attr1(attr1), m_##attr2(attr2) {} \
		virtual ~Class() {} \
	private: \
		type1 m_##attr1; type2 m_##attr2;
///////////////////////////////////////////////////////////


class NumbersFrom : public Generator<int>
{
	STRUCT_BODY_1(NumbersFrom, int, from)
protected:
	virtual void run()
	{
		int n = m_from;
		while( true )
		{
			yield(n);
			++n;
		}
	}
};

class Evens : public Generator<int>
{
	STRUCT_BODY_1(Evens, Generator<int>&, source)
protected:
	virtual void run()
	{
		while( true )
		{
			int n = m_source.resume();
			if( n % 2 == 0 )
			{
				yield(n);
			}
		}
	}
};

class LimitCount : public Generator<int>
{
	STRUCT_BODY_2(LimitCount, Generator<int>&, source, int, count)
protected:
	virtual void run()
	{
		for( int i = 0; i < m_count; ++i )
		{
			yield(m_source.resume());
		}
	}
};

void testGenerators()
{
	MyGenerator f;
	cout << "1" << endl;
	f.resume();
	cout << "2" << endl;
	f.resume();
	cout << "3" << endl;
	cout << endl;

	ThreeTimesGenerator f3;
	cout << f3.resume() << endl;
	cout << f3.resume() << endl;
	cout << f3.resume() << endl;
	cout << endl;

	NumbersFrom numbers(100);
	Evens evens(numbers);
	LimitCount limit(evens, 10);

	while( limit.isValid() )
	{
		int n = limit.resume();
		cout << n << endl;
	}

	cout << "Generator tests done" << endl;
}

int main()
{
	testGenerators();

	return 0;
}

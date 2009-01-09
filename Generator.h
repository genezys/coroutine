#ifndef COROUTINE_GENERATOR_INCLUDED
#define COROUTINE_GENERATOR_INCLUDED

#include "Fiber.h"
#include <vector>

namespace coroutine {

template <typename T>
class Generator : public Fiber
{
public:
	Generator();
	virtual ~Generator();

public:
	T resume();

protected:
	void yield(T data = NULL);

private:
	static std::vector<Generator<T>*> ms_stack;
	static T ms_return;
};



template <typename T>
std::vector<Generator<T>*> Generator<T>::ms_stack;

template <typename T>
T Generator<T>::ms_return;

template <typename T>
Generator<T>::Generator()
{
}

template <typename T>
Generator<T>::~Generator()
{
}

template <typename T>
T Generator<T>::resume()
{
	ms_stack.push_back(this);
	switchTo();	

	return ms_return;
}

template <typename T>
void Generator<T>::yield(T data)
{
	ms_stack.pop_back();
	
	ms_return = data;
	const Fiber* pFiberCaller = ms_stack.empty() ? &Fiber::MAIN : ms_stack.back();
	pFiberCaller->switchTo();
	ms_return = NULL;
}

} // namespace coroutine

#endif // ndef COROUTINE_GENERATOR_INCLUDED
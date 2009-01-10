#include "Fiber.h"

#include <stdlib.h>
#include <assert.h>

namespace coroutine {

class Fiber::FiberMain : public Fiber
{
protected:
	virtual void run() {}
};

const Fiber& Fiber::MAIN = FiberMain();

Fiber::Fiber(): m_pFiber(NULL)
{
	assert( false );
}

Fiber::~Fiber()
{
}

void Fiber::switchTo() const
{
}

bool Fiber::isValid() const
{
}

} // namespace coroutine
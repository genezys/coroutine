#include "Fiber.h"

#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <assert.h>

namespace coroutine {
	
class Fiber::FiberMain : public Fiber
{
public:
	FiberMain()
	{
		// Don't call parent constructor because it will make this a fiber
		// We only want the main thread to become a fiber
		m_pFiber = ConvertThreadToFiber(NULL);
	}

	virtual ~FiberMain()
	{
	}

public:
	static Fiber& getInstance()
	{
		static FiberMain fiberMain;
		return fiberMain;
	}

protected:
	virtual void run()
	{
		// The main thread should never be run like a fiber
		// As we are converted from the thread, this should never run
		assert( false );
	}
};

const Fiber& Fiber::MAIN = Fiber::FiberMain::getInstance();

Fiber::Fiber(): m_pFiber(NULL)
{
	m_pFiber = CreateFiber(0, &Fiber::proc, (void*)this);
}

Fiber::~Fiber()
{
	deleteFiber();
}

bool Fiber::isValid() const
{
	return ( m_pFiber != NULL );
}

void Fiber::switchTo() const
{
	if( isValid() )
	{
		SwitchToFiber(m_pFiber);
	}
}

void __stdcall Fiber::proc(void* pParam)
{
	Fiber* pThis = (Fiber*)pParam;
	pThis->run();
	pThis->deleteFiber();
}

void Fiber::deleteFiber()
{
	if( isValid() )
	{
		DeleteFiber(m_pFiber);
		m_pFiber = NULL;
	}
}

} // namespace coroutine
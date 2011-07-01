#include "Fiber.h"

#define _XOPEN_SOURCE

#include <stdlib.h>
#include <assert.h>
#include <ucontext.h>

namespace coroutine {
	
static ucontext_t contextMain;
	
class Fiber::FiberMain : public Fiber
{
public:
	FiberMain(): Fiber(0)
	{
        m_pFiber = &contextMain;
		getcontext(&contextMain);
	}
	
	~FiberMain()
	{
	}

protected:
	virtual void run() 
	{
		// The main thread should never be run like a fiber
		// As we are converted from the thread, this should never run
		assert(false);
	}
};

const Fiber& Fiber::MAIN = FiberMain();

Fiber::Fiber(): m_pFiber(NULL)
{
	ucontext_t* pContext = new ucontext_t();
	getcontext(pContext);
	pContext->uc_link = NULL;
	pContext->uc_stack.ss_sp = malloc(SIGSTKSZ);
	pContext->uc_stack.ss_size = SIGSTKSZ;
	pContext->uc_stack.ss_flags = 0;	
	makecontext(pContext, (void(*)())&Fiber::proc, 1, this);
	
	m_pFiber = pContext;
}
    
Fiber::Fiber(int): m_pFiber(NULL)
{
}

Fiber::~Fiber()
{
	deleteFiber();
}

void Fiber::switchTo() const
{
	ucontext_t* pContext = (ucontext_t*)m_pFiber;
	setcontext(pContext);
}

bool Fiber::isValid() const
{
	return ( m_pFiber != NULL );
}

void Fiber::proc(void* pParam)
{
	Fiber* pThis = (Fiber*)pParam;
	pThis->run();
	pThis->deleteFiber();
}

void Fiber::deleteFiber()
{
	if( isValid() )
	{
		ucontext_t* pContext = (ucontext_t*)m_pFiber;
		free(pContext->uc_stack.ss_sp);
		delete pContext;
		
		m_pFiber = NULL;
	}
}

} // namespace coroutine
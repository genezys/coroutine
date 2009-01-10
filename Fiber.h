#ifndef COROUTINE_FIBER_INCLUDED
#define COROUTINE_FIBER_INCLUDED

#ifdef WIN32
#	define STDCALL __stdcall
#else
#	define STDCALL
#endif

namespace coroutine {

class Fiber
{
public:
	static const Fiber& MAIN;

public:
	Fiber();
	virtual ~Fiber();

public:
	bool isValid() const;
	void switchTo() const;

protected:
	virtual void run() = 0;

private:
	class FiberMain;
	friend class FiberMain;

private:
	static void STDCALL proc(void* pParam);
	void* m_pFiber;

private:
	void deleteFiber();
};

} // namespace coroutine

#endif // ndef COROUTINE_FIBER_INCLUDED
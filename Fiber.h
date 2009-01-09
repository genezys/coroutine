#ifndef COROUTINE_FIBER_INCLUDED
#define COROUTINE_FIBER_INCLUDED

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
	friend FiberMain;

private:
	static void __stdcall proc(void* pParam);
	void* m_pFiber;

private:
	void deleteFiber();
};

} // namespace coroutine

#endif // ndef COROUTINE_FIBER_INCLUDED
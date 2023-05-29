// Lazy initialization (multi-threaded)
// Uses std::call_once()
#include <mutex>
#include <thread>
#include <iostream>

class Test {
	// ...
public:
	Test()
	{
		std::cout << "Test constructor called\n";
	}

	void func()
	{
		/*...*/
	}
};

Test* ptest = nullptr;             // Variable to be lazily initialized

std::once_flag ptest_flag;         // The flag stores synchronization data

void process()
{
	// Pass a callable object which performs the initialization
	std::call_once(ptest_flag, []() {
		ptest = new Test;
		});
	ptest->func();
}

int main()
{
	std::thread thr1(process);
	std::thread thr2(process);
	thr1.join(); thr2.join();
}
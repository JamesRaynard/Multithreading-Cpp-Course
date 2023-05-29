// Lazy initialization (multi-threaded)
// Uses Meyers singleton
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

void process()
{
	static Test ptest;            // Variable which is lazily initialized
	ptest.func();
}

int main()
{
	std::thread thr1(process);
	std::thread thr2(process);
	thr1.join(); thr2.join();
}
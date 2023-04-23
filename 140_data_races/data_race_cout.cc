// Unsynchronized threads which make conflicting accesses.
// But where is the shared memory location?
#include <thread>
#include <iostream>

void print(std::string str)
{
	// A very artificial way to display a string!
	for (int i = 0; i < 5; ++i) {
		std::cout << str[0] << str[1] << str[2] << std::endl;
	}
}

int main()
{
	std::thread thr1(print, "abc");
	std::thread thr2(print, "def");
	std::thread thr3(print, "xyz");

	// Wait for the tasks to complete
	thr1.join();
	thr2.join();
	thr3.join();
}
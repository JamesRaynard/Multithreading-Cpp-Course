// Thread-local random number engine
// Ensures that each thread generates the same sequence
// (Useful for testing)
#include <random>
#include <thread>
#include <iostream>

// Thread-local random number engine
thread_local std::mt19937 mt;

void func()
{
	std::uniform_real_distribution<double> dist(0, 1);   // Doubles in the range 0 to 1

	for (int i = 0; i < 10; ++i)                         // Generate 10 random numbers
		std::cout << dist(mt) << ", ";
}

int main()
{
	std::cout << "Thread 1's random values:\n";
	std::thread thr1(func);
	thr1.join();

	std::cout << "\nThread 2's random values:\n";
	std::thread thr2(func);
	thr2.join();
	std::cout << '\n';
}
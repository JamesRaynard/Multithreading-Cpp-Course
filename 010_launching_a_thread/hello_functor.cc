// Example of std::thread with a functor
#include <thread>
#include <iostream>

// Functor class with overloaded () operator
class Hello {
	public:
	void operator()() { std::cout << "Hello, Functor Thread!\n"; }
};

int main() {
	// Create an object of the functor class
	Hello hello;
	
	// Pass the functor object to std::thread's constructor
	std::thread thr(hello);
	
	// Wait for the thread to complete
	thr.join();
}
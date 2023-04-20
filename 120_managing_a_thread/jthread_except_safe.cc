// A std::jthread object is safely destroyed
// when an exception is thrown
// Requires a compiler which supports C++20
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello()
{
	std::cout << "Hello, Thread!\n";
}

int main()
{
	try {
		// Create an std::jthread object
		std::jthread thr(hello);
		
		// Code that might throw an exception
		throw std::exception();

		// std::jthread's destructor will call join() if necessary
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}
}
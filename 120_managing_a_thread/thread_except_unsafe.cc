// What happens to an std::thread object
// when an exception is thrown?
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
		// Create an std::thread object
		std::thread thr(hello);

		// Code that might throw an exception
		throw std::exception();

		thr.join();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}
}
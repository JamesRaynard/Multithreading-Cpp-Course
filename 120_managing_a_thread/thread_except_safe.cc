// Safely destroying an std::thread object
// when an exception is thrown (verbose)
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello()
{
	std::cout << "Hello, Thread!\n";
}

int main()
{
	// Create an std::thread object
	std::thread thr(hello);
	
	try {
		// Code that might throw an exception
		throw std::exception();

		// No exception if we got here - call join() as usual
		thr.join();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
		thr.join();                           // Call join() before thr's destructor is called
	}
} // Calls ~thr()
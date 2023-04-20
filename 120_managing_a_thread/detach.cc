// std::thread and detach()
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
	
	// Detach the child thread
	thr.detach();
	
	// Continue executing without waiting for the child thread
}
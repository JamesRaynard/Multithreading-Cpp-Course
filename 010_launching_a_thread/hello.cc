// First program with std::thread
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello() {
	std::cout << "Hello, Thread!\n";
}

int main() {
	// Create an std::thread object
	// Pass the entry point function to the constructor
	std::thread thr(hello);
	
	// Wait for the thread to complete
	thr.join();
}
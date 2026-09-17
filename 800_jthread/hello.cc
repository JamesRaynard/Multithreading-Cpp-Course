// First program with std::jthread
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello() {
	std::cout << "Hello, jthread!\n";
}

int main() {
	// Create an std::jthread object
	// Pass the entry point function to the constructor
	std::jthread thr(hello);
	
	// No longer needed with std::jthread
	// Wait for the thread to complete
	// thr.join();
}
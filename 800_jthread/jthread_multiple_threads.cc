// Use std::jthread to simplify thread creation
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello() {
	std::cout << "Hello, jthread!\n";
}

int main() {
	// Start the threads in an inner scope
	for (int i = 0; i < 10; ++i)
		std::jthread thr{hello};
	
} // End of scope
// The destructors for the thread objects are called	
// The threads will automatically be joined when the destructors are called
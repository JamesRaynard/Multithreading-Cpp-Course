#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello() {
	std::cout << "Hello, Thread!\n";
}

int main() {
	try {
		// Create an instance of std::thread and initialize it with the task
		std::thread t{ hello };
		try {
			// Throw exception
			throw std::exception();
		}
		catch (...) {
			t.join();
			throw;
		}
		t.join();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught\n";
	}
}
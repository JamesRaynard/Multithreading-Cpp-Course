#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello() {
	try {
		// Throw exception
		throw std::exception();
			}
	catch (std::exception& e) {
		std::cout << "Exception caught\n";
	}
	std::cout << "Hello, Thread!\n";
}

int main() {
	// Create an instance of std::thread and initialize it with the task
	//try {
		std::thread t{ hello };
		t.join();
	//}
	//catch (std::exception& e) {
		//std::cout << "Exception caught\n";
	//}

	std::cout << "Finished\n";
}
// Example with thread ID
#include <thread>
#include <iostream>

// Task function
// Displays the thread's ID
void hello() {
	std::cout << "Hello from thread with ID " << std::this_thread::get_id() << '\n';
}

int main() {
	// Display the main thread's ID
	std::cout << "Main thread has ID " << std::this_thread::get_id() << '\n';
	
	// Create an std::thread object
	std::thread thr(hello);
	
	// Display the child thread's ID
	std::cout << "Hello thread has ID " << thr.get_id() << '\n';
	
	// Wait for the thread to complete
	thr.join();
	
	// Display the child thread's ID again
	std::cout << "Hello thread now has ID " << thr.get_id() << '\n';
}
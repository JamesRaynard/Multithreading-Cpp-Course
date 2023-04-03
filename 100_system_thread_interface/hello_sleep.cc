// Example of pausing a thread
#include <thread>
#include <iostream>

using namespace std::literals;

void hello() {
	//std::this_thread::sleep_for(std::chrono::seconds(2));
	std::this_thread::sleep_for(2s);
	std::cout << "Hello, Thread!\n";
}

int main() {
	// Create an std::thread object
	std::cout << "Starting thread...\n";
	std::thread thr(hello);
	
	// Wait for the thread to complete
	thr.join();
}
#include <thread>
#include <iostream>

using namespace std::chrono;

void hello() {
	//std::this_thread::sleep_for(std::chrono::seconds(2));
	std::this_thread::sleep_for(2s);
	std::cout << "Hello, Thread!" << std::endl;
}

int main() {
	// Create an instance of std::thread and initialize it with the task
	std::cout << "Starting thread..." << std::endl;
	std::thread t{ hello };
	// Wait for the thread to complete
	t.join();
}
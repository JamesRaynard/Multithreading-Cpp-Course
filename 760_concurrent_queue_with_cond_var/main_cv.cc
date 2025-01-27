// Test program for concurrent blocking queue
#include "concurrent_queue_cv.h"
#include <iostream>
#include <future>
#include <string>

concurrent_queue_cv<std::string> conc_que;
	
// Waiting thread
void reader() {
	std::string data;
	
	// Pop some elements from the queue
	std::cout << "Reader calling pop..." << std::endl;
	for (int i = 0; i < 60; ++i) {
		conc_que.pop(data);                                    // Pop the data off the queue
		std::cout << "Reader received data: " << data << std::endl;
	}
}

// Modyifing thread
void writer() {
	using namespace std::literals;
	std::this_thread::sleep_for(2s);                       // Pretend to be busy...
	std::cout << "Writer calling push..." << std::endl;
	
	// Push the data onto the queue
	for (int i = 0; i < 60; ++i) {
		std::string data = "Item " + std::to_string(i);
		conc_que.push(data);
	}
	
	std::cout << "Writer returned from push..." << std::endl;
}

int main() {
	// Start the threads
	std::cout << "Starting reader" << std::endl;
	auto read_fut = async(std::launch::async, reader);
	std::cout << "Starting writer" << std::endl;
	auto write_fut = std::async(std::launch::async, writer);
	
	// Wait for them to complete
	read_fut.wait();
	write_fut.wait();
}
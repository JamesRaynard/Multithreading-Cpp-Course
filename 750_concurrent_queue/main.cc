// Test program for simple concurrent queue
#include "concurrent_queue.h"
#include <iostream>
#include <future>
#include <string>
#include <thread>

// Shared queue object
concurrent_queue<std::string> conc_que;
	
// Waiting thread
void reader() {
	using namespace std::literals;
	std::this_thread::sleep_for(2s);                         // Pretend to be busy...
	std::string sdata;
	
	// Pop some elements from the queue
	std::cout << "Reader calling pop..." << std::endl;
	for (int i = 0; i < 50; ++i) {
		conc_que.pop(sdata);                                    // Pop the data off the queue
		std::cout << "Reader received data: " << sdata << std::endl;
	}
}

// Modifying thread
void writer() {
	// Push the data onto the queue
	for (int i = 0; i < 50; ++i) {
		std::string sdata = "Item " + std::to_string(i);
		conc_que.push(sdata);
	}
	
	std::cout << "Writer returned from push..." << std::endl;
}

int main() {
	// Start the threads
	auto write_fut = std::async(std::launch::async, writer);
	auto read_fut = std::async(std::launch::async, reader);
	
	// Wait for them to complete
	try {
		read_fut.get();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	try {
		write_fut.get();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}
// Test program for simple concurrent queue
// with exception handling
#include "concurrent_queue.h"
#include <iostream>
#include <future>
#include <string>

// Shared queue object
concurrent_queue<std::string> cq;
	
// Waiting thread
void reader() {
	std::string sdata;
	
	// Pop an element from the queue
	std::cout << "Reader calling pop..." << std::endl;
	cq.pop(sdata);                                       // Pop the data off the queue
	std::cout << "Reader received data: " << sdata << std::endl;
}

// Modifying thread
void writer() {
	// Push an element onto the queue
	using namespace std::literals;
	std::this_thread::sleep_for(2s);                         // Pretend to be busy...
	std::cout << "Writer calling push..." << std::endl;
	cq.push("Populated");                                    // Push the data onto the queue
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
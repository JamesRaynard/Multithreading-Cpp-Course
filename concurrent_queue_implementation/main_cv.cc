#include "concurrent_queue_cv.h"
#include <iostream>
#include <future>
#include <string>

using namespace std;

concurrent_queue_cv<string> cq;
	
// Waiting thread
void reader() {
	string sdata;
	cout << "Reader calling pop..." << endl;
	cq.pop(sdata);                                       // Pop the data off the queue
	cout << "Reader received data: " << sdata << endl;
}

// Modyifing thread
void writer() {
	std::this_thread::sleep_for(2s);                     // Pretend to be busy...
	cout << "Writer calling push..." << endl;
	cq.push("Populated");                                // Push the data onto the queue
	cout << "Writer returned from push..." << endl;
}

int main() {
	cout << "Starting reader" << endl;
	auto r = async(std::launch::async, reader);
	cout << "Starting writer" << endl;
	auto w = async(std::launch::async, writer);
	r.wait();
	w.wait();
}
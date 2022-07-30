#include "concurrent_queue.h"
#include <iostream>
#include <future>
#include <string>

using namespace std;

concurrent_queue<string> cq;
	
// Waiting thread
void reader() {
	string sdata;
	cout << "Reader calling pop..." << endl;
	cq.pop(sdata);                                       // Pop the data off the queue
	cout << "Reader received data: " << sdata << endl;
}

// Modyifing thread
void writer() {
	std::this_thread::sleep_for(2s);                         // Pretend to be busy...
	cout << "Writer calling push..." << endl;
	cq.push("Populated");                                    // Push the data onto the queue
	cout << "Writer returned from push..." << endl;
}

int main() {
	auto w = async(std::launch::async, writer);
	auto r = async(std::launch::async, reader);
	try {
		r.wait();
	}
	catch (exception& e) {
		cout << "Exception caught: " << e.what() << endl;
	}

	w.wait();
}
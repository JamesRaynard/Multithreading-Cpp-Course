#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>

using namespace std;
using namespace std::chrono;

// Global variables
mutex mut;
condition_variable cv;
string sdata{"Empty"};
bool condition {false};			                       // Flag

// Waiting thread
void reader() {
	unique_lock<std::mutex> lk(mut);                   // Acquire lock
	cv.wait(lk, [] {return condition;});	           // Lambda predicate that checks the flag
	cout << "Data is \"" << sdata << "\"" << endl;     // Wake up and use the new value
}

// Modyifing thread
void writer() {
	cout << "Writing data..." << endl;
	{
		lock_guard<std::mutex> lg(mut);                // Acquire lock
		std::this_thread::sleep_for(2s);               // Pretend to be busy...
		sdata = "Populated";                           // Modify the data
		condition = true;			                   // Set the flag
	}
	cv.notify_one();                                   // Notify the condition variable
}

int main() {
	cout << "Data is \"" << sdata << "\"" << endl;
	// The notification is not lost,
	// even if the writer thread finishes before the reader thread starts
	// or there is a "spurious wakeup" (wait returns without a notification)
	thread write{writer};
	std::this_thread::sleep_for(500ms);
	thread read{reader};
	write.join();
	read.join();
}
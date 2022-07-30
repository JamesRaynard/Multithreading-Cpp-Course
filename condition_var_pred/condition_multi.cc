#include <iostream>
#include <thread>
#include <condition_variable>

using namespace std;
using namespace std::chrono;

// Global variables
mutex mut;
condition_variable cv;
string sdata {"Empty"};
bool ready{false};

// Waiting thread
void reader() {
    cout << "Thread " << this_thread::get_id() << " calling wait" << endl;
	unique_lock<std::mutex> guard(mut);                    // Acquire lock
    cv.wait(guard, [] {return ready;});                    // Wait for condition variable to be notified
	// Wake up and use the new value
    cout << "Thread " << this_thread::get_id() << " read \"" << sdata << "\"" << endl;
}

// Modyifing thread
void writer() {
	{
		lock_guard<std::mutex> lg(mut);                    // Acquire lock
		cout << "Writing data..." << endl; 
		std::this_thread::sleep_for(2s);                   // Pretend to be busy...
		sdata = "Populated";                               // Modify the data
		ready = true;
    }
	
	cv.notify_one();                                       // Notify the condition variable
	/*
	cv.notify_one();
	cv.notify_one();
	*/
	//cv.notify_all();
}

int main() {
	cout << "Data is " << sdata << endl;
	thread read1{reader};
	this_thread::sleep_for(10ms);
	thread read2{reader};
	this_thread::sleep_for(10ms);
	thread read3{reader};
	this_thread::sleep_for(10ms);
	thread write{writer};
	read1.join();
	read2.join();
	read3.join();
	write.join();
}
// Condition variable example
//
// The reader thread waits for a notification
// The writer thread modifies the shared variable "sdata"
// The writer thread sends a notification
// The reader thread receives the notification and resumes
// The reader thread uses the new value of the shared data
#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <chrono>

using namespace std::literals;

// The shared data
std::string sdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

// Waiting thread
void reader()
{
	// Lock the mutex
	std::cout << "Reader thread locking mutex\n";
	std::unique_lock<std::mutex> uniq_lck(mut);
	std::cout << "Reader thread has locked the mutex\n";

	// Call wait()
	// This will unlock the mutex and make this thread
	// sleep until the condition variable wakes us up
	std::cout << "Reader thread sleeping...\n";
	cond_var.wait(uniq_lck);

	// The condition variable has woken this thread up
	// and locked the mutex
	std::cout << "Reader thread wakes up\n";

	// Display the new value of the string
	std::cout << "Data is \"" << sdata << "\"\n";
}

// Notifying thread
void writer()
{
	{
		// Lock the mutex
		std::cout << "Writer thread locking mutex\n";

		// Lock the mutex
		// This will not be explicitly unlocked
		// std::lock_guard is sufficient
		std::lock_guard<std::mutex> lck_guard(mut);
		std::cout << "Writer thread has locked the mutex\n";

		// Pretend to be busy...
		std::this_thread::sleep_for(2s);

		// Modify the string
		std::cout << "Writer thread modifying data...\n";
		sdata = "Populated";
	}

	// Notify the condition variable
	std::cout << "Writer thread sends notification\n";
	cond_var.notify_one();
}

int main()
{
	// Initialize the shared string
	sdata = "Empty";

	// Display its initial value
	std::cout << "Data is \"" << sdata << "\"\n";

	// Start the threads
	std::thread read(reader);
	std::thread write(writer);

	write.join();
	read.join();
}
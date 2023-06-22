// Condition variable with predicate
//
// The reader thread will wait until "condition" becomes true
// This avoids lost and spurious wakeups
#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>

using namespace std::chrono;

// The shared data
std::string sdata;

// Mutex to protect critical sections
std::mutex mut;

// The condition variable
std::condition_variable cond_var;

// bool flag for predicate
bool condition = false;

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
	
	// Lambda predicate that checks the flag
	cond_var.wait(uniq_lck, [] {return condition;});

	// The condition variable has woken this thread up
	// and locked the mutex
	std::cout << "Reader thread wakes up\n";

	// Display the new value of the string
	std::cout << "Data is \"" << sdata << "\"\n";
	std::cout << "Reader thread unlocks the mutex\n";
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
		
		// Set the flag
		condition = true;
		
		std::cout << "Writer thread unlocks the mutex\n";
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
	
	// The notification is not lost,
	// even if the writer thread finishes before the reader thread starts
	// or there is a "spurious wakeup" (wait returns without a notification)
	std::thread write(writer);
	std::this_thread::sleep_for(500ms);
	std::thread read(reader);
	
	write.join();
	read.join();
}
// Example of std::timed_mutex try_lock_until() member function
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::timed_mutex the_mutex;

void task1()
{
	std::cout << "Task1 trying to get lock\n";
	the_mutex.lock();
	std::cout << "Task1 locks the mutex\n";
	std::this_thread::sleep_for(5s);
	std::cout << "Task1 unlocking the mutex\n";
	the_mutex.unlock();
}

void task2()
{
	std::this_thread::sleep_for(500ms);
	std::cout << "Task2 trying to lock the mutex\n";
	auto deadline = std::chrono::system_clock::now() + 900ms;

	// Try until "deadline" to lock the mutex
	while (!the_mutex.try_lock_until(deadline)) {
		// Returned false
		// Update "deadline" and try again
		deadline = std::chrono::system_clock::now() + 900ms;
		std::cout << "Task2 could not lock the mutex\n";
	}

	// Returned true - the mutex is now locked

	// Start of critical section
	std::cout << "Task2 has locked the mutex\n";
	// End of critical section

	the_mutex.unlock();
}

int main()
{
	std::thread thr1(task1);
	std::thread thr2(task2);

	thr1.join(); thr2.join();
}
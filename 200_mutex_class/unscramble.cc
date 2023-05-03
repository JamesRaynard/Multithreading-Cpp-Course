// Use a mutex to avoid scrambled output
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

// Global mutex object
std::mutex task_mutex;

void task(const std::string& str)
{
	for (int i = 0; i < 5; ++i) {
		// Lock the mutex before the critical section
		task_mutex.lock();

		// Start of critical section
		std::cout << str[0] << str[1] << str[2] << std::endl;
		// End of critical section

		// Unlock the mutex after the critical section
		task_mutex.unlock();
	}
}

int main()
{
	std::thread thr1(task, "abc");
	std::thread thr2(task, "def");
	std::thread thr3(task, "xyz");

	thr1.join();
	thr2.join();
	thr3.join();
}
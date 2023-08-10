// Use std::mutex to avoid scrambled output
// Find out what happens when an exception is thrown
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex task_mutex;						// Global mutex object

void task(const std::string& str)
{
	for (int i = 0; i < 5; ++i) {
		try {
			// Lock the mutex before the critical section
			task_mutex.lock();

			// Start of critical section
			std::cout << str[0] << str[1] << str[2] << std::endl;

			// Critical section throws an exception
			throw std::exception();
			// End of critical section

			// Never gets called
			task_mutex.unlock();
			std::this_thread::sleep_for(50ms);
		}
		catch (std::exception& e) {
			std::cout << "Exception caught: " << e.what() << '\n';
		}
	}
}

int main()
{
	std::thread thr1(task, "abc");
	std::thread thr2(task, "def");
	std::thread thr3(task, "xyz");

	thr1.join(); thr2.join(); thr3.join();
}

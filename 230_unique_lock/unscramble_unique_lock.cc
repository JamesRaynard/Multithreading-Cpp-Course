// Use std::unique_lock to avoid scrambled output
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex print_mutex;

void task(std::string str)
{
    for (int i = 0; i < 5; ++i) {
		// Create an std::unique_lock object
        // This calls print_mutex.lock()
        std::unique_lock<std::mutex> uniq_lck(print_mutex);
		
		// Start of critical section
        std::cout << str[0] << str[1] << str[2] << std::endl;
		// End of critical section
		
		// Unlock the mutex
		uniq_lck.unlock();

        std::this_thread::sleep_for(50ms);
    } // Calls ~std::unique_lock
}

int main()
{
	std::thread thr1(task, "abc");
	std::thread thr2(task, "def");
	std::thread thr3(task, "xyz");
	
	thr1.join(); thr2.join(); thr3.join();
}
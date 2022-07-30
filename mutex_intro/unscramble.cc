#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std;
using namespace std::literals;

mutex task_mutex;						// Global mutex instance

void task(string str) {
    for (int i = 0; i < 5; ++i) {
        task_mutex.lock();				// Lock the mutex before the "critical region"
        cout << str[0] << str[1] << str[2] << endl;
        // Commenting out the next line will deadlock the program
		task_mutex.unlock();					// Unlock the mutex afterwards
        this_thread::sleep_for(50ms);
    }
}

int main() {
	thread t{task, "abc"};
	thread t2{task, "def"};
	thread t3{task, "xyz"};
	t.join();
	t2.join();
	t3.join();
}
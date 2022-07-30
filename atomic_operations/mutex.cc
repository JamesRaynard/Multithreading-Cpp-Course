#include <mutex>
#include <thread>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::literals;

mutex m;

void task(int n) {
	lock_guard<mutex> lg(m);
	std::this_thread::sleep_for(50ms);                       // Look busy
	std::cout << "I'm a task with argument " << n << endl;	
}

int main() {
	std::vector<std::thread> threads;                        // Vector of threads
	for (int i=1; i<=10; ++i)
	    threads.push_back(std::thread{task, i});             // Add each thread to vector and run it
	for (auto& th : threads)
	th.join();
}
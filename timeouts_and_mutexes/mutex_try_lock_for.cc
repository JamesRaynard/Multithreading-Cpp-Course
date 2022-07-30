#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
using namespace std::literals;

timed_mutex the_mutex;

void task1() {
	cout << "Task1 trying to get lock" << endl;
	the_mutex.lock();
	cout << "Task1 has lock" << endl;
	this_thread::sleep_for(500ms);
	cout << "Task1 releasing lock" << endl;
	the_mutex.unlock();
}

void task2() {
	this_thread::sleep_for(100ms);
	cout << "Task2 trying to get lock" << endl;
	while (!the_mutex.try_lock_for(100ms)) {
		cout << "Task2 could not get lock" << endl;
	}
	cout << "Task2 has lock" << endl;
	the_mutex.unlock();
}

int main() {
	thread t1{task1}, t2{task2};
	t1.join();
	t2.join();
}
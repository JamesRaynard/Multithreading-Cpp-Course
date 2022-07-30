#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

mutex mutex1;
mutex mutex2;

void func1() {
	cout << "Thread 1 locking mutexes..." << endl;
	scoped_lock lk1(mutex1, mutex2);
	cout << "Thread 1 has locked mutexes..." << endl;
	std::this_thread::sleep_for(50ms);
	cout << "Thread 1 releasing mutexes..." << endl;
}

void func2() {
	cout << "Thread 2 locking mutexes..." << endl;
	scoped_lock lk1(mutex2, mutex1);
	cout << "Thread 2 has locked mutexes..." << endl;
	std::this_thread::sleep_for(50ms);
	cout << "Thread 2 releasing mutexes..." << endl;
}

int main() {
	thread t1{ func1 };
	thread t2{ func2 };
	t1.join();
	t2.join();
}
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

mutex mutex1;
mutex mutex2;

void func1() {
	cout << "Thread 1 locking mutexes..." << endl;
	lock(mutex1, mutex2);				               // Lock both mutexes
	cout << "Thread 1 has locked the mutexes..." << endl;
	unique_lock<mutex> lk1(mutex1, std::adopt_lock);   // Associate each mutex
	unique_lock<mutex> lk2(mutex2, std::adopt_lock);   // with a unique_lock
	cout << "Thread 1 releasing mutexes..." << endl;
}

void func2() {
	cout << "Thread 2 locking mutexes..." << endl;
	lock(mutex2, mutex1);				               // Lock both mutexes
	cout << "Thread 2 has locked the mutexes..." << endl;
	unique_lock<mutex> lk1(mutex1, std::adopt_lock);   // Associate each mutex
	unique_lock<mutex> lk2(mutex2, std::adopt_lock);   // with a unique_lock
	cout << "Thread 2 releasing mutexes..." << endl;
}

int main() {
	thread t1{ func1 };
	thread t2{ func2 };
	t1.join();
	t2.join();
}
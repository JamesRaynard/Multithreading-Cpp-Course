#include <thread>
#include <mutex>
#include <iostream>
#include <string>

using namespace std;
using namespace std::literals;

timed_mutex mutex1, mutex2;

void func1() {
	std::this_thread::sleep_for(10ms);
	bool locked{false};
    while (!locked) {
        lock_guard lk(mutex1);		 // Lock mutex1
        std::this_thread::sleep_for(1s);	    
        cout << "After you, Claude!" << endl;
		locked = mutex2.try_lock_for(5ms);			// Try to get a lock on mutex2
	}
	if (locked)
		cout << "Thread1 has locked both mutexes" << endl;
}

void func2() {
    bool locked{false};
    while (!locked) {
        lock_guard lk(mutex2);		 // Lock mutex2
        std::this_thread::sleep_for(1s);	    
        cout << "No, after you, Cecil!" << endl;
		locked = mutex1.try_lock_for(5ms);			// Try to get a lock on mutex1
	}
	if (locked)
		cout << "Thread2 has locked both mutexes" << endl;
}

int main() {
	thread t1(func1);
	std::this_thread::sleep_for(10ms);
	thread t2(func2);
	t1.join();
	t2.join();
}
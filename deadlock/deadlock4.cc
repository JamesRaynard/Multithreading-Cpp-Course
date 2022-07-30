#include <thread>
#include <mutex>

using namespace std;

mutex mutex1;
mutex mutex2;

void func1() {
    unique_lock<mutex> lk1(mutex1, std::defer_lock);	// Associate mutex with lock...
    unique_lock<mutex> lk2(mutex2, std::defer_lock);	// ...but don’t lock it yet
    lock(lk1, lk2);										// Now lock both of them
}

void func2() {
    unique_lock<mutex> lk2(mutex2, std::defer_lock);	// Associate mutex with lock...
    unique_lock<mutex> lk1(mutex1, std::defer_lock);	// ...but don’t lock it yet
    lock(lk1, lk2);										// Now lock both of them
}

int main() {
	thread t1{ func1 };
	thread t2{ func2 };
	t1.join();
	t2.join();
}
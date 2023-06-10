// Livelock caused by poorly implemented deadlock avoidance
// If the thread cannot get a lock, sleep and try again
// However, all the threads wake up at the same time
#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <chrono>

using namespace std::literals;

std::mutex mut1, mut2;

void funcA()
{
	std::this_thread::sleep_for(10ms);
	bool locked = false;
	while (!locked) {
		std::lock_guard<std::mutex> lck_guard(mut1);  // Lock mut1
		std::cout << "After you, Claude!\n";
		std::this_thread::sleep_for(2s);
		locked = mut2.try_lock();                           // Try to lock mut2
	}
	if (locked)
		std::cout << "ThreadA has locked both mutexes\n";
}

void funcB() {
	bool locked = false;
	while (!locked) {
		std::lock_guard<std::mutex> lk(mut2);         // Lock mut2
		std::cout << "After you, Cecil!\n";
		std::this_thread::sleep_for(2s);
		locked = mut1.try_lock();                           // Try to lock mut1
	}
	if (locked)
		std::cout << "ThreadB has locked both mutexes\n";
}

int main() {
	std::thread thrA(funcA);
	std::this_thread::sleep_for(10ms);
	std::thread thrB(funcB);

	thrA.join(); thrB.join();
}
// std::shared_lock and std::lock() avoid deadlock
// when locking multiple mutexes. They also avoid livelock.
#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <chrono>	

using namespace std::literals;

std::mutex mut1, mut2;

void funcA() {
	std::this_thread::sleep_for(10ms);

	std::cout << "After you, Claude!" << std::endl;
	std::scoped_lock scoped_lck(mut1, mut2);		 // Lock both mutexes
	std::this_thread::sleep_for(2s);
	std::cout << "Thread A has locked both mutexes\n";
}

void funcB() {
	std::cout << "After you, Cecil!\n";
	std::scoped_lock scoped_lck(mut2, mut1);		 // Lock mutexes
	std::this_thread::sleep_for(2s);
	std::cout << "Thread B has locked both mutexes\n";
}

int main() {
	std::thread thrA(funcA);
	std::this_thread::sleep_for(10ms);
	std::thread thrB(funcB);

	thrA.join(); thrB.join();
}
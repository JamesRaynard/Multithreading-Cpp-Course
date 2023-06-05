// Use std::adopt_lock to avoid deadlock
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
	std::lock(mut1, mut2);				               // Lock both mutexes
	std::cout << "Thread A has locked mutexes 1 and 2\n";
	
	// Adopt the locks
	std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);   // Associate each mutex
	std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);   // with a unique_lock
	std::cout << "Thread A has adopted the locks\n";
	
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB() {
	std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
	lock(mut2, mut1);				               // Lock both mutexes
	std::cout << "Thread B has locked mutexes 2 and 1\n";
	
	// Adopt the locks
	std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);   // with a unique_lock
	std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);   // Associate each mutex
	std::cout << "Thread B has adopted the locks\n";
	
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main() {
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
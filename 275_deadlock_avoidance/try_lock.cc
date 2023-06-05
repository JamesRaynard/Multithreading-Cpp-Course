// Use std::defer_lock to avoid deadlock
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);   // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);   // ...but don’t lock it yet
	
	std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
    
	// Now lock both of them
	auto idx = std::try_lock(uniq_lk1, uniq_lk2);
	if (idx != -1) {
		std::cout << "try_lock failed on mutex with index " << idx << '\n';
	}
	else {
		std::cout << "Thread A has locked mutexes 1 and 2\n";
		std::this_thread::sleep_for(50ms);
		std::cout << "Thread A releasing mutexes 1 and 2...\n";
	}
}

void funcB() {
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);   // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);   // ...but don’t lock it yet
	
	std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
    
	// Now lock both of them
	auto idx = std::try_lock(uniq_lk2, uniq_lk1);
	if (idx != -1) {
		std::cout << "try_lock failed on mutex with index " << idx << '\n';
	}
	else {
		std::cout << "Thread B has locked mutexes 2 and 1\n";
		std::this_thread::sleep_for(50ms);
		std::cout << "Thread B releasing mutexes 2 and 1...\n";
	}
}

int main() {
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
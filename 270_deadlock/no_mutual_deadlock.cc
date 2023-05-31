// Avoid deadlock by writing the threads
// so that they lock the mutexes in the same order
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "Thread A trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard(mut1);        // Acquire lock on mut1
	std::cout << "Thread A has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread A trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard2(mut2);       // Wait for lock on mut2
	std::cout << "Thread A has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);                  // Do some work
	std::cout << "Thread A releases all its locks\n";
}

void funcB()
{
	std::cout << "Thread B trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard1(mut1);       // Acquire lock on mut1
	std::cout << "Thread B has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);                  // Do some work
	std::cout << "Thread B trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard2(mut2);	    // Wait for lock on mut2
	std::cout << "Thread B has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread B releases all its locks\n";
}

int main()
{
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
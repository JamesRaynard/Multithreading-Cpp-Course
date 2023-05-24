// Test program for classic Singleton
#include "classic_singleton.h"
#include <thread>
#include <vector>

Singleton* Singleton::single = nullptr;

void task()
{
	Singleton* single = Singleton::get_Singleton();
	std::cout << single << std::endl;
}

int main()
{
	std::vector<std::thread> threads;
	
	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread(task));
	
	for (auto& thr : threads)
		thr.join();
}
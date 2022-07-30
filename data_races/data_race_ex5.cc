#include <thread>
#include <iostream>

using namespace std::literals;

int x{0};
bool done{false};

void func1() {
	std::this_thread::sleep_for(50ms); // Pretend to do some work
	x = 42;
	done = true;
}

void func2() {
	//std::this_thread::sleep_for(50ms); // Pretend to do some work
	while (!done) {}
	std::cout << x << std::endl;
}

int main() {
	std::thread t{func1};
	std::thread t2{func2};
	
	t.join();
	t2.join();
}
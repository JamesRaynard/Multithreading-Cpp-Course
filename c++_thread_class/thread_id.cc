#include <thread>
#include <iostream>

void hello() {
	std::cout << "Hello from thread with ID " << std::this_thread::get_id() << std::endl;
}

int main() {
	std::cout << "Main thread has ID " << std::this_thread::get_id() << std::endl;
	std::thread t{ hello };
	std::cout << "Hello thread has ID " << t.get_id() << std::endl;
	t.join();
	std::cout << "Hello thread has ID " << t.get_id() << std::endl;
}
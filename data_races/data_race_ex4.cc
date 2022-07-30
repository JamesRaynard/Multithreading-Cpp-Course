#include <thread>
#include <iostream>

void task() {
	for (int i = 0; i < 5; ++i) {
		std::cout << "I'm a task with ID " << std::this_thread::get_id() << "!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pretend to do some work
	}
}
int main() {
	std::thread t{task};
	std::thread t2{task};
	std::thread t3{task};
	// Wait for the tasks to complete
	t.join();
	t2.join();
	t3.join();
}
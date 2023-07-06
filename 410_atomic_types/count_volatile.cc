// A shared variable is modified by multiple threads
// Using a "volatile" variable does not prevent a data race
#include <thread>
#include <iostream>
#include <vector>
#include <atomic>

volatile int counter = 0;

void task() {
    for (int i = 0; i < 100'000; ++i)
        ++counter;
}

int main() {
    std::vector<std::thread> tasks;
    for (int i = 0; i < 10; ++i)
        tasks.push_back(std::thread(task));
    for (auto& thr: tasks)
		thr.join();
    std::cout << counter << '\n';
}

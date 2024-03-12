#include <iostream>
#include <thread>
#include <vector>
#include "binary_semaphore.h"

int main() {
    Semaphore sem;

    auto insert = [&sem]() {
        sem.release();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    };

    auto relinquish = [&sem] {
        sem.acquire();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    };

    std::vector<std::thread> tasks;

    for (int i = 0; i < 2; ++i)
        tasks.push_back(std::thread(insert));
    for (int i = 0; i < 4; ++i)
        tasks.push_back(std::thread(relinquish));
    for (int i = 0; i < 3; ++i)
        tasks.push_back(std::thread(insert));
    for (auto& task : tasks) {
        task.join();
    }
}
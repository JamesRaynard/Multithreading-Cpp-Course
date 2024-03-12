#include <mutex>
#include <condition_variable>
#include <iostream>

class Semaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int counter{0};
    const int max_count{1};
public:
    void release() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Adding one item" << std::endl;

        if (counter < max_count) {
            ++counter;
			count();
		}

        cv.notify_all();
    }

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Removing one item" << std::endl;

        while (counter == 0) {
            cv.wait(lock);
        }

        --counter;
        count();
    }

    void count() const {
        std::cout << "Value of counter: ";
        std::cout << counter << std::endl;
    }
};

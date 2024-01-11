// Another way to solve double-checked locking
// Make the lazily-initialized variable atomic
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

class Test {
	// ...
public:
	void func() { /*...*/ }
};

std::atomic<Test*> ptest = nullptr;  // Variable to be lazily initialized
std::mutex mut;

void process()
{
	// First check of ptest
	if (!ptest) {
		std::lock_guard<std::mutex> lck_guard(mut);

		// Second check of ptest
		if (!ptest) {
			// Initialize ptest
			ptest = new Test;
		}
	}

	// Atomic pointers cannot be dereferenced
	// Copy it to a non-atomic pointer first
	Test *ptr_test = ptest;
	ptr_test->func();
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread(process));

	for (auto& thr : threads)
		thr.join();
}
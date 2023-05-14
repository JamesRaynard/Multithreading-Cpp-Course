// Example of std::recursive_mutex
#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rmut;

int bad_factorial(int n)
{
	if (n <= 1) {
		std::cout << "Returning " << 1 << '\n';
		return 1;
	}
	
	std::lock_guard<std::recursive_mutex> lck_guard(rmut);
	//rmut.lock();
	
	// Start of critical section
	int retval = n*bad_factorial(n-1);
	std::cout << "Returning " << retval << std::endl;
	// End of critical section
	
	//rmut.unlock();
	return retval;
}

int main()
{
	std::thread thr1(bad_factorial, 10);
	std::thread thr2(bad_factorial, 11);
	
	thr1.join(); thr2.join();
}
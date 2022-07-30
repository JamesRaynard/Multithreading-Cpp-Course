#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

recursive_mutex rm;

int bad_factorial(int n) {
	if (n <= 1) {
		cout << "Returning " << 1 << endl;
		return 1;
	}
	lock_guard<recursive_mutex> lg(rm);
	//rm.lock();
	int retval = n*bad_factorial(n-1);
	cout << "Returning " << retval << endl;
	//rm.unlock();
	return retval;
}

int main() {
	thread t1{bad_factorial, 10};
	thread t2{bad_factorial, 11};
	t1.join();
	t2.join();
}
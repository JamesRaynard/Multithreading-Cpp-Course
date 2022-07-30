#include <iostream>
#include <thread>

using namespace std;
using namespace std::literals;

void hello(int num) {
	this_thread::sleep_for(chrono::seconds(num));
	cout << "Hello from thread " << num << endl;
}

int main() {
	thread t1{hello, 1};
	thread t2{hello, 2};
	thread t3{hello, 3};
	t1.join();
	t2.join();
	t3.join();
}
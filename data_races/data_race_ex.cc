#include <thread>
#include <iostream>

using namespace std;

// Exercise 1
const int x{5};

int func1() {
    return 2*x;
}

int func2() {
    return 3*x;
}

int main() {
	thread f1{ func1 };
	thread f2{ func2 };
	f1.join();
	f2.join();
}
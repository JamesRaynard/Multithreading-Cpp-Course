#include <thread>
#include <iostream>

using namespace std;

int x{0}, y{0};

void func1() {
    if (x) {
        y = 1;
		cout << "y set\n";
	}
}

void func2() {
    if (y) {
        x = 1;
		cout << "x set\n";
	}
}

int main() {
	thread f1{ func1 };
	thread f2{ func2 };
	f1.join();
	f2.join();
}
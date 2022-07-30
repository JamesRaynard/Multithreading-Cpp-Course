#include <thread>
#include <iostream>

using namespace std;
using namespace std::literals;

int x{0}, y{0};
int r1, r2;

void func1() {
	std::this_thread::sleep_for(100ms);
	//cout << "x = " << x << endl;
	x = 1;
    r1 = y;
}

void func2() {
    std::this_thread::sleep_for(90ms);
	//cout << "y = " << y << endl;
	y = 1;
    r2 = x;
}

int main() {
	thread f1{ func1 };
	thread f2{ func2 };
	f1.join();
	f2.join();
	cout << "x = " << x << ", r1 = " << r1 << endl;
	cout << "y	= " << y << ", r2 = " << r2 << endl;
}
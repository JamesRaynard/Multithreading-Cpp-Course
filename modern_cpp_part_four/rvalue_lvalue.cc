#include <iostream>

using namespace std;

void func(const int& x) {
	cout << "Lvalue reference" << endl;
}

void func(int&& x) {
	cout << "Rvalue reference" << endl;
}

int main() {
	int y{2};
	
	cout << "Argument y:\t\t";
	func(y);
	
	cout << "Argument move(y):\t";
	func(std::move(y));
	
	cout << "Argument 2:\t\t";
	func(2);
}
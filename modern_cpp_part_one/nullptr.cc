#include <iostream>

using namespace std;

void func(int i) {
	cout << "func(int) called\n";
}

void func(int *i) {
	cout << "func(int *) called\n";
}

int main() {
	func(NULL);
	func(nullptr);
}
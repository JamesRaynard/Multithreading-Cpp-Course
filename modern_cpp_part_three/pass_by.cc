#include <iostream>
#include <vector>
#include <string>

using namespace std;

void func(vector<string> arg) {
	cout << "Argument vector has " << arg.size() << " elements" << endl;
}

int main() {
	vector<string> vec(1000000);
	
	cout << "Before calling func, vector has " << vec.size() << " elements" << endl;
	func(vec);
	//func(std::move(vec));
	cout << "After calling func, vector has " << vec.size() << " elements" << endl;
}
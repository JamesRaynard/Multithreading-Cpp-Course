#include <thread>
#include <iostream>
#include <string>

using namespace std;

void hello(string& s) {
	s = "xyz";
}

int main() {
	string str{ "abc" };
	thread t{ hello, std::ref(str)};
	t.join();
	cout << "str is now " << str << endl;
}
#include <thread>
#include <iostream>

using namespace std;

class Change {
	public:
	void operator () (int& i) {
		i *= 2;
	}
};

void change(int& i) {
	i *= 2;
}

int main() {
	int i{ 3 };
	//thread t{ change, std::ref(i) };
	// thread t{ [&] () {
	//	i *= 2;
	// }};
	Change change;
	thread t{ change, std::ref(i) };
	t.join();
	cout << "Value of is is now " << i << endl;
}
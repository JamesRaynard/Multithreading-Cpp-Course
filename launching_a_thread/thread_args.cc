#include <thread>
#include <iostream>

using namespace std;

class Add {
	public:
	void operator () (int i1, int i2) {
		cout << "Sum of " << i1 << " and " << i2 << " is " << i1 + i2<< endl;
	}
};

void add(int i1, int i2) {
	cout << "Sum of " << i1 << " and " << i2 << "is " << i1 + i2<< endl;
}

int main() {
	// thread t{ add, 2, 3 };
	// thread t{ [] (int i1, int i2) {
	//	cout << "Sum of " << i1 << " and " << i2 << " is " << i1 + i2<< endl;
	// }, 2, 3};
	Add add;
	thread t{ add, 2, 3 };
	t.join();
}
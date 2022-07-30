#include <future>
#include <iostream>
#include <thread>
#include <exception>

using namespace std;

int produce() {
	int x{42};          
	this_thread::sleep_for(5s);
	throw std::out_of_range("Oops");
	cout << "Produce returning " << x << endl;
	return x;
}

int main() {
	auto f = async(produce);

	cout << "Future calling get()..." << endl;
	try {
		int x = f.get();				           // Get the result
		cout << "Future returns from calling get()" << endl;
		cout << "The answer is " << x << endl;
	}
	catch(exception& e) {
		cout << "Exception caught: " << e.what() << endl;
	}
}

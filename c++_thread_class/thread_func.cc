#include <thread>
#include <iostream>

using namespace std;

// Function taking a thread object as argument
void f(std::thread t) {
	cout << "Received thread with ID " << this_thread::get_id() << endl;
	t.join();
}

void hello() {
	std::cout << "Hello, Thread!\n";
}

int main() {
	std::thread t{ hello };
	// f(std::thread{ hello });                   // Pass temporary to f
	f(std::move(t));         // Pass variable to f using std::move()
}

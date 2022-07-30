#include <thread>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void hello() {
	std::cout << "Hello, Thread!\n";
	std::this_thread::sleep_for(100ms);
}

std::thread g() {                       // Function returning a thread object
    // return std::thread{ func };      // Return temporary
    std::thread t{ hello };    
    return t;                           // Return local variable
}

int main() {
	std::thread t{ g() };
	cout << "Received thread with ID " << t.get_id() << endl;
	t.join();
}

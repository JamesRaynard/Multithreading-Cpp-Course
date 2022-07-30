#include <chrono>

using namespace std::chrono;
using namespace std::literals;

int main() {
	seconds(2);                              // 2 second interval
	milliseconds(20);                        // 20 millisecond interval
	microseconds(50);                        // 50 microsecond interval
	2s;
	20ms;
	50us;
}
#include <iostream>
#include <thread>
#include <string>

class Grabber {
	public:
	void operator () (std::string s) {
		std::cout << "Ownership of \"" << s << "\" transferred to thread" << std::endl;
	}
};

void func(std::string s) {
	std::cout << "Ownership of \"" << s << "\" transferred to thread" << std::endl;
}

int main() {
	std::string s{"moveable"};
	std::cout << "Starting thread" << std::endl;
	//auto t = std::thread(func, std::move(s));
	//Grabber grab;
	//auto t = std::thread(grab, std::move(s));
	auto t = std::thread([s = std::move(s)]{
		std::cout << "Ownership of \"" << s << "\" transferred to thread" << std::endl;
	});
	t.join();
	std::cout << "Do I still have any data?" << std::endl;
	std::cout << s << std::endl;
}
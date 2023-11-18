// std::shared_ptr and thread safety
// Operations which only affect the reference counter are safe
// and do not need to be synchronized
#include <memory>
#include <thread>
#include <iostream>

// std::shared_ptr has an "atomic" reference counter
std::shared_ptr<int> shptr = std::make_shared<int>(42);

void func1()
{
    // Increments shared_p's reference counter - safe
    std::shared_ptr<int> shp1 = shptr;
}

void func2()
{
    // Increments shared_p's reference counter - safe
    std::shared_ptr<int> shp2 = shptr;
}

int main()
{
	std::thread thr1(func1);
	std::thread thr2(func2);
	thr1.join();
	thr2.join();
}
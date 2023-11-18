// Operations on std::shared_ptr
#include <memory>
#include <iostream>

int main()
{
	// Pass a pointer as the constructor argument
	std::shared_ptr<int> ptr1(new int(42));
	
	// Calling std::make_shared() is better
	auto ptr2 = std::make_shared<int>(42);
	
	// Can be dereferenced
	std::cout << *ptr1 << '\n';
	
	// Pointer arithmetic is not supported
	// ++ptr1;
	
	// Assignment, copying and moving are allowed
	ptr1 = ptr2;
	std::shared_ptr<int> ptr3(ptr2);
	std::shared_ptr<int> ptr4(std::move(ptr2));
	
	// Releases the allocated memory
	ptr1 = nullptr;
}
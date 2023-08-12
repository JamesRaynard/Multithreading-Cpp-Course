// Hello world using std::async()
#include <future>
#include <iostream>

// Task function
void hello()
{
    std::cout << "Hello, Async!\n";
}

int main()
{
	// Call std::async() to perform the task
    std::async(hello);
}

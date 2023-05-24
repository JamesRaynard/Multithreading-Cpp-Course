// Singleton class definition
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton {
  public:
	// The copy and move operators are deleted
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
	
	Singleton() { std::cout << "Initializing Singleton\n";}
};

// Function to obtain the Singleton object
Singleton& get_Singleton();

#endif //SINGLETON_H
// Singleton class definition
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton {
	// Pointer to unique instance
	static Singleton *single;
	
	// The constructor is private
	Singleton() { std::cout << "Initializing Singleton" << std::endl;}
public:
	// The copy and move operators are deleted
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
	
	// Static member function to obtain the Singleton object
	static Singleton* get_Singleton();
};

#endif //Singleton_H
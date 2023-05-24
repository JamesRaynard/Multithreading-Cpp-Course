// Singleton class implementation (Meyers Singleton)
// Uses C++11's guarantees about initializing static variables
#include "cpp11_singleton.h"

// Function to obtain the Singleton object
Singleton& get_Singleton()
{
    // Initialized by the first thread that executes this code
	static Singleton single;
	return single;
}

// Lazy initialization (single-threaded)
class Test {
	// ...
public:
	void func() { /*...*/ }
};

Test *ptest = nullptr;          // Variable to be lazily initialized

void process() {
    if (!ptest)                // First time variable has been used
        ptest = new Test;      // Initialize it
    ptest->func();             // Use it
}

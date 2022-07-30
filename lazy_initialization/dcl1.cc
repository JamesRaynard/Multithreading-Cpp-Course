class some_type {
	// ...
public:
	void do_it() { /*...*/ }
};

some_type *ptr{nullptr};          // Variable to be lazily initialized

void process() {
    if (!ptr)                     // First time variable has been used
        ptr = new some_type;      // Initialize it
    ptr->do_it();                 // Use it
}

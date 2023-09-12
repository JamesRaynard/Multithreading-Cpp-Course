// Uses a standard algorithm to find a character in a string
// The predicate makes the search case-insensitive
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main() {
	std::string str("Hello world");
	std::cout << "String to search: " << str << '\n';

	// Search string for first occurrence of 'o'
	std::cout << "Searching for first occurrence of \'o\'\n";

	// Use a predicate function which ignores case
	auto res = std::find_if(str.cbegin(), str.cend(),
					[](const char c) {
						return ::toupper(c) == 'O';
					});

	// Did we find it?
	if (res != str.cend()) {
		// Access the result
		std::cout << "Found a matching element at index: " << res - str.cbegin() << '\n';

		std::cout << "At this point in the string: ";
		for (auto it = res; it != str.cend(); ++it)
			std::cout << *it;
		std::cout << '\n';
	}
	else
		std::cout << "No matching element\n";
}
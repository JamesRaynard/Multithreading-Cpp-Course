// Example of std::unique_ptr
#include <iostream>
#include <memory>

// Data structure representing a point on the screen
struct Point {
    int x;
    int y;
};

int main()
{
	// Create a unique_ptr to an Point object which has initial values {3,6}
	auto uniq_ptr = std::make_unique<Point>( Point{3, 6} );
	//std::unique_ptr<Point> uniq_ptr(new Point{3, 6});           // C++11

	std::cout << uniq_ptr->x << ", " << uniq_ptr->y << '\n';
}
#include <cassert>
#include "Lines.cpp" // Note: usually we don't include source files to code

// Note: it might be useful to use google test framework
// it is really easy to use with CMake (but only if you don't use MacOS)
void runTests() {
    // Test 1: intersection
    Line l1(Point(0, 0), Point(2, 2)); // y = x
    Line l2(Point(0, 2), Point(2, 0)); // y = -x + 2
    Point intersection = l1.getIntersection(l2);
    assert(intersection.x == 1 && intersection.y == 1);

    // Test 2: perpendicular?
    Line perp = l1.getPerpendicular(Point(1, 1));
    std::cout << perp.a << "x + " << perp.b << "y + " << perp.c << " = 0" << std::endl;

    // Test 3: matching lines
    try {
        Line l3(Point(0, 0), Point(1, 1)); // y = x
        l3.getIntersection(l1); // y = x
        assert(false);
    } catch (const std::runtime_error&) {
        std::cerr << "Matching lines detected.\n";
    }

    // Test 4: parallel lines
    try {
        Line l4(Point(0, 1), Point(1, 2)); // y = x + 1
        l1.getIntersection(l4); // y = x
        assert(false);
    } catch (const std::runtime_error&) {
        std::cerr << "Parallel lines detected.\n";
    }

    // Test 5: weird lines
    try {

        std::cout << "Test 5: weird lines " << std::endl;

        Point p1(1, 1);
        Point p2(1, 1);
        Line plane(p1, p2);
        std::cout << "equation of line: " << plane.a << "*x " << plane.b 
            << "*y " << "+ " << plane.c << " = 0" << std::endl;

        std::cout << "But actually it is not line!\n" << "This line is a plane!\n\n";

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl; 
    }

    // Test 6: tricky floats
    try {

        std::cout << "Test 6: tricky floats\n" << std::endl;

        Line first(1.0 / 3, 2, 0);
        Line second(0.1, 3.0 / 5, 1);

        Point intersection = first.getIntersection(second);
        std::cout << "Lines has intersection: (" << intersection.x << ", " 
            << intersection.y << ")" << std::endl;

        std::cout << "But math says that there is no intersection!\n" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl; 
    }


    std::cout << "Tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}

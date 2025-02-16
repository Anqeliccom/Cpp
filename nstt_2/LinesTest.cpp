#include <cassert>
#include "Lines.cpp"

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

    std::cout << "Tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}

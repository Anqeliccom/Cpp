#include <cassert>
#include <iostream>
#include "Lines.hpp"

void runTests() {
    // Test 1: intersection
    Line l1(Point(0, 0), Point(2, 2)); // y = x
    Line l2(Point(0, 2), Point(2, 0)); // y = -x + 2
    auto intersection= l1.getIntersection(l2);
    assert(intersection.has_value());
    assert(isEqual(intersection->x, 1) && isEqual(intersection->y, 1));

    // Test 2: perpendicular
    Line perp = l1.getPerpendicular(Point(1, 1));
    std::cout << perp.a << "x + " << perp.b << "y + " << perp.c << " = 0" << std::endl;

    // Test 3: matching lines
    auto sameLine = l1.getIntersection(l1);
    assert(!sameLine.has_value());

    // Test 4: parallel lines
    Line l4(Point(0, 1), Point(1, 2)); // y = x + 1
    auto parallelIntersection = l1.getIntersection(l4);
    assert(!parallelIntersection.has_value());

    // Test 5: weird lines
    auto invalidLine = Line::create(Point(1, 1), Point(1, 1));
    assert(!invalidLine.has_value());

    // Test 6: tricky floats
    std::cout << "Test 6: tricky floats\n" << std::endl;
    Line first(1.0 / 3, 2, 0);
    Line second(0.1, 3.0 / 5, 1);
    auto trickyIntersection = first.getIntersection(second);
    if (trickyIntersection) {
        std::cout << "Lines has intersection: (" << trickyIntersection->x << ", "
        << trickyIntersection->y << ")" << std::endl;
    } else {
        std::cout << "There is no intersection\n";
    }

    std::cout << "Tests passed!" << std::endl;
}

int main() {
    runTests();
    return 0;
}

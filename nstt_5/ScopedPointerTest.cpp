#include <cassert>
#include <iostream>

#include "ScopedPointer.hpp"

void ScopedPointerDeepCopyTest() {
    ScopedPointerDeepCopy<int> p1(new int(10));
    ScopedPointerDeepCopy<int> p2 = p1;
    p1.get() = 15;
    assert(p2.get() == 10);
    assert(p1.get() == 15);

    ScopedPointerDeepCopy<int> p3(new int(20));
    p3 = p1;
    assert(p3.get() == 15);
}

void ScopedPointerMoveTest() {
    ScopedPointerMove<int> p1(new int(10));
    ScopedPointerMove<int> p2 = std::move(p1);
    assert(p2.get() == 10);
    assert(p1.operator->() == nullptr);

    ScopedPointerMove<int> p3(new int(20));
    p3 = std::move(p2);
    assert(p3.get() == 10);
    assert(p2.operator->() == nullptr);
}

int main() {
    ScopedPointerDeepCopyTest();
    ScopedPointerMoveTest();
    std::cout << "Tests passed" << std::endl;
    return 0;
}

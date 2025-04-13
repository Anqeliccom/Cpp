#include <cassert>
#include <iostream>

#include "ScopedPointer.hpp"

void ScopedPointerDeepCopyTest() {
    ScopedPointerDeepCopy<int> p1(new int(10));
    ScopedPointerDeepCopy<int> p2 = p1;
    *p1 = 15;
    assert(*p2 == 10);
    assert(*p1 == 15);

    ScopedPointerDeepCopy<int> p3(new int(20));
    p3 = p1;
    assert(*p3 == 15);
}

void ScopedPointerMoveTest() {
    ScopedPointerMove<int> p1(new int(10));
    ScopedPointerMove<int> p2 = std::move(p1);
    assert(*p2 == 10);
    assert(p1.operator->() == nullptr);

    ScopedPointerMove<int> p3(new int(20));
    p3 = std::move(p2);
    assert(*p3 == 10);
    assert(p2.operator->() == nullptr);
}

void DrillDownDeepCopyTest() {
    int *x =  new int(10);
    ScopedPointerDeepCopy<int> px(x);
    ScopedPointerDeepCopy<int> ppx(px);
    assert(*ppx == 10);
    assert(ppx.operator->() != x);
}

void DrillDownMoveTest() {
    int* x = new int(10);
    ScopedPointerMove<int> px(x);
    ScopedPointerMove<int> ppx(std::move(px));
    assert(*ppx == 10);
    assert(ppx.operator->() == x);
}

int main() {
    ScopedPointerDeepCopyTest();
    ScopedPointerMoveTest();
    DrillDownDeepCopyTest();
    DrillDownMoveTest();
    std::cout << "Tests passed" << std::endl;
    return 0;
}

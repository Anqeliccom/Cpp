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

struct C {
    int value;
    C(int v) : value(v) {}
};

struct B {
    ScopedPointerDeepCopy<C> c;
    B(int v) : c(new C(v)) {}
};

struct A {
    ScopedPointerDeepCopy<B> b;
    A(int v) : b(new B(v)) {}
};

void DrillDownTest() {
    ScopedPointerDeepCopy<A> pa(new A(12));
    int v1 = pa.operator->()->b.operator->()->c.operator->()->value;
    int v2 = pa->b->c->value;
    assert(v1 == v2);
    assert(v2 == 12);
}

int main() {
    ScopedPointerDeepCopyTest();
    ScopedPointerMoveTest();
    DrillDownTest();
    std::cout << "Tests passed" << std::endl;
    return 0;
}

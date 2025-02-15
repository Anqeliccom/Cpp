#include <iostream>
#include <cassert>

#include "SegmentTree.cpp"

void runTests() {
    SegmentTree arr({1, 3, 5, 7, 9});
    assert(arr.sumRange(2, 4) == 21);
    arr.update(3, 5);
    assert(arr.sumRange(2, 4) == 19);

    SegmentTree negArr({-8, -7, -5, -6, -9, -10});
    assert(negArr.sumRange(0, 2) == -20);
    negArr.update(0, -1);
    assert(negArr.sumRange(0, 2) == -13);

    SegmentTree emptyArr({});
    assert(emptyArr.sumRange(0, 0) == 0);
    emptyArr.update(0, 5);

    std::cout << "Tests passed" << std::endl;
}

int main() {
    runTests();
    return 0;
}


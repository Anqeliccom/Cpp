#include <cassert>

#include "SegmentTree.cpp" // PR: include source is always looks strange
                           // lets convert SegmentTree to header file (just change .cpp to .hpp)

void runSumRangeAndUpdateTest() {
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
}

void runCopyConstructorTest() {
    SegmentTree tree1({1, 3, 5, 7, 9});
    SegmentTree tree2(tree1);

    assert(tree2.sumRange(2, 4) == tree1.sumRange(2, 4));

    tree2.update(3, 5);
    assert(tree2.sumRange(2, 4) != tree1.sumRange(2, 4));
}

void runAssignmentOperatorTest() {
    SegmentTree tree1({2, 4, 6, 8, 10});
    SegmentTree tree2({1, 3, 5, 7, 9});

    tree1.operator=(tree2); // Note: You can write just tree1 = tree2

    assert(tree1.sumRange(2, 4) == tree2.sumRange(2, 4));

    tree1.update(3, 5);
    assert(tree1.sumRange(2, 4) != tree2.sumRange(2, 4));
}

int main() {
    runSumRangeAndUpdateTest();
    runCopyConstructorTest();
    runAssignmentOperatorTest();
    std::cout << "Tests passed" << std::endl;
    return 0;
}

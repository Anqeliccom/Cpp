#include <cassert>
#include <iostream>
#include "SegmentTree.hpp"

void runDynamicSumRangeAndUpdateTest() {
    SegmentTree tree(10);
    assert(tree.sumRange(0, 9) == 0);

    tree.update(2, 5);
    assert(tree.sumRange(0, 9) == 5);

    tree.update(8, 10);
    assert(tree.sumRange(0, 9) == 15);
}

void runDynamicCopyConstructorTest() {
    SegmentTree tree1(10);
    tree1.update(2, 5);
    tree1.update(8, 10);

    SegmentTree tree2(tree1);
    assert(tree2.sumRange(2, 2) == 5);
    assert(tree2.sumRange(8, 8) == 10);

    tree2.update(8, 2);
    assert(tree1.sumRange(8, 8) == 10);
    assert(tree2.sumRange(8, 8) == 2);
}

void runDynamicAssignmentOperatorTest() {
    SegmentTree tree1(10);
    tree1.update(2, 5);
    tree1.update(8, 10);

    SegmentTree tree2(10);
    tree2.update(3, 7);
    tree2 = tree1;

    assert(tree2.sumRange(2, 2) == 5);
    assert(tree2.sumRange(8, 8) == 10);
    assert(tree2.sumRange(3, 3) == 0);

    tree2.update(2, 3);
    assert(tree1.sumRange(2, 2) == 5);
    assert(tree2.sumRange(2, 2) == 3);
}

void runDynamicMoveConstructorTest() {
    std::cout << "//// Move Constructor Test ////" << std::endl;
    SegmentTree tree1(10);
    tree1.update(2, 5);
    tree1.update(8, 10);

    SegmentTree tree2(std::move(tree1));

    assert(tree2.sumRange(2, 2) == 5);
    assert(tree2.sumRange(8, 8) == 10);

    assert(tree1.sumRange(2, 2) == 0);
}

void runDynamicMoveAssignmentOperatorTest() {
    std::cout << "//// Move Assignment Operator Test ////" << std::endl;
    SegmentTree tree1(10);
    tree1.update(2, 5);
    tree1.update(8, 10);

    SegmentTree tree2(10);
    tree2.update(3, 7);

    tree2 = std::move(tree1);

    assert(tree2.sumRange(2, 2) == 5);
    assert(tree2.sumRange(8, 8) == 10);
    assert(tree2.sumRange(3, 3) == 0);

    assert(tree1.sumRange(2, 2) == 0);
}

int main() {
    runDynamicSumRangeAndUpdateTest();
    runDynamicCopyConstructorTest();
    runDynamicAssignmentOperatorTest();
    runDynamicMoveConstructorTest();
    runDynamicMoveAssignmentOperatorTest();

    std::cout << "Tests passed" << std::endl;
    return 0;
}

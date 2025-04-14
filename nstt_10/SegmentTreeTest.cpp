#include <cmath>
#include <cassert>
#include <iostream>
#include "SegmentTree.hpp"

template <typename T>
void runDynamicSumRangeAndUpdateTest() {
    SegmentTree<T> tree(10);
    assert(tree.sumRange(0, 9) == T(0));

    tree.update(2, T(5));
    assert(tree.sumRange(0, 9) == T(5));

    tree.update(8, T(10));
    assert(tree.sumRange(0, 9) == T(15));
}

template <typename T>
void runDynamicCopyConstructorTest() {
    SegmentTree<T> tree1(10);
    tree1.update(2, T(5));
    tree1.update(8, T(10));

    SegmentTree<T> tree2(tree1);
    assert(tree2.sumRange(2, 2) == T(5));
    assert(tree2.sumRange(8, 8) == T(10));

    tree2.update(8, T(2));
    assert(tree1.sumRange(8, 8) == T(10));
    assert(tree2.sumRange(8, 8) == T(2));
}

template <typename T>
void runDynamicAssignmentOperatorTest() {
    SegmentTree<T> tree1(10);
    tree1.update(2, T(5));
    tree1.update(8, T(10));

    SegmentTree<T> tree2(10);
    tree2.update(3, T(7));
    tree2 = tree1;

    assert(tree2.sumRange(2, 2) == T(5));
    assert(tree2.sumRange(8, 8) == T(10));
    assert(tree2.sumRange(3, 3) == T(0));

    tree2.update(2, T(3));
    assert(tree1.sumRange(2, 2) == T(5));
    assert(tree2.sumRange(2, 2) == T(3));
}

template <typename T>
void runDynamicMoveConstructorTest() {
    std::cout << "//// Move Constructor Test ////" << std::endl;
    SegmentTree<T> tree1(10);
    tree1.update(2, T(5));
    tree1.update(8, T(10));

    SegmentTree<T> tree2(std::move(tree1));

    assert(tree2.sumRange(2, 2) == T(5));
    assert(tree2.sumRange(8, 8) == T(10));

    assert(tree1.sumRange(2, 2) == T(0));
}

template <typename T>
void runDynamicMoveAssignmentOperatorTest() {
    std::cout << "//// Move Assignment Operator Test ////" << std::endl;
    SegmentTree<T> tree1(10);
    tree1.update(2, T(5));
    tree1.update(8, T(10));

    SegmentTree<T> tree2(10);
    tree2.update(3, T(7));

    tree2 = std::move(tree1);

    assert(tree2.sumRange(2, 2) == T(5));
    assert(tree2.sumRange(8, 8) == T(10));
    assert(tree2.sumRange(3, 3) == T(0));

    assert(tree1.sumRange(2, 2) == T(0));
}

int main() {
    std::cout << "TESTS FOR INT" << std::endl;
    runDynamicSumRangeAndUpdateTest<int>();
    runDynamicCopyConstructorTest<int>();
    runDynamicAssignmentOperatorTest<int>();
    runDynamicMoveConstructorTest<int>();
    runDynamicMoveAssignmentOperatorTest<int>();

    std::cout << "\nTESTS FOR DOUBLE" << std::endl;
    runDynamicSumRangeAndUpdateTest<double>();
    runDynamicCopyConstructorTest<double>();
    runDynamicAssignmentOperatorTest<double>();
    runDynamicMoveConstructorTest<double>();
    runDynamicMoveAssignmentOperatorTest<double>();

    std::cout << "Tests passed" << std::endl;
    return 0;
}


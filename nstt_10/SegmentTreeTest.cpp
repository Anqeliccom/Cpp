#include <cmath>
#include <cassert>
#include <iostream>
#include "SegmentTree.hpp"

struct Mod5 {
    int m;

    Mod5() : m(0) {}
    Mod5(int val) : m(val % 5) {}

    Mod5 operator+(const Mod5& other) const {
        return Mod5(m + other.m);
    }

    bool operator==(const Mod5& other) const {
        return m == other.m;
    }
};

template<>
struct Defaulter<Mod5> {
    Mod5 operator()() const {
        return Mod5(0);
    }
};

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

void runMod5Test() {
    std::cout << "\n//// Mod5 Test ////" << std::endl;
    SegmentTree<Mod5> tree(10);

    tree.update(2, Mod5(7));
    assert(tree.sumRange(0, 9) == Mod5(2));

    tree.update(5, Mod5(8));
    assert(tree.sumRange(0, 9) == Mod5(0));
    assert(tree.sumRange(0, 4) == Mod5(2));
    assert(tree.sumRange(5, 9) == Mod5(3));
}

void runProductTest() {
    std::cout << "\n//// Product Test ////" << std::endl;
    SegmentTree<Product<int>> tree(10);

    assert(tree.sumRange(0, 9).val == 1);

    tree.update(2, Product<int>(5));
    assert(tree.sumRange(0, 9).val == 5);

    tree.update(5, Product<int>(3));
    assert(tree.sumRange(0, 9).val == 15);
    assert(tree.sumRange(0, 4).val == 5);
    assert(tree.sumRange(5, 9).val == 3);
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

    runProductTest();
    runMod5Test();
    std::cout << "Tests passed" << std::endl;
    return 0;
}

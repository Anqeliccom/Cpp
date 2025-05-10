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

void runInitializerListTest() {
    std::cout << "\n//// Initializer List Test ////" << std::endl;

    SegmentTree<int> tree1(5, {1, 2, 3, 4, 5});
    assert(tree1.sumRange(1, 3) == 9);

    SegmentTree<int> tree2(10, {1, 2, 3});
    assert(tree2.sumRange(0, 9) == 6);
}

int main() {
    runProductTest();
    runMod5Test();
    runInitializerListTest();
    std::cout << "Tests passed" << std::endl;
    return 0;
}

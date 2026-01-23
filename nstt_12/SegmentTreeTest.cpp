#include <cmath>
#include <iostream>
#include "SegmentTree.hpp"


int main() {
    SegmentTree<int> tree(3);
    tree.update(0, 1);
    tree.update(1, 2);
    tree.update(2, 3);

    for (int val : tree) {
        std::cout << val << std::endl;
    }
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << std::endl;
    }
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        const int* ptr = it.operator->();
        std::cout << *ptr << std::endl;
    }
    return 0;
}

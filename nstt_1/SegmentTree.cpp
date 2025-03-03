#include <iostream>

#include "SegmentTree.hpp"

SegmentTree::Node::Node() : value(0), left(nullptr), right(nullptr) {}

SegmentTree::Node::Node(const Node& other) : value(other.value) {
    left = other.left ? new Node(*other.left) : nullptr;
    right = other.right ? new Node(*other.right) : nullptr;
}

SegmentTree::Node& SegmentTree::Node::operator=(const Node& other) {
    if (this != &other) {
        value = other.value;
        delete left;
        delete right;
        left = other.left ? new Node(*other.left) : nullptr;
        right = other.right ? new Node(*other.right) : nullptr;
    }
    return *this;
}

SegmentTree::Node::~Node() {
    delete left;
    delete right;
}

void SegmentTree::updateRecursive(Node*& node, size_t tl, size_t tr, size_t index, int val) {
    if (!node) node = new Node();

    if (tl == tr) {
        node->value = val;
        return;
    } else {
        size_t tm = (tl + tr) >> 1;
        if (index <= tm) {
            updateRecursive(node->left, tl, tm, index, val);
        } else {
            updateRecursive(node->right, tm + 1, tr, index, val);
        }
        node->value = (node->left ? node->left->value : 0) + (node->right ? node->right->value : 0);
    }
}

int SegmentTree::sumRecursive(Node* node, size_t tl, size_t tr, size_t left, size_t right) {
    if (!node) return 0;

    if (left == tl && right == tr) return node->value;
    size_t tm = (tl + tr) >> 1;
    int res = 0;
    if (left <= tm) {
        res += sumRecursive(node->left, tl, tm, left, std::min(right, tm));
    }
    if (right >= tm + 1) {
        res += sumRecursive(node->right, tm + 1, tr, std::max(left, tm + 1), right);
    }
    return res;
}

SegmentTree::SegmentTree(unsigned int C) : root(nullptr), n(C) {
    std::cout << "SegmentTree created" << std::endl;
}

SegmentTree::SegmentTree(const SegmentTree& other) : n(other.n), root(nullptr) {
    if (other.root) {
        root = new Node(*other.root);
    }
    std::cout << "SegmentTree copied" << std::endl;
}

SegmentTree& SegmentTree::operator=(const SegmentTree& other) {
    if (this != &other) {
        n = other.n;
        delete root;
        root = other.root ? new Node(*other.root) : nullptr;
    }
    std::cout << "SegmentTree copy-assigned" << std::endl;
    return *this;
}

SegmentTree::SegmentTree(SegmentTree&& other) noexcept : n(other.n), root(other.root) {
    other.root = nullptr;
    std::cout << "SegmentTree moved" << std::endl;
}

SegmentTree& SegmentTree::operator=(SegmentTree&& other) noexcept {
    if (this != &other) {
        n = other.n;
        delete root;
        root = other.root;
        other.root = nullptr;
    }
    std::cout << "SegmentTree move-assigned" << std::endl;
    return *this;
}

void SegmentTree::update(size_t index, int val) {
    updateRecursive(root, 0, n - 1, index, val);
}

int SegmentTree::sumRange(size_t left, size_t right) {
    if (!root || left > right || right >= n) return 0;
    return sumRecursive(root, 0, n - 1, left, right);
}

SegmentTree::~SegmentTree() {
    delete root;
    std::cout << "SegmentTree deleted" << std::endl;
}

#include <iostream>
#include <vector>

#include "SegmentTree.hpp"

/* PR: about dynamic SegmentTree
 * --
 * The general idea of segment tree - that we have a segment (ordered set without 'gaps')
 * with some binary op with neutral element
 * And then magic happens)
 *
 * Your implementation of SegmentTree is nice! And magic really happens in it)
 * For ordinary SegmentTree it is enough to store just vector of values 
 * (but Ivan suggest you to implement 'dynamic' SegmentTree).
 * And you have all things (actually Nodes) to implement dynamic SegmentTree - so let's do that!
 *
 * --
 * Idea of dynamic SegmentTree
 * 
 * Usually we have some small segment in tree. 
 * By 'small' I mean that there is enough memory to allocate all nodes of your tree at once.
 * Or maybe we don't care about memory usage ¯\_(ツ)_/¯
 *
 * But let's pretend that we care about memory, 
 * and we need to analyse large segment (from 0 to C, where C is really large)
 * 
 * Looks like hard problem, so lets make one usefull assumption -
 * - by default all values in segment is initialized by neutral element (in our case it is zero)
 * 
 * In this case we can update tree lazely (i.e. only when update called)
 * Initially we create only root of the tree. Other nodes will be created only we need them 
 * (i.e. when we go to the node in update and if it is empty then create new node)
 *
 * When we go to unexisted node in sum it means that its controlled segment is
 * initialized by zeroes
 *
 * These changes are small, but powerfull!
 * (and don't forget about tests on new functionallity)
 */
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

// PR: implement building implicit SegmentTree
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

// PR: let's add lazyness to update function
void SegmentTree::update(size_t index, int val) {
    updateRecursive(root, 0, n - 1, index, val);
}

// PR: let's add lazyness to sumRange and sumRecursive
int SegmentTree::sumRange(size_t left, size_t right) {
    if (!root || left > right || right >= n) return 0;
    return sumRecursive(root, 0, n - 1, left, right);
}

SegmentTree::~SegmentTree() {
    delete root;
    std::cout << "SegmentTree deleted" << std::endl;
}

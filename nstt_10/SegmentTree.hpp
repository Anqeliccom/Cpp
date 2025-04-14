#ifndef SEGMENTTREE_HPP
#define SEGMENTTREE_HPP

#include <iostream>

template <typename T, T default_value = T()>
class SegmentTree {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node() : value(default_value), left(nullptr), right(nullptr) {}
        Node(const Node& other) : value(other.value) {
            left = other.left ? new Node(*other.left) : nullptr;
            right = other.right ? new Node(*other.right) : nullptr;
        }
        Node& operator=(const Node& other) {
            if (this != &other) {
                value = other.value;
                delete left;
                delete right;
                left = other.left ? new Node(*other.left) : nullptr;
                right = other.right ? new Node(*other.right) : nullptr;
            }
            return *this;
        }
        ~Node() {
            delete left;
            delete right;
        }
    };

    Node* root;
    size_t n;

    void updateRecursive(Node*& node, size_t tl, size_t tr, size_t index, T val) {
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
            node->value = (node->left ? node->left->value : default_value) +
                          (node->right ? node->right->value : default_value);
        }
    }

    T sumRecursive(Node* node, size_t tl, size_t tr, size_t left, size_t right) {
        if (!node) return default_value;

        if (left == tl && right == tr) return node->value;
        size_t tm = (tl + tr) >> 1;
        T res = default_value;
        if (left <= tm) {
            res += sumRecursive(node->left, tl, tm, left, std::min(right, tm));
        }
        if (right >= tm + 1) {
            res += sumRecursive(node->right, tm + 1, tr, std::max(left, tm + 1), right);
        }
        return res;
    }

public:
    explicit SegmentTree(unsigned int C) : root(nullptr), n(C) {
        std::cout << "SegmentTree created" << std::endl;
    }

    SegmentTree(const SegmentTree& other) : n(other.n), root(nullptr) {
        if (other.root) {
            root = new Node(*other.root);
        }
        std::cout << "SegmentTree copied" << std::endl;
    }

    SegmentTree& operator=(const SegmentTree& other) {
        if (this != &other) {
            n = other.n;
            delete root;
            root = other.root ? new Node(*other.root) : nullptr;
        }
        std::cout << "SegmentTree copy-assigned" << std::endl;
        return *this;
    }

    SegmentTree(SegmentTree&& other) noexcept : n(other.n), root(other.root) {
        other.root = nullptr;
        std::cout << "SegmentTree moved" << std::endl;
    }

    SegmentTree& operator=(SegmentTree&& other) noexcept {
        if (this != &other) {
            n = other.n;
            delete root;
            root = other.root;
            other.root = nullptr;
        }
        std::cout << "SegmentTree move-assigned" << std::endl;
        return *this;
    }

    void update(size_t index, T val) {
        updateRecursive(root, 0, n - 1, index, val);
    }

    T sumRange(size_t left, size_t right) {
        if (!root || left > right || right >= n) return default_value;
        return sumRecursive(root, 0, n - 1, left, right);
    }

    ~SegmentTree() {
        delete root;
        std::cout << "SegmentTree deleted" << std::endl;
    }
};

#endif // SEGMENTTREE_HPP

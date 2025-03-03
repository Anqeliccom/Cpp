#ifndef SEGMENTTREE_HPP
#define SEGMENTTREE_HPP

#include <iostream>

class SegmentTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        Node();
        Node(const Node& other);
        Node& operator=(const Node& other);
        ~Node();
    };

    Node* root;
    size_t n;

    void updateRecursive(Node*& node, size_t tl, size_t tr, size_t index, int val);
    int sumRecursive(Node* node, size_t tl, size_t tr, size_t left, size_t right);

public:
    explicit SegmentTree(unsigned int C);
    SegmentTree(const SegmentTree& other);
    SegmentTree& operator=(const SegmentTree& other);
    SegmentTree(SegmentTree&& other) noexcept;
    SegmentTree& operator=(SegmentTree&& other) noexcept;
    ~SegmentTree();

    void update(size_t index, int val);
    int sumRange(size_t left, size_t right);
};

#endif // SEGMENTTREE_HPP

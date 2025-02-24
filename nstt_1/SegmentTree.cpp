#include <iostream>
#include <vector>

class SegmentTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        Node() {
            value = 0;
            left = nullptr;
            right = nullptr;
        }

        ~Node() {
            delete left;
            delete right;
        }
    };

    size_t n;
    Node* root;

    void build(Node*& node, size_t tl, size_t tr, const std::vector<int>& nums) {
        node = new Node();
        if (tl == tr) {
            node->value = nums[tl];
            return;
        } else {
            size_t tm = (tl + tr) >> 1;
            build(node->left, tl, tm, nums);
            build(node->right, tm + 1, tr, nums);
            node->value = node->left->value + node->right->value;
        }
    }

    void updateRecursive(Node* node, size_t tl, size_t tr, size_t index, int val) {
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
            node->value = node->left->value + node->right->value;
        }
    }

    int sumRecursive(Node* node, size_t tl, size_t tr, size_t left, size_t right) {
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

public:
    explicit SegmentTree(const std::vector<int>& nums) {
        n = nums.size();
        root = nullptr;
        if (n != 0) {
            build(root, 0, n - 1, nums);
        }
    }

    void update(size_t index, int val) {
        if (!root) {
            std::cerr << "Error: update element in empty tree!" << std::endl;
            return;
        }
        if (index >= n){
            std::cerr << "Error: going beyond the boundaries of tree!" << std::endl;
        }
        updateRecursive(root, 0, n - 1, index, val);
    }

    int sumRange(size_t left, size_t right) {
        if (!root || left > right || right >= n) return 0;
        return sumRecursive(root, 0, n - 1, left, right);
    }

    ~SegmentTree() {
        delete root;
    }
};

#include <cassert>
#include <iostream>
#include <vector>

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
class SegmentTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        Node() : value(0), left(nullptr), right(nullptr) {}

        Node(const Node& other) : value(other.value) {
            left = other.left ? new Node(*other.left) : nullptr;
            right = other.right ? new Node(*other.right) : nullptr;
        }
        
        /* Note: I guess it is okay not to have copy assigment operator
         * in the private part of your code
         * But I highly reccomend you to use the 'rule of three' everywhere 
         */

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

    SegmentTree(const SegmentTree& other) : n(other.n), root(nullptr) {
        if (other.root) {
            root = new Node(*other.root);
        }
    }
    
    // PR: implement building implicit SegmentTree
    SegmentTree(unsigned int C) {
        assert(false);
    }

    SegmentTree& operator=(const SegmentTree& other) {
        if (this != &other) {
            n = other.n;
            delete root;
            root = other.root ? new Node(*other.root) : nullptr;
        }
        return *this;
    }

    // PR: let's add lazyness to update function
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

    // PR: let's add lazyness to sumRange and sumRecursive
    int sumRange(size_t left, size_t right) {
        if (!root || left > right || right >= n) return 0;
        return sumRecursive(root, 0, n - 1, left, right);
    }

    ~SegmentTree() {
        delete root;
    }
};

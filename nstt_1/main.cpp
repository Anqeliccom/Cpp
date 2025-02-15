#include <iostream>
#include <vector>
#include <cassert>

class SegmentTree {
private:
    size_t n;
    int* tree;

    void build(size_t v, size_t tl, size_t tr, const int* nums) {
        if (tl == tr) {
            tree[v] = nums[tl];
        } else {
            size_t tm = (tl + tr) >> 1;
            build(v * 2, tl, tm, nums);
            build(v * 2 + 1, tm + 1, tr, nums);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    void updateRecursive(size_t v, size_t tl, size_t tr, size_t index, int val) {
        if (tl == tr) {
            tree[v] = val;
        } else {
            size_t tm = (tl + tr) >> 1;
            if (index <= tm) {
                updateRecursive(v * 2, tl, tm, index, val);
            } else {
                updateRecursive(v * 2 + 1, tm + 1, tr, index, val);
            }
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    int sumRecursive(size_t v, size_t tl, size_t tr, size_t left, size_t right) {
        if (left > right) return 0;
        if (left == tl && right == tr) return tree[v];
        size_t tm = (tl + tr) >> 1;
        int res = 0;
        if (left <= tm) {
            res += sumRecursive(v * 2, tl, tm, left, std::min(right, tm));
        }
        if (right >= tm + 1) {
            res += sumRecursive(v * 2 + 1, tm + 1, tr, std::max(left, tm + 1), right);
        }
        return res;
    }

public:
    explicit SegmentTree(const std::vector<int>& nums) {
        n = nums.size();
        if (n == 0) {
            tree = nullptr; // if delete is called on a null pointer, it has no effect
            return;
        }
        tree = new int[4 * n]{}; // without {} - trash in tree
        build(1, 0, n - 1, &nums[0]);
    }

    void update(size_t index, int val) {
        if (n == 0) {
            std::cerr << "Error: update element in empty array!" << std::endl;
            return;
        }
        updateRecursive(1, 0, n - 1, index, val);
    }

    int sumRange(size_t left, size_t right) {
        if (n == 0 || left > right) return 0;
        return sumRecursive(1, 0, n - 1, left, right);
    }

    ~SegmentTree() {
        delete[] tree;
    }
};

void runTests() {
    SegmentTree arr({1, 3, 5, 7, 9});
    assert(arr.sumRange(2, 4) == 21);
    arr.update(3, 5);
    assert(arr.sumRange(2, 4) == 19);

    SegmentTree negArr({-8, -7, -5, -6, -9, -10});
    assert(negArr.sumRange(0, 2) == -20);
    negArr.update(0, -1);
    assert(negArr.sumRange(0, 2) == -13);

    SegmentTree emptyArr({});
    assert(emptyArr.sumRange(0, 0) == 0);
    emptyArr.update(0, 5);

    std::cout << "Tests passed" << std::endl;
}

int main() {
    runTests();
    return 0;
}
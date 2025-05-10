#ifndef SEGMENTTREE_HPP
#define SEGMENTTREE_HPP

#include <iostream>
#include <memory>
#include <vector>

template<typename T>
struct Defaulter {
    T operator()() const {
        return T();
    }
};

template<typename T>
struct Operation {
    T operator()(const T& l, const T& r) const {
        return l + r;
    }
};

template<typename T>
struct Product {
    T val;
    Product() : val(1) {}
    Product(T v) : val(v) {}
};

template<typename T>
struct Defaulter<Product<T>> {
    Product<T> operator()() const {
        return Product<T>(1);
    }
};

template<typename T>
struct Operation<Product<T>> {
    Product<T> operator()(const Product<T>& l, const Product<T>& r) const {
        return Product<T>(l.val * r.val);
    }
};

template <typename T, typename F = Operation<T>, typename D = Defaulter<T>>
class SegmentTree {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(const D& defaulter) : value(defaulter()), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;
    size_t n;
    F op;
    D default_value;

    std::unique_ptr<Node> updateRecursive(std::unique_ptr<Node> node, size_t tl, size_t tr, size_t index, T val) {
        if (!node) node = std::make_unique<Node>(default_value);

        if (tl == tr) {
            node->value = val;
            return node;
        } else {
            size_t tm = (tl + tr) >> 1;
            if (index <= tm) {
                node->left = updateRecursive(std::move(node->left), tl, tm, index, val);
            } else {
                node->right = updateRecursive(std::move(node->right), tm + 1, tr, index, val);
            }
            node->value = op(node->left ? node->left->value : default_value(),
                             node->right ? node->right->value : default_value());
            return node;
        }
    }

    T sumRecursive(std::unique_ptr<Node>& node, size_t tl, size_t tr, size_t left, size_t right) {
        if (!node) return default_value();

        if (left == tl && right == tr) return node->value;
        size_t tm = (tl + tr) >> 1;
        T res = default_value();
        if (left <= tm) {
            res = op(res, sumRecursive(node->left, tl, tm, left, std::min(right, tm)));
        }
        if (right >= tm + 1) {
            res = op(res, sumRecursive(node->right, tm + 1, tr, std::max(left, tm + 1), right));
        }
        return res;
    }

    std::unique_ptr<Node> buildFromList(size_t tl, size_t tr, const std::vector<T>& vector) {
        auto node = std::make_unique<Node>(default_value);

        if (tl == tr) {
            if (tl < vector.size()) {
                node->value = vector[tl];
            }
            return node;
        }

        size_t tm = (tl + tr) >> 1;
        node->left = buildFromList(tl, tm, vector);
        node->right = buildFromList(tm + 1, tr, vector);

        node->value = op(
                node->left ? node->left->value : default_value(),
                node->right ? node->right->value : default_value()
        );
        return node;
    }

public:
    explicit SegmentTree(unsigned int C) : root(nullptr), n(C), op(F()), default_value(D()) {
        std::cout << "SegmentTree created" << std::endl;
    }

    SegmentTree(size_t C, std::initializer_list<T> il) : n(C), op(F()), default_value(D()) {
        std::vector<T> vector(il);
        root = buildFromList(0, n-1, vector);
        std::cout << "SegmentTree created from initializer_list" << std::endl;
    }

    void update(size_t index, T val) {
        root = updateRecursive(std::move(root), 0, n - 1, index, val);
    }

    T sumRange(size_t left, size_t right) {
        if (!root || left > right || right >= n) return default_value();
        return sumRecursive(root, 0, n - 1, left, right);
    }

    ~SegmentTree() {
        std::cout << "SegmentTree deleted" << std::endl;
    }
};

#endif // SEGMENTTREE_HPP

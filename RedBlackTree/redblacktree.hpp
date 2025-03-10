#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <memory>
#include <vector>
#include <stdexcept>

enum class Color {
    RED,
    BLACK
};

template <typename T1, typename T2>
class RedBlackTree {
public:
    struct Node {
        T1 value1;
        T2 value2;
        std::shared_ptr<Node> left, right;
        std::weak_ptr<Node> parent;
        Color color;

        explicit Node(T1 val1, T2 val2)
            : value1(std::move(val1)), value2(std::move(val2)), left(nullptr), right(nullptr), parent(), color(Color::RED) {}
    };

    RedBlackTree();
    void insert(T1 value1, T2 value2);
    std::pair<T1, T2> getTop() const;
    /*************************测试***********************/
    void inOrderTraversal(std::shared_ptr<Node> node, std::vector<std::pair<T1, T2>>& result) const {
        if (!node) return;
        inOrderTraversal(node->left, result);
        result.emplace_back(node->value1, node->value2);
        inOrderTraversal(node->right, result);
    }

    std::vector<std::pair<T1, T2>> inOrderTraversal() const {
        std::vector<std::pair<T1, T2>> result;
        inOrderTraversal(root, result);
        return result;
    }
    /**************************************************/

private:
    std::shared_ptr<Node> root;

    void rotateLeft(std::shared_ptr<Node> x) noexcept;
    void rotateRight(std::shared_ptr<Node> x) noexcept;
    void fixRedBlackTree(std::shared_ptr<Node> node) noexcept;
    void insertNode(T1 value1, T2 value2);
};

template <typename T1, typename T2>
RedBlackTree<T1, T2>::RedBlackTree() : root(nullptr) {}

template <typename T1, typename T2>
std::pair<T1, T2> RedBlackTree<T1, T2>::getTop() const {
    if (!root) {
        throw std::runtime_error("Empty Tree");
    }
    return {root->value1, root->value2};
}

template <typename T1, typename T2>
void RedBlackTree<T1, T2>::rotateLeft(std::shared_ptr<Node> x) noexcept {
    auto y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;
    if (!x->parent.lock()) root = y;
    else if (x == x->parent.lock()->left) x->parent.lock()->left = y;
    else x->parent.lock()->right = y;

    y->left = x;
    x->parent = y;
}

template <typename T1, typename T2>
void RedBlackTree<T1, T2>::rotateRight(std::shared_ptr<Node> x) noexcept {
    auto y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;

    y->parent = x->parent;
    if (!x->parent.lock()) root = y;
    else if (x == x->parent.lock()->right) x->parent.lock()->right = y;
    else x->parent.lock()->left = y;

    y->right = x;
    x->parent = y;
}

template <typename T1, typename T2>
void RedBlackTree<T1, T2>::fixRedBlackTree(std::shared_ptr<Node> node) noexcept {
    while (node != root && node->parent.lock() && node->parent.lock()->color == Color::RED) {
        auto parent = node->parent.lock();
        if (!parent) break;
        auto grandparent = parent->parent.lock();
        if (!grandparent) break;

        if (parent == grandparent->left) {
            auto uncle = grandparent->right;
            if (uncle && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    rotateLeft(node);
                }
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateRight(grandparent);
            }
        } else {
            auto uncle = grandparent->left;
            if (uncle && uncle->color == Color::RED) {
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                grandparent->color = Color::RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rotateRight(node);
                }
                parent->color = Color::BLACK;
                grandparent->color = Color::RED;
                rotateLeft(grandparent);
            }
        }
    }
    root->color = Color::BLACK;
}

template <typename T1, typename T2>
void RedBlackTree<T1, T2>::insertNode(T1 value1, T2 value2) {
    auto node = std::make_shared<Node>(value1, value2);

    if (!root) {
        root = node;
        root->color = Color::BLACK;
        return;
    }

    std::shared_ptr<Node> parent = nullptr;
    std::shared_ptr<Node> current = root;

    while (current) {
        parent = current;
        if (value1 < current->value1) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;
    if (value1 < parent->value1) {
        parent->left = node;
    } else if (value1 > parent->value1) {
        parent->right = node;
    } else {
        return; // 忽略重复值
    }
    fixRedBlackTree(node);
}

template <typename T1, typename T2>
void RedBlackTree<T1, T2>::insert(T1 value1, T2 value2) {
    insertNode(value1, value2);
}

#endif
"yehonatan@gmail.com"
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stack>
#include <queue>
#include <vector>
#include "node.hpp"

// Pre-order iterator
template <typename T>
class PreOrderIterator {
public:
    explicit PreOrderIterator(Node<T> *root, size_t k) : k(k) {
        if (root)
            nodes.push(root);
    }

    bool operator!=(const PreOrderIterator &other) const {
        return !(*this == other);
    }

    bool operator==(const PreOrderIterator &other) const {
        return nodes == other.nodes;
    }

    Node<T> *operator*() {
        return nodes.top();
    }

    PreOrderIterator &operator++() {
        Node<T> *node = nodes.top();
        nodes.pop();
        for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) {
            if (*it)
                nodes.push(*it);
        }
        return *this;
    }

private:
    std::stack<Node<T> *> nodes;
    size_t k;
};

// Post-order iterator
template <typename T>
class PostOrderIterator {
public:
    explicit PostOrderIterator(Node<T> *root, size_t k) : k(k) {
        traverse(root);
    }

    bool operator!=(const PostOrderIterator &other) const {
        return !(*this == other);
    }

    bool operator==(const PostOrderIterator &other) const {
        return nodes == other.nodes;
    }

    Node<T> *operator*() {
        return nodes.top();
    }

    PostOrderIterator &operator++() {
        nodes.pop();
        return *this;
    }

private:
    void traverse(Node<T> *node) {
        if (!node)
            return;
        for (auto child : node->get_children()) {
            traverse(child);
        }
        nodes.push(node);
    }

    std::stack<Node<T> *> nodes;
    size_t k;
};

// In-order iterator
template <typename T>
class InOrderIterator {
public:
    explicit InOrderIterator(Node<T> *root, size_t k) : k(k) {
        if (root) {
            nodes.push(root);
            while (!nodes.empty() && !nodes.top()->get_children().empty()) {
                Node<T> *current = nodes.top();
                nodes.push(current->get_children().front());
            }
        }
    }

    bool operator!=(const InOrderIterator &other) const {
        return !(*this == other);
    }

    bool operator==(const InOrderIterator &other) const {
        return nodes == other.nodes;
    }

    Node<T> *operator*() {
        return nodes.top();
    }

    InOrderIterator &operator++() {
        Node<T> *node = nodes.top();
        nodes.pop();

        if (!nodes.empty()) {
            Node<T> *parent = nodes.top();
            auto &siblings = parent->get_children();
            auto it = std::find(siblings.begin(), siblings.end(), node);
            if (it != siblings.end() && ++it != siblings.end()) {
                Node<T> *sibling = *it;
                nodes.push(sibling);
                while (!nodes.top()->get_children().empty()) {
                    nodes.push(nodes.top()->get_children().front());
                }
            }
        }
        return *this;
    }

private:
    std::stack<Node<T> *> nodes;
    size_t k;
};

// BFS iterator
template <typename T>
class BFSIterator {
public:
    explicit BFSIterator(Node<T> *root) {
        if (root)
            nodes.push(root);
    }

    bool operator!=(const BFSIterator &other) const {
        return !(*this == other);
    }

    bool operator==(const BFSIterator &other) const {
        return nodes == other.nodes;
    }

    Node<T> *operator*() {
        return nodes.front();
    }

    BFSIterator &operator++() {
        Node<T> *node = nodes.front();
        nodes.pop();
        for (auto child : node->get_children()) {
            if (child)
                nodes.push(child);
        }
        return *this;
    }

private:
    std::queue<Node<T> *> nodes;
};

// DFS iterator
template <typename T>
class DFSIterator {
public:
    explicit DFSIterator(Node<T> *root) {
        if (root)
            nodes.push(root);
    }

    bool operator!=(const DFSIterator &other) const {
        return !(*this == other);
    }

    bool operator==(const DFSIterator &other) const {
        return nodes == other.nodes;
    }

    Node<T> *operator*() {
        return nodes.top();
    }

    DFSIterator &operator++() {
        Node<T> *node = nodes.top();
        nodes.pop();
        for (auto it = node->get_children().rbegin(); it != node->get_children().rend(); ++it) {
            if (*it)
                nodes.push(*it);
        }
        return *this;
    }

private:
    std::stack<Node<T> *> nodes;
};

// Heap iterator
template <typename T>
class HeapIterator {
public:
    explicit HeapIterator(Node<T> *root) {
        if (root)
            flatten_to_vector(root, nodes);
    }

    bool operator!=(const HeapIterator &other) const {
        return !(*this == other);
    }

    bool operator==(const HeapIterator &other) const {
        return index == other.index && nodes == other.nodes;
    }

    Node<T> *operator*() {
        return nodes[index];
    }

    HeapIterator &operator++() {
        ++index;
        return *this;
    }

private:
    void flatten_to_vector(Node<T> *node, std::vector<Node<T> *> &result) {
        if (!node)
            return;
        result.push_back(node);
        for (auto child : node->get_children()) {
            flatten_to_vector(child, result);
        }
    }

    std::vector<Node<T> *> nodes;
    size_t index = 0;
};

#endif // ITERATOR_HPP

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "TreeNode.hpp"
#include <stack>
#include <queue>
#include <string>

template <typename Key>
class PreOrderIterator {
public:
    PreOrderIterator(TreeNode<Key>* root);
    Key& operator*();
    PreOrderIterator& operator++();
    bool operator!=(const PreOrderIterator& other) const;

private:
    std::stack<TreeNode<Key>*> stack;
};

template <typename Key>
class PostOrderIterator {
public:
    PostOrderIterator(TreeNode<Key>* root);
    Key& operator*();
    PostOrderIterator& operator++();
    bool operator!=(const PostOrderIterator& other) const;

private:
    std::stack<TreeNode<Key>*> stack;
    std::stack<bool> visited;
};

template <typename Key>
class InOrderIterator {
public:
    InOrderIterator(TreeNode<Key>* root);
    Key& operator*();
    InOrderIterator& operator++();
    bool operator!=(const InOrderIterator& other) const;

private:
    std::stack<TreeNode<Key>*> stack;
    void pushLeft(TreeNode<Key>* node);
};

template <typename Key>
class BFSIterator {
public:
    BFSIterator(TreeNode<Key>* root);
    Key& operator*();
    BFSIterator& operator++();
    bool operator!=(const BFSIterator& other) const;

private:
    std::queue<TreeNode<Key>*> queue;
};

template <typename Key>
class DFSIterator {
public:
    DFSIterator(TreeNode<Key>* root);
    Key& operator*();
    DFSIterator& operator++();
    bool operator!=(const DFSIterator& other) const;

private:
    std::stack<TreeNode<Key>*> stack;
};

#endif // ITERATOR_HPP

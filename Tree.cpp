#include "Tree.hpp"

// Constructor
template <typename Key>
Tree<Key>::Tree(int maxChildren) : root(nullptr), maxChildren(maxChildren) {}

// Destructor
template <typename Key>
Tree<Key>::~Tree() {
    deleteTree(root);
}

// Returns the root of the tree
template <typename Key>
TreeNode<Key>* Tree<Key>::get_root() {
    return this->root;
}

// Add root to the tree
template <typename Key>
void Tree<Key>::add_root(const Key& key) {
    if (root) {
        root->key = key;
    } else {
        root = new TreeNode<Key>(key);
    }
}

// Add a child to a parent node
template <typename Key>
void Tree<Key>::add_sub_node(const Key& parent_key, const Key& child_key) {
    TreeNode<Key>* parent = findNode(root, parent_key);
    if (parent && parent->children.size() < static_cast<size_t>(maxChildren)) {
        TreeNode<Key>* child = new TreeNode<Key>(child_key);
        parent->addChild(child);
    }
}

// Recursive function to delete all nodes in the tree
template <typename Key>
void Tree<Key>::deleteTree(TreeNode<Key>* node) {
    if (node == nullptr) return;

    for (TreeNode<Key>* child : node->children) {
        deleteTree(child);
    }

    delete node;
}

// Helper function to find a node
template <typename Key>
TreeNode<Key>* Tree<Key>::findNode(TreeNode<Key>* node, const Key& key) {
    if (node == nullptr) return nullptr;
    if (node->key == key) return node;

    for (TreeNode<Key>* child : node->children) {
        TreeNode<Key>* found = findNode(child, key);
        if (found) return found;
    }

    return nullptr;
}

// Iterator methods
template <typename Key>
PreOrderIterator<Key> Tree<Key>::begin_pre_order() {
    return PreOrderIterator<Key>(root);
}

template <typename Key>
PreOrderIterator<Key> Tree<Key>::end_pre_order() {
    return PreOrderIterator<Key>(nullptr);
}

template <typename Key>
PostOrderIterator<Key> Tree<Key>::begin_post_order() {
    return PostOrderIterator<Key>(root);
}

template <typename Key>
PostOrderIterator<Key> Tree<Key>::end_post_order() {
    return PostOrderIterator<Key>(nullptr);
}

template <typename Key>
InOrderIterator<Key> Tree<Key>::begin_in_order() {
    return InOrderIterator<Key>(root);
}

template <typename Key>
InOrderIterator<Key> Tree<Key>::end_in_order() {
    return InOrderIterator<Key>(nullptr);
}

template <typename Key>
BFSIterator<Key> Tree<Key>::begin_bfs_scan() {
    return BFSIterator<Key>(root);
}

template <typename Key>
BFSIterator<Key> Tree<Key>::end_bfs_scan() {
    return BFSIterator<Key>(nullptr);
}

template <typename Key>
DFSIterator<Key> Tree<Key>::begin_dfs_scan() {
    return DFSIterator<Key>(root);
}

template <typename Key>
DFSIterator<Key> Tree<Key>::end_dfs_scan() {
    return DFSIterator<Key>(nullptr);
}

// Explicit instantiation of the template classes used in Tree.cpp
template class Tree<int>;
template class Tree<std::string>;


#ifndef TREE_HPP
#define TREE_HPP

#include "TreeNode.hpp"
#include "Iterator.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>

// Define a generic Tree class
template <typename Key>
class Tree {
private:
    TreeNode<Key>* root;  // Root of the tree
    int maxChildren;      // Maximum number of children for each node

public:
    // Constructor with optional maxChildren parameter (defaults to 2 for binary tree)
    Tree(int maxChildren = 2);
    
    // Destructor to delete the tree
    ~Tree();
    
    TreeNode<Key>* get_root();

    // Add root to the tree
    void add_root(const Key& key);

    // Add a child to a parent node
    void add_sub_node(const Key& parent_key, const Key& child_key);

    // Iterators for different traversal methods
    PreOrderIterator<Key> begin_pre_order();
    PreOrderIterator<Key> end_pre_order();

    PostOrderIterator<Key> begin_post_order();
    PostOrderIterator<Key> end_post_order();

    InOrderIterator<Key> begin_in_order();
    InOrderIterator<Key> end_in_order();

    BFSIterator<Key> begin_bfs_scan();
    BFSIterator<Key> end_bfs_scan();

    DFSIterator<Key> begin_dfs_scan();
    DFSIterator<Key> end_dfs_scan();

    void myHeap();
private:
    // Recursive function to delete all nodes in the tree
    void deleteTree(TreeNode<Key>* node);

    // Helper function to find a node
    TreeNode<Key>* findNode(TreeNode<Key>* node, const Key& key);
};

#endif // TREE_HPP

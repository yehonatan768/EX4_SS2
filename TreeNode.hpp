#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <string> 
#include <vector>

// Forward declaration of Tree class
template <typename Key>
class Tree;

// Define a generic TreeNode class
template <typename Key>
class TreeNode {
public:
    Key key;
    std::vector<TreeNode*> children;

    // Constructor to initialize with a key
    TreeNode(const Key& key) : key(key) {}

    // Function to add a child to the current node
    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    // Allow Tree class to access TreeNode's private members
    friend class Tree<Key>;
};

#endif // TREENODE_HPP

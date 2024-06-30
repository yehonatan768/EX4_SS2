#include "Tree.hpp"
#include "Iterator.hpp"
#include <iostream>
#include <string>
#include <queue>

// Function to print the tree structure
template <typename Key>
void printTree(Tree<Key>& tree) {
    std::cout << "Tree structure:" << std::endl;

    // BFS traversal to print the tree structure
    std::queue<TreeNode<Key>*> q;
    q.push(tree.get_root());

    while (!q.empty()) {
        TreeNode<Key>* current = q.front();
        q.pop();

        std::cout << current->key << " -> ";
        for (TreeNode<Key>* child : current->children) {
            std::cout << child->key << " ";
            q.push(child);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // Create a k-ary tree (default is binary tree)
    Tree<int> intTree(3);  // k=3 for a 3-ary tree

    // Add root
    intTree.add_root(1);

    // Add children to the root
    intTree.add_sub_node(1, 2);
    intTree.add_sub_node(1, 3);
    intTree.add_sub_node(1, 4);

    // Add children to node 2
    intTree.add_sub_node(2, 5);
    intTree.add_sub_node(2, 6);
    intTree.add_sub_node(2, 7);

    // Add children to node 3
    intTree.add_sub_node(3, 8);
    intTree.add_sub_node(3, 9);
    intTree.add_sub_node(3, 10);

    // Print the tree structure
    std::cout << "Integer Tree:" << std::endl;
    printTree(intTree);

    // Check BFS traversal
    std::cout << "BFS traversal:" << std::endl;
    for (auto it = intTree.begin_bfs_scan(); it != intTree.end_bfs_scan(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Check DFS traversal
    std::cout << "DFS traversal:" << std::endl;
    for (auto it = intTree.begin_dfs_scan(); it != intTree.end_dfs_scan(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Check Pre-Order traversal
    std::cout << "Pre-Order traversal:" << std::endl;
    for (auto it = intTree.begin_pre_order(); it != intTree.end_pre_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Check Post-Order traversal
    std::cout << "Post-Order traversal:" << std::endl;
    for (auto it = intTree.begin_post_order(); it != intTree.end_post_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Check In-Order traversal
    std::cout << "In-Order traversal:" << std::endl;
    for (auto it = intTree.begin_in_order(); it != intTree.end_in_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Create a string tree
    Tree<std::string> strTree;

    // Add root
    strTree.add_root("root");

    // Add children to the root
    strTree.add_sub_node("root", "child1");
    strTree.add_sub_node("root", "child2");
    strTree.add_sub_node("root", "child3");

    // Add children to "child1"
    strTree.add_sub_node("child1", "child1.1");
    strTree.add_sub_node("child1", "child1.2");

    // Print the tree structure
    std::cout << "String Tree:" << std::endl;
    printTree(strTree);

    // Check BFS traversal on string tree
    std::cout << "String Tree BFS traversal:" << std::endl;
    for (auto it = strTree.begin_bfs_scan(); it != strTree.end_bfs_scan(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}

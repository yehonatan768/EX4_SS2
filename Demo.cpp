#include <iostream>
#include "node.hpp"
#include "tree.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    Node<string> root_node("root");
    Tree<string> tree(3); // 3-ary tree

    tree.add_root(root_node);

    Node<string> n1("child_1");
    Node<string> n2("child_2");
    Node<string> n3("child_3");
    Node<string> n4("child_4");
    Node<string> n5("child_5");
    Node<string> n6("child_6");

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(root_node, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n3, n6);

    cout << "Pre-order traversal:" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << (*node)->get_value() << endl;
    }

    cout << "Post-order traversal:" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << (*node)->get_value() << endl;
    }

    cout << "In-order traversal:" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << (*node)->get_value() << endl;
    }

    cout << "BFS scan traversal:" << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        cout << (*node)->get_value() << endl;
    }

    cout << "Range-based for loop (BFS):" << endl;
    for (auto node : tree) {
        cout << node->get_value() << endl;
    }

    cout << "DFS scan traversal:" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        cout << (*node)->get_value() << endl;
    }

    // Uncomment or correct this section if the method exists
    // cout << "Heap traversal:" << endl;
    // for (auto node = tree.myHeap(); node != tree.end_heap(); ++node) {
    //     cout << (*node)->get_value() << endl;
    // }

    // Visualize the 3-ary tree
    std::cout << "Visualizing 3-ary Tree..." << std::endl;
    std::cout << tree << std::endl;

    return 0;
}

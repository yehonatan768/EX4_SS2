"yehonatan@gmail.com"
#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <iostream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <map>
#include <sstream>
#include "node.hpp"
#include "complex.hpp"
#include "Iterator.hpp"

/**
 * @brief A generic k-ary tree class.
 * 
 * @tparam T Type of data stored in each node.
 */
template <typename T>
class Tree {
private:
    Node<T> *root;
    size_t k;

    /**
     * @brief Recursively flattens the tree into a vector in pre-order.
     * 
     * @param node The current node to flatten.
     * @param result Vector to store flattened nodes.
     */
    static void flatten_to_vector(Node<T> *node, std::vector<Node<T> *> &result) {
        if (!node)
            return;
        result.push_back(node);
        for (auto child : node->get_children()) {
            flatten_to_vector(child, result);
        }
    }

    /**
     * @brief Deletes the entire tree starting from a given node.
     * 
     * @param node The root node of the tree to delete.
     */
    void delete_tree(Node<T> *node) {
        if (!node)
            return;
        for (auto child : node->get_children()) {
            delete_tree(child);
        }
        delete node;
        node = nullptr;
    }

    /**
     * @brief Finds a node in the tree by its value.
     * 
     * @param current The current node being examined.
     * @param value The value to search for.
     * @return Node<T>* Pointer to the found node, or nullptr if not found.
     */
    Node<T> *find_node(Node<T> *current, const T &value) const {
        if (current->get_value() == value)
            return current;
        for (auto child : current->get_children()) {
            if (child) {
                Node<T> *result = find_node(child, value);
                if (result)
                    return result;
            }
        }
        return nullptr;
    }
public:
    explicit Tree(size_t k = 2) : root(nullptr), k(k) {}

    /**
     * @brief Sets the root node of the tree.
     * 
     * @param node The node to be set as the root.
     */
    void add_root(Node<T> &node) {
        root = &node;
    }

    /**
     * @brief Adds a child node to a parent node in the tree.
     * 
     * @param parent The parent node to which the child will be added.
     * @param child The child node to be added.
     * @throws std::runtime_error if the root node is not set or if the parent node is not found.
     */
    void add_sub_node(Node<T> &parent, Node<T> &child) {
        if (!root) {
            throw std::runtime_error("Error: Root not set.");
        }

        Node<T> *parentNode = find_node(root, parent.get_value());
        if (parentNode) {
            parentNode->add_child(&child, k);
        }
        else {
            throw std::runtime_error("Parent node not found.");
        }
    }

    template <typename U>   
    void add_sub_node(Node<T> &parent, Node<U> &child) {
        throw std::runtime_error("Child node type does not match");
    }

    ~Tree() {
        delete_tree(root);
    }

    // Iterators
    using pre_order_iterator = PreOrderIterator<T>;
    using post_order_iterator = PostOrderIterator<T>;
    using in_order_iterator = InOrderIterator<T>;
    using bfs_iterator = BFSIterator<T>;
    using dfs_iterator = DFSIterator<T>;
    using heap_iterator = HeapIterator<T>;

    pre_order_iterator begin_pre_order() const {
        return pre_order_iterator(root, k);
    }

    pre_order_iterator end_pre_order() const {
        return pre_order_iterator(nullptr, k);
    }

    post_order_iterator begin_post_order() const {
        return post_order_iterator(root, k);
    }

    post_order_iterator end_post_order() const {
        return post_order_iterator(nullptr, k);
    }

    in_order_iterator begin_in_order() const {
        return in_order_iterator(root, k);
    }

    in_order_iterator end_in_order() const {
        return in_order_iterator(nullptr, k);
    }

    bfs_iterator begin_bfs_scan() const {
        return bfs_iterator(root);
    }

    bfs_iterator end_bfs_scan() const {
        return bfs_iterator(nullptr);
    }

    dfs_iterator begin_dfs_scan() const {
        return dfs_iterator(root);
    }

    dfs_iterator end_dfs_scan() const {
        return dfs_iterator(nullptr);
    }

    bfs_iterator begin() const {
        return bfs_iterator(root);
    }

    bfs_iterator end() const {
        return bfs_iterator(nullptr);
    }

    heap_iterator begin_heap() const {
        return heap_iterator(root);
    }

    heap_iterator end_heap() const {
        return heap_iterator(nullptr);
    }

    /**
     * @brief Overloaded stream insertion operator to visualize the tree using SFML graphics.
     * 
     * @param os Output stream.
     * @param tree The tree to visualize.
     * @return std::ostream& Reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Tree &tree) {
        if (!tree.root)
            return os;

        sf::RenderWindow window(sf::VideoMode(1000, 800), "Tree Visualization");
        sf::Font font;
        if (!font.loadFromFile("Sarlotte.otf")) {
            std::cerr << "Error loading font\n";
            return os;
        }

        const float node_radius = 37.5f; // Increased node radius by 50%
        const float vertical_spacing = 80.f;
        const float initial_horizontal_spacing = 200.f;

        std::map<Node<T> *, sf::Vector2f> positions;

        // Recursively position nodes
        std::function<void(Node<T> *, float, float, float)> position_nodes = [&](Node<T> *node, float x, float y, float horizontal_spacing) {
            if (!node)
                return;

            positions[node] = sf::Vector2f(x, y);

            float child_x_offset = x - (node->get_children().size() - 1) * horizontal_spacing / 2.f;

            for (size_t i = 0; i < node->get_children().size(); ++i) {
                Node<T> *child = node->get_children()[i];
                if (child) {
                    position_nodes(child, child_x_offset + i * horizontal_spacing, y + vertical_spacing, horizontal_spacing / 2.f);
                }
            }
        };

        position_nodes(tree.root, window.getSize().x / 2.f, node_radius + 50.f, initial_horizontal_spacing);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            for (const auto &pair : positions) {
                Node<T> *node = pair.first;
                sf::Vector2f position = pair.second;

                sf::CircleShape circle(node_radius);
                circle.setFillColor(sf::Color::Blue);
                circle.setPosition(position - sf::Vector2f(node_radius, node_radius));
                window.draw(circle);

                sf::Text text;
                text.setFont(font);
                if constexpr (std::is_same<T, std::string>::value) {
                    text.setString(node->get_value());
                }
                else if constexpr (std::is_same<T, Complex>::value) {
                    std::ostringstream oss;
                    oss << node->get_value();
                    text.setString(oss.str());
                }
                else {
                    text.setString(std::to_string(node->get_value()));
                }
                text.setCharacterSize(16);
                text.setFillColor(sf::Color::Black); 
                sf::FloatRect text_bounds = text.getLocalBounds();
                text.setOrigin(text_bounds.left + text_bounds.width / 2.0f, text_bounds.top + text_bounds.height / 2.0f);
                text.setPosition(position);
                window.draw(text);

                for (Node<T> *child : node->get_children()) {
                    if (child) {
                        sf::Vector2f child_position = positions[child];

                        // Draw lines from mid-bottom of the circle
                        sf::Vector2f line_start(position.x, position.y + node_radius);
                        sf::Vector2f line_end(child_position.x, child_position.y - node_radius);

                        sf::Vertex line[] =
                            {
                                sf::Vertex(line_start, sf::Color::Black),
                                sf::Vertex(line_end, sf::Color::Black)};
                        window.draw(line, 2, sf::Lines);
                    }
                }
            }

            window.display();
        }
        return os;
    }
};

#endif // TREE_HPP

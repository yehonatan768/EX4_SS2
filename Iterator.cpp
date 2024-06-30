#include "Iterator.hpp"

using namespace std;

// PreOrderIterator
template <typename Key>
PreOrderIterator<Key>::PreOrderIterator(TreeNode<Key>* root) {
    if (root) stack.push(root);
}

template <typename Key>
Key& PreOrderIterator<Key>::operator*() {
    return stack.top()->key;
}

template <typename Key>
PreOrderIterator<Key>& PreOrderIterator<Key>::operator++() {
    TreeNode<Key>* node = stack.top();
    stack.pop();
    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
        stack.push(*it);
    }
    return *this;
}

template <typename Key>
bool PreOrderIterator<Key>::operator!=(const PreOrderIterator<Key>& other) const {
    return !stack.empty();
}

// PostOrderIterator
template <typename Key>
PostOrderIterator<Key>::PostOrderIterator(TreeNode<Key>* root) {
    if (root) {
        stack.push(root);
        visited.push(false);
    }
}

template <typename Key>
Key& PostOrderIterator<Key>::operator*() {
    return stack.top()->key;
}

template <typename Key>
PostOrderIterator<Key>& PostOrderIterator<Key>::operator++() {
    while (!stack.empty()) {
        TreeNode<Key>* node = stack.top();
        bool visit = visited.top();
        visited.pop();
        if (visit) {
            stack.pop();
            return *this;
        } else {
            visited.push(true);
            for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                stack.push(*it);
                visited.push(false);
            }
        }
    }
    return *this;
}

template <typename Key>
bool PostOrderIterator<Key>::operator!=(const PostOrderIterator<Key>& other) const {
    return !stack.empty();
}

// InOrderIterator
template <typename Key>
InOrderIterator<Key>::InOrderIterator(TreeNode<Key>* root) {
    pushLeft(root);
}

template <typename Key>
void InOrderIterator<Key>::pushLeft(TreeNode<Key>* node) {
    while (node) {
        stack.push(node);
        node = node->children.empty() ? nullptr : node->children[0];
    }
}

template <typename Key>
Key& InOrderIterator<Key>::operator*() {
    return stack.top()->key;
}

template <typename Key>
InOrderIterator<Key>& InOrderIterator<Key>::operator++() {
    TreeNode<Key>* node = stack.top();
    stack.pop();
    if (!node->children.empty()) {
        pushLeft(node->children[1]);
    }
    return *this;
}

template <typename Key>
bool InOrderIterator<Key>::operator!=(const InOrderIterator<Key>& other) const {
    return !stack.empty();
}

// BFSIterator
template <typename Key>
BFSIterator<Key>::BFSIterator(TreeNode<Key>* root) {
    if (root) queue.push(root);
}

template <typename Key>
Key& BFSIterator<Key>::operator*() {
    return queue.front()->key;
}

template <typename Key>
BFSIterator<Key>& BFSIterator<Key>::operator++() {
    TreeNode<Key>* node = queue.front();
    queue.pop();
    for (auto child : node->children) {
        queue.push(child);
    }
    return *this;
}

template <typename Key>
bool BFSIterator<Key>::operator!=(const BFSIterator<Key>& other) const {
    return !queue.empty();
}

// DFSIterator
template <typename Key>
DFSIterator<Key>::DFSIterator(TreeNode<Key>* root) {
    if (root) stack.push(root);
}

template <typename Key>
Key& DFSIterator<Key>::operator*() {
    return stack.top()->key;
}

template <typename Key>
DFSIterator<Key>& DFSIterator<Key>::operator++() {
    TreeNode<Key>* node = stack.top();
    stack.pop();
    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
        stack.push(*it);
    }
    return *this;
}

template <typename Key>
bool DFSIterator<Key>::operator!=(const DFSIterator<Key>& other) const {
    return !stack.empty();
}

// Explicit instantiation
template class PreOrderIterator<int>;
template class PostOrderIterator<int>;
template class InOrderIterator<int>;
template class BFSIterator<int>;
template class DFSIterator<int>;

template class PreOrderIterator<std::string>;
template class PostOrderIterator<std::string>;
template class InOrderIterator<std::string>;
template class BFSIterator<std::string>;
template class DFSIterator<std::string>;

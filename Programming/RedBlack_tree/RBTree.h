#pragma once
#include <iostream>
#include <cstddef>
#include <memory>

template <typename T>
class RBTree {
private:
    size_t sz = 0;
    struct Node {
        T key = T();
        char color = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
    };

    void right_turn(Node* vertex) {
        Node* temp = vertex->left;
        temp->parent = vertex->parent;
        if (vertex->parent != nullptr) {
            if (vertex == vertex->parent->left)
                vertex->parent->left = temp;
            else
                vertex->parent->right = temp;
        }
        vertex->left = temp->right;
        if (temp->right != nullptr)
            temp->right->parent = vertex;
        vertex->parent = temp;
        temp->right = vertex;
        if (temp->parent == nullptr)
            head = temp;
        return;
    }

    void left_turn(Node* vertex) {
        Node* temp = vertex->right;
        temp->parent = vertex->parent;
        if (vertex->parent != nullptr) {
            if (vertex == vertex->parent->left)
                vertex->parent->left = temp;
            else
                vertex->parent->right = temp;
        }
        vertex->right = temp->left;
        if (temp->left != nullptr)
            temp->left->parent = vertex;
        vertex->parent = temp;
        temp->left = vertex;
        if (temp->parent == nullptr)
            head = temp;
        return;
    }

    Node* grandparent(Node* vertex) {
        if (vertex != nullptr && vertex->parent != nullptr)
            return vertex->parent->parent;
        return nullptr;
    }

    Node* uncle(Node* vertex) {
        Node* grandpa = grandparent(vertex);
        if (grandpa == nullptr)
            return nullptr;
        if (grandpa->left == vertex->parent)
            return grandpa->right;
        else
            return grandpa->left;
    }

    void correction(Node* vertex) {
        if (vertex->parent == nullptr) {
            vertex->color = 'B';
            return;
        }
        if (vertex->parent->color == 'B')
            return;
        if (vertex->parent->color == 'R') {
            Node* uncle_ = uncle(vertex);
            if (uncle_ != nullptr && uncle_->color == 'R') {
                Node* grandpa = grandparent(vertex);
                vertex->parent->color = 'B';
                uncle_->color = 'B';
                grandpa->color = 'R';
                correction(grandpa);
                return;
            }
            if (uncle_ == nullptr || uncle_->color == 'B') {
                Node* grandpa = grandparent(vertex);
                if (vertex == vertex->parent->right && vertex->parent == grandpa->left) {
                    left_turn(vertex->parent);
                    vertex = vertex->left;
                } else if (vertex == vertex->parent->left
                    && vertex->parent == grandpa->right) {
                    right_turn(vertex->parent);
                    vertex = vertex->right;
                }
                grandpa = grandparent(vertex);
                vertex->parent->color = 'B';
                grandpa->color = 'R';
                if (vertex == vertex->parent->left && vertex->parent == grandpa->left)
                    right_turn(grandpa);
                else
                    left_turn(grandpa);
            }
        }
    }

public:
    Node* head;

    size_t size() {
        return sz;
    }

    RBTree() {
        head = nullptr;
        sz = 0;
    }

    void insert(T x) {
        if (head == nullptr) {
            head = new Node();
            head->key = x;
            head->color = 'B';
            ++sz;
            return;
        }
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (x < current->key) {
                previous = current;
                current = current->left;
            } else {
                if (current->key == x)
                    return;
                previous = current;
                current = current->right;
            }
        }
        ++sz;
        current = new Node();
        current->key = x;
        current->left = nullptr;
        current->right = nullptr;
        current->parent = previous;
        current->color = 'R';
        if (x < previous->key)
            previous->left = current;
        else
            previous->right = current;
        correction(current);
        return;
    }
    void inOrdetTraversal(Node* vertex) {
        if (vertex != nullptr) {
            inOrdetTraversal(vertex->left);
            std::cout << vertex->key << ' ';
            if (vertex->left == nullptr)
                std::cout << "null ";
            else
                std::cout << vertex->left->key << ' ';
            if (vertex->right == nullptr)
                std::cout << "null ";
            else
                std::cout << vertex->right->key << ' ';
            std::cout << vertex->color << '\n';
            inOrdetTraversal(vertex->right);
        }
    }

    bool find(T x) {
        Node* temp = head;
        while (temp != nullptr) {
            if (x < temp->key)
                temp = temp->left;
            else if (temp->key < x)
                temp = temp->right;
            else
                return true;
        }
        return false;
    }
};

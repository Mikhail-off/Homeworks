#include <iostream>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

struct Node {
    int key = 0;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    Node* parent = nullptr;
    std::string color = "";
};

int main() {
    size_t n;
    std::cin >> n;
    if (n == 0) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    std::vector<std::shared_ptr<Node>> data(n);
    int root;
    std::cin >> root;
    for (size_t i = 0; i != n; ++i) {
        int number, value;
        std::cin >> number >> value;
        std::string left, right, color;
        std::cin >> left >> right >> color;
        data[number] = std::make_shared<Node>();
        data[number]->key = value;
        if (left == "null") {
            data[number]->left = nullptr;
        } else {
            data[number]->left = data[std::stoi(left)];
            data[std::stoi(left)]->parent = data[number].get();
        }
        if (right == "null") {
            data[number]->right = nullptr;
        } else {
            data[number]->right = data[std::stoi(right)];
            data[std::stoi(right)]->parent = data[number].get();
        }
        data[number]->color = color;
    }
    Node* temp = data[0]->parent;
    while (temp != nullptr)
        temp = temp->parent;
    return 0;
}

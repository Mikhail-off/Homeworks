#include <iostream>
#include <cstddef>
#include <memory>
#include "RBTree.h"

int main() {
    size_t n;
    std::cin >> n;
    RBTree<int> tree;
    for (size_t i = 0; i != n; ++i) {
        bool operation;
        std::cin >> operation;
        int value;
        std::cin >> value;
        if (operation == 0) {
            tree.insert(value);
        } else {
            if (tree.find(value) == true)
                std::cout << "Yes" << '\n';
            else
                std::cout << "No" << '\n';
        }
    }
    std::cout << tree.size() << std::endl;
    tree.inOrdetTraversal(tree.head);
    std::cout << std::endl;
    return 0;
}

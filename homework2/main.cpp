#include <vector>

#include "BST.hpp"

int main() {
    BST<int> bst;
    std::vector<int> vec = {40, 60, 20, 80, 50, 10, 30, 15, 5, 35,
                            25, 45, 55, 70, 90, 32, 33, 48, 46};

    for (int i = 0; i < vec.size(); i++) {
        bst.insertToBST(vec[i]);
    }
    bst.PrintInOrder();
    bst.deleteFromBST(40);
    bst.PrintInOrder();
    bst.deleteFromBST(15);
    bst.PrintInOrder();
    bst.deleteFromBST(9);
    bst.PrintInOrder();
    bst.deleteFromBST(20);
    bst.PrintInOrder();
    bst.deleteFromBST(10);
    bst.PrintInOrder();
    bst.deleteFromBST(30);
    bst.PrintInOrder();
}
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
    string c = "y";
    while (c == "y") {
        int val;
        cout << "Enter the Node to be deleted" << endl;
        cin >> val;
        bst.deleteFromBST(val);
        bst.PrintInOrder();
        cout << "Deleted more elements? [Y/n]" << endl;
        cin >> c;
    }
}
// Just learning templates to write generic code, please ignore templates
#include <iostream>
using namespace std;

#define DEBUG 0

template <typename T>
struct Node {
    Node* lch = NULL;
    Node* rch = NULL;
    T data;
    Node(T data, Node* lch = NULL, Node* rch = NULL) {
        this->data = data;
        this->lch = lch;
        this->rch = rch;
    }
};

template <typename T>
class BST {
    Node<T>* get_pre(Node<T>* node) {
        if (node->lch == NULL)
            return node->lch;

        Node<T>* curr = node->lch;
        Node<T>* prev = NULL;
        while (curr->rch != NULL) {
            prev = curr;
            curr = curr->rch;
        }
        if (prev != NULL) {
            prev->rch = curr->lch;
            curr->lch = NULL;
        }
        return curr;
    }

    void inOrderPrint(Node<T>* tmp) {
        if (tmp == NULL)
            return;
        inOrderPrint(tmp->lch);
        std::cout << tmp->data << " ";
        inOrderPrint(tmp->rch);
    }
    Node<T>* root = NULL;

   public:
    void PrintInOrder() {
        cout << "Printing InOrder: ";
        inOrderPrint(root);
        std::cout << "\n";
    }

    void BinarySearch(Node<T>* tmp, T data, Node<T>*& parent, Node<T>*& child) {
        if (!tmp || tmp->data == data) {
            child = tmp;
            return;
        }

        if (tmp->lch != NULL && tmp->lch->data == data) {
            child = tmp->lch;
            parent = tmp;
            return;
        }

        if (tmp->rch != NULL && tmp->rch->data == data) {
            child = tmp->rch;
            parent = tmp;
            return;
        }

        if (tmp->data > data) {
            BinarySearch(tmp->lch, data, parent, child);
        } else {
            BinarySearch(tmp->rch, data, parent, child);
        }
    }

    void insertToBST(T data) {
        Node<T>* curr = root;
        while (true) {
            // This will happen only when root is NULL
            if (curr == NULL) {
                root = new Node<T>(data);
                break;
            }

            if (data > curr->data) {
                if (curr->rch == NULL) {
                    curr->rch = new Node<T>(data);
                    break;
                }
                curr = curr->rch;
            } else {
                if (curr->lch == NULL) {
                    curr->lch = new Node<T>(data);
                    break;
                }
                curr = curr->lch;
            }
        }
    }

    void deleteFromBST(T data) {
        Node<T>* parent = NULL;
        Node<T>* child = NULL;
        this->BinarySearch(root, data, parent, child);
        cout << "Deleting " << data << " ";
        if (!child) {
            cout << " - Not found in the tree" << endl;
            return;
        }
        cout << endl;
        auto replace_with = this->get_pre(child);

        // Nothing to replace with i.e no predecessor
        if (replace_with) {
            // we don't want to add self link if the predecessor is itself left child
            if (replace_with != child->lch)
                replace_with->lch = child->lch;
            replace_with->rch = child->rch;
        }

#if DEBUG
        if (replace_with != NULL)
            cout << "replace_with: " << replace_with->data << endl;
        cout << "to_delete: " << child->data << endl;
        if (parent != NULL)
            cout << "parent: " << parent->data << endl;
#endif

        // which means deleting root
        if (parent == NULL) {
            root = replace_with;
        } else if (replace_with == NULL && child->rch != NULL) {
            // Storing Address of the pointer
            Node<T>** which_child = parent->lch == child ? &parent->lch : &parent->rch;
            // Assign value to the address of the lch or rch
            *which_child = child->rch;
        } else {
            // Storing Address of the pointer
            Node<T>** which_child = parent->lch == child ? &parent->lch : &parent->rch;
            // Assign value to the address of the parent lch or parent rch
            *which_child = replace_with;
        }

        delete child;
    }
};

#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename T>
class Node {
   public:
    vector<Node<T>*> childrens;
    T val;
    Node(T val) { this->val = val; }
    Node<T>* recursive(map<T, bool>& visited, Node<T>* node, int val) {
        if (node == NULL) {
            return NULL;
        }
        if (visited.find(node->val) == visited.end()) visited[node->val] = true;
        visited[node->val] = true;
        if (node->val == val) {
            return node;
        }
        for (int i = 0; i < node->childrens.size(); i++) {
            if (visited.find(node->childrens[i]->val) != visited.end() && visited.at(node->childrens[i]->val) == true) continue;
            auto nd = recursive(visited, node->childrens[i], val);
            if (nd != NULL) return nd;
        }
        return NULL;
    }

    bool detectCycle(map<T, bool>& visited, map<T, bool>& done, Node<T>* node) {
        if (node == NULL) return false;

        if (visited.find(node->val) == visited.end()) visited[node->val] = true;
        visited[node->val] = true;

        for (int i = 0; i < node->childrens.size(); i++) {
            auto nd = recursive(node->childrens[i], val);
            if (nd != NULL) return nd;
        }
    }

    Node<T>* get_present_node(std::vector<Node<T>*> heads, int val) {
        map<T, bool> visited = {};
        for (int i = 0; i < heads.size(); i++) {
            auto nd = recursive(visited, heads[i], val);
            if (nd != NULL) return nd;
        }
        return NULL;
    }

    void add_children(std::vector<Node<int>*> heads, T info) {
        auto node = get_present_node(heads, info);
        if (node == NULL) node = new Node(info);
        childrens.push_back(node);
    }

    static bool insert(std::vector<Node<int>*> heads, Node<T>*& node, T parent, T child) {
        if (node == NULL) {
            node = new Node<T>(parent);
            node->add_children(heads, child);
            return true;
        }

        if (node->val == parent) {
            node->add_children(heads, child);
            return true;
        }

        for (int i = 0; i < node->childrens.size(); i++) {
            if (insert(heads, node->childrens[i], parent, child)) return true;
        }
        return false;
    }

    static void print_values(std::vector<Node<int>*> heads) {
        map<T, bool> visited = {};
        for (int i = 0; i < heads.size(); i++) {
            Node<int>::show(visited, heads[i]);
            cout << ")";
        }
    }

    static void show(map<T, bool>& visited, Node<T>*& node) {
        if (node == NULL) return;
        if (visited.find(node->val) == visited.end()) visited[node->val] = true;
        visited[node->val] = true;
        cout << " (" << node->val;
        for (int i = 0; i < node->childrens.size(); i++) {
            if (visited.find(node->childrens[i]->val) != visited.end() && visited.at(node->childrens[i]->val) == true) continue;
            show(visited, node->childrens[i]);
            cout << ")";
        }
        return;
    }

    static void cycle(map<T, bool>& visited, map<T, bool>& done, Node<T>*& node) {}

    static void SORT(map<T, bool>& visited, map<T, bool>& done, Node<T>*& node) {}
};

int main() {
    std::vector<int> vertices = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<pair<int, int>> edges = {
        {1, 2}, {1, 5}, {1, 6}, {2, 5}, {2, 3}, {2, 7}, {3, 4}, {4, 5}, {5, 8}, {5, 7}, {6, 8}, {6, 5}, {7, 4}, {7, 8},
    };

    std::vector<Node<int>*> heads = {NULL};
    int h = 0;
    for (int i = 0; i < edges.size(); i++) {
        bool inserted = false;
        do {
            inserted = Node<int>::insert(heads, heads[h], edges[i].first, edges[i].second);
            if (!inserted) {
                heads.push_back(NULL);
                h++;
            }
        } while (!inserted);
    }
    Node<int>::print_values(heads);
    cout << endl;
}
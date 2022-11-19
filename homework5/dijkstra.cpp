#include <bits/stdc++.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define INF 99999

// Data of each node
class Data {
   public:
    int name;
    int value;
    int visited = false;
    int src = -1;
    Data() {}
    Data(int name, int value) {
        this->name = name;
        this->value = value;
    }
};

// Helper class to create Tree to display
class TreeNode {
   public:
    Data info;
    vector<TreeNode*> children;
    void add_children(TreeNode* ch) {
        for (int i = 0; i < children.size(); i++) {
            if (children[i]->info.name == ch->info.name) return;
        }
        children.push_back(ch);
    }

    TreeNode* right = NULL;
    TreeNode(Data data) { this->info = data; }
    void print() { cout << info.name << "(" << info.value << ")"; }

    static bool MakeTree(TreeNode*& node, Data data) {
        if (node == NULL) {
            node = new TreeNode(data);
            return true;
        }
        if (node->info.name == data.src) {
            node->add_children(new TreeNode(data));
            return true;
        }
        for (int i = 0; i < node->children.size(); i++) {
            if (TreeNode::MakeTree(node->children[i], data)) return true;
        }
        return false;
    }

    static void printBT(std::string prefix, TreeNode* node, bool isLeft) {
        if (node == nullptr) return;
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        node->print();
        cout << "\n";
        for (int i = 0; i < node->children.size(); i++) {
            string newP = prefix + (isLeft ? "│   " : "    ");
            printBT(newP, node->children[i], i != node->children.size() - 1);
        }
    }
};

class myComparator {
   public:
    int operator()(Data& p1, Data& p2) { return p1.value > p2.value; }
};

void recursive(const std::vector<std::vector<int>>& matrix, map<int, Data>& vec_weights, priority_queue<Data, vector<Data>, myComparator>& queue, Data present) {
    if (!vec_weights[present.name].visited) {
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[present.name][i] == INF) continue;
            int val = vec_weights[present.name].value + matrix[present.name][i];
            if (val < vec_weights[i].value) {
                vec_weights[i].value = val;
                vec_weights[i].src = present.name;
                queue.push(vec_weights[i]);
            }
        }
        vec_weights[present.name].visited = true;
    }

    if (queue.size() == 0) return;
    Data top = queue.top();
    queue.pop();
    recursive(matrix, vec_weights, queue, top);
}

void dijkstra(std::vector<int> vertices, std::vector<vector<int>> paths, int initial) {
    std::vector<std::vector<int>> matrix(vertices.size());
    map<int, Data> vec_weights;

    for (int i = 0; i < vertices.size(); i++) {
        for (int i = 0; i < vertices.size(); i++) matrix[i].push_back(INF);
        vec_weights[i] = Data(vertices[i], INF);
    }

    for (int i = 0; i < paths.size(); i++) {
        matrix[paths[i][0]][paths[i][1]] = paths[i][2];
        matrix[paths[i][1]][paths[i][0]] = paths[i][2];
    }

    vec_weights[initial] = Data(initial, 0);
    priority_queue<Data, vector<Data>, myComparator> queue;
    recursive(matrix, vec_weights, queue, Data(initial, 0));

    TreeNode* head = NULL;
    std::vector<Data> values;
    for (auto v : vec_weights) values.push_back(v.second);

    sort(values.begin(), values.end(), [&](Data i1, Data i2) {
        if (i1.src == initial) return false;
        return i1.src < i2.src;
    });

    int count = 0, i = 0;
    while (count != values.size()) {
        count += TreeNode::MakeTree(head, values[i]);
        i = (i + 1) % values.size();
    }
    TreeNode::printBT("", head, false);
}

int main() {
    // std::vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    // std::vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    // std::vector<vector<int>> paths = {{0, 1, 4}, {1, 2, 8}, {2, 3, 7}, {3, 4, 9}, {4, 5, 10}, {5, 6, 2}, {6, 7, 1}, {7, 0, 8}, {1, 7, 11}, {2, 8, 2}, {3, 5, 14}, {2, 5, 4}, {8, 6, 6}, {7, 8, 7}};
    // std::vector<vector<int>> paths = {{0, 1, 2}, {0, 3, 2}, {0, 4, 1}, {0, 6, 3}, {1, 2, 1}, {1, 4, 2},  {2, 5, 1}, {3, 4, 2},  {3, 6, 2}, {3, 7, 2},  {4, 5, 3},
    //   {4, 7, 1}, {4, 8, 1}, {5, 8, 1}, {6, 7, 1}, {6, 9, 2}, {6, 10, 3}, {7, 8, 2}, {7, 10, 4}, {8, 9, 1}, {8, 10, 1}, {9, 10, 1}};
    std::vector<vector<int>> paths = {{0, 1, 1}, {0, 2, 4}, {1, 2, 2},  {1, 3, 9}, {1, 6, 4}, {2, 3, 1}, {2, 4, 3}, {3, 4, 1}, {3, 6, 1},  {3, 5, 3},   {4, 5, 1},  {4, 8, 5},
                                      {6, 8, 3}, {8, 5, 2}, {8, 7, 14}, {1, 7, 2}, {6, 9, 2}, {6, 5, 6}, {5, 9, 6}, {7, 9, 5}, {0, 10, 5}, {0, 11, 12}, {10, 11, 5}};
    cout << "Tree" << endl;
    dijkstra(vertices, paths, 0);
}
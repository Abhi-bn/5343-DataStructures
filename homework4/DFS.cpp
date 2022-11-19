#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

bool dfs(std::map<char, std::vector<char>> graph, char n, map<char, bool>& visited, map<char, bool>& done, vector<char>& order) {
    visited[n] = true;
    if (graph.find(n) == graph.end()) {
        done[n] = true;
        order.push_back(n);
        return false;
    }

    for (auto v : graph[n]) {
        if (visited[v] && !done[v]) {
            cout << "Cycle Detected" << endl;
            return true;
        }
        if (visited[v]) continue;
        if (dfs(graph, v, visited, done, order)) {
            return true;
        }
    }

    done[n] = true;
    order.push_back(n);
    return false;
}

void DFS_magic(std::vector<char> vertices, std::vector<pair<char, char>> paths) {
    std::map<char, std::vector<char>> graph;
    for (int i = 0; i < vertices.size(); i++) {
        graph[paths[i].first] = {};
    }
    for (int i = 0; i < paths.size(); i++) {
        graph[paths[i].first].push_back(paths[i].second);
        std::sort(graph[paths[i].first].begin(), graph[paths[i].first].end());
    }

    cout << "Vertices\t"
         << "Connecting To\n";
    for (auto key : graph) {
        cout << key.first << "\t\t";
        for (int j = 0; j < key.second.size(); j++) cout << key.second[j] << " ";
        cout << endl;
    }
    std::map<char, bool> visited;
    std::map<char, bool> done;
    vector<char> order;
    cout << endl << "Topological DFS SORT: ";

    while (vertices.size() != 0) {
        if (dfs(graph, vertices[0], visited, done, order)) break;
        for (int i = 0; i < order.size(); i++) {
            vertices.erase(std::remove(vertices.begin(), vertices.end(), order[i]), vertices.end());
        }
    }

    for (int i = order.size() - 1; i >= 0; i--) {
        cout << order[i] << "  ";
    }
    cout << endl << "done" << endl;
}

int main() {
    std::vector<char> vertices = {
        '1', '2', '3', '4', '5', '6', '7', '8',
    };

    std::vector<pair<char, char>> paths = {
        {'1', '2'}, {'1', '5'}, {'1', '6'}, {'2', '5'}, {'2', '3'}, {'2', '7'}, {'3', '4'}, {'4', '5'}, {'5', '8'}, {'5', '7'}, {'6', '8'}, {'6', '5'}, {'7', '4'}, {'7', '8'},
    };
    DFS_magic(vertices, paths);

    vertices = {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    paths = {
        {'s', 'r'}, {'r', 'u'}, {'r', 'y'}, {'u', 't'}, {'y', 'v'}, {'v', 'w'}, {'w', 'z'}, {'v', 'x'}, {'m', 'x'}, {'m', 'q'}, {'m', 'r'},
        {'q', 't'}, {'n', 'q'}, {'n', 'u'}, {'n', 'o'}, {'o', 'r'}, {'o', 'v'}, {'o', 's'}, {'p', 'o'}, {'p', 's'}, {'p', 'z'},
    };

    DFS_magic(vertices, paths);
}
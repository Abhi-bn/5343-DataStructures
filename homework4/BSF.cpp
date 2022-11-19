#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<char> GetNodeWithNoIncoming(std::map<char, int> external_count) {
    vector<char> to_rm;
    for (auto key : external_count)
        if (key.second == 0) to_rm.push_back(key.first);

    return to_rm;
}
void printExternalCount(std::map<char, int> external_count) {
    cout << endl;
    for (auto key : external_count) {
        cout << key.first << ":" << (int)key.second << "     ";
    }
    cout << endl;
}

void BFS_magic(std::vector<char> vertices, std::vector<pair<char, char>> paths) {
    std::map<char, std::vector<char>> graph;
    std::map<char, int> external_count;
    for (int i = 0; i < paths.size(); i++) {
        external_count[paths[i].first] = 0;
        graph[paths[i].first].push_back(paths[i].second);
        std::sort(graph[paths[i].first].begin(), graph[paths[i].first].end());
    }

    for (auto key : graph)
        for (int i = 0; i < key.second.size(); i++) external_count[key.second[i]] += 1;
    cout << "Vertices\t"
         << "Connecting To\n";

    for (auto key : graph) {
        cout << key.first << "\t\t";
        for (int j = 0; j < key.second.size(); j++) cout << key.second[j] << " ";
        cout << endl;
    }

    vector<char> first_to_zero;
    cout << "Topological BFS SORT: ";
    while (true) {
        vector<char> zeros = GetNodeWithNoIncoming(external_count);
        for (int i = 0; i < zeros.size(); i++) first_to_zero.push_back(zeros[i]);

        if (first_to_zero.size() == 0 && external_count.size() == 0) {
            cout << "\n[Done]" << endl;
            break;
        } else if (first_to_zero.size() == 0 && external_count.size() != 0) {
            cout << "\n[Cycle Detected]" << endl;
            break;
        }

        cout << first_to_zero[0] << "  ";

        for (int i = 0; i < first_to_zero.size(); i++) external_count.erase(first_to_zero[i]);

        for (int i = 0; i < graph[first_to_zero[0]].size(); i++) external_count[graph[first_to_zero[0]][i]]--;

        first_to_zero.erase(first_to_zero.begin());
    }
    cout << endl;
}

int main() {
    std::vector<char> vertices = {
        '1', '2', '3', '4', '5', '6', '7', '8',
    };

    std::vector<pair<char, char>> paths = {
        {'1', '2'}, {'1', '5'}, {'1', '6'}, {'2', '5'}, {'2', '3'}, {'2', '7'}, {'3', '4'}, {'4', '5'}, {'5', '8'}, {'5', '7'}, {'6', '8'}, {'6', '5'}, {'7', '4'}, {'7', '8'},
    };
    BFS_magic(vertices, paths);

    vertices = {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    paths = {
        {'s', 'r'}, {'r', 'u'}, {'r', 'y'}, {'u', 't'}, {'y', 'v'}, {'v', 'w'}, {'w', 'z'}, {'v', 'x'}, {'m', 'x'}, {'m', 'q'}, {'m', 'r'},
        {'q', 't'}, {'n', 'q'}, {'n', 'u'}, {'n', 'o'}, {'o', 'r'}, {'o', 'v'}, {'o', 's'}, {'p', 'o'}, {'p', 's'}, {'p', 'z'},
    };
    BFS_magic(vertices, paths);
}
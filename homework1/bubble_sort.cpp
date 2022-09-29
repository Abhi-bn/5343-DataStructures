#include <vector>
#include <time.h>
#include "helper.h"
#include "Node.h"
using namespace std;

int main()
{
    srand(time(0));
    vector<int> data;
    // generating 20 random number
    for (int i = 0; i < 20; i++)
        data.push_back(rand() % 2000);

    // Adding data to Nodes using add_Node function
    Node *n = new Node(data[0]);
    Node *head = n;
    for (int i = 1; i < data.size(); i++)
        Node::add_Node(head, new Node(data[i]));

    cout << "Before Sorting Nodes:" << endl;
    print_all_node_data(head);

    // using bubble_sort function to sort the nodes
    Node::bubble_sort(head);

    cout << "After Sorting Nodes: " << endl;
    print_all_node_data(head);
}
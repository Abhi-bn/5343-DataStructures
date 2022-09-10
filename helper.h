#pragma once

#ifndef HELPER_H // include guard
#define HELPER_H

#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

void print_all_node_data(Node *head)
{
    cout << "Node Data: ";
    Node *curr = head;
    while (curr != NULL)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}
void print_all_vector_values(const vector<int> &data)
{
    cout << "Vector Data: ";
    for (int i = 0; i < data.size(); i++)
        cout << data[i] << " ";
    cout << "\n";
}
#endif /* HELPER_H */
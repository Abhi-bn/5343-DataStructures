#pragma once

#ifndef NODE_H // include guard
#define NODE_H

#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next;

    Node(int data, Node *next = NULL)
    {
        this->data = data;
        this->next = next;
    };

    static void add_Node(Node *head, Node *new_node)
    {
        Node *curr = head;
        while (curr->next != NULL)
            curr = curr->next;

        curr->next = new_node;
    }

    static void bubble_sort(Node *&head)
    {
        // if the head is null or if it only contains only 1 value,
        // just return the head
        if (head == NULL || head->next == NULL)
            return;

        // run while for ever (NOTE: there is a stopping condition :P)
        while (true)
        {
            bool changed = false;

            // curr holds pointer to current Node which is being worked with
            Node *curr = head;

            // future is pointer to the next Node to compare with
            Node *future = curr->next;
            // old Node we need to keep track as we need to re-attach
            // future node to previous when swapping
            Node *prev = NULL;

            // Do until there is no more future Nodes
            while (future != NULL)
            {
                // we need to check present node and future node for the order
                // i.e Ascending order
                if (curr->data > future->data)
                {
                    // Since there is need of change in position of node,
                    // we set changed to true as we might need more iteration
                    // to compare with other Node's
                    changed = true;

                    if (prev == NULL)
                        // prev is NULL only when its the first node,
                        // hence we need to update the head as well
                        head = future;
                    else
                        // here we point previous node to future node
                        prev->next = future;

                    // Now, curr will be pointing to future of future
                    curr->next = future->next;
                    // then we update the future to point to the current Node
                    future->next = curr;

                    // update the previous and future nodes, leaving curr as is
                    prev = future;
                    future = curr->next;

                    /*
                        Jest of whats happening above
                        Before:
                        prev    curr   future
                        [3] ->  [7] ->  [5] ->  [9] -> NULL

                        After:
                        prev -> future -> curr
                        [3] ->   [5]  ->   [7] -> [9] -> NULL

                        Update prev and future:
                               prev -> curr -> future
                        [3] ->  [5]  -> [7] ->  [9] -> NULL
                    */
                }
                else
                {
                    // just move the pointers to next elements as nothing
                    // to be done here
                    prev = curr;
                    curr = curr->next;
                    future = future->next;
                }
            }
            // if no swapping occurs even once, stop while as all the data has been sorted in the node
            if (!changed)
                return;
        }
    }
};

#endif /* NODE_H */
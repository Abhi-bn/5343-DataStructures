#include <iostream>
#include <vector>
#include <time.h>
#include <bits/stdc++.h>
#include "helper.h"
using namespace std;

/*
    Tertiary_search which splits the problem into 3 segments and search's the data
    in these segments, similar to the way binary search operates.
*/
int tertiary_search(vector<int> search, int k, int f, int l)
{
    if (f >= l)
        return -1;

    // ----|----|----
    // if dash's represents numbers, segments are divided into
    // 3 parts who's mids are calculated as below
    int mid1 = f + (l - f) / 3;
    int mid2 = l - (l - f) / 3;

    // checking at both mids
    if (search[mid1] == k)
        return mid1;
    else if (search[mid2] == k)
        return mid2;
    // if not found at both the mids, check which segment the number
    // might be in, then do appropriate recursive calls, which is just an
    // extension of binary search algo
    else if (k > search[mid1] && k < search[mid2])
        return tertiary_search(search, k, mid1 + 1, mid2 - 1);
    else if (search[mid2] < k)
        return tertiary_search(search, k, mid1 + 1, l);
    else
        return tertiary_search(search, k, f, mid2 - 1);
}

void search_with_messages(const vector<int> &data, int key)
{
    int at_index;
    if ((at_index = tertiary_search(data, key, 0, data.size() - 1)) != -1)
        cout << "Found at index: " << at_index << endl;
    else
        cout << "Key not found in the vector\n";
}

int main()
{
    // setting seed value for random number generator
    srand(time(0));
    vector<int> data;
    for (int i = 0; i < 20; i++)
        data.push_back(rand() % 2000);

    // similar to binary search, data has to be sorted, which is done below
    sort(data.begin(), data.end());

    print_all_vector_values(data);

    // select a random index within the data vector
    int k = data[rand() % data.size() - 1];

    cout << "Searching for: " << k << endl;

    search_with_messages(data, k);

    // Now generating another random number and searching for that number, usually the number is not found
    k = rand() % 2000;

    cout << "Now searching for: " << k << endl;

    search_with_messages(data, k);
}
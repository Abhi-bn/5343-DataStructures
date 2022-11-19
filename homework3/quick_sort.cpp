#include <bits/stdc++.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool compare(int val1, int val2, bool asc) {
    if (asc) return val1 > val2;
    return val1 < val2;
}
// Quick Sort algorithm which accepts array, start index to sort from, end index to sort till
void quick_sort(vector<int>& array, int min_ind, int max_ind, bool asc) {
    // pivot element would first the start element
    int pivot = min_ind;
    // start searching for larger than pivot from min_ind + 1
    int l_c = min_ind + 1;
    // end will start from the max_ind
    int r_c = max_ind;
    // this will be conditions where recursion has to stop
    if (min_ind >= array.size() || min_ind >= max_ind || max_ind <= 0) return;

    while (true) {
        // find an element index which is larger than pivot from the start
        if (asc) {
            while (array[pivot] > array[l_c] && l_c <= r_c) l_c++;
            while (array[pivot] < array[r_c] && r_c >= l_c) r_c--;
        } else {
            while (array[pivot] < array[l_c] && l_c <= r_c) l_c++;
            while (array[pivot] > array[r_c] && r_c >= l_c) r_c--;
        }

        // find an element index which is less than pivot from the end
        if (l_c >= r_c) {
            // over step caused by while loop above
            l_c--;
            r_c++;
            break;
        }
        // swap that element if a larger from start and smaller from end than the pivot element
        swap(array[l_c++], array[r_c--]);
    }
    if (asc && array[l_c] > array[pivot])
        swap(array[pivot], array[l_c - 1]);
    else if (!asc && array[l_c] < array[pivot])
        swap(array[pivot], array[l_c + 1]);
    else
        swap(array[pivot], array[l_c]);

    // now sort left side of pivot index
    quick_sort(array, min_ind, l_c - 1, asc);
    // then sort right side of pivot index
    quick_sort(array, l_c + 1, max_ind, asc);
    // do this till start > end and other conditions
}

int main() {
    srand(time(0));
    std::vector<int> data, test;
    // generating 20 random number
    for (int i = 0; i < 20; i++) {
        auto val = rand() % 2000;
        data.push_back(val);
        test.push_back(val);
    }
    cout << "UnSorted Array(asc): " << endl;
    for (int i = 0; i < data.size(); i++) cout << data[i] << " ";
    cout << endl;
    quick_sort(data, 0, data.size() - 1, true);

    cout << "Sorted Using Quick Sort(asc): " << endl;
    for (int i = 0; i < data.size(); i++) cout << data[i] << " ";

    cout << endl;
    sort(test.begin(), test.end());
    cout << "Sorted Using C++ built in Sort(asc): " << endl;
    for (int i = 0; i < test.size(); i++) cout << test[i] << " ";
    cout << "\nChecking from both vectors are equal(asc): " << std::equal(data.begin(), data.begin() + data.size(), test.begin()) << endl;

    std::vector<int> data1, test1;
    // generating 20 random number
    for (int i = 0; i < 20; i++) {
        auto val = rand() % 2000;
        data1.push_back(val);
        test1.push_back(val);
    }
    cout << "\n\nUnSorted Array(desc): " << endl;
    for (int i = 0; i < data1.size(); i++) cout << data1[i] << " ";
    cout << endl;
    quick_sort(data1, 0, data1.size() - 1, false);

    cout << "Sorted Using Quick Sort(desc): " << endl;
    for (int i = 0; i < data1.size(); i++) cout << data1[i] << " ";

    cout << endl;
    sort(test1.begin(), test1.end(), greater<int>());
    cout << "Sorted Using C++ built in Sort(desc): " << endl;
    for (int i = 0; i < test1.size(); i++) cout << test1[i] << " ";
    cout << "\nChecking from both vectors are equal(desc): " << std::equal(data1.begin(), data1.begin() + data1.size(), test1.begin()) << endl;
}
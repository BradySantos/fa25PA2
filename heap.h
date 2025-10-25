#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap().
        // Fix this size condition below::::::::::::::::::::::::::::::
        if (idx < 0 || idx >= size) { // Check index out of bounds
            cout << "Index out of bounds. Cannot push." << endl;
            return;
        }

        weightArr[size] = weightArr[idx]; // Insert index at end of heap; size value is index at end of heap
        // data[size] = weightArr[size];, figure out data use, might not need this line
        size++;

        // upheap(idx, weightArr); // Upheap after insertion

    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) {  // If heap is already empty, do not pop; just return 0 index
            cout << "Heap is empty. Cannot pop; returning 0 index." << endl;
            return 0; // Should 0 be returned??????
        }
        if (size == 1) { // If heap only has a root, remove root and return 0 index
            cout << "Heap only has one element. Removing and returning 0 index." << endl;
            // weightArr[size - 1] = -1; Figure out how to set array as "empty"
            return 0;
        }

        weightArr[0] = weightArr[size - 1]; // Replace root with last element
        size--;

// Downheap:::::::


        return weightArr[0]; // Return root (contains smallest index)
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        if (size == 0) { // If empty, cannot upheap
            cout << "Heap is empty. Cannot upheap." << endl;
            return;
        }
        if (size == 1) { // If only one element, cannot upheap
            cout << "Heap only has one element. No need to upheap." << endl;
            return;
        }

        int i = pos;
        while (weightArr[i] < weightArr[(i - 1) / 2]) { // Compare target index to parent
            int tempParent = weightArr[(i - 1) / 2]; // Store old parent
            weightArr[(i - 1) / 2] = weightArr[i];
            weightArr[i] = tempParent;
        }
        // Parent: (i - 1) / 2, children: 2*i + 1, 2*i + 2.
        // Fix i?

    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        if (size == 0) { // If empty, cannot downheap
            cout << "Heap is empty. Cannot downheap." << endl;
            return;
        }
        if (size == 1) { // If only one element, cannot downheap
            cout << "Heap only has one element. No need to downheap." << endl;
            return;
        }

        int i = pos;
        while ((weightArr[(i - 1) / 2] > weightArr[2*i + 1]) ||
              (weightArr[(i - 1) / 2] > weightArr[2*i + 2])) { // Downheap if parent is greater than either child
            if (weightArr[(i - 1) / 2] > weightArr[2*i + 1]) { // If parent is greater than left child, swap
                int tempParent = weightArr[(i - 1) / 2];
                weightArr[(i - 1) / 2] = weightArr[2*i + 1];
                weightArr[2*i + 1] = tempParent;
            }
            if (weightArr[(i - 1) / 2] > weightArr[2*i + 2]) { // If parent is greater than right child, swap
                int tempParent = weightArr[(i - 1) / 2];
                weightArr[(i - 1) / 2] = weightArr[2*i + 2];
                weightArr[2*i + 2] = tempParent;
            }

            // Fix??
        }
    }
};

#endif
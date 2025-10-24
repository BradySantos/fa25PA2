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


        return -1; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif
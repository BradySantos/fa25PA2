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
        // Fix this size condition below:::::::::::::::::::::::::::::: What is max array size?
        if (size >= ???) { // Check index out of bounds
            cout << "Index out of bounds. Cannot push." << endl;
            return;
        }

        weightArr[size] = idx; // Insert index at end of heap

        upheap(size, weightArr); // Upheap after insertion

        size++; // Update size
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int minIndex = weightArr[0]; // Save smallest index

        if (size == 0) {  // If heap is already empty, do not pop; just return 0 index
            cout << "Heap is empty. Cannot pop; returning -1 index." << endl;
            return -1;
        }
        if (size == 1) { // If heap only has a root, remove root and return 0 index
            cout << "Heap only has one element. Removing and returning smallest index." << endl;
            size--;
            return minIndex;
        }

        weightArr[0] = weightArr[size - 1]; // Replace root with last element
        size--;

        downheap(0, weightArr); // Downheap from root after deletion

        return minIndex; // Return root (contains smallest index)
    }

    void upheap(int pos, int weightArr[]) { // Upheap and downheap should both be O(logn); therefore also pop and push
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
        while ((i > 0) && (weightArr[i] < weightArr[(i - 1)/ 2])) { // Compare target index to parent
            int tempParent = weightArr[(i - 1) / 2]; // Store old parent
            weightArr[(i - 1) / 2] = weightArr[i]; // Parent: (i - 1) / 2
            weightArr[i] = tempParent;

            i = (i - 1) / 2; // Move up (O(logn))
        }
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

        int i = pos; // Parent start
        int currChild; // Track which child is being traced

        while (2 * i + 1 < size) { // Enter loop if left child is within array size
            int leftChild = 2 * i + 1; // Children: 2*i + 1, 2*i + 2.
            int rightChild = 2 * i + 2;

            currChild = leftChild; // Start at left child

            if ((rightChild < size) && (weightArr[rightChild] < weightArr[currChild])) {
                currChild = rightChild; // If right child is in array and less than left, set right as current
            }

            if (weightArr[currChild] >= weightArr[i]) { // If smallest child is already smaller than parent, no need for downheap
                break;
            }

            int tempParent = weightArr[i]; // Swap parent down
            weightArr[i] = weightArr[currChild];
            weightArr[currChild] = tempParent;

            i = currChild; // Update parent to child (O(logn))
        }
    }
};

#endif
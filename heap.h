#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    /**
     * The push function inserts a given index at the end of the heap and restores order through upheap
     * @param idx : Index value to insert
     * @param weightArr : Array to modify
     */
    void push(int idx, int weightArr[]) {
        if (size >= 64) { // Check array out of bounds past index 63 (array only has indices 0 to 63, totalling 64)
            cout << "Index out of bounds. Cannot push." << endl;
            return;
        }

        data[size] = idx; // Insert index at end of heap

        upheap(size, weightArr); // Upheap after insertion

        size++; // Update size
    }

    /**
     * The pop function removes and returns the smallest index of a given array; it restores order through downheap
     * @param weightArr : Array to modify
     * @return : Smallest index
     */
    int pop(int weightArr[]) {
        // Replace root with last element, then call downheap()
        int minIndex = data[0]; // Save smallest index

        if (size == 0) {  // If heap is already empty, do not pop; just return 0 index
            cout << "Heap is empty. Cannot pop; returning -1 index." << endl;
            return -1;
        }
        if (size == 1) { // If heap only has a root, remove root and return 0 index
            cout << "Heap only has one element. Removing and returning smallest index." << endl;
            size--;
            return minIndex;
        }

        data[0] = data[size - 1]; // Replace root with last element
        size--;

        downheap(0, weightArr); // Downheap from root after deletion

        return minIndex; // Return root (contains smallest index)
    }

    /**
     * The upheap function repeatedly swaps the child upward as long as it is smaller than its parent
     * @param pos : Keep track of node
     * @param weightArr : Array to modify
     */
    void upheap(int pos, int weightArr[]) { // Upheap and downheap should both be O(logn); therefore so are pop and push
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

    /**
     * The downheap function repeatedly swaps the parent downward as long as it is larger than any child
     * @param pos : Keep track of node
     * @param weightArr : Array to modify
     */
    void downheap(int pos, int weightArr[]) {
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

            if ((rightChild < size) && (weightArr[rightChild] < weightArr[currChild])) { // Check if right child in array and < left
                currChild = rightChild;
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
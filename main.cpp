#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

/**
 * Step 1: Read file and count frequencies
 * @param freq : Stores frequencies of letters
 * @param filename : File to read
 */
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}


/**
 * Step 2: Create leaf nodes for each character
 * @param freq : Stores frequencies of letters
 * @return : Next available index
 */
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

/**
 * Step 3: Build the encoding tree using heap operations
 * @param nextFree : Track next available index
 * @return : Index of final root node
 */
int buildEncodingTree(int nextFree) {
    MinHeap heap;
    for (int i = 0; i < nextFree; ++i) { // Push all used (leaf) indices into heap
        heap.push(i, weightArr);
    }

    int parent; // Tracks index
    while (heap.size > 1) {
        int firstSmallest = heap.pop(weightArr); // Pop first smallest
        int secondSmallest = heap.pop(weightArr); // Pop second smallest

        parent = nextFree; // Update tracker
        weightArr[parent] = weightArr[firstSmallest] + weightArr[secondSmallest]; // Combine two smallest nodes into parent

        leftArr[parent] = firstSmallest; // Set left pointer index of current parent
        rightArr[parent] = secondSmallest; // Set right pointer index of current parent

        heap.push(parent, weightArr); // Push new parent back into heap
        nextFree++;
    }

    return parent; // Return index of root node
}

/**
 * Step 4: Use an STL stack to generate codes
 * @param root : Index to start from
 * @param codes : Stores binary codes of letters
 */
void generateCodes(int root, string codes[]) {
    stack<pair<int, string>> codesStack; // Create stack

    codesStack.push({root, ""}); // Push root and empty string to stack

    while (!codesStack.empty()) {
        pair<int, string> currVal = codesStack.top(); // Track current value of both node and string
        codesStack.pop(); // Remove top node

        if ((leftArr[currVal.first] == -1) && rightArr[currVal.first] == -1) { // Check if leaf node
            int index = charArr[currVal.first] - 'a'; // Update index
            codes[index] = currVal.second; // Update code string
        }

        if (leftArr[currVal.first] != -1) { // Left edge
            codesStack.push({leftArr[currVal.first], currVal.second + "0"}); // Add 0 for left edge
        }

        if (rightArr[currVal.first] != -1) { // Right edge
            codesStack.push({rightArr[currVal.first], currVal.second + "1"}); // Add 1 for right edge
        }
    }
}

/**
 * Step 5: Print table and encoded message
 * @param filename : File to read
 * @param codes : Stores binary codes of letters
 */
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}
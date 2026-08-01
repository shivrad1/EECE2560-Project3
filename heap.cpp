//
//  heap.cpp
//  wordsearch
//
//Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

#include "heap.h"

using namespace std;

// Default constructor
// Initializes the heap size to zero since the heap is initially empty.
heap::heap()
{
    heapSize = 0;
}

// Returns the index of the parent node.
int heap::parent(int index) const
{
    return (index - 1) / 2;
}

// Returns the index of the left child.
int heap::left(int index) const
{
    return (2 * index) + 1;
}

// Returns the index of the right child.
int heap::right(int index) const
{
    return (2 * index) + 2;
}

// Returns the string stored at the specified index.
string heap::getItem(int n) const
{
    return items.at(n);
}

// Copies the dictionary words into the heap
// and builds the initial max heap.
void heap::initializeMaxHeap(const vector<string>& words)
{
    items = words;
    buildMaxHeap();
}

// Restores the max heap property beginning
// at the specified index.
void heap::maxHeapify(int index)
{
    int l = left(index);
    int r = right(index);
    int largest;

    // Compare the current node with its left child.
    if (l < heapSize && items[l] > items[index])
    {
        largest = l;
    }
    else
    {
        largest = index;
    }

    // Compare the current largest value with the right child.
    if (r < heapSize && items[r] > items[largest])
    {
        largest = r;
    }

    // If a child is larger than the current node,
    // swap them and continue heapifying.
    if (largest != index)
    {
        string temp = items[index];
        items[index] = items[largest];
        items[largest] = temp;

        maxHeapify(largest);
    }
}

// Converts the vector into a valid max heap.
void heap::buildMaxHeap()
{
    // The heap initially contains every element.
    heapSize = items.size();

    // Start at the last non-leaf node and
    // restore the heap property moving upward.
    for (int index = (heapSize / 2) - 1; index >= 0; index--)
    {
        maxHeapify(index);
    }
}

// Performs heap sort and returns the
// alphabetically sorted vector.
vector<string> heap::heapSort()
{
    // Ensure the vector satisfies the max heap property.
    buildMaxHeap();

    // Move the largest element to the end of the heap,
    // reduce the heap size, and restore the heap.
    for (int index = heapSize - 1; index >= 1; index--)
    {
        string temp = items[0];
        items[0] = items[index];
        items[index] = temp;

        // One less element is part of the heap.
        heapSize = heapSize - 1;

        // Restore the heap after the swap.
        maxHeapify(0);
    }

    return items;
}

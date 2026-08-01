//
//  heap.h
//  wordsearch
//
//Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

#ifndef HEAP_H
#define HEAP_H

#include <string>   // std::string
#include <vector>   // std::vector

//===========================================
// heap class (Part B)
// Stores words in a max heap and performs
// heap sort.
//===========================================

class heap
{
private:
    std::vector<std::string> items;   // Stores the words in heap order.
    int heapSize;                     // Number of elements in the heap.

    // Return the index of the parent node.
    int parent(int n) const;

    // Return the index of the left child.
    int left(int n) const;

    // Return the index of the right child.
    int right(int n) const;

    // Restore the max heap property.
    void maxHeapify(int n);

    // Convert the vector into a max heap.
    void buildMaxHeap();

public:
    // Default constructor.
    heap();

    // Return the word stored at index n.
    std::string getItem(int n) const;

    // Copy the dictionary words into the heap.
    void initializeMaxHeap(const std::vector<std::string>& words);

    // Sort the words using heap sort.
    std::vector<std::string> heapSort();
};

#endif

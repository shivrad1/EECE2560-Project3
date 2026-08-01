//
//  heap.h
//  wordsearch
//
//Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

#ifndef HEAP_H
#define HEAP_H


#include <string>
#include <vector>



class heap
{
private:
    std::vector<std::string> items;
    
    int parent(int n) const;
    int left(int n) const;
    int right(int n) const;
    
    void maxHeapify(int n);
    void buildMaxHeap();
    
    int heapSize;

    
public:
    heap();
    
    std::string getItem(int n) const;
    
    void initializeMaxHeap(const std::vector<std::string>& words);
    
    std::vector<std::string> heapSort();
    
    
};

#endif

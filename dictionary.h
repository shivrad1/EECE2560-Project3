//
//  dictionary.h
//  wordsearch
//
//
//Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.
//
//===========================================
// dictionary class  (parts 1a-1d)
// Reads the word list, stores it in a vector, sorts it with selection sort,
// and supports fast lookups with binary search.
//===========================================

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>   // ostream (for the overloaded output operator)
#include <string>     // std::string
#include <vector>     // std::vector


class dictionary
{
private:
    std::vector<std::string> words;   // the stored word list
  
    void quickSortHelper(int low, int high);// QuickSort helper methods
    int partition(int low, int high);
public:
    void readDict(const std::string& filename);            // (1a) load words from file
    void selectionSort();                             // (1c) sort words ascending
    int binarySearch(const std::string& target) const;    // (1d) find a word, return its index
    // (1b) output operator, declared friend so it can read the private 'words'.
    friend std::ostream& operator<<(std::ostream& outputstring, const dictionary& d);
    void heapSort();  // (Part B, 3) sort words ascending using heap sort
    void quickSort(); //part B, 1
};

// (1b) Overloaded output operator, declared here so callers in other files can
// use it. Global (non-member) so the stream is the left operand (cout << dict).
std::ostream& operator<<(std::ostream& outputstring, const dictionary& d);

#endif

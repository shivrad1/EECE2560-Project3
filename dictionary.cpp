//
//  dictionary.cpp
//  wordsearch
//
//
//Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

#include <fstream>    // ifstream / ofstream for reading and writing files
#include <iostream>   // communicates with the user if there is an error opening the file
#include <string>     // std::string and getline
#include <vector>     // std::vector

#include "dictionary.h"
#include "heap.h"

using namespace std;

//===========================================
// dictionary class implementation  (parts 1a-1d)
//===========================================
// (1a) Read words from the dictionary file, one word per line.
// Filters out anything shorter than 5 characters, since the puzzle only cares
// about words of length >= 5.
void dictionary::readDict(const string& filename)
{
    ifstream dict(filename);       // open the dictionary file
    string word;                   // scratch variable for each line read
    if (!dict)
    {                   // guard: couldn't open the file
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    // getline pulls one whole line (one word) at a time until end of file.
    while (getline(dict, word))
    {
        // Strip a trailing carriage return if the file has Windows line endings.
        // getline removes '\n' but leaves '\r', which would corrupt comparisons.
        if (!word.empty() && word.back() == '\r')
        {
            word.pop_back();
        }
        // Only keep words that meet the 5-character minimum.
        if (word.length() >= 5)
        {
            words.push_back(word);
        }
    }
}

// (1c) Selection sort: sorts 'words' into ascending (alphabetical) order.
// Required for binarySearch to work, since binary search assumes sorted data.
// Selection sort repeatedly finds the smallest remaining element and swaps it
// into the next position.
void dictionary::selectionSort()
{
    int min;                        // index of the smallest word found so far
    // Guard against an empty list: words.size()-1 is unsigned, so on an empty
    // vector it would wrap to a huge number and the loop would run out of bounds.
    if (words.empty())
    {
        return;
    }
    // Outer loop: position being filled with the next-smallest word.
    for (int i = 0; i < words.size() - 1; i++)
    {
        min = i;                    // assume the current position holds the smallest
        // Inner loop: scan the unsorted remainder for anything smaller.
        for (int j = i + 1; j < words.size(); j++)
        {
            if (words[j] < words[min]) {   // string < compares lexicographically
                min = j;                    // found a smaller word; remember it
            }
        }
        swap(words[i], words[min]);  // put the smallest found into position i
    }
}

// (1d) Binary search over the sorted 'words' vector.
// Returns the index of 'target' if present, or -1 if not found.
// Repeatedly halves the search range by comparing against the middle element.
int dictionary::binarySearch(const string& target) const
{
    int first = 0;                     // low end of the current search range
    int last = words.size() - 1;       // high end of the current search range
    while (first <= last)              // continue while the range is non-empty
    {
        int mid = (first + last) / 2;  // middle index of the current range
        string midValue = words[mid];  // the word at the middle
        if (target == midValue)
        {
            return mid;                // exact match: return its index
        }
        else if (target < midValue)
        {
            last = mid - 1;            // target is earlier: discard the right half
        }
        else
        {
            first = mid + 1;           // target is later: discard the left half
        }
    }
    return -1;                          // range exhausted without a match
}

// part a: rearranges the array around a pivot element. All words smaller than or equal
// to the pivot are placed to its left; larger words are placed to its right.
int dictionary::partition(int low, int high)
{
    string pivot = words[high]; // Select the last element in the range as pivot
    int i = low - 1;            // Index marking the edge of smaller elements

    for (int j = low; j < high; ++j)
    {
        // If current word is alphabetically smaller than or equal to pivot
        if (words[j] <= pivot)
        {
            ++i;
            swap(words[i], words[j]);
        }
    }
    // Place pivot in its correct sorted position
    swap(words[i + 1], words[high]);
    return (i + 1); // Return pivot index
}

// Recursive helper for QuickSort
void dictionary::quickSortHelper(int low, int high)
{
    if (low < high)
    {
        // pi is partitioning index; words[pi] is now in its correct place
        int pi = partition(low, high);

        // Recursively sort elements before and after partition
        quickSortHelper(low, pi - 1);
        quickSortHelper(pi + 1, high);
    }
}

// QuickSort: sorts 'words' vector into ascending order.
void dictionary::quickSort()
{
    if (!words.empty())
    {
        quickSortHelper(0, words.size() - 1);
    }
}

// (1b) Overloaded output operator: prints every stored word on its own line.
ostream& operator<<(ostream& outputstring, const dictionary& d)
{
    for (const auto& word : d.words) {
        outputstring << word << "\n";
    }
    return outputstring;
}

// (part b) Heapsort: sorts 'words' into ascending order by delegating to the
// heap class. A local heap object is built from the word list, sorted, and the
// sorted result is copied back into 'words' so binarySearch can run on it.
void dictionary::heapSort()
{
    heap wordHeap;                          // local heap used only for sorting
    wordHeap.initializeMaxHeap(words);      // copy words in and build the max-heap
    words = wordHeap.heapSort();            // sort, then copy the result back out
}


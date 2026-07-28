// File: wordsearch.h
// Declarations for the Word Search project: the grid and dictionary classes,
// plus the global findMatches() and search() functions.
// Implementations live in wordsearch.cpp.
//Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

#ifndef WORDSEARCH_H
#define WORDSEARCH_H

#include <iostream>   // ostream (for the overloaded output operator)
#include <string>     // std::string
#include <vector>     // std::vector

using namespace std;

// Direction offsets for the 8 directions a word can run in the grid.
// Each index 0..7 pairs one dr[] value with the matching dc[] value, giving a
// (row-step, col-step) vector:
//   0: (-1, 0) up (N)      1: (-1,+1) up-right (NE)   2: (0,+1) right (E)
//   3: (+1,+1) down-right  4: (+1, 0) down (S)        5: (+1,-1) down-left
//   6: (0,-1) left (W)     7: (-1,-1) up-left (NW)
// 'extern' here: these are DECLARED in the header and DEFINED once in the .cpp,
// so every file that includes this header shares the same single copy.
extern const int dr[8];
extern const int dc[8];

//===========================================
// grid class  (part 2)
// Loads an n x n block of letters from a file and stores it as a 2D matrix,
// exposing read-only access to individual cells and the dimensions.
//===========================================
class grid {
private:
    int rows;                      // number of rows (n)
    int cols;                      // number of columns (n)
    vector<vector<char>> matrix;   // the letters, indexed matrix[row][col]
public:
    grid();                                    // default constructor
    void readGrid(const string& filename);     // load dimensions + letters from file
    int getRows() const { return rows; }       // inline getter for row count
    int getCols() const { return cols; }       // inline getter for column count
    char getChar(int r, int c) const;          // fetch the letter at (r, c)
    void printGrid() const;                    // debug helper: dump grid to console
};

//===========================================
// dictionary class  (parts 1a-1d)
// Reads the word list, stores it in a vector, sorts it with selection sort,
// and supports fast lookups with binary search.
//===========================================
class dictionary {
private:
    vector<string> words;   // the stored word list
public:
    void readDict(const string& filename);            // (1a) load words from file
    void selectionSort();                             // (1c) sort words ascending
    int binarySearch(const string& target) const;    // (1d) find a word, return its index
    // (1b) output operator, declared friend so it can read the private 'words'.
    friend ostream& operator<<(ostream& outputstring, const dictionary& d);
};

// (1b) Overloaded output operator, declared here so callers in other files can
// use it. Global (non-member) so the stream is the left operand (cout << dict).
ostream& operator<<(ostream& outputstring, const dictionary& d);

//===========================================
// Global functions
//===========================================

// (part 3) Scan the grid from every start cell in all 8 directions, build
// candidate words, and write any found in the dictionary to outputFile.
void findMatches(const dictionary& dict, const grid& g, const string& outputFile);

// (part 4) Top-level driver: read the grid filename from the keyboard, load
// both input files, sort the dictionary, and run findMatches().
void search();

#endif // WORDSEARCH_H

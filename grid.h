//
//  grid.h
//  wordsearch
//
//
//Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

#ifndef GRID_H
#define GRID_H

#include <string>     // std::string and getline
#include <vector>     // std::vector
    

//===========================================
// grid class  (part 2)
// Loads an n x n block of letters from a file and stores it as a 2D matrix,
// exposing read-only access to individual cells and the dimensions.
//===========================================

class grid
{
private:
    int rows;                      // number of rows (n)
    int cols;                      // number of columns (n)
    std::vector<std::vector<char>> matrix;   // the letters, indexed matrix[row][col]
public:
    grid();                                    // default constructor
    void readGrid(const std::string& filename);     // load dimensions + letters from file
    int getRows() const { return rows; }       // inline getter for row count
    int getCols() const { return cols; }       // inline getter for column count
    char getChar(int r, int c) const;          // fetch the letter at (r, c)
    void printGrid() const;                    // debug helper: dump grid to console
};

#endif

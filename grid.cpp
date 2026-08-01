//
//  grid.cpp
//  wordsearch
//
//
//Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

#include "grid.h"

#include <fstream>    // ifstream / ofstream for reading and writing files
#include <iostream>   // communicates with the user if there is an error opening the file
#include <string>     // std::string and getline
#include <vector>     // std::vector

using namespace std;

//===========================================
// grid class implementation  (part 2)
//===========================================

// Default constructor: start empty (0x0) until readGrid populates the object.
// Uses an initializer list to set rows and cols before the body runs.
grid::grid() : rows(0), cols(0)
{
}

// Reads the grid file. Expected format: first two numbers are rows and cols,
// followed by rows*cols letters (whitespace-separated, as in the sample file).
void grid::readGrid(const string& filename)
{
    ifstream file(filename);           // open the file for reading
    if (!file.is_open())
    {             // guard: file missing or unreadable
        cerr << "Error: Could not open grid file " << filename << endl;
        return;                        // leave the object empty and bail out
    }
    file >> rows >> cols;                          // read the two dimension values
    matrix.resize(rows, vector<char>(cols));       // size the matrix to rows x cols
    // Fill the matrix cell by cell. operator>> skips whitespace automatically,
    // so it reads one letter per extraction regardless of spacing/newlines.
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            file >> matrix[i][j];
    file.close();                       // release the file handle
}

// Return the letter stored at row r, column c.
// const because looking up a cell doesn't modify the grid.
char grid::getChar(int r, int c) const
{
    return matrix[r][c];
}

// Print the grid to the console, space-separated, one row per line.
// Purely a debugging aid; not part of the search pipeline.
void grid::printGrid() const
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
}


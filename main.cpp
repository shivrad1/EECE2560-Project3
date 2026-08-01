//
//  main.cpp
//  wordsearch
//
// Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

#include <fstream>
#include <iostream>
#include <string>

//include dictionary and grid headers
#include "dictionary.h"
#include "grid.h"


using namespace std;

// Row and column offsets for the eight search directions.
const int dr[8] = {-1, -1, 0, 1, 1,  1,  0, -1};
const int dc[8] = { 0,  1, 1, 1, 0, -1, -1, -1};


//===========================================
// Global Functions
//==========================================

//===========================================
// findMatches  (part 3)
//===========================================
void findMatches(const dictionary& dict, const grid& g, const string& outputFile)
{
    ofstream out(outputFile);          // open the output file for writing
    if (!out.is_open())
    {              // guard: couldn't create/open output
        cerr << "Error opening output file: " << outputFile << endl;
        return;
    }
    int rows = g.getRows();            // cache dimensions to avoid repeat calls
    int cols = g.getCols();

    // Try every cell in the grid as a starting point.
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            // From each start cell, try all 8 directions.
            for (int dir = 0; dir < 8; ++dir)
            {
                string currentWord = "";   // candidate word built up as we walk
                int r = i;                 // current row  (starts at the origin cell)
                int c = j;                 // current col

                // Walk in this direction, extending the candidate one letter at a
                // time. Cap the length at 'rows' (= n): on a toroidal grid a straight
                // walk of n steps returns to its start, so this cap also guarantees
                // a word never re-reads its own starting cell.
                for (int len = 1; len <= rows; ++len)
                {
                    currentWord += g.getChar(r, c);   // append the current cell's letter

                    // Only bother searching once the candidate is long enough (>= 5).
                    if (len >= 5)
                    {
                        int index = dict.binarySearch(currentWord);
                        if (index != -1)
                        {            // found in the dictionary
                            // Output format: word (startRow,startCol) foundIndex
                            out << currentWord << " (" << i << "," << j << ") " << index << "\n";
                        }
                    }

                    // Step to the next cell in this direction, wrapping around the
                    // edges. Adding rows/cols before the % keeps the result
                    // non-negative: e.g. -1 becomes rows-1, and rows becomes 0.
                    r = (r + dr[dir] + rows) % rows;
                    c = (c + dc[dir] + cols) % cols;
                }
            }
        }
    }
    out.close();                        // flush and close the output file
}

//===========================================
// search  (part 4)
//===========================================
void search(int selection)
{
    // (1) Read the grid filename from the keyboard.
    // The dictionary filename is fixed as "dictionary.txt".
    string gridFile;
    cout << "Enter grid file name: ";
    cin >> gridFile;
    
    grid g;             // grid object to hold the puzzle
    dictionary d;       // dictionary object to hold the word list
    
    // (2) Load both input files.
    g.readGrid(gridFile);
    d.readDict("dictionary.txt");
    
    // (3) Sort the dictionary so binarySearch will work in findMatches.
    // This MUST happen before any lookups.
    switch (selection)
    {
        case 1:
            d.selectionSort();
            break;
        case 2:
            d.heapSort();
            break;
        case 3:
            d.quickSort();
            break;
        default:
            cout << "Defaulting to selection sort." << endl;
            d.selectionSort();
    }
    
    // (4) Scan the grid and write all found words to "output.txt".
    findMatches(d, g, "output.txt");
}


int main()
{
    int selection;
    cout << "Choose sorting method (1 for selection sort (default), 2 for heap sort, 3 for quick sort): ";
    cin >> selection;
    search(selection);   // read input, sort dictionary, scan grid, write output.txt
    return 0;
}

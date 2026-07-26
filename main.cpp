#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//#include "grid.h"
//#include "dictionary.h"

using namespace std;

// Direction offsets for 8 directions (N, NE, E, SE, S, SW, W, NW)
const int dr[] = {-1, -1, 0, 1, 1,  1,  0, -1};
const int dc[] = { 0,  1, 1, 1, 0, -1, -1, -1};


void findMatches(const dictionary& dict, const grid& g, const string& outputFile) {
    ofstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Error opening output file: " << outputFile << endl;
        return;
    }

    int rows = g.getRows();
    int cols = g.getCols();

    // Iterate over every starting position in the grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            // Explore all 8 directions
            for (int dir = 0; dir < 8; ++dir) {
                string currentWord = "";
                int r = i;
                int c = j;

                // Build candidate strings up to grid dimension length
                for (int len = 1; len <= rows; ++len) {
                    currentWord += g.getChar(r, c);

                    if (len >= 5) {
                        int index = dict.binarySearch(currentWord);
                        if (index != -1) {
                            out << currentWord << " (" << i << "," << j << ") " << index << "\n";
                        }
                    }

                    // Advance with edge wraparound logic
                    r = (r + dr[dir] % rows + rows) % rows;
                    c = (c + dc[dir] % cols + cols) % cols;
                }
            }
        }
    }

    out.close();
}
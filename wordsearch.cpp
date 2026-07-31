// File: wordsearch.cpp
// Implementations for the Word Search project.
// Class and function declarations are in wordsearch.h.
// Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.


#include "wordsearch.h"

#include <fstream>    // ifstream / ofstream for reading and writing files
#include <string>     // std::string and getline
#include <vector>     // std::vector

using namespace std;

// Definition of the direction offset arrays declared 'extern' in the header.
// Defined here exactly once so there is a single shared copy across the program.
const int dr[8] = {-1, -1, 0, 1, 1,  1,  0, -1};
const int dc[8] = { 0,  1, 1, 1, 0, -1, -1, -1};

//===========================================
// grid class implementation  (part 2)
//===========================================

// Default constructor: start empty (0x0) until readGrid populates the object.
// Uses an initializer list to set rows and cols before the body runs.
grid::grid() : rows(0), cols(0) {}

// Reads the grid file. Expected format: first two numbers are rows and cols,
// followed by rows*cols letters (whitespace-separated, as in the sample file).
void grid::readGrid(const string& filename) {
    ifstream file(filename);           // open the file for reading
    if (!file.is_open()) {             // guard: file missing or unreadable
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
char grid::getChar(int r, int c) const {
    return matrix[r][c];
}

// Print the grid to the console, space-separated, one row per line.
// Purely a debugging aid; not part of the search pipeline.
void grid::printGrid() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
}

//===========================================
// dictionary class implementation  (parts 1a-1d)
//===========================================

// (1a) Read words from the dictionary file, one word per line.
// Filters out anything shorter than 5 characters, since the puzzle only cares
// about words of length >= 5.
void dictionary::readDict(const string& filename) {
    ifstream dict(filename);       // open the dictionary file
    string word;                   // scratch variable for each line read
    if (!dict) {                   // guard: couldn't open the file
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    // getline pulls one whole line (one word) at a time until end of file.
    while (getline(dict, word)) {
        // Strip a trailing carriage return if the file has Windows line endings.
        // getline removes '\n' but leaves '\r', which would corrupt comparisons.
        if (!word.empty() && word.back() == '\r') {
            word.pop_back();
        }
        // Only keep words that meet the 5-character minimum.
        if (word.length() >= 5) {
            words.push_back(word);
        }
    }
}

// (1c) Selection sort: sorts 'words' into ascending (alphabetical) order.
// Required for binarySearch to work, since binary search assumes sorted data.
// Selection sort repeatedly finds the smallest remaining element and swaps it
// into the next position.
void dictionary::selectionSort() {
    int min;                        // index of the smallest word found so far
    // Guard against an empty list: words.size()-1 is unsigned, so on an empty
    // vector it would wrap to a huge number and the loop would run out of bounds.
    if (words.empty()) {
        return;
    }
    // Outer loop: position being filled with the next-smallest word.
    for (int i = 0; i < words.size() - 1; i++) {
        min = i;                    // assume the current position holds the smallest
        // Inner loop: scan the unsorted remainder for anything smaller.
        for (int j = i + 1; j < words.size(); j++) {
            if (words[j] < words[min]) {   // string < compares lexicographically
                min = j;                    // found a smaller word; remember it
            }
        }
        swap(words[i], words[min]);  // put the smallest found into position i
    }
}

// Rearranges the array around a pivot element. All words smaller than or equal 
// to the pivot are placed to its left; larger words are placed to its right.
int dictionary::partition(int low, int high) {
    string pivot = words[high]; // Select the last element in the range as pivot
    int i = low - 1;            // Index marking the edge of smaller elements

    for (int j = low; j < high; ++j) {
        // If current word is alphabetically smaller than or equal to pivot
        if (words[j] <= pivot) {
            ++i;
            swap(words[i], words[j]);
        }
    }
    // Place pivot in its correct sorted position
    swap(words[i + 1], words[high]);
    return (i + 1); // Return pivot index
}

// Recursive helper for QuickSort
void dictionary::quickSortHelper(int low, int high) {
    if (low < high) {
        // pi is partitioning index; words[pi] is now in its correct place
        int pi = partition(low, high);

        // Recursively sort elements before and after partition
        quickSortHelper(low, pi - 1);
        quickSortHelper(pi + 1, high);
    }
}

// QuickSort: sorts 'words' vector into ascending order.
void dictionary::quickSort() {
    if (!words.empty()) {
        quickSortHelper(0, words.size() - 1);
    }
}

// (1d) Binary search over the sorted 'words' vector.
// Returns the index of 'target' if present, or -1 if not found.
// Repeatedly halves the search range by comparing against the middle element.
int dictionary::binarySearch(const string& target) const {
    int first = 0;                     // low end of the current search range
    int last = words.size() - 1;       // high end of the current search range
    while (first <= last) {            // continue while the range is non-empty
        int mid = (first + last) / 2;  // middle index of the current range
        string midValue = words[mid];  // the word at the middle
        if (target == midValue) {
            return mid;                // exact match: return its index
        }
        else if (target < midValue) {
            last = mid - 1;            // target is earlier: discard the right half
        }
        else {
            first = mid + 1;           // target is later: discard the left half
        }
    }
    return -1;                         // range exhausted without a match
}

// (1b) Overloaded output operator: prints every stored word on its own line.
// Global (non-member) so the stream can be the left operand (cout << dict).
// Declared friend in the header so it can access the private 'words' vector.
// Returns the stream by reference to allow chaining (cout << a << b).
ostream& operator<<(ostream& outputstring, const dictionary& d) {
    for (const auto& word : d.words) {   // range-based loop over each word
        outputstring << word << "\n";
    }
    return outputstring;
}

//===========================================
// findMatches  (part 3)
//===========================================
void findMatches(const dictionary& dict, const grid& g, const string& outputFile) {
    ofstream out(outputFile);          // open the output file for writing
    if (!out.is_open()) {              // guard: couldn't create/open output
        cerr << "Error opening output file: " << outputFile << endl;
        return;
    }
    int rows = g.getRows();            // cache dimensions to avoid repeat calls
    int cols = g.getCols();

    // Try every cell in the grid as a starting point.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // From each start cell, try all 8 directions.
            for (int dir = 0; dir < 8; ++dir) {
                string currentWord = "";   // candidate word built up as we walk
                int r = i;                 // current row  (starts at the origin cell)
                int c = j;                 // current col

                // Walk in this direction, extending the candidate one letter at a
                // time. Cap the length at 'rows' (= n): on a toroidal grid a straight
                // walk of n steps returns to its start, so this cap also guarantees
                // a word never re-reads its own starting cell.
                for (int len = 1; len <= rows; ++len) {
                    currentWord += g.getChar(r, c);   // append the current cell's letter

                    // Only bother searching once the candidate is long enough (>= 5).
                    if (len >= 5) {
                        int index = dict.binarySearch(currentWord);
                        if (index != -1) {            // found in the dictionary
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
void search() {
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
    d.selectionSort();

    // (4) Scan the grid and write all found words to "output.txt".
    findMatches(d, g, "output.txt");
}

int main() {
    search();   // read input, sort dictionary, scan grid, write output.txt
    return 0;
}
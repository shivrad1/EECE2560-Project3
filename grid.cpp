#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class grid {
private:
    int rows;
    int cols;
    vector<vector<char>> matrix;

public:
    grid();
    void readGrid(const string& filename);
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    char getChar(int r, int c) const;
    void printGrid() const;
};


grid::grid() : rows(0), cols(0) {}

// Reads grid dimensions and matrix characters from a file
void grid::readGrid(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open grid file " << filename << endl;
        return;
    }

    // reads first 2 lines to get row and col
    file >> rows >> cols;

    matrix.resize(rows, vector<char>(cols));//resize matrix to gridsize


    //inputs nums from grid into matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> matrix[i][j];
        }
    }

    file.close();
}

// Safely retrieve character from matrix
char grid::getChar(int r, int c) const {
    return matrix[r][c];
}

// Helper function to display the loaded grid
void grid::printGrid() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}
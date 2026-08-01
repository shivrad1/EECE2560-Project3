# Word Search
EECE2560  
Project Word Search

Solves a word search puzzle. The program reads an *n* x *n* grid of letters and a
dictionary of words, then finds every dictionary word that appears in the grid.
Words may run in any of the 8 directions (left, right, up, down, and the four
diagonals), may wrap around the edges of the grid, and must be at least 5
characters long. All matches are written to an output file.

## Files

- `dictionary.h` / `dictionary.cpp` — stores the dictionary words, reads the
  dictionary file, sorts the words using selection sort, heap sort, or quick
  sort, and performs binary search.
- `grid.h` / `grid.cpp` — stores the letter grid and provides access to the
  characters in the puzzle.
- `heap.h` / `heap.cpp` — implements a max heap and performs heap sort.
- `main.cpp` — contains the global functions `findMatches()` and `search()`,
  along with `main()`.

## Build

```bash
g++ -std=c++11 main.cpp dictionary.cpp grid.cpp heap.cpp -o wordsearch
```

## Run

```bash
./wordsearch
```

The program prompts for the grid filename at the keyboard. The dictionary
filename is fixed as `dictionary.txt`, and results are written to
`output.txt`. Both `dictionary.txt` and the grid file must be in the
working directory.

## Input formats

**Grid file** — the first two numbers are the row and column counts, followed by
that many letters (whitespace-separated).

**Dictionary file** — one word per line. Words shorter than five characters are
ignored when the dictionary is loaded.

## Output format

One line per match: the word, its starting cell `(row,col)`, and the index at
which it was found in the sorted dictionary.

```
north (0,2) 1200
```

## How it works

1. `dictionary::readDict()` reads the dictionary file and stores only words
   that are at least five characters long.
2. The dictionary is sorted using the algorithm selected by the user:
   selection sort, heap sort, or quick sort.
3. `findMatches()` starts from every cell in the grid and searches in all
   eight directions. Candidate words of length five or greater are looked up
   using binary search.
4. Every matching word is written to `output.txt` with its starting position
   and dictionary index.

## Classes and key functions

**`dictionary`**
- `readDict(filename)` — load and filter the dictionary (Part 1a)
- `operator<<` — print the dictionary (Part 1b)
- `selectionSort()` — selection sort (Part 1c)
- `binarySearch(target)` — binary search (Part 1d)
- `quickSort()` — quick sort (Part B)
- `heapSort()` — heap sort using the `heap` class (Part B)

**`heap`**
- `initializeMaxHeap()` — copy the dictionary into a heap
- `buildMaxHeap()` — build a max heap
- `maxHeapify()` — restore the heap property
- `heapSort()` — sort the words using heap sort

**`grid`**
- `readGrid(filename)` — load the letter grid (Part 2)
- `getRows()` / `getCols()` — return the grid dimensions
- `getChar(r, c)` — return the character at a given position
- `printGrid()` — print the grid for testing

**Global functions**
- `findMatches(dict, grid, outputFile)` — search the grid for words (Part 3)
- `search()` — load the files, sort the dictionary, and search the grid
  (Part 4)

## Part B

Part B extends the original project by adding two additional sorting
algorithms: quick sort and heap sort. The user can now choose which sorting
algorithm to use before the dictionary is searched.

Testing showed that quick sort and heap sort performed very similarly. Both
completed the sorting process much faster than selection sort. Selection sort
took significantly longer to complete because it repeatedly searches the
remaining unsorted portion of the dictionary for the next smallest element.

## Notes

- The grid is assumed to be square (*n* × *n*), matching the assignment
  specification.
- Words shorter than five characters are ignored when the dictionary is read.
- The dictionary must be sorted before binary search can be used.

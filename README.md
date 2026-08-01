# Word Search

EECE 2560 — Project Word Search
Code by Hayden Trent, Alex Viatchenko-Karpinski, Shiv Radhakrishnan.

Solves a word search puzzle. The program reads an *n* x *n* grid of letters and a
dictionary of words, then finds every dictionary word that appears in the grid.
Words may run in any of the 8 directions (left, right, up, down, and the four
diagonals), may wrap around the edges of the grid, and must be at least 5
characters long. All matches are written to an output file.

## Files

- `dictionary.h` / `dictionary.cpp` — the `dictionary` class: loads the word
  list and provides selection sort, quicksort, heapsort (via the heap class),
  binary search, and the output operator.
- `grid.h` / `grid.cpp` — the `grid` class: loads and stores the letter matrix.
- `heap.h` / `heap.cpp` — the `heap` class: a max-heap used by the dictionary's
  heapsort.
- `main.cpp` — the direction-offset arrays, the global `findMatches()` and
  `search()` functions, and `main()`.

## Build

    g++ -std=c++11 main.cpp dictionary.cpp grid.cpp heap.cpp -o wordsearch

## Run

    ./wordsearch

The program first asks which sorting method to use (1 = selection sort,
2 = heap sort, 3 = quick sort), then prompts for the grid filename. The
dictionary filename is fixed as `dictionary.txt`, and results are written to
`output.txt`. Both `dictionary.txt` and the grid file must be in the working
directory.

## Input formats

**Grid file** — the first two numbers are the row and column counts, followed by
that many letters (whitespace-separated):

    15 15
    n y d m k u a s l m o q y r c
    ...

**Dictionary file** — one word per line. Words shorter than 5 characters are
ignored when the list is loaded.

## Output format

One line per match: the word, its starting cell `(row,col)`, and the index at
which it was found in the sorted dictionary.

    north (0,2) 1200

## How it works

1. `dictionary::readDict` loads the word list, strips trailing carriage returns
   (in case of Windows line endings), and keeps only words of length >= 5.
2. The chosen sort (`selectionSort`, `quickSort`, or `heapSort`) orders the words
   alphabetically. This must run before any lookups, because binary search
   requires sorted data.
3. `findMatches` starts from every cell, walks all 8 directions, and builds a
   candidate string one letter at a time. Each candidate of length >= 5 is looked
   up with `dictionary::binarySearch`; matches are written to the output file.
   Walks wrap around the grid edges and are capped at length *n*, which also
   prevents a straight walk from re-reading its own starting cell.
4. `search` ties these steps together: read the sort choice and grid filename,
   load both files, sort the dictionary, and run `findMatches`.

## Classes and key functions

**`dictionary`** (parts 1a-1d, part b)
- `readDict(filename)` — load and filter the word list
- `operator<<` — print the word list
- `selectionSort()` — selection sort
- `quickSort()` — quicksort (part b)
- `heapSort()` — heapsort via the heap class (part b)
- `binarySearch(target)` — look up a word, returns its index or -1

**`grid`** (part 2)
- `readGrid(filename)` — load the letter matrix
- `getRows()` / `getCols()` — dimensions
- `getChar(r, c)` — the letter at a cell
- `printGrid()` — debug helper

**`heap`** (part b)
- `initializeMaxHeap(words)` — copy words in and build a max-heap
- `heapSort()` — return the words sorted ascending

**Global functions** (in main.cpp)
- `findMatches(dict, grid, outputFile)` — scan and report matches (part 3)
- `search(selection)` — top-level driver (part 4)

## Notes

- The grid is assumed square (*n* x *n*), matching the assignment input. Candidate
  words are capped at *n* characters.
- Selection sort is O(n²); heapsort is O(n log n); quicksort is O(n log n)
  average, O(n²) worst case. Heapsort copies the word list into a heap object,
  sorts, and copies it back, as the assignment specifies.
- Compiling with `-Wall` produces signed/unsigned comparison warnings in
  `selectionSort`; they are harmless (an explicit empty-list guard covers the one
  edge case) and can be silenced with `size_t` loop counters.


## Part 5 Comment, which algorithm is fastest?
-Quick sort was the fastest, clocking in at 36 ms
-Heap sort was slightly slower-- though not perceivably so at 64 ms
-Selection sort was by far the slowest at around 46.7 seconds, this was slow enough that it was thought originally it may have been bugged.
-Both Quick and Heap sort are both O(n*log(n)) whereas selection sort is O(n^2), which is much slower at the scale of this dictionary.

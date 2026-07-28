# Word Search
EECE2560
Project Word Search

Solves a word search puzzle. The program reads an *n* x *n* grid of letters and a
dictionary of words, then finds every dictionary word that appears in the grid.
Words may run in any of the 8 directions (left, right, up, down, and the four
diagonals), may wrap around the edges of the grid, and must be at least 5
characters long. All matches are written to an output file.

## Files

- `wordsearch.h` — declarations: the `grid` and `dictionary` classes, the
  direction-offset arrays (`dr` / `dc`), and prototypes for the global
  `findMatches()` and `search()` functions.
- `wordsearch.cpp` — implementations of everything declared in the header,
  plus `main()`.

## Build


g++ -std=c++11 wordsearch.cpp -o wordsearch


## Run


./wordsearch


The program prompts for the grid filename at the keyboard. The dictionary
filename is fixed as `dictionary.txt`, and results are written to `output.txt`.
Both `dictionary.txt` and the grid file must be in the working directory.

## Input formats

**Grid file** — the first two numbers are the row and column counts, followed by
that many letters (whitespace-separated):

**Dictionary file** — one word per line. Words shorter than 5 characters are
ignored when the list is loaded.

## Output format

One line per match: the word, its starting cell `(row,col)`, and the index at
which it was found in the sorted dictionary.


north (0,2) 1200


## How it works

1. `dictionary::readDict` loads the word list, strips trailing carriage returns
   (in case of Windows line endings), and keeps only words of length >= 5.
2. `dictionary::selectionSort` sorts the words alphabetically. This must run
   before any lookups, because binary search requires sorted data.
3. `findMatches` starts from every cell, walks all 8 directions, and builds a
   candidate string one letter at a time. Each candidate of length >= 5 is looked
   up with `dictionary::binarySearch`; matches are written to the output file.
   Walks wrap around the grid edges and are capped at length *n*, which also
   prevents a straight walk from re-reading its own starting cell.
4. `search` ties these steps together: read the grid filename, load both files,
   sort the dictionary, and run `findMatches`.

## Classes and key functions

**`dictionary`**
- `readDict(filename)` — load and filter the word list (part 1a)
- `operator<<` — print the word list (part 1b)
- `selectionSort()` — sort the words (part 1c)
- `binarySearch(target)` — look up a word, returns its index or -1 (part 1d)

**`grid`**
- `readGrid(filename)` — load the letter matrix (part 2)
- `getRows()` / `getCols()` — dimensions
- `getChar(r, c)` — the letter at a cell
- `printGrid()` — debug helper

**Global functions**
- `findMatches(dict, grid, outputFile)` — scan and report matches (part 3)
- `search()` — top-level driver (part 4)

## Notes

- The grid is assumed square (*n* x *n*), matching the assignment input. Candidate
  words are capped at *n* characters.
- Compiling with `-Wall` produces two signed/unsigned comparison warnings in
  `selectionSort`; they are harmless (an explicit empty-list guard covers the one
  edge case they concern) and can be silenced by using `size_t` loop counters.
